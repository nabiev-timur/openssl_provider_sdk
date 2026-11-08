#ifndef OPS_PARAMS_H_
#define OPS_PARAMS_H_

#include "ops_defines.h"

#include <openssl/params.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * @brief Typed parameter access by key, using native OpenSSL conversions.
 *     Arrays must be terminated with OSSL_PARAM_END; keys are exact, case-sensitive
 *     strings. The first matching entry is used if keys repeat.
 *
 *     All get/set helpers return 1 on success and 0 on conversion failure or an
 *     invalid key. Missing keys (including params == NULL) return 1 and leave all
 *     outputs unchanged. key must not be NULL. A present get parameter must have
 *     non-NULL data; output arguments follow the native OSSL_PARAM helper contract.
 *     Use ops_params_has() before get when a key is mandatory.
 *
 *     Set helpers preserve native return_size/size-query behavior, including
 *     params[i].data == NULL. No provider context is needed: these functions call
 *     libcrypto's OSSL_PARAM helpers, not the incoming core dispatch.
 *     Changes to earlier parameters in an || chain are not rolled back on failure.
 */

/** Returns 1 if key is present, 0 otherwise; NULL params/key returns 0. */
OPS_API int ops_params_has(const OSSL_PARAM params[], const char *key);

OPS_API int ops_params_get_int(const OSSL_PARAM params[], const char *key, int *val);

OPS_API int ops_params_get_uint(const OSSL_PARAM params[], const char *key, unsigned int *val);

OPS_API int ops_params_get_long(const OSSL_PARAM params[], const char *key, long int *val);

OPS_API int ops_params_get_ulong(const OSSL_PARAM params[], const char *key, unsigned long int *val);

OPS_API int ops_params_get_int32(const OSSL_PARAM params[], const char *key, int32_t *val);

OPS_API int ops_params_get_uint32(const OSSL_PARAM params[], const char *key, uint32_t *val);

OPS_API int ops_params_get_int64(const OSSL_PARAM params[], const char *key, int64_t *val);

OPS_API int ops_params_get_uint64(const OSSL_PARAM params[], const char *key, uint64_t *val);

OPS_API int ops_params_get_size_t(const OSSL_PARAM params[], const char *key, size_t *val);

OPS_API int ops_params_get_time_t(const OSSL_PARAM params[], const char *key, time_t *val);

OPS_API int ops_params_set_int(OSSL_PARAM params[], const char *key, int val);

OPS_API int ops_params_set_uint(OSSL_PARAM params[], const char *key, unsigned int val);

OPS_API int ops_params_set_long(OSSL_PARAM params[], const char *key, long int val);

OPS_API int ops_params_set_ulong(OSSL_PARAM params[], const char *key, unsigned long int val);

OPS_API int ops_params_set_int32(OSSL_PARAM params[], const char *key, int32_t val);

OPS_API int ops_params_set_uint32(OSSL_PARAM params[], const char *key, uint32_t val);

OPS_API int ops_params_set_int64(OSSL_PARAM params[], const char *key, int64_t val);

OPS_API int ops_params_set_uint64(OSSL_PARAM params[], const char *key, uint64_t val);

OPS_API int ops_params_set_size_t(OSSL_PARAM params[], const char *key, size_t val);

OPS_API int ops_params_set_time_t(OSSL_PARAM params[], const char *key, time_t val);

OPS_API int ops_params_get_double(const OSSL_PARAM params[], const char *key, double *val);

OPS_API int ops_params_set_double(OSSL_PARAM params[], const char *key, double val);

/** Native allocation rules apply: BN_free for BN, OPENSSL_free for strings. */
OPS_API int ops_params_get_bn(const OSSL_PARAM params[], const char *key, BIGNUM **val);

OPS_API int ops_params_set_bn(OSSL_PARAM params[], const char *key, const BIGNUM *val);

/** Native allocation rules apply: BN_free for BN, OPENSSL_free for strings. */
OPS_API int ops_params_get_utf8_string(
    const OSSL_PARAM params[],
    const char *key,
    char **val,
    size_t max_len);

OPS_API int ops_params_set_utf8_string(OSSL_PARAM params[], const char *key, const char *val);

/** Native allocation rules apply: BN_free for BN, OPENSSL_free for strings. */
OPS_API int ops_params_get_octet_string(
    const OSSL_PARAM params[],
    const char *key,
    void **val,
    size_t max_len,
    size_t *used_len);

OPS_API int ops_params_set_octet_string(OSSL_PARAM params[], const char *key, const void *val, size_t len);

/** Returns borrowed storage with the native OSSL_PARAM lifetime. */
OPS_API int ops_params_get_utf8_ptr(const OSSL_PARAM params[], const char *key, const char **val);

OPS_API int ops_params_set_utf8_ptr(OSSL_PARAM params[], const char *key, const char *val);

/** Returns borrowed storage with the native OSSL_PARAM lifetime. */
OPS_API int ops_params_get_octet_ptr(
    const OSSL_PARAM params[],
    const char *key,
    const void **val,
    size_t *used_len);

OPS_API int ops_params_set_octet_ptr(
    OSSL_PARAM params[],
    const char *key,
    const void *val,
    size_t used_len);

/** Returns borrowed storage with the native OSSL_PARAM lifetime. */
OPS_API int ops_params_get_utf8_string_ptr(const OSSL_PARAM params[], const char *key, const char **val);

/** Returns borrowed storage with the native OSSL_PARAM lifetime. */
OPS_API int ops_params_get_octet_string_ptr(
    const OSSL_PARAM params[],
    const char *key,
    const void **val,
    size_t *used_len);

#ifdef __cplusplus
}
#endif

#endif
