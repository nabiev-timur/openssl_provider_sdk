#include "openssl_provider_sdk/ops_algorithm.h"
#include "openssl_provider_sdk/ops_core.h"
#include "openssl_provider_sdk/ops_crt.h"
#include "openssl_provider_sdk/ops_provider.h"

#include <stdio.h>
#include <stdlib.h>

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

static int allocations;
static int frees;
static int init_calls;
static int cleanup_calls;
static int errors;
static int mode;
static int handle;

static void *core_malloc(size_t size, const char *file, int line)
{
    void *result;

    (void)file;
    (void)line;
    result = malloc(size);
    if (result != NULL)
    {
        ++allocations;
    }

    return result;
}

static void core_free(void *ptr, const char *file, int line)
{
    (void)file;
    (void)line;
    if (ptr != NULL)
    {
        ++frees;
    }

    free(ptr);
}

int ops_provider_user_init(void *provctx, void **user_data)
{
    int *state;

    ++init_calls;
    if (*user_data != NULL || ops_provider_get_user_data(provctx) != NULL
        || !ops_core_has_function(provctx, OSSL_FUNC_CRYPTO_MALLOC))
    {
        ++errors;
        return 0;
    }

    if (mode == 1) /* Failure before acquiring resources. */
    {
        return 0;
    }

    if (mode == 3) /* Successful init is allowed to retain no user state. */
    {
        return 1;
    }

    state = ops_malloc(provctx, sizeof *state);
    if (state == NULL)
    {
        return 0;
    }

    *state = init_calls;
    *user_data = state;
    if (ops_provider_get_user_data(provctx) != state)
    {
        ++errors;
    }

    if (mode == 2) /* Failing init cleans up its own partial state. */
    {
        ops_free(provctx, state);
        *user_data = NULL;
        return 0;
    }

    return 1;
}

void ops_provider_user_cleanup(void *provctx, void *user_data)
{
    ++cleanup_calls;
    if (ops_provider_get_user_data(provctx) != user_data
        || !ops_core_has_function(provctx, OSSL_FUNC_CRYPTO_FREE))
    {
        ++errors;
    }

    ops_free(provctx, user_data);
}

static void teardown(const OSSL_DISPATCH *out, void *ctx)
{
    for (; out->function_id != 0; ++out)
    {
        if (out->function_id == OSSL_FUNC_PROVIDER_TEARDOWN)
        {
            OSSL_FUNC_provider_teardown(out)(ctx);
            return;
        }
    }

    ++errors;
}

int main(void)
{
    const OSSL_DISPATCH in[] = {
        OPS_FUNCTION(OSSL_FUNC_CRYPTO_MALLOC, core_malloc),
        OPS_FUNCTION(OSSL_FUNC_CRYPTO_FREE, core_free), { 0, NULL }
    };

    const OSSL_DISPATCH *out_a = NULL;
    const OSSL_DISPATCH *out_b = NULL;
    void *ctx_a = NULL;
    void *ctx_b = NULL;
    int before_cleanup;

    CHECK(ops_provider_get_user_data(NULL) == NULL);
    CHECK(OSSL_provider_init((const OSSL_CORE_HANDLE *)&handle,
        in, &out_a, &ctx_a) == 1);
    CHECK(OSSL_provider_init((const OSSL_CORE_HANDLE *)&handle,
        in, &out_b, &ctx_b) == 1);
    CHECK(allocations == 4 && frees == 0 && init_calls == 2);
    CHECK(ops_provider_get_user_data(ctx_a) != ops_provider_get_user_data(ctx_b));
    CHECK(*(int *)ops_provider_get_user_data(ctx_a) == 1);
    CHECK(*(int *)ops_provider_get_user_data(ctx_b) == 2);
    teardown(out_a, ctx_a);
    CHECK(cleanup_calls == 1 && frees == 2);
    CHECK(*(int *)ops_provider_get_user_data(ctx_b) == 2);
    teardown(out_b, ctx_b);
    CHECK(cleanup_calls == 2 && allocations == frees);

    before_cleanup = cleanup_calls;
    for (mode = 1; mode <= 2; ++mode)
    {
        out_a = in;
        ctx_a = &handle;
        CHECK(OSSL_provider_init((const OSSL_CORE_HANDLE *)&handle,
            in, &out_a, &ctx_a) == 0);
        CHECK(out_a == NULL && ctx_a == NULL);
        CHECK(cleanup_calls == before_cleanup && allocations == frees);
    }

    mode = 3;
    CHECK(OSSL_provider_init((const OSSL_CORE_HANDLE *)&handle,
        in, &out_a, &ctx_a) == 1);
    CHECK(ops_provider_get_user_data(ctx_a) == NULL);
    teardown(out_a, ctx_a);
    CHECK(cleanup_calls == before_cleanup + 1 && allocations == frees);
    CHECK(errors == 0);
    return 0;
}
