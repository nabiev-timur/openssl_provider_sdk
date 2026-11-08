#include "openssl_provider_sdk/ops_algorithm.h"
#include "platform/ops_platform.h"

/* The platform linker setup relies on four native pointer-sized fields. */
_Static_assert(sizeof(OSSL_ALGORITHM) == 4 * sizeof(void *),
    "Unexpected OSSL_ALGORITHM layout");

const OSSL_ALGORITHM *ops_digest_algorithms(void)
{
    return ops_platform_digest_algorithms();
}
