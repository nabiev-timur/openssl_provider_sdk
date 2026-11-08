#include <openssl/core.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/provider.h>

#include <stdio.h>
#include <string.h>

#if defined(__linux__)
/*
 * Имитируем другой SDK в host: модуль провайдера обязан использовать собственный
 * реестр, даже если host экспортирует одноимённый getter с пустым списком.
 * Ошибочная ELF interposition приведёт к отказу реальных EVP_MD_fetch ниже.
 */
__attribute__((visibility("default")))
const OSSL_ALGORITHM *ops_digest_algorithms(void);

const OSSL_ALGORITHM *ops_digest_algorithms(void)
{
    static const OSSL_ALGORITHM empty_algorithms[] = {
        { NULL, NULL, NULL, NULL }
    };

    return empty_algorithms;
}
#endif /* defined(__linux__) */

static int check_digest(OSSL_LIB_CTX *libctx, OSSL_PROVIDER *provider, const char *name)
{
    static const unsigned char expected_abc[] = {
        0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea,
        0x41, 0x41, 0x40, 0xde, 0x5d, 0xae, 0x22, 0x23,
        0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17, 0x7a, 0x9c,
        0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad
    };

    static const unsigned char expected_empty[] = {
        0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14,
        0x9a, 0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24,
        0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c,
        0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55
    };

    unsigned char output[EVP_MAX_MD_SIZE];
    unsigned int output_size = 0;
    EVP_MD *digest = NULL;
    EVP_MD_CTX *ctx = NULL;
    int result = 0;

    digest = EVP_MD_fetch(libctx, name, "provider=ops-test");
    if (digest == NULL || EVP_MD_get0_provider(digest) != provider
        || EVP_MD_get_size(digest) != 32 || EVP_MD_get_block_size(digest) != 64)
    {
        fprintf(stderr, "%s: could not fetch digest from test provider\n", name);
        goto cleanup;
    }

    ctx = EVP_MD_CTX_new();
    if (ctx == NULL
        || !EVP_DigestInit_ex2(ctx, digest, NULL)
        || !EVP_DigestUpdate(ctx, "a", 1)
        || !EVP_DigestUpdate(ctx, "bc", 2)
        || !EVP_DigestFinal_ex(ctx, output, &output_size)
        || output_size != sizeof expected_abc
        || memcmp(output, expected_abc, sizeof expected_abc) != 0)
    {
        fprintf(stderr, "%s: SHA256 abc known-answer mismatch\n", name);
        goto cleanup;
    }

    if (!EVP_DigestInit_ex2(ctx, digest, NULL)
        || !EVP_DigestFinal_ex(ctx, output, &output_size)
        || output_size != sizeof expected_empty
        || memcmp(output, expected_empty, sizeof expected_empty) != 0)
    {
        fprintf(stderr, "%s: SHA256 empty known-answer mismatch\n", name);
        goto cleanup;
    }

    result = 1;

cleanup:
    EVP_MD_CTX_free(ctx);
    EVP_MD_free(digest);
    return result;
}

int main(int argc, char **argv)
{
    OSSL_LIB_CTX *libctx = NULL;
    OSSL_PROVIDER *default_provider = NULL;
    OSSL_PROVIDER *test_provider = NULL;
    EVP_MD *unexpected = NULL;
    int result = 1;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <absolute-provider-module-directory>\n", argv[0]);
        return 1;
    }

    libctx = OSSL_LIB_CTX_new();
    if (libctx == NULL || !OSSL_PROVIDER_set_default_search_path(libctx, argv[1]))
    {
        fprintf(stderr, "Could not initialize provider search path\n");
        goto cleanup;
    }

    default_provider = OSSL_PROVIDER_load(libctx, "default");
    test_provider = OSSL_PROVIDER_load(libctx, "test_provider");
    if (default_provider == NULL || test_provider == NULL)
    {
        fprintf(stderr, "Required default/test provider could not be loaded\n");
        goto cleanup;
    }

    if (!check_digest(libctx, test_provider, "OPS-TEST-SHA256-A")
        || !check_digest(libctx, test_provider, "OPS-TEST-SHA256-B"))
    {
        goto cleanup;
    }

    unexpected = EVP_MD_fetch(libctx, "OPS-TEST-SHA256-MISSING", "provider=ops-test");
    if (unexpected != NULL)
    {
        fprintf(stderr, "Unexpected digest was advertised\n");
        goto cleanup;
    }

    ERR_clear_error();
    result = 0;

cleanup:
    if (result != 0)
    {
        ERR_print_errors_fp(stderr);
    }

    EVP_MD_free(unexpected);
    if (test_provider != NULL)
    {
        OSSL_PROVIDER_unload(test_provider);
    }

    if (default_provider != NULL)
    {
        OSSL_PROVIDER_unload(default_provider);
    }

    OSSL_LIB_CTX_free(libctx);
    return result;
}
