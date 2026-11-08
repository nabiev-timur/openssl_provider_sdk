#include "openssl_provider_sdk/ops_algorithm.h"
#include "openssl_provider_sdk/ops_crt.h"

#include <stddef.h>
#include <stdint.h>

#include <openssl/core_names.h>
#include <openssl/params.h>
#include "openssl_provider_sdk/ops_params.h"

/* Только демонстрация SDK: сумма байт не является криптографическим хешем. */
typedef struct ops_dummy_hash_ctx
{
    void *sdk;
    uint32_t sum;
} ops_dummy_hash_ctx_t;

static OSSL_FUNC_digest_newctx_fn ops_dummy_hash_newctx;
static OSSL_FUNC_digest_freectx_fn ops_dummy_hash_freectx;
static OSSL_FUNC_digest_init_fn ops_dummy_hash_init;
static OSSL_FUNC_digest_update_fn ops_dummy_hash_update;
static OSSL_FUNC_digest_final_fn ops_dummy_hash_final;
static OSSL_FUNC_digest_get_params_fn ops_dummy_hash_get_params;
static OSSL_FUNC_digest_gettable_params_fn ops_dummy_hash_gettable_params;

static void *ops_dummy_hash_newctx(void *provctx)
{
    ops_dummy_hash_ctx_t *ctx = ops_malloc(provctx, sizeof *ctx);

    if (ctx != NULL)
    {
        ctx->sdk = provctx;
        ctx->sum = 0;
    }

    return ctx;
}

static void ops_dummy_hash_freectx(void *dctx)
{
    ops_dummy_hash_ctx_t *ctx = dctx;

    if (ctx != NULL)
    {
        ops_free(ctx->sdk, ctx);
    }
}

static int ops_dummy_hash_init(void *dctx, const OSSL_PARAM params[])
{
    ops_dummy_hash_ctx_t *ctx = dctx;

    (void)params;
    if (ctx == NULL)
    {
        return 0;
    }

    ctx->sum = 0;
    return 1;
}

static int ops_dummy_hash_update(void *dctx, const unsigned char *in, size_t inl)
{
    ops_dummy_hash_ctx_t *ctx = dctx;
    size_t i;

    if (ctx == NULL || (in == NULL && inl != 0))
    {
        return 0;
    }

    for (i = 0; i < inl; ++i)
    {
        /* Преобразование в uint32_t определяет сумму по модулю 2^32. */
        ctx->sum = (uint32_t)(ctx->sum + (uint32_t)in[i]);
    }

    return 1;
}

static int ops_dummy_hash_final(
    void *dctx,
    unsigned char *out,
    size_t *outl,
    size_t outsz)
{
    const ops_dummy_hash_ctx_t *ctx = dctx;

    if (outl == NULL)
    {
        return 0;
    }

    *outl = 0;
    if (ctx == NULL || out == NULL || outsz < 4)
    {
        return 0;
    }

    out[0] = (unsigned char)(ctx->sum >> 24);
    out[1] = (unsigned char)(ctx->sum >> 16);
    out[2] = (unsigned char)(ctx->sum >> 8);
    out[3] = (unsigned char)ctx->sum;
    *outl = 4;
    return 1;
}

static int ops_dummy_hash_get_params(OSSL_PARAM params[])
{
    if (!ops_params_set_size_t(params, OSSL_DIGEST_PARAM_SIZE, 4)
        || !ops_params_set_size_t(params, OSSL_DIGEST_PARAM_BLOCK_SIZE, 1)
        || !ops_params_set_int(params, OSSL_DIGEST_PARAM_XOF, 0)
        || !ops_params_set_int(params, OSSL_DIGEST_PARAM_ALGID_ABSENT, 1))
    {
        return 0;
    }

    return 1;
}

static const OSSL_PARAM *ops_dummy_hash_gettable_params(void *provctx)
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

OPS_DECLARE_ALGORITHM_DISPATCH(ops_dummy_hash_dispatch,
    OPS_FUNCTION(OSSL_FUNC_DIGEST_NEWCTX, ops_dummy_hash_newctx),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_FREECTX, ops_dummy_hash_freectx),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_INIT, ops_dummy_hash_init),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_UPDATE, ops_dummy_hash_update),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_FINAL, ops_dummy_hash_final),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_GET_PARAMS, ops_dummy_hash_get_params),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_GETTABLE_PARAMS, ops_dummy_hash_gettable_params)
);

OPS_DECLARE_DIGEST(
    ops_dummy_hash_algorithm,
    "OPS-DUMMY-HASH",
    "provider=ops-example",
    ops_dummy_hash_dispatch,
    "Non-cryptographic demonstration: sum32 in big-endian order"
);
