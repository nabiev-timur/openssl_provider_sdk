#include "ops_platform.h"
#include "openssl_provider_sdk/ops_provider.h"
#include <stddef.h>

extern const OSSL_ALGORITHM ops_digest_begin[];

/* Compiler emission and linker KEEP are both needed under LTO/section GC. */
const OSSL_ALGORITHM ops_digest_terminal_record
    __attribute__((section(".ops_digest.end"), used,
        aligned(__alignof__(OSSL_ALGORITHM)))) = { NULL, NULL, NULL, NULL };

const OSSL_ALGORITHM *ops_platform_digest_algorithms(void)
{
    return ops_digest_begin;
}

/* These definitions are weak; declarations in the public header stay ordinary.
 * Definitions supplied by the provider module override these defaults. */
__attribute__((weak))
int ops_provider_user_init(void *provctx, void **user_data)
{
    (void)provctx;
    *user_data = NULL;
    return 1;
}

__attribute__((weak))
void ops_provider_user_cleanup(void *provctx, void *user_data)
{
    (void)provctx;
    (void)user_data;
}
