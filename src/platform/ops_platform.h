#ifndef OPS_PLATFORM_H_
#define OPS_PLATFORM_H_

#include <openssl/core.h>
#include "ops_platform_config.h"

/* Shared contract for platform implementations; not an installed SDK API. */
/**
 * @brief Returns this module's immutable, contiguous digest records.
 * @return Non-NULL borrowed array ending in exactly one all-NULL record.
 *     Empty registries consist only of the terminator. No allocation or
 *     ownership transfer occurs; storage lives until the module is unloaded.
 * @note The selected linker setup must retain records and prevent padding.
 *     Record order is unspecified. Symbols must resolve within this module.
 */
const OSSL_ALGORITHM *ops_platform_digest_algorithms(void);

#endif
