#include "openssl_provider_sdk/ops_algorithm.h"
#include "openssl_provider_sdk/ops_provider.h"
#include "ops_provider_ctx_internal.h"
#include "platform/ops_platform.h"

static OSSL_FUNC_provider_teardown_fn ops_provider_teardown;
static OSSL_FUNC_provider_query_operation_fn ops_provider_query_operation;
OSSL_provider_init_fn OSSL_provider_init;

static void ops_provider_teardown(void *provctx)
{
    ops_provider_ctx_t *ctx = provctx;

    if (ctx != NULL)
    {
        ops_provider_user_cleanup(ctx, ctx->user_data);
    }

    ops_provider_ctx_destroy(ctx);
}

static const OSSL_ALGORITHM *ops_provider_query_operation(
    void *provctx,
    int operation_id,
    int *no_store)
{
    (void)provctx;

    if (no_store != NULL)
    {
        *no_store = 0;
    }

    if (operation_id == OSSL_OP_DIGEST)
    {
        return ops_digest_algorithms();
    }

    return NULL;
}

static const OSSL_DISPATCH ops_provider_dispatch[] = {
    OPS_FUNCTION(OSSL_FUNC_PROVIDER_TEARDOWN, ops_provider_teardown),
    OPS_FUNCTION(OSSL_FUNC_PROVIDER_QUERY_OPERATION, ops_provider_query_operation),
    { 0, NULL }
};

/* Standard entry point; the SDK currently publishes only static digest records. */
OPS_PROVIDER_EXPORT
int OSSL_provider_init(
    const OSSL_CORE_HANDLE *handle,
    const OSSL_DISPATCH *in,
    const OSSL_DISPATCH **out,
    void **provctx)
{
    ops_provider_ctx_t *ctx;

    if (out == NULL || provctx == NULL)
    {
        return 0;
    }

    *out = NULL;
    *provctx = NULL;
    ctx = ops_provider_ctx_create(handle, in);
    if (ctx == NULL)
    {
        return 0;
    }

    if (ops_provider_user_init(ctx, &ctx->user_data) != 1)
    {
        ops_provider_ctx_destroy(ctx);
        return 0;
    }

    *provctx = ctx;
    *out = ops_provider_dispatch;
    return 1;
}
