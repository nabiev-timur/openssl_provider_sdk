#ifndef OPS_BIO_H_
#define OPS_BIO_H_

#include "ops_defines.h"

#include <stdarg.h>
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
/* Availability is queried through ops_core_has_function in ops_core.h. */
#ifdef OSSL_FUNC_BIO_NEW_FILE
/** @brief Calls the incoming BIO_new_file callback for provctx. */
OPS_API OSSL_CORE_BIO *ops_bio_new_file(void *provctx, const char *filename, const char *mode);
#endif

#ifdef OSSL_FUNC_BIO_NEW_MEMBUF
/** @brief Calls the incoming BIO_new_membuf callback for provctx. */
OPS_API OSSL_CORE_BIO *ops_bio_new_membuf(void *provctx, const void *buf, int len);
#endif

#ifdef OSSL_FUNC_BIO_READ_EX
/** @brief Calls the incoming BIO_read_ex callback for provctx. */
OPS_API int ops_bio_read_ex(
    void *provctx,
    OSSL_CORE_BIO *bio,
    void *data,
    size_t data_len,
    size_t *bytes_read);
#endif

#ifdef OSSL_FUNC_BIO_WRITE_EX
/** @brief Calls the incoming BIO_write_ex callback for provctx. */
OPS_API int ops_bio_write_ex(
    void *provctx,
    OSSL_CORE_BIO *bio,
    const void *data,
    size_t data_len,
    size_t *written);
#endif

#ifdef OSSL_FUNC_BIO_GETS
/** @brief Calls the incoming BIO_gets callback for provctx. */
OPS_API int ops_bio_gets(void *provctx, OSSL_CORE_BIO *bio, char *buf, int size);
#endif

#ifdef OSSL_FUNC_BIO_PUTS
/** @brief Calls the incoming BIO_puts callback for provctx. */
OPS_API int ops_bio_puts(void *provctx, OSSL_CORE_BIO *bio, const char *str);
#endif

#ifdef OSSL_FUNC_BIO_UP_REF
/** @brief Calls the incoming BIO_up_ref callback for provctx. */
OPS_API int ops_bio_up_ref(void *provctx, OSSL_CORE_BIO *bio);
#endif

#ifdef OSSL_FUNC_BIO_FREE
/** @brief Calls the incoming BIO_free callback for provctx. */
OPS_API int ops_bio_free(void *provctx, OSSL_CORE_BIO *bio);
#endif

#ifdef OSSL_FUNC_BIO_VPRINTF
/** @brief Calls the incoming BIO_vprintf callback for provctx. */
OPS_API int ops_bio_vprintf(void *provctx, OSSL_CORE_BIO *bio, const char *format, va_list args);
#endif

#ifdef OSSL_FUNC_BIO_VSNPRINTF
/** @brief Calls the incoming BIO_vsnprintf callback for provctx. */
OPS_API int ops_bio_vsnprintf(void *provctx, char *buf, size_t n, const char *fmt, va_list args);
#endif

#ifdef OSSL_FUNC_BIO_CTRL
/** @brief Calls the incoming BIO_ctrl callback for provctx. */
OPS_API int ops_bio_ctrl(void *provctx, OSSL_CORE_BIO *bio, int cmd, long num, void *ptr);
#endif

#ifdef __cplusplus
}
#endif

#endif
