#ifndef OPS_CORE_H_
#define OPS_CORE_H_

#include "ops_defines.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
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
/** Returns 1 iff provctx contains the callback identified by function_id. */
OPS_API int ops_core_has_function(const void *provctx, int function_id);

#ifdef OSSL_FUNC_CORE_GETTABLE_PARAMS
/** @brief Calls the incoming core_gettable_params callback for provctx. */
OPS_API const OSSL_PARAM *ops_core_gettable_params(void *provctx);
#endif

#ifdef OSSL_FUNC_CORE_GET_PARAMS
/** @brief Calls the incoming core_get_params callback for provctx. */
OPS_API int ops_core_get_params(void *provctx, OSSL_PARAM params[]);
#endif

#ifdef OSSL_FUNC_CORE_THREAD_START
/** @brief Calls the incoming core_thread_start callback for provctx. */
OPS_API int ops_core_thread_start(void *provctx, OSSL_thread_stop_handler_fn handfn, void *arg);
#endif

#ifdef OSSL_FUNC_CORE_GET_LIBCTX
/** @brief Calls the incoming core_get_libctx callback for provctx. */
OPS_API OPENSSL_CORE_CTX *ops_core_get_libctx(void *provctx);
#endif

#ifdef OSSL_FUNC_CORE_NEW_ERROR
/** @brief Calls the incoming core_new_error callback for provctx. */
OPS_API void ops_core_new_error(void *provctx);
#endif

#ifdef OSSL_FUNC_CORE_SET_ERROR_DEBUG
/** @brief Calls the incoming core_set_error_debug callback for provctx. */
OPS_API void ops_core_set_error_debug(void *provctx, const char *file, int line, const char *func);
#endif

#ifdef OSSL_FUNC_CORE_VSET_ERROR
/** @brief Calls the incoming core_vset_error callback for provctx. */
OPS_API void ops_core_vset_error(void *provctx, uint32_t reason, const char *fmt, va_list args);
#endif

#ifdef OSSL_FUNC_CORE_SET_ERROR_MARK
/** @brief Calls the incoming core_set_error_mark callback for provctx. */
OPS_API int ops_core_set_error_mark(void *provctx);
#endif

#ifdef OSSL_FUNC_CORE_CLEAR_LAST_ERROR_MARK
/** @brief Calls the incoming core_clear_last_error_mark callback for provctx. */
OPS_API int ops_core_clear_last_error_mark(void *provctx);
#endif

#ifdef OSSL_FUNC_CORE_POP_ERROR_TO_MARK
/** @brief Calls the incoming core_pop_error_to_mark callback for provctx. */
OPS_API int ops_core_pop_error_to_mark(void *provctx);
#endif

#ifdef OSSL_FUNC_CORE_OBJ_ADD_SIGID
/** @brief Calls the incoming core_obj_add_sigid callback for provctx. */
OPS_API int ops_core_obj_add_sigid(
    void *provctx,
    const char *sign_name,
    const char *digest_name,
    const char *pkey_name);
#endif

#ifdef OSSL_FUNC_CORE_OBJ_CREATE
/** @brief Calls the incoming core_obj_create callback for provctx. */
OPS_API int ops_core_obj_create(void *provctx, const char *oid, const char *sn, const char *ln);
#endif

#ifdef OSSL_FUNC_INDICATOR_CB
/** @brief Calls the incoming indicator_cb callback for provctx. */
OPS_API void ops_indicator_cb(void *provctx, OPENSSL_CORE_CTX *core_ctx, OSSL_INDICATOR_CALLBACK **cb);
#endif

#ifdef OSSL_FUNC_SELF_TEST_CB
/** @brief Calls the incoming self_test_cb callback for provctx. */
OPS_API void ops_self_test_cb(void *provctx, OPENSSL_CORE_CTX *core_ctx, OSSL_CALLBACK **cb, void **cbarg);
#endif

#ifdef OSSL_FUNC_GET_ENTROPY
/** @brief Calls the incoming get_entropy callback for provctx. */
OPS_API size_t ops_get_entropy(
    void *provctx,
    unsigned char **pout,
    int entropy,
    size_t min_len,
    size_t max_len);
#endif

#ifdef OSSL_FUNC_GET_USER_ENTROPY
/** @brief Calls the incoming get_user_entropy callback for provctx. */
OPS_API size_t ops_get_user_entropy(
    void *provctx,
    unsigned char **pout,
    int entropy,
    size_t min_len,
    size_t max_len);
#endif

#ifdef OSSL_FUNC_CLEANUP_ENTROPY
/** @brief Calls the incoming cleanup_entropy callback for provctx. */
OPS_API void ops_cleanup_entropy(void *provctx, unsigned char *buf, size_t len);
#endif

#ifdef OSSL_FUNC_CLEANUP_USER_ENTROPY
/** @brief Calls the incoming cleanup_user_entropy callback for provctx. */
OPS_API void ops_cleanup_user_entropy(void *provctx, unsigned char *buf, size_t len);
#endif

#ifdef OSSL_FUNC_GET_NONCE
/** @brief Calls the incoming get_nonce callback for provctx. */
OPS_API size_t ops_get_nonce(
    void *provctx,
    unsigned char **pout,
    size_t min_len,
    size_t max_len,
    const void *salt,
    size_t salt_len);
#endif

#ifdef OSSL_FUNC_GET_USER_NONCE
/** @brief Calls the incoming get_user_nonce callback for provctx. */
OPS_API size_t ops_get_user_nonce(
    void *provctx,
    unsigned char **pout,
    size_t min_len,
    size_t max_len,
    const void *salt,
    size_t salt_len);
#endif

#ifdef OSSL_FUNC_CLEANUP_NONCE
/** @brief Calls the incoming cleanup_nonce callback for provctx. */
OPS_API void ops_cleanup_nonce(void *provctx, unsigned char *buf, size_t len);
#endif

#ifdef OSSL_FUNC_CLEANUP_USER_NONCE
/** @brief Calls the incoming cleanup_user_nonce callback for provctx. */
OPS_API void ops_cleanup_user_nonce(void *provctx, unsigned char *buf, size_t len);
#endif

#ifdef OSSL_FUNC_PROVIDER_REGISTER_CHILD_CB
/** @brief Calls the incoming provider_register_child_cb callback for provctx. */
OPS_API int ops_provider_register_child_cb(
    void *provctx,
    int (*create_cb)(const OSSL_CORE_HANDLE *provider, void *cbdata),
    int (*remove_cb)(const OSSL_CORE_HANDLE *provider, void *cbdata),
    int (*global_props_cb)(const char *props, void *cbdata),
    void *cbdata);
#endif

#ifdef OSSL_FUNC_PROVIDER_DEREGISTER_CHILD_CB
/** @brief Calls the incoming provider_deregister_child_cb callback for provctx. */
OPS_API void ops_provider_deregister_child_cb(void *provctx);
#endif

#ifdef OSSL_FUNC_PROVIDER_NAME
/** @brief Calls the incoming provider_name callback for provctx. */
OPS_API const char *ops_provider_name(void *provctx, const OSSL_CORE_HANDLE *prov);
#endif

#ifdef OSSL_FUNC_PROVIDER_GET0_PROVIDER_CTX
/** @brief Calls the incoming provider_get0_provider_ctx callback for provctx. */
OPS_API void *ops_provider_get0_provider_ctx(void *provctx, const OSSL_CORE_HANDLE *prov);
#endif

#ifdef OSSL_FUNC_PROVIDER_GET0_DISPATCH
/** @brief Calls the incoming provider_get0_dispatch callback for provctx. */
OPS_API const OSSL_DISPATCH *ops_provider_get0_dispatch(void *provctx, const OSSL_CORE_HANDLE *prov);
#endif

#ifdef OSSL_FUNC_PROVIDER_UP_REF
/** @brief Calls the incoming provider_up_ref callback for provctx. */
OPS_API int ops_provider_up_ref(void *provctx, const OSSL_CORE_HANDLE *prov, int activate);
#endif

#ifdef OSSL_FUNC_PROVIDER_FREE
/** @brief Calls the incoming provider_free callback for provctx. */
OPS_API int ops_provider_free(void *provctx, const OSSL_CORE_HANDLE *prov, int deactivate);
#endif

#ifdef OSSL_FUNC_CORE_COUNT_TO_MARK
/** @brief Calls the incoming core_count_to_mark callback for provctx. */
OPS_API int ops_core_count_to_mark(void *provctx);
#endif

#ifdef __cplusplus
}
#endif

#endif
