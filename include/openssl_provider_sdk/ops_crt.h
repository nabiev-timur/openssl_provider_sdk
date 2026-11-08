#ifndef OPS_CRT_H_
#define OPS_CRT_H_

#include "ops_defines.h"

#include <stddef.h>
#include <openssl/core.h>
#include <openssl/core_dispatch.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * @brief Forward core services through an explicit provider instance.
 * @note provctx is borrowed from the algorithm's provctx and must remain alive
 *     throughout the call and the lifetime of returned core-owned resources.
 *     Pass the unchanged provctx received from an OpenSSL algorithm callback.
 *     Call only after successful SDK provider initialization. For optional callbacks,
 *     first check ops_core_has_function(provctx, OSSL_FUNC_*); invoking an unavailable
 *     callback violates the precondition. Native OpenSSL return values, ownership,
 *     buffer requirements and thread-safety rules apply without translation.
 *     Never mix resources from different contexts or allocator families.
 */
/* Allocations use core CRYPTO_* callbacks. Debug file/line identify the
 * wrapper implementation. Secure allocations require secure_free/clear_free.
 * No system allocator fallback is provided. */
/* Availability is queried through ops_core_has_function in ops_core.h. */
#ifdef OSSL_FUNC_CRYPTO_MALLOC
/** @brief Calls the incoming CRYPTO_malloc callback for provctx. */
OPS_API void *ops_malloc(void *provctx, size_t num);
#endif

#ifdef OSSL_FUNC_CRYPTO_ZALLOC
/** @brief Calls the incoming CRYPTO_zalloc callback for provctx. */
OPS_API void *ops_zalloc(void *provctx, size_t num);
#endif

#ifdef OSSL_FUNC_CRYPTO_FREE
/** @brief Calls the incoming CRYPTO_free callback for provctx. */
OPS_API void ops_free(void *provctx, void *ptr);
#endif

#ifdef OSSL_FUNC_CRYPTO_CLEAR_FREE
/** @brief Calls the incoming CRYPTO_clear_free callback for provctx. */
OPS_API void ops_clear_free(void *provctx, void *ptr, size_t num);
#endif

#ifdef OSSL_FUNC_CRYPTO_REALLOC
/** @brief Calls the incoming CRYPTO_realloc callback for provctx. */
OPS_API void *ops_realloc(void *provctx, void *addr, size_t num);
#endif

#ifdef OSSL_FUNC_CRYPTO_CLEAR_REALLOC
/** @brief Calls the incoming CRYPTO_clear_realloc callback for provctx. */
OPS_API void *ops_clear_realloc(void *provctx, void *addr, size_t old_num, size_t num);
#endif

#ifdef OSSL_FUNC_CRYPTO_SECURE_MALLOC
/** @brief Calls the incoming CRYPTO_secure_malloc callback for provctx. */
OPS_API void *ops_secure_malloc(void *provctx, size_t num);
#endif

#ifdef OSSL_FUNC_CRYPTO_SECURE_ZALLOC
/** @brief Calls the incoming CRYPTO_secure_zalloc callback for provctx. */
OPS_API void *ops_secure_zalloc(void *provctx, size_t num);
#endif

#ifdef OSSL_FUNC_CRYPTO_SECURE_FREE
/** @brief Calls the incoming CRYPTO_secure_free callback for provctx. */
OPS_API void ops_secure_free(void *provctx, void *ptr);
#endif

#ifdef OSSL_FUNC_CRYPTO_SECURE_CLEAR_FREE
/** @brief Calls the incoming CRYPTO_secure_clear_free callback for provctx. */
OPS_API void ops_secure_clear_free(void *provctx, void *ptr, size_t num);
#endif

#ifdef OSSL_FUNC_CRYPTO_SECURE_ALLOCATED
/** @brief Calls the incoming CRYPTO_secure_allocated callback for provctx. */
OPS_API int ops_secure_allocated(void *provctx, const void *ptr);
#endif

#ifdef OSSL_FUNC_OPENSSL_CLEANSE
/** @brief Calls the incoming OPENSSL_cleanse callback for provctx. */
OPS_API void ops_cleanse(void *provctx, void *ptr, size_t len);
#endif

#ifdef __cplusplus
}
#endif

#endif
