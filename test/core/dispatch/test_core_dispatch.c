#include "openssl_provider_sdk/ops_algorithm.h"
#include "openssl_provider_sdk/ops_bio.h"
#include "openssl_provider_sdk/ops_core.h"
#include "openssl_provider_sdk/ops_crt.h"
#include "openssl_provider_sdk/ops_provider.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

OSSL_provider_init_fn OSSL_provider_init;

#define CHECK(condition) \
    do \
    { \
        if (!(condition)) \
        { \
            fprintf(stderr, "Check failed at line %d: %s\n", __LINE__, #condition); \
            return 1; \
        } \
    } while (0)

static int handle_a;
static int handle_b;
static int bio_a;
static int bio_b;
static int allocations_a;
static int allocations_b;
static int frees_a;
static int frees_b;
static int cleanses;

static void *malloc_a(size_t size, const char *file, int line)
{
    (void)file;
    (void)line;
    ++allocations_a;
    return malloc(size);
}

static void *malloc_b(size_t size, const char *file, int line)
{
    (void)file;
    (void)line;
    ++allocations_b;
    return malloc(size);
}

static void *malloc_fail(size_t size, const char *file, int line)
{
    (void)size;
    (void)file;
    (void)line;
    return NULL;
}

static void free_a(void *ptr, const char *file, int line)
{
    (void)file;
    (void)line;
    ++frees_a;
    free(ptr);
}

static void free_b(void *ptr, const char *file, int line)
{
    (void)file;
    (void)line;
    ++frees_b;
    free(ptr);
}

static void cleanse(void *ptr, size_t size)
{
    ++cleanses;
    memset(ptr, 0, size);
}

static OSSL_CORE_BIO *new_bio_a(const void *buf, int len)
{
    (void)buf;
    (void)len;
    return (OSSL_CORE_BIO *)&bio_a;
}

static OSSL_CORE_BIO *new_bio_b(const void *buf, int len)
{
    (void)buf;
    (void)len;
    return (OSSL_CORE_BIO *)&bio_b;
}

static int get_params_a(const OSSL_CORE_HANDLE *handle, OSSL_PARAM params[])
{
    (void)params;
    return handle == (const OSSL_CORE_HANDLE *)&handle_a;
}

static int get_params_b(const OSSL_CORE_HANDLE *handle, OSSL_PARAM params[])
{
    (void)params;
    return handle == (const OSSL_CORE_HANDLE *)&handle_b;
}

static void destroy(const OSSL_DISPATCH *out, void *ctx)
{
    for (; out->function_id != 0; ++out)
    {
        if (out->function_id == OSSL_FUNC_PROVIDER_TEARDOWN)
        {
            OSSL_FUNC_provider_teardown(out)(ctx);
            return;
        }
    }
}

int main(void)
{
    const OSSL_DISPATCH in_a[] = {
        OPS_FUNCTION(OSSL_FUNC_CRYPTO_MALLOC, malloc_a),
        OPS_FUNCTION(OSSL_FUNC_CRYPTO_FREE, free_a),
        OPS_FUNCTION(OSSL_FUNC_OPENSSL_CLEANSE, cleanse),
        OPS_FUNCTION(OSSL_FUNC_BIO_NEW_MEMBUF, new_bio_a),
        OPS_FUNCTION(OSSL_FUNC_CORE_GET_PARAMS, get_params_a),
        { 999, NULL }, /* Unknown core services do not prevent initialization. */
        { 0, NULL }
    };

    const OSSL_DISPATCH in_b[] = {
        OPS_FUNCTION(OSSL_FUNC_CRYPTO_MALLOC, malloc_b),
        OPS_FUNCTION(OSSL_FUNC_CRYPTO_FREE, free_b),
        OPS_FUNCTION(OSSL_FUNC_BIO_NEW_MEMBUF, new_bio_b),
        OPS_FUNCTION(OSSL_FUNC_CORE_GET_PARAMS, get_params_b),
        { 0, NULL }
    };

    const OSSL_DISPATCH missing_free[] = {
        OPS_FUNCTION(OSSL_FUNC_CRYPTO_MALLOC, malloc_a), { 0, NULL }
    };

    const OSSL_DISPATCH failed_allocation[] = {
        OPS_FUNCTION(OSSL_FUNC_CRYPTO_MALLOC, malloc_fail),
        OPS_FUNCTION(OSSL_FUNC_CRYPTO_FREE, free_a), { 0, NULL }
    };

    const OSSL_DISPATCH *out_a = NULL;
    const OSSL_DISPATCH *out_b = NULL;
    const OSSL_DISPATCH *out_failed;
    void *ctx_a = NULL;
    void *ctx_b = NULL;
    void *ctx_failed;
    unsigned char *a;
    void *b;

    CHECK(OSSL_provider_init((const OSSL_CORE_HANDLE *)&handle_a,
        in_a, &out_a, &ctx_a) == 1);
    CHECK(OSSL_provider_init((const OSSL_CORE_HANDLE *)&handle_b,
        in_b, &out_b, &ctx_b) == 1);
    CHECK(ctx_a != NULL && ctx_b != NULL && ctx_a != ctx_b);
    CHECK(ops_provider_get_user_data(ctx_a) == NULL);
    CHECK(ops_provider_get_user_data(ctx_b) == NULL);
    CHECK(allocations_a == 1 && allocations_b == 1);
    CHECK(ops_core_get_params(ctx_a, NULL) == 1);
    CHECK(ops_core_get_params(ctx_b, NULL) == 1);
    CHECK(ops_core_has_function(ctx_a, OSSL_FUNC_OPENSSL_CLEANSE) == 1);
    CHECK(ops_core_has_function(ctx_b, OSSL_FUNC_OPENSSL_CLEANSE) == 0);
    CHECK(ops_core_has_function(ctx_a, 999) == 0);
    CHECK(ops_core_has_function(NULL, OSSL_FUNC_CRYPTO_MALLOC) == 0);
    a = ops_malloc(ctx_a, 4);
    b = ops_malloc(ctx_b, 8);
    CHECK(a != NULL && b != NULL);
    CHECK(allocations_a == 2 && allocations_b == 2);
    memset(a, 0xff, 4);
    ops_cleanse(ctx_a, a, 4);
    CHECK(cleanses == 1 && a[0] == 0 && a[3] == 0);
    CHECK(ops_bio_new_membuf(ctx_a, "a", 1) == (OSSL_CORE_BIO *)&bio_a);
    CHECK(ops_bio_new_membuf(ctx_b, "b", 1) == (OSSL_CORE_BIO *)&bio_b);
    ops_free(ctx_a, a);
    ops_free(ctx_b, b);
    destroy(out_b, ctx_b);
    CHECK(frees_b == 2 && frees_a == 1);
    CHECK(ops_core_get_params(ctx_a, NULL) == 1);
    destroy(out_a, ctx_a);
    CHECK(frees_a == 2);

    out_failed = in_a;
    ctx_failed = &handle_a;
    CHECK(OSSL_provider_init((const OSSL_CORE_HANDLE *)&handle_a,
        missing_free, &out_failed, &ctx_failed) == 0);
    CHECK(out_failed == NULL && ctx_failed == NULL && allocations_a == 2);
    CHECK(OSSL_provider_init((const OSSL_CORE_HANDLE *)&handle_a,
        failed_allocation, &out_failed, &ctx_failed) == 0);
    CHECK(out_failed == NULL && ctx_failed == NULL);
    return 0;
}
