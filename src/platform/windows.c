#include "ops_platform.h"
#include "openssl_provider_sdk/ops_provider.h"
#include <stddef.h>

#pragma section(".opsdg$a", read)
#pragma section(".opsdg$z", read)
#pragma comment(linker, "/include:" OPS_COFF_SYMBOL_PREFIX "ops_digest_terminal_record")

__declspec(allocate(".opsdg$a")) __declspec(align(OPS_PLATFORM_ALIGNMENT))
const OSSL_ALGORITHM ops_digest_begin_record = { NULL, NULL, NULL, NULL };
__declspec(allocate(".opsdg$z")) __declspec(align(OPS_PLATFORM_ALIGNMENT))
const OSSL_ALGORITHM ops_digest_terminal_record = { NULL, NULL, NULL, NULL };

#pragma comment(linker, "/alternatename:" OPS_COFF_SYMBOL_PREFIX "ops_provider_user_init=" \
    OPS_COFF_SYMBOL_PREFIX "ops_provider_default_user_init")
#pragma comment(linker, "/alternatename:" OPS_COFF_SYMBOL_PREFIX "ops_provider_user_cleanup=" \
    OPS_COFF_SYMBOL_PREFIX "ops_provider_default_user_cleanup")

const OSSL_ALGORITHM *ops_platform_digest_algorithms(void)
{
    return (const OSSL_ALGORITHM *)(
        (const unsigned char *)&ops_digest_begin_record + sizeof(OSSL_ALGORITHM));
}

/* MSVC resolves an undefined user hook to these default functions. */
int ops_provider_default_user_init(void *provctx, void **user_data)
{
    (void)provctx;
    *user_data = NULL;
    return 1;
}

void ops_provider_default_user_cleanup(void *provctx, void *user_data)
{
    (void)provctx;
    (void)user_data;
}
