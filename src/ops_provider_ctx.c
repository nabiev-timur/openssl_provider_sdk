#include "ops_provider_ctx_internal.h"
#include "openssl_provider_sdk/ops_provider.h"
#include <stddef.h>

ops_provider_ctx_t *ops_provider_ctx_create(
    const OSSL_CORE_HANDLE *handle,
    const OSSL_DISPATCH *in)
{
    ops_provider_ctx_t candidate = {0};
    ops_provider_ctx_t *ctx;

    if (handle == NULL || in == NULL)
    {
        return NULL;
    }

    candidate.handle = handle;
    for (; in->function_id != 0; ++in)
    {
        switch (in->function_id)
        {
#ifdef OSSL_FUNC_CORE_GETTABLE_PARAMS
        case OSSL_FUNC_CORE_GETTABLE_PARAMS:
            candidate.core_gettable_params = OSSL_FUNC_core_gettable_params(in);
            break;
#endif
#ifdef OSSL_FUNC_CORE_GET_PARAMS
        case OSSL_FUNC_CORE_GET_PARAMS:
            candidate.core_get_params = OSSL_FUNC_core_get_params(in);
            break;
#endif
#ifdef OSSL_FUNC_CORE_THREAD_START
        case OSSL_FUNC_CORE_THREAD_START:
            candidate.core_thread_start = OSSL_FUNC_core_thread_start(in);
            break;
#endif
#ifdef OSSL_FUNC_CORE_GET_LIBCTX
        case OSSL_FUNC_CORE_GET_LIBCTX:
            candidate.core_get_libctx = OSSL_FUNC_core_get_libctx(in);
            break;
#endif
#ifdef OSSL_FUNC_CORE_NEW_ERROR
        case OSSL_FUNC_CORE_NEW_ERROR:
            candidate.core_new_error = OSSL_FUNC_core_new_error(in);
            break;
#endif
#ifdef OSSL_FUNC_CORE_SET_ERROR_DEBUG
        case OSSL_FUNC_CORE_SET_ERROR_DEBUG:
            candidate.core_set_error_debug = OSSL_FUNC_core_set_error_debug(in);
            break;
#endif
#ifdef OSSL_FUNC_CORE_VSET_ERROR
        case OSSL_FUNC_CORE_VSET_ERROR:
            candidate.core_vset_error = OSSL_FUNC_core_vset_error(in);
            break;
#endif
#ifdef OSSL_FUNC_CORE_SET_ERROR_MARK
        case OSSL_FUNC_CORE_SET_ERROR_MARK:
            candidate.core_set_error_mark = OSSL_FUNC_core_set_error_mark(in);
            break;
#endif
#ifdef OSSL_FUNC_CORE_CLEAR_LAST_ERROR_MARK
        case OSSL_FUNC_CORE_CLEAR_LAST_ERROR_MARK:
            candidate.core_clear_last_error_mark = OSSL_FUNC_core_clear_last_error_mark(in);
            break;
#endif
#ifdef OSSL_FUNC_CORE_POP_ERROR_TO_MARK
        case OSSL_FUNC_CORE_POP_ERROR_TO_MARK:
            candidate.core_pop_error_to_mark = OSSL_FUNC_core_pop_error_to_mark(in);
            break;
#endif
#ifdef OSSL_FUNC_CORE_OBJ_ADD_SIGID
        case OSSL_FUNC_CORE_OBJ_ADD_SIGID:
            candidate.core_obj_add_sigid = OSSL_FUNC_core_obj_add_sigid(in);
            break;
#endif
#ifdef OSSL_FUNC_CORE_OBJ_CREATE
        case OSSL_FUNC_CORE_OBJ_CREATE:
            candidate.core_obj_create = OSSL_FUNC_core_obj_create(in);
            break;
#endif
#ifdef OSSL_FUNC_CRYPTO_MALLOC
        case OSSL_FUNC_CRYPTO_MALLOC:
            candidate.CRYPTO_malloc = OSSL_FUNC_CRYPTO_malloc(in);
            break;
#endif
#ifdef OSSL_FUNC_CRYPTO_ZALLOC
        case OSSL_FUNC_CRYPTO_ZALLOC:
            candidate.CRYPTO_zalloc = OSSL_FUNC_CRYPTO_zalloc(in);
            break;
#endif
#ifdef OSSL_FUNC_CRYPTO_FREE
        case OSSL_FUNC_CRYPTO_FREE:
            candidate.CRYPTO_free = OSSL_FUNC_CRYPTO_free(in);
            break;
#endif
#ifdef OSSL_FUNC_CRYPTO_CLEAR_FREE
        case OSSL_FUNC_CRYPTO_CLEAR_FREE:
            candidate.CRYPTO_clear_free = OSSL_FUNC_CRYPTO_clear_free(in);
            break;
#endif
#ifdef OSSL_FUNC_CRYPTO_REALLOC
        case OSSL_FUNC_CRYPTO_REALLOC:
            candidate.CRYPTO_realloc = OSSL_FUNC_CRYPTO_realloc(in);
            break;
#endif
#ifdef OSSL_FUNC_CRYPTO_CLEAR_REALLOC
        case OSSL_FUNC_CRYPTO_CLEAR_REALLOC:
            candidate.CRYPTO_clear_realloc = OSSL_FUNC_CRYPTO_clear_realloc(in);
            break;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_MALLOC
        case OSSL_FUNC_CRYPTO_SECURE_MALLOC:
            candidate.CRYPTO_secure_malloc = OSSL_FUNC_CRYPTO_secure_malloc(in);
            break;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_ZALLOC
        case OSSL_FUNC_CRYPTO_SECURE_ZALLOC:
            candidate.CRYPTO_secure_zalloc = OSSL_FUNC_CRYPTO_secure_zalloc(in);
            break;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_FREE
        case OSSL_FUNC_CRYPTO_SECURE_FREE:
            candidate.CRYPTO_secure_free = OSSL_FUNC_CRYPTO_secure_free(in);
            break;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_CLEAR_FREE
        case OSSL_FUNC_CRYPTO_SECURE_CLEAR_FREE:
            candidate.CRYPTO_secure_clear_free = OSSL_FUNC_CRYPTO_secure_clear_free(in);
            break;
#endif
#ifdef OSSL_FUNC_CRYPTO_SECURE_ALLOCATED
        case OSSL_FUNC_CRYPTO_SECURE_ALLOCATED:
            candidate.CRYPTO_secure_allocated = OSSL_FUNC_CRYPTO_secure_allocated(in);
            break;
#endif
#ifdef OSSL_FUNC_OPENSSL_CLEANSE
        case OSSL_FUNC_OPENSSL_CLEANSE:
            candidate.OPENSSL_cleanse = OSSL_FUNC_OPENSSL_cleanse(in);
            break;
#endif
#ifdef OSSL_FUNC_BIO_NEW_FILE
        case OSSL_FUNC_BIO_NEW_FILE:
            candidate.BIO_new_file = OSSL_FUNC_BIO_new_file(in);
            break;
#endif
#ifdef OSSL_FUNC_BIO_NEW_MEMBUF
        case OSSL_FUNC_BIO_NEW_MEMBUF:
            candidate.BIO_new_membuf = OSSL_FUNC_BIO_new_membuf(in);
            break;
#endif
#ifdef OSSL_FUNC_BIO_READ_EX
        case OSSL_FUNC_BIO_READ_EX:
            candidate.BIO_read_ex = OSSL_FUNC_BIO_read_ex(in);
            break;
#endif
#ifdef OSSL_FUNC_BIO_WRITE_EX
        case OSSL_FUNC_BIO_WRITE_EX:
            candidate.BIO_write_ex = OSSL_FUNC_BIO_write_ex(in);
            break;
#endif
#ifdef OSSL_FUNC_BIO_GETS
        case OSSL_FUNC_BIO_GETS:
            candidate.BIO_gets = OSSL_FUNC_BIO_gets(in);
            break;
#endif
#ifdef OSSL_FUNC_BIO_PUTS
        case OSSL_FUNC_BIO_PUTS:
            candidate.BIO_puts = OSSL_FUNC_BIO_puts(in);
            break;
#endif
#ifdef OSSL_FUNC_BIO_UP_REF
        case OSSL_FUNC_BIO_UP_REF:
            candidate.BIO_up_ref = OSSL_FUNC_BIO_up_ref(in);
            break;
#endif
#ifdef OSSL_FUNC_BIO_FREE
        case OSSL_FUNC_BIO_FREE:
            candidate.BIO_free = OSSL_FUNC_BIO_free(in);
            break;
#endif
#ifdef OSSL_FUNC_BIO_VPRINTF
        case OSSL_FUNC_BIO_VPRINTF:
            candidate.BIO_vprintf = OSSL_FUNC_BIO_vprintf(in);
            break;
#endif
#ifdef OSSL_FUNC_BIO_VSNPRINTF
        case OSSL_FUNC_BIO_VSNPRINTF:
            candidate.BIO_vsnprintf = OSSL_FUNC_BIO_vsnprintf(in);
            break;
#endif
#ifdef OSSL_FUNC_BIO_CTRL
        case OSSL_FUNC_BIO_CTRL:
            candidate.BIO_ctrl = OSSL_FUNC_BIO_ctrl(in);
            break;
#endif
#ifdef OSSL_FUNC_INDICATOR_CB
        case OSSL_FUNC_INDICATOR_CB:
            candidate.indicator_cb = OSSL_FUNC_indicator_cb(in);
            break;
#endif
#ifdef OSSL_FUNC_SELF_TEST_CB
        case OSSL_FUNC_SELF_TEST_CB:
            candidate.self_test_cb = OSSL_FUNC_self_test_cb(in);
            break;
#endif
#ifdef OSSL_FUNC_GET_ENTROPY
        case OSSL_FUNC_GET_ENTROPY:
            candidate.get_entropy = OSSL_FUNC_get_entropy(in);
            break;
#endif
#ifdef OSSL_FUNC_GET_USER_ENTROPY
        case OSSL_FUNC_GET_USER_ENTROPY:
            candidate.get_user_entropy = OSSL_FUNC_get_user_entropy(in);
            break;
#endif
#ifdef OSSL_FUNC_CLEANUP_ENTROPY
        case OSSL_FUNC_CLEANUP_ENTROPY:
            candidate.cleanup_entropy = OSSL_FUNC_cleanup_entropy(in);
            break;
#endif
#ifdef OSSL_FUNC_CLEANUP_USER_ENTROPY
        case OSSL_FUNC_CLEANUP_USER_ENTROPY:
            candidate.cleanup_user_entropy = OSSL_FUNC_cleanup_user_entropy(in);
            break;
#endif
#ifdef OSSL_FUNC_GET_NONCE
        case OSSL_FUNC_GET_NONCE:
            candidate.get_nonce = OSSL_FUNC_get_nonce(in);
            break;
#endif
#ifdef OSSL_FUNC_GET_USER_NONCE
        case OSSL_FUNC_GET_USER_NONCE:
            candidate.get_user_nonce = OSSL_FUNC_get_user_nonce(in);
            break;
#endif
#ifdef OSSL_FUNC_CLEANUP_NONCE
        case OSSL_FUNC_CLEANUP_NONCE:
            candidate.cleanup_nonce = OSSL_FUNC_cleanup_nonce(in);
            break;
#endif
#ifdef OSSL_FUNC_CLEANUP_USER_NONCE
        case OSSL_FUNC_CLEANUP_USER_NONCE:
            candidate.cleanup_user_nonce = OSSL_FUNC_cleanup_user_nonce(in);
            break;
#endif
#ifdef OSSL_FUNC_PROVIDER_REGISTER_CHILD_CB
        case OSSL_FUNC_PROVIDER_REGISTER_CHILD_CB:
            candidate.provider_register_child_cb = OSSL_FUNC_provider_register_child_cb(in);
            break;
#endif
#ifdef OSSL_FUNC_PROVIDER_DEREGISTER_CHILD_CB
        case OSSL_FUNC_PROVIDER_DEREGISTER_CHILD_CB:
            candidate.provider_deregister_child_cb = OSSL_FUNC_provider_deregister_child_cb(in);
            break;
#endif
#ifdef OSSL_FUNC_PROVIDER_NAME
        case OSSL_FUNC_PROVIDER_NAME:
            candidate.provider_name = OSSL_FUNC_provider_name(in);
            break;
#endif
#ifdef OSSL_FUNC_PROVIDER_GET0_PROVIDER_CTX
        case OSSL_FUNC_PROVIDER_GET0_PROVIDER_CTX:
            candidate.provider_get0_provider_ctx = OSSL_FUNC_provider_get0_provider_ctx(in);
            break;
#endif
#ifdef OSSL_FUNC_PROVIDER_GET0_DISPATCH
        case OSSL_FUNC_PROVIDER_GET0_DISPATCH:
            candidate.provider_get0_dispatch = OSSL_FUNC_provider_get0_dispatch(in);
            break;
#endif
#ifdef OSSL_FUNC_PROVIDER_UP_REF
        case OSSL_FUNC_PROVIDER_UP_REF:
            candidate.provider_up_ref = OSSL_FUNC_provider_up_ref(in);
            break;
#endif
#ifdef OSSL_FUNC_PROVIDER_FREE
        case OSSL_FUNC_PROVIDER_FREE:
            candidate.provider_free = OSSL_FUNC_provider_free(in);
            break;
#endif
#ifdef OSSL_FUNC_CORE_COUNT_TO_MARK
        case OSSL_FUNC_CORE_COUNT_TO_MARK:
            candidate.core_count_to_mark = OSSL_FUNC_core_count_to_mark(in);
            break;
#endif
        default:
            break;
        }
    }

    if (candidate.CRYPTO_malloc == NULL || candidate.CRYPTO_free == NULL)
    {
        return NULL;
    }

    ctx = candidate.CRYPTO_malloc(sizeof *ctx, __FILE__, __LINE__);
    if (ctx != NULL)
    {
        *ctx = candidate;
    }

    return ctx;
}

void ops_provider_ctx_destroy(ops_provider_ctx_t *ctx)
{
    if (ctx != NULL)
    {
        ctx->CRYPTO_free(ctx, __FILE__, __LINE__);
    }
}

void *ops_provider_get_user_data(void *provctx)
{
    const ops_provider_ctx_t *ctx = provctx;

    return ctx != NULL ? ctx->user_data : NULL;
}
