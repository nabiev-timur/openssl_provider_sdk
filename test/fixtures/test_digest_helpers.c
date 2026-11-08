#include "test_digest_helpers.h"
#include "openssl_provider_sdk/ops_crt.h"

#include <openssl/core_names.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/params.h>
#include "openssl_provider_sdk/ops_params.h"
#include <openssl/provider.h>

typedef struct ops_test_digest_ctx
{
    void *sdk;
    OSSL_LIB_CTX *libctx;
    OSSL_PROVIDER *provider;
    EVP_MD *digest;
    EVP_MD_CTX *md_ctx;
} ops_test_digest_ctx_t;

void *ops_test_digest_newctx(void *provctx)
{
    ops_test_digest_ctx_t *ctx = ops_malloc(provctx, sizeof *ctx);

    if (ctx == NULL)
    {
        return NULL;
    }

    *ctx = (ops_test_digest_ctx_t){0};
    ctx->sdk = provctx;
    /* Изолированный default provider исключает рекурсию и глобальные настройки. */
    ctx->libctx = OSSL_LIB_CTX_new();
    if (ctx->libctx == NULL)
    {
        goto error;
    }

    ctx->provider = OSSL_PROVIDER_load(ctx->libctx, "default");
    ctx->digest = EVP_MD_fetch(ctx->libctx, "SHA256", "provider=default");
    ctx->md_ctx = EVP_MD_CTX_new();
    if (ctx->provider == NULL || ctx->digest == NULL || ctx->md_ctx == NULL)
    {
        goto error;
    }

    return ctx;

error:
    ops_test_digest_freectx(ctx);
    return NULL;
}

void ops_test_digest_freectx(void *dctx)
{
    ops_test_digest_ctx_t *ctx = dctx;

    if (ctx != NULL)
    {
        EVP_MD_CTX_free(ctx->md_ctx);
        EVP_MD_free(ctx->digest);
        if (ctx->provider != NULL)
        {
            OSSL_PROVIDER_unload(ctx->provider);
        }

        OSSL_LIB_CTX_free(ctx->libctx);
        ops_free(ctx->sdk, ctx);
    }
}

int ops_test_digest_init(void *dctx, const OSSL_PARAM params[])
{
    ops_test_digest_ctx_t *ctx = dctx;

    (void)params;
    return EVP_DigestInit_ex2(ctx->md_ctx, ctx->digest, NULL);
}

int ops_test_digest_update(void *dctx, const unsigned char *in, size_t inl)
{
    ops_test_digest_ctx_t *ctx = dctx;

    return EVP_DigestUpdate(ctx->md_ctx, in, inl);
}

int ops_test_digest_final(
    void *dctx,
    unsigned char *out,
    size_t *outl,
    size_t outsz)
{
    ops_test_digest_ctx_t *ctx = dctx;
    unsigned int length = 0;

    if (outl == NULL)
    {
        return 0;
    }

    *outl = 0;
    if (out == NULL || outsz < 32
        || !EVP_DigestFinal_ex(ctx->md_ctx, out, &length))
    {
        return 0;
    }

    *outl = length;
    return 1;
}

int ops_test_digest_get_params(OSSL_PARAM params[])
{
    if (!ops_params_set_size_t(params, OSSL_DIGEST_PARAM_SIZE, 32)
        || !ops_params_set_size_t(params, OSSL_DIGEST_PARAM_BLOCK_SIZE, 64)
        || !ops_params_set_int(params, OSSL_DIGEST_PARAM_XOF, 0)
        || !ops_params_set_int(params, OSSL_DIGEST_PARAM_ALGID_ABSENT, 0))
    {
        return 0;
    }

    return 1;
}

const OSSL_PARAM *ops_test_digest_gettable_params(void *provctx)
{
    (void)provctx;
    static const OSSL_PARAM params[] = {
        OSSL_PARAM_size_t(OSSL_DIGEST_PARAM_SIZE, NULL),
        OSSL_PARAM_size_t(OSSL_DIGEST_PARAM_BLOCK_SIZE, NULL),
        OSSL_PARAM_int(OSSL_DIGEST_PARAM_XOF, NULL),
        OSSL_PARAM_int(OSSL_DIGEST_PARAM_ALGID_ABSENT, NULL),
        OSSL_PARAM_END
    };

    return params;
}
