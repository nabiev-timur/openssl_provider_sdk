#include "openssl_provider_sdk/ops_core.h"
#include "ops_provider_ctx_internal.h"

#ifdef OSSL_FUNC_CORE_GETTABLE_PARAMS
const OSSL_PARAM *ops_core_gettable_params(void *provctx)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->core_gettable_params(ctx->handle);
}
#endif

#ifdef OSSL_FUNC_CORE_GET_PARAMS
int ops_core_get_params(void *provctx, OSSL_PARAM params[])
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->core_get_params(ctx->handle, params);
}
#endif

#ifdef OSSL_FUNC_CORE_THREAD_START
int ops_core_thread_start(void *provctx, OSSL_thread_stop_handler_fn handfn, void *arg)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->core_thread_start(ctx->handle, handfn, arg);
}
#endif

#ifdef OSSL_FUNC_CORE_GET_LIBCTX
OPENSSL_CORE_CTX *ops_core_get_libctx(void *provctx)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->core_get_libctx(ctx->handle);
}
#endif

#ifdef OSSL_FUNC_CORE_NEW_ERROR
void ops_core_new_error(void *provctx)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->core_new_error(ctx->handle);
}
#endif

#ifdef OSSL_FUNC_CORE_SET_ERROR_DEBUG
void ops_core_set_error_debug(void *provctx, const char *file, int line, const char *func)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->core_set_error_debug(ctx->handle, file, line, func);
}
#endif

#ifdef OSSL_FUNC_CORE_VSET_ERROR
void ops_core_vset_error(void *provctx, uint32_t reason, const char *fmt, va_list args)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->core_vset_error(ctx->handle, reason, fmt, args);
}
#endif

#ifdef OSSL_FUNC_CORE_SET_ERROR_MARK
int ops_core_set_error_mark(void *provctx)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->core_set_error_mark(ctx->handle);
}
#endif

#ifdef OSSL_FUNC_CORE_CLEAR_LAST_ERROR_MARK
int ops_core_clear_last_error_mark(void *provctx)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->core_clear_last_error_mark(ctx->handle);
}
#endif

#ifdef OSSL_FUNC_CORE_POP_ERROR_TO_MARK
int ops_core_pop_error_to_mark(void *provctx)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->core_pop_error_to_mark(ctx->handle);
}
#endif

#ifdef OSSL_FUNC_CORE_OBJ_ADD_SIGID
int ops_core_obj_add_sigid(
    void *provctx,
    const char *sign_name,
    const char *digest_name,
    const char *pkey_name)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->core_obj_add_sigid(ctx->handle, sign_name, digest_name, pkey_name);
}
#endif

#ifdef OSSL_FUNC_CORE_OBJ_CREATE
int ops_core_obj_create(void *provctx, const char *oid, const char *sn, const char *ln)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->core_obj_create(ctx->handle, oid, sn, ln);
}
#endif

#ifdef OSSL_FUNC_INDICATOR_CB
void ops_indicator_cb(void *provctx, OPENSSL_CORE_CTX *core_ctx, OSSL_INDICATOR_CALLBACK **cb)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->indicator_cb(core_ctx, cb);
}
#endif

#ifdef OSSL_FUNC_SELF_TEST_CB
void ops_self_test_cb(void *provctx, OPENSSL_CORE_CTX *core_ctx, OSSL_CALLBACK **cb, void **cbarg)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->self_test_cb(core_ctx, cb, cbarg);
}
#endif

#ifdef OSSL_FUNC_GET_ENTROPY
size_t ops_get_entropy(
    void *provctx,
    unsigned char **pout,
    int entropy,
    size_t min_len,
    size_t max_len)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->get_entropy(ctx->handle, pout, entropy, min_len, max_len);
}
#endif

#ifdef OSSL_FUNC_GET_USER_ENTROPY
size_t ops_get_user_entropy(
    void *provctx,
    unsigned char **pout,
    int entropy,
    size_t min_len,
    size_t max_len)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->get_user_entropy(ctx->handle, pout, entropy, min_len, max_len);
}
#endif

#ifdef OSSL_FUNC_CLEANUP_ENTROPY
void ops_cleanup_entropy(void *provctx, unsigned char *buf, size_t len)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->cleanup_entropy(ctx->handle, buf, len);
}
#endif

#ifdef OSSL_FUNC_CLEANUP_USER_ENTROPY
void ops_cleanup_user_entropy(void *provctx, unsigned char *buf, size_t len)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->cleanup_user_entropy(ctx->handle, buf, len);
}
#endif

#ifdef OSSL_FUNC_GET_NONCE
size_t ops_get_nonce(
    void *provctx,
    unsigned char **pout,
    size_t min_len,
    size_t max_len,
    const void *salt,
    size_t salt_len)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->get_nonce(ctx->handle, pout, min_len, max_len, salt, salt_len);
}
#endif

#ifdef OSSL_FUNC_GET_USER_NONCE
size_t ops_get_user_nonce(
    void *provctx,
    unsigned char **pout,
    size_t min_len,
    size_t max_len,
    const void *salt,
    size_t salt_len)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->get_user_nonce(ctx->handle, pout, min_len, max_len, salt, salt_len);
}
#endif

#ifdef OSSL_FUNC_CLEANUP_NONCE
void ops_cleanup_nonce(void *provctx, unsigned char *buf, size_t len)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->cleanup_nonce(ctx->handle, buf, len);
}
#endif

#ifdef OSSL_FUNC_CLEANUP_USER_NONCE
void ops_cleanup_user_nonce(void *provctx, unsigned char *buf, size_t len)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->cleanup_user_nonce(ctx->handle, buf, len);
}
#endif

#ifdef OSSL_FUNC_PROVIDER_REGISTER_CHILD_CB
int ops_provider_register_child_cb(
    void *provctx,
    int (*create_cb)(const OSSL_CORE_HANDLE *provider, void *cbdata),
    int (*remove_cb)(const OSSL_CORE_HANDLE *provider, void *cbdata),
    int (*global_props_cb)(const char *props, void *cbdata),
    void *cbdata)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->provider_register_child_cb(ctx->handle, create_cb, remove_cb, global_props_cb, cbdata);
}
#endif

#ifdef OSSL_FUNC_PROVIDER_DEREGISTER_CHILD_CB
void ops_provider_deregister_child_cb(void *provctx)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->provider_deregister_child_cb(ctx->handle);
}
#endif

#ifdef OSSL_FUNC_PROVIDER_NAME
const char *ops_provider_name(void *provctx, const OSSL_CORE_HANDLE *prov)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->provider_name(prov);
}
#endif

#ifdef OSSL_FUNC_PROVIDER_GET0_PROVIDER_CTX
void *ops_provider_get0_provider_ctx(void *provctx, const OSSL_CORE_HANDLE *prov)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->provider_get0_provider_ctx(prov);
}
#endif

#ifdef OSSL_FUNC_PROVIDER_GET0_DISPATCH
const OSSL_DISPATCH *ops_provider_get0_dispatch(void *provctx, const OSSL_CORE_HANDLE *prov)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->provider_get0_dispatch(prov);
}
#endif

#ifdef OSSL_FUNC_PROVIDER_UP_REF
int ops_provider_up_ref(void *provctx, const OSSL_CORE_HANDLE *prov, int activate)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->provider_up_ref(prov, activate);
}
#endif

#ifdef OSSL_FUNC_PROVIDER_FREE
int ops_provider_free(void *provctx, const OSSL_CORE_HANDLE *prov, int deactivate)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->provider_free(prov, deactivate);
}
#endif

#ifdef OSSL_FUNC_CORE_COUNT_TO_MARK
int ops_core_count_to_mark(void *provctx)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->core_count_to_mark(ctx->handle);
}
#endif

int ops_core_has_function(const void *provctx, int function_id)
{
    const ops_provider_ctx_t *ctx = provctx;

    if (ctx == NULL)
    {
        return 0;
    }

    switch (function_id)
    {
#ifdef OSSL_FUNC_CORE_GETTABLE_PARAMS
    case OSSL_FUNC_CORE_GETTABLE_PARAMS:
        return ctx->core_gettable_params != NULL;
#endif
#ifdef OSSL_FUNC_CORE_GET_PARAMS
    case OSSL_FUNC_CORE_GET_PARAMS:
        return ctx->core_get_params != NULL;
#endif
#ifdef OSSL_FUNC_CORE_THREAD_START
    case OSSL_FUNC_CORE_THREAD_START:
        return ctx->core_thread_start != NULL;
#endif
#ifdef OSSL_FUNC_CORE_GET_LIBCTX
    case OSSL_FUNC_CORE_GET_LIBCTX:
        return ctx->core_get_libctx != NULL;
#endif
#ifdef OSSL_FUNC_CORE_NEW_ERROR
    case OSSL_FUNC_CORE_NEW_ERROR:
        return ctx->core_new_error != NULL;
#endif
#ifdef OSSL_FUNC_CORE_SET_ERROR_DEBUG
    case OSSL_FUNC_CORE_SET_ERROR_DEBUG:
        return ctx->core_set_error_debug != NULL;
#endif
#ifdef OSSL_FUNC_CORE_VSET_ERROR
    case OSSL_FUNC_CORE_VSET_ERROR:
        return ctx->core_vset_error != NULL;
#endif
#ifdef OSSL_FUNC_CORE_SET_ERROR_MARK
    case OSSL_FUNC_CORE_SET_ERROR_MARK:
        return ctx->core_set_error_mark != NULL;
#endif
#ifdef OSSL_FUNC_CORE_CLEAR_LAST_ERROR_MARK
    case OSSL_FUNC_CORE_CLEAR_LAST_ERROR_MARK:
        return ctx->core_clear_last_error_mark != NULL;
#endif
#ifdef OSSL_FUNC_CORE_POP_ERROR_TO_MARK
    case OSSL_FUNC_CORE_POP_ERROR_TO_MARK:
        return ctx->core_pop_error_to_mark != NULL;
#endif
#ifdef OSSL_FUNC_CORE_OBJ_ADD_SIGID
    case OSSL_FUNC_CORE_OBJ_ADD_SIGID:
        return ctx->core_obj_add_sigid != NULL;
#endif
#ifdef OSSL_FUNC_CORE_OBJ_CREATE
    case OSSL_FUNC_CORE_OBJ_CREATE:
        return ctx->core_obj_create != NULL;
#endif
#ifdef OSSL_FUNC_CRYPTO_MALLOC
    case OSSL_FUNC_CRYPTO_MALLOC:
        return ctx->CRYPTO_malloc != NULL;
#endif
#ifdef OSSL_FUNC_CRYPTO_ZALLOC
    case OSSL_FUNC_CRYPTO_ZALLOC:
        return ctx->CRYPTO_zalloc != NULL;
#endif
#ifdef OSSL_FUNC_CRYPTO_FREE
    case OSSL_FUNC_CRYPTO_FREE:
        return ctx->CRYPTO_free != NULL;
#endif
#ifdef OSSL_FUNC_CRYPTO_CLEAR_FREE
    case OSSL_FUNC_CRYPTO_CLEAR_FREE:
        return ctx->CRYPTO_clear_free != NULL;
#endif
#ifdef OSSL_FUNC_CRYPTO_REALLOC
    case OSSL_FUNC_CRYPTO_REALLOC:
        return ctx->CRYPTO_realloc != NULL;
#endif
#ifdef OSSL_FUNC_CRYPTO_CLEAR_REALLOC
    case OSSL_FUNC_CRYPTO_CLEAR_REALLOC:
        return ctx->CRYPTO_clear_realloc != NULL;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_MALLOC
    case OSSL_FUNC_CRYPTO_SECURE_MALLOC:
        return ctx->CRYPTO_secure_malloc != NULL;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_ZALLOC
    case OSSL_FUNC_CRYPTO_SECURE_ZALLOC:
        return ctx->CRYPTO_secure_zalloc != NULL;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_FREE
    case OSSL_FUNC_CRYPTO_SECURE_FREE:
        return ctx->CRYPTO_secure_free != NULL;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_CLEAR_FREE
    case OSSL_FUNC_CRYPTO_SECURE_CLEAR_FREE:
        return ctx->CRYPTO_secure_clear_free != NULL;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_ALLOCATED
    case OSSL_FUNC_CRYPTO_SECURE_ALLOCATED:
        return ctx->CRYPTO_secure_allocated != NULL;
#endif
#ifdef OSSL_FUNC_OPENSSL_CLEANSE
    case OSSL_FUNC_OPENSSL_CLEANSE:
        return ctx->OPENSSL_cleanse != NULL;
#endif
#ifdef OSSL_FUNC_BIO_NEW_FILE
    case OSSL_FUNC_BIO_NEW_FILE:
        return ctx->BIO_new_file != NULL;
#endif
#ifdef OSSL_FUNC_BIO_NEW_MEMBUF
    case OSSL_FUNC_BIO_NEW_MEMBUF:
        return ctx->BIO_new_membuf != NULL;
#endif
#ifdef OSSL_FUNC_BIO_READ_EX
    case OSSL_FUNC_BIO_READ_EX:
        return ctx->BIO_read_ex != NULL;
#endif
#ifdef OSSL_FUNC_BIO_WRITE_EX
    case OSSL_FUNC_BIO_WRITE_EX:
        return ctx->BIO_write_ex != NULL;
#endif
#ifdef OSSL_FUNC_BIO_GETS
    case OSSL_FUNC_BIO_GETS:
        return ctx->BIO_gets != NULL;
#endif
#ifdef OSSL_FUNC_BIO_PUTS
    case OSSL_FUNC_BIO_PUTS:
        return ctx->BIO_puts != NULL;
#endif
#ifdef OSSL_FUNC_BIO_UP_REF
    case OSSL_FUNC_BIO_UP_REF:
        return ctx->BIO_up_ref != NULL;
#endif
#ifdef OSSL_FUNC_BIO_FREE
    case OSSL_FUNC_BIO_FREE:
        return ctx->BIO_free != NULL;
#endif
#ifdef OSSL_FUNC_BIO_VPRINTF
    case OSSL_FUNC_BIO_VPRINTF:
        return ctx->BIO_vprintf != NULL;
#endif
#ifdef OSSL_FUNC_BIO_VSNPRINTF
    case OSSL_FUNC_BIO_VSNPRINTF:
        return ctx->BIO_vsnprintf != NULL;
#endif
#ifdef OSSL_FUNC_BIO_CTRL
    case OSSL_FUNC_BIO_CTRL:
        return ctx->BIO_ctrl != NULL;
#endif
#ifdef OSSL_FUNC_INDICATOR_CB
    case OSSL_FUNC_INDICATOR_CB:
        return ctx->indicator_cb != NULL;
#endif
#ifdef OSSL_FUNC_SELF_TEST_CB
    case OSSL_FUNC_SELF_TEST_CB:
        return ctx->self_test_cb != NULL;
#endif
#ifdef OSSL_FUNC_GET_ENTROPY
    case OSSL_FUNC_GET_ENTROPY:
        return ctx->get_entropy != NULL;
#endif
#ifdef OSSL_FUNC_GET_USER_ENTROPY
    case OSSL_FUNC_GET_USER_ENTROPY:
        return ctx->get_user_entropy != NULL;
#endif
#ifdef OSSL_FUNC_CLEANUP_ENTROPY
    case OSSL_FUNC_CLEANUP_ENTROPY:
        return ctx->cleanup_entropy != NULL;
#endif
#ifdef OSSL_FUNC_CLEANUP_USER_ENTROPY
    case OSSL_FUNC_CLEANUP_USER_ENTROPY:
        return ctx->cleanup_user_entropy != NULL;
#endif
#ifdef OSSL_FUNC_GET_NONCE
    case OSSL_FUNC_GET_NONCE:
        return ctx->get_nonce != NULL;
#endif
#ifdef OSSL_FUNC_GET_USER_NONCE
    case OSSL_FUNC_GET_USER_NONCE:
        return ctx->get_user_nonce != NULL;
#endif
#ifdef OSSL_FUNC_CLEANUP_NONCE
    case OSSL_FUNC_CLEANUP_NONCE:
        return ctx->cleanup_nonce != NULL;
#endif
#ifdef OSSL_FUNC_CLEANUP_USER_NONCE
    case OSSL_FUNC_CLEANUP_USER_NONCE:
        return ctx->cleanup_user_nonce != NULL;
#endif
#ifdef OSSL_FUNC_PROVIDER_REGISTER_CHILD_CB
    case OSSL_FUNC_PROVIDER_REGISTER_CHILD_CB:
        return ctx->provider_register_child_cb != NULL;
#endif
#ifdef OSSL_FUNC_PROVIDER_DEREGISTER_CHILD_CB
    case OSSL_FUNC_PROVIDER_DEREGISTER_CHILD_CB:
        return ctx->provider_deregister_child_cb != NULL;
#endif
#ifdef OSSL_FUNC_PROVIDER_NAME
    case OSSL_FUNC_PROVIDER_NAME:
        return ctx->provider_name != NULL;
#endif
#ifdef OSSL_FUNC_PROVIDER_GET0_PROVIDER_CTX
    case OSSL_FUNC_PROVIDER_GET0_PROVIDER_CTX:
        return ctx->provider_get0_provider_ctx != NULL;
#endif
#ifdef OSSL_FUNC_PROVIDER_GET0_DISPATCH
    case OSSL_FUNC_PROVIDER_GET0_DISPATCH:
        return ctx->provider_get0_dispatch != NULL;
#endif
#ifdef OSSL_FUNC_PROVIDER_UP_REF
    case OSSL_FUNC_PROVIDER_UP_REF:
        return ctx->provider_up_ref != NULL;
#endif
#ifdef OSSL_FUNC_PROVIDER_FREE
    case OSSL_FUNC_PROVIDER_FREE:
        return ctx->provider_free != NULL;
#endif
#ifdef OSSL_FUNC_CORE_COUNT_TO_MARK
    case OSSL_FUNC_CORE_COUNT_TO_MARK:
        return ctx->core_count_to_mark != NULL;
#endif
    default:
        return 0;
    }
}
