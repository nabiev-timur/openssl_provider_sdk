#include "openssl_provider_sdk/ops_crt.h"
#include "openssl_provider_sdk/ops_provider.h"
#include "../state.h"

int ops_provider_user_init(void *provctx, void **user_data)
{
    ops_test_user_state *state = ops_malloc(provctx, sizeof *state);

    if (state == NULL)
    {
        return 0;
    }

    state->value = 42;
    *user_data = state;
    return 1;
}

void ops_provider_user_cleanup(void *provctx, void *user_data)
{
    ops_free(provctx, user_data);
}
