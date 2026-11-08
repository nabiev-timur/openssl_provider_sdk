#ifndef OPS_PROVIDER_CTX_INTERNAL_H_
#define OPS_PROVIDER_CTX_INTERNAL_H_

#include <openssl/core_dispatch.h>

/* Private representation of the void *provctx published to OpenSSL. */
typedef struct ops_provider_ctx ops_provider_ctx_t;

struct ops_provider_ctx
{
    const OSSL_CORE_HANDLE *handle;
    void *user_data;
#ifdef OSSL_FUNC_CORE_GETTABLE_PARAMS
    OSSL_FUNC_core_gettable_params_fn *core_gettable_params;
#endif
#ifdef OSSL_FUNC_CORE_GET_PARAMS
    OSSL_FUNC_core_get_params_fn *core_get_params;
#endif
#ifdef OSSL_FUNC_CORE_THREAD_START
    OSSL_FUNC_core_thread_start_fn *core_thread_start;
#endif
#ifdef OSSL_FUNC_CORE_GET_LIBCTX
    OSSL_FUNC_core_get_libctx_fn *core_get_libctx;
#endif
#ifdef OSSL_FUNC_CORE_NEW_ERROR
    OSSL_FUNC_core_new_error_fn *core_new_error;
#endif
#ifdef OSSL_FUNC_CORE_SET_ERROR_DEBUG
    OSSL_FUNC_core_set_error_debug_fn *core_set_error_debug;
#endif
#ifdef OSSL_FUNC_CORE_VSET_ERROR
    OSSL_FUNC_core_vset_error_fn *core_vset_error;
#endif
#ifdef OSSL_FUNC_CORE_SET_ERROR_MARK
    OSSL_FUNC_core_set_error_mark_fn *core_set_error_mark;
#endif
#ifdef OSSL_FUNC_CORE_CLEAR_LAST_ERROR_MARK
    OSSL_FUNC_core_clear_last_error_mark_fn *core_clear_last_error_mark;
#endif
#ifdef OSSL_FUNC_CORE_POP_ERROR_TO_MARK
    OSSL_FUNC_core_pop_error_to_mark_fn *core_pop_error_to_mark;
#endif
#ifdef OSSL_FUNC_CORE_OBJ_ADD_SIGID
    OSSL_FUNC_core_obj_add_sigid_fn *core_obj_add_sigid;
#endif
#ifdef OSSL_FUNC_CORE_OBJ_CREATE
    OSSL_FUNC_core_obj_create_fn *core_obj_create;
#endif
#ifdef OSSL_FUNC_CRYPTO_MALLOC
    OSSL_FUNC_CRYPTO_malloc_fn *CRYPTO_malloc;
#endif
#ifdef OSSL_FUNC_CRYPTO_ZALLOC
    OSSL_FUNC_CRYPTO_zalloc_fn *CRYPTO_zalloc;
#endif
#ifdef OSSL_FUNC_CRYPTO_FREE
    OSSL_FUNC_CRYPTO_free_fn *CRYPTO_free;
#endif
#ifdef OSSL_FUNC_CRYPTO_CLEAR_FREE
    OSSL_FUNC_CRYPTO_clear_free_fn *CRYPTO_clear_free;
#endif
#ifdef OSSL_FUNC_CRYPTO_REALLOC
    OSSL_FUNC_CRYPTO_realloc_fn *CRYPTO_realloc;
#endif
#ifdef OSSL_FUNC_CRYPTO_CLEAR_REALLOC
    OSSL_FUNC_CRYPTO_clear_realloc_fn *CRYPTO_clear_realloc;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_MALLOC
    OSSL_FUNC_CRYPTO_secure_malloc_fn *CRYPTO_secure_malloc;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_ZALLOC
    OSSL_FUNC_CRYPTO_secure_zalloc_fn *CRYPTO_secure_zalloc;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_FREE
    OSSL_FUNC_CRYPTO_secure_free_fn *CRYPTO_secure_free;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_CLEAR_FREE
    OSSL_FUNC_CRYPTO_secure_clear_free_fn *CRYPTO_secure_clear_free;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_ALLOCATED
    OSSL_FUNC_CRYPTO_secure_allocated_fn *CRYPTO_secure_allocated;
#endif
#ifdef OSSL_FUNC_OPENSSL_CLEANSE
    OSSL_FUNC_OPENSSL_cleanse_fn *OPENSSL_cleanse;
#endif
#ifdef OSSL_FUNC_BIO_NEW_FILE
    OSSL_FUNC_BIO_new_file_fn *BIO_new_file;
#endif
#ifdef OSSL_FUNC_BIO_NEW_MEMBUF
    OSSL_FUNC_BIO_new_membuf_fn *BIO_new_membuf;
#endif
#ifdef OSSL_FUNC_BIO_READ_EX
    OSSL_FUNC_BIO_read_ex_fn *BIO_read_ex;
#endif
#ifdef OSSL_FUNC_BIO_WRITE_EX
    OSSL_FUNC_BIO_write_ex_fn *BIO_write_ex;
#endif
#ifdef OSSL_FUNC_BIO_GETS
    OSSL_FUNC_BIO_gets_fn *BIO_gets;
#endif
#ifdef OSSL_FUNC_BIO_PUTS
    OSSL_FUNC_BIO_puts_fn *BIO_puts;
#endif
#ifdef OSSL_FUNC_BIO_UP_REF
    OSSL_FUNC_BIO_up_ref_fn *BIO_up_ref;
#endif
#ifdef OSSL_FUNC_BIO_FREE
    OSSL_FUNC_BIO_free_fn *BIO_free;
#endif
#ifdef OSSL_FUNC_BIO_VPRINTF
    OSSL_FUNC_BIO_vprintf_fn *BIO_vprintf;
#endif
#ifdef OSSL_FUNC_BIO_VSNPRINTF
    OSSL_FUNC_BIO_vsnprintf_fn *BIO_vsnprintf;
#endif
#ifdef OSSL_FUNC_BIO_CTRL
    OSSL_FUNC_BIO_ctrl_fn *BIO_ctrl;
#endif
#ifdef OSSL_FUNC_INDICATOR_CB
    OSSL_FUNC_indicator_cb_fn *indicator_cb;
#endif
#ifdef OSSL_FUNC_SELF_TEST_CB
    OSSL_FUNC_self_test_cb_fn *self_test_cb;
#endif
#ifdef OSSL_FUNC_GET_ENTROPY
    OSSL_FUNC_get_entropy_fn *get_entropy;
#endif
#ifdef OSSL_FUNC_GET_USER_ENTROPY
    OSSL_FUNC_get_user_entropy_fn *get_user_entropy;
#endif
#ifdef OSSL_FUNC_CLEANUP_ENTROPY
    OSSL_FUNC_cleanup_entropy_fn *cleanup_entropy;
#endif
#ifdef OSSL_FUNC_CLEANUP_USER_ENTROPY
    OSSL_FUNC_cleanup_user_entropy_fn *cleanup_user_entropy;
#endif
#ifdef OSSL_FUNC_GET_NONCE
    OSSL_FUNC_get_nonce_fn *get_nonce;
#endif
#ifdef OSSL_FUNC_GET_USER_NONCE
    OSSL_FUNC_get_user_nonce_fn *get_user_nonce;
#endif
#ifdef OSSL_FUNC_CLEANUP_NONCE
    OSSL_FUNC_cleanup_nonce_fn *cleanup_nonce;
#endif
#ifdef OSSL_FUNC_CLEANUP_USER_NONCE
    OSSL_FUNC_cleanup_user_nonce_fn *cleanup_user_nonce;
#endif
#ifdef OSSL_FUNC_PROVIDER_REGISTER_CHILD_CB
    OSSL_FUNC_provider_register_child_cb_fn *provider_register_child_cb;
#endif
#ifdef OSSL_FUNC_PROVIDER_DEREGISTER_CHILD_CB
    OSSL_FUNC_provider_deregister_child_cb_fn *provider_deregister_child_cb;
#endif
#ifdef OSSL_FUNC_PROVIDER_NAME
    OSSL_FUNC_provider_name_fn *provider_name;
#endif
#ifdef OSSL_FUNC_PROVIDER_GET0_PROVIDER_CTX
    OSSL_FUNC_provider_get0_provider_ctx_fn *provider_get0_provider_ctx;
#endif
#ifdef OSSL_FUNC_PROVIDER_GET0_DISPATCH
    OSSL_FUNC_provider_get0_dispatch_fn *provider_get0_dispatch;
#endif
#ifdef OSSL_FUNC_PROVIDER_UP_REF
    OSSL_FUNC_provider_up_ref_fn *provider_up_ref;
#endif
#ifdef OSSL_FUNC_PROVIDER_FREE
    OSSL_FUNC_provider_free_fn *provider_free;
#endif
#ifdef OSSL_FUNC_CORE_COUNT_TO_MARK
    OSSL_FUNC_core_count_to_mark_fn *core_count_to_mark;
#endif
};

ops_provider_ctx_t *ops_provider_ctx_create(
    const OSSL_CORE_HANDLE *handle,
    const OSSL_DISPATCH *in);
void ops_provider_ctx_destroy(ops_provider_ctx_t *ctx);

#endif
