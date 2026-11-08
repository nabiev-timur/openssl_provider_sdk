#include "openssl_provider_sdk/ops_bio.h"
#include "openssl_provider_sdk/ops_core.h"
#include "openssl_provider_sdk/ops_crt.h"

#include <openssl/provider.h>
#include <openssl/crypto.h>
#include <stdio.h>
#include <string.h>

#define CHECK(condition) \
    do \
    { \
        if (!(condition)) \
        { \
            fprintf(stderr, "Check failed at line %d: %s\n", __LINE__, #condition); \
            goto cleanup; \
        } \
    } while (0)

static int format(
    void *ctx,
    char *buf,
    size_t size,
    const char *fmt,
    ...)
{
    int result;
    va_list args;

    va_start(args, fmt);
    result = ops_bio_vsnprintf(ctx, buf, size, fmt, args);
    va_end(args);
    return result;
}

int main(int argc, char **argv)
{
    OSSL_LIB_CTX *libctx_a = NULL;
    OSSL_LIB_CTX *libctx_b = NULL;
    OSSL_PROVIDER *provider_a = NULL;
    OSSL_PROVIDER *provider_b = NULL;
    void *ctx_a;
    void *ctx_b = NULL;
    OSSL_CORE_BIO *bio = NULL;
    unsigned char *allocation = NULL;
    unsigned char *resized;
    char buffer[16] = {0};
    size_t bytes_read = 0;
    int result = 1;

    CHECK(argc == 2);
    libctx_a = OSSL_LIB_CTX_new();
    libctx_b = OSSL_LIB_CTX_new();
    CHECK(libctx_a != NULL && libctx_b != NULL);
    CHECK(OSSL_PROVIDER_set_default_search_path(libctx_a, argv[1]) == 1);
    CHECK(OSSL_PROVIDER_set_default_search_path(libctx_b, argv[1]) == 1);
    provider_a = OSSL_PROVIDER_load(libctx_a, "test_provider");
    provider_b = OSSL_PROVIDER_load(libctx_b, "test_provider");
    CHECK(provider_a != NULL && provider_b != NULL);
    ctx_a = OSSL_PROVIDER_get0_provider_ctx(provider_a);
    ctx_b = OSSL_PROVIDER_get0_provider_ctx(provider_b);
    CHECK(ctx_a != NULL && ctx_b != NULL && ctx_a != ctx_b);
    CHECK(ops_core_has_function(ctx_b, OSSL_FUNC_CRYPTO_ZALLOC));
    CHECK(ops_core_has_function(ctx_b, OSSL_FUNC_CRYPTO_REALLOC));
    CHECK(ops_core_has_function(ctx_b, OSSL_FUNC_OPENSSL_CLEANSE));
    CHECK(ops_core_has_function(ctx_b, OSSL_FUNC_BIO_NEW_MEMBUF));
    CHECK(ops_core_has_function(ctx_b, OSSL_FUNC_BIO_READ_EX));
    CHECK(ops_core_has_function(ctx_b, OSSL_FUNC_BIO_FREE));
    CHECK(ops_core_has_function(ctx_b, OSSL_FUNC_BIO_VSNPRINTF));
    allocation = ops_malloc(ctx_a, 4);
    CHECK(allocation != NULL);
    ops_free(ctx_a, allocation);
    allocation = NULL;
    CHECK(OSSL_PROVIDER_unload(provider_a) == 1);
    provider_a = NULL;
    OSSL_LIB_CTX_free(libctx_a);
    libctx_a = NULL;

    /* The second instance remains usable after teardown of the first. */
    allocation = ops_zalloc(ctx_b, 4);
    CHECK(allocation != NULL && allocation[0] == 0 && allocation[3] == 0);
    allocation[0] = 42;
    resized = ops_realloc(ctx_b, allocation, 8);
    CHECK(resized != NULL);
    allocation = resized;
    CHECK(allocation[0] == 42);
    ops_cleanse(ctx_b, allocation, 8);
    CHECK(allocation[0] == 0 && allocation[7] == 0);
    ops_free(ctx_b, allocation);
    allocation = NULL;
    bio = ops_bio_new_membuf(ctx_b, "abc", 3);
    CHECK(bio != NULL);
    CHECK(ops_bio_read_ex(ctx_b, bio, buffer, sizeof buffer, &bytes_read) == 1);
    CHECK(bytes_read == 3 && memcmp(buffer, "abc", 3) == 0);
    CHECK(ops_bio_free(ctx_b, bio) == 1);
    bio = NULL;
    CHECK(format(ctx_b, buffer, sizeof buffer, "%s:%d", "core", 7) == 6);
    CHECK(strcmp(buffer, "core:7") == 0);
    result = 0;

cleanup:
    if (bio != NULL)
    {
        ops_bio_free(ctx_b, bio);
    }

    if (allocation != NULL)
    {
        /* All failure paths retaining an allocation have a live owner. */
        ops_free(provider_a != NULL ?
            OSSL_PROVIDER_get0_provider_ctx(provider_a) : ctx_b, allocation);
    }

    OSSL_PROVIDER_unload(provider_a);
    OSSL_PROVIDER_unload(provider_b);
    OSSL_LIB_CTX_free(libctx_a);
    OSSL_LIB_CTX_free(libctx_b);
    return result;
}
