#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/provider.h>

#include <stdio.h>
#include <string.h>

static int check_result(
    EVP_MD_CTX *ctx,
    const unsigned char expected[4],
    const char *scenario)
{
    unsigned char output[EVP_MAX_MD_SIZE];
    unsigned int output_size = 0;

    if (!EVP_DigestFinal_ex(ctx, output, &output_size)
        || output_size != 4 || memcmp(output, expected, 4) != 0)
    {
        fprintf(stderr, "%s: dummy sum32 result mismatch\n", scenario);
        return 0;
    }

    return 1;
}

static int check_vectors(EVP_MD *digest)
{
    static const unsigned char expected_abc[4] = { 0x00, 0x00, 0x01, 0x26 };
    static const unsigned char expected_empty[4] = { 0x00, 0x00, 0x00, 0x00 };
    static const unsigned char binary[3] = { 0x00, 0x80, 0xff };
    static const unsigned char expected_binary[4] = { 0x00, 0x00, 0x01, 0x7f };
    /* 4113 * 4096 * 255 modulo 2^32 = 978944 = 0x000ef000. */
    static const unsigned char expected_wrap[4] = { 0x00, 0x0e, 0xf0, 0x00 };
    unsigned char block[4096];
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    size_t i;
    int result = 0;

    if (ctx == NULL)
    {
        fprintf(stderr, "Could not allocate digest consumer context\n");
        return 0;
    }

    if (!EVP_DigestInit_ex2(ctx, digest, NULL)
        || !EVP_DigestUpdate(ctx, "a", 1)
        || !EVP_DigestUpdate(ctx, "bc", 2)
        || !check_result(ctx, expected_abc, "streamed abc"))
    {
        goto cleanup;
    }

    if (!EVP_DigestInit_ex2(ctx, digest, NULL)
        || !check_result(ctx, expected_empty, "empty input after reinit"))
    {
        goto cleanup;
    }

    if (!EVP_DigestInit_ex2(ctx, digest, NULL)
        || !EVP_DigestUpdate(ctx, binary, sizeof binary)
        || !check_result(ctx, expected_binary, "unsigned binary input"))
    {
        goto cleanup;
    }

    memset(block, 0xff, sizeof block);
    if (!EVP_DigestInit_ex2(ctx, digest, NULL))
    {
        goto cleanup;
    }

    for (i = 0; i < 4113; ++i)
    {
        if (!EVP_DigestUpdate(ctx, block, sizeof block))
        {
            goto cleanup;
        }
    }

    if (!check_result(ctx, expected_wrap, "modulo 2^32 wrap"))
    {
        goto cleanup;
    }

    result = 1;

cleanup:
    EVP_MD_CTX_free(ctx);
    return result;
}

int main(int argc, char **argv)
{
    OSSL_LIB_CTX *libctx = NULL;
    OSSL_PROVIDER *provider = NULL;
    EVP_MD *digest = NULL;
    int result = 1;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <absolute-provider-module-directory>\n", argv[0]);
        return 1;
    }

    libctx = OSSL_LIB_CTX_new();
    if (libctx == NULL || !OSSL_PROVIDER_set_default_search_path(libctx, argv[1]))
    {
        fprintf(stderr, "Could not initialize isolated provider search path\n");
        goto cleanup;
    }

    /* Единственный явно загружаемый provider; default/global fallback не нужен. */
    provider = OSSL_PROVIDER_load(libctx, "ops_example");
    if (provider == NULL)
    {
        fprintf(stderr, "Could not load ops_example provider\n");
        goto cleanup;
    }

    digest = EVP_MD_fetch(libctx, "OPS-DUMMY-HASH", "provider=ops-example");
    if (digest == NULL || EVP_MD_get0_provider(digest) != provider
        || EVP_MD_get_size(digest) != 4 || EVP_MD_get_block_size(digest) != 1)
    {
        fprintf(stderr, "Could not fetch four-byte dummy hash from ops_example\n");
        goto cleanup;
    }

    if (!check_vectors(digest))
    {
        goto cleanup;
    }

    result = 0;

cleanup:
    if (result != 0)
    {
        ERR_print_errors_fp(stderr);
    }

    EVP_MD_free(digest);
    if (provider != NULL)
    {
        OSSL_PROVIDER_unload(provider);
    }

    OSSL_LIB_CTX_free(libctx);
    return result;
}
