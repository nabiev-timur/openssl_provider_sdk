#include "openssl_provider_sdk/ops_crt.h"
#include "ops_provider_ctx_internal.h"

#ifdef OSSL_FUNC_CRYPTO_MALLOC
void *ops_malloc(void *provctx, size_t num)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->CRYPTO_malloc(num, __FILE__, __LINE__);
}
#endif

#ifdef OSSL_FUNC_CRYPTO_ZALLOC
void *ops_zalloc(void *provctx, size_t num)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->CRYPTO_zalloc(num, __FILE__, __LINE__);
}
#endif

#ifdef OSSL_FUNC_CRYPTO_FREE
void ops_free(void *provctx, void *ptr)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->CRYPTO_free(ptr, __FILE__, __LINE__);
}
#endif

#ifdef OSSL_FUNC_CRYPTO_CLEAR_FREE
void ops_clear_free(void *provctx, void *ptr, size_t num)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->CRYPTO_clear_free(ptr, num, __FILE__, __LINE__);
}
#endif

#ifdef OSSL_FUNC_CRYPTO_REALLOC
void *ops_realloc(void *provctx, void *addr, size_t num)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->CRYPTO_realloc(addr, num, __FILE__, __LINE__);
}
#endif

#ifdef OSSL_FUNC_CRYPTO_CLEAR_REALLOC
void *ops_clear_realloc(void *provctx, void *addr, size_t old_num, size_t num)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->CRYPTO_clear_realloc(addr, old_num, num, __FILE__, __LINE__);
}
#endif

#ifdef OSSL_FUNC_CRYPTO_SECURE_MALLOC
void *ops_secure_malloc(void *provctx, size_t num)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->CRYPTO_secure_malloc(num, __FILE__, __LINE__);
}
#endif

#ifdef OSSL_FUNC_CRYPTO_SECURE_ZALLOC
void *ops_secure_zalloc(void *provctx, size_t num)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->CRYPTO_secure_zalloc(num, __FILE__, __LINE__);
}
#endif

#ifdef OSSL_FUNC_CRYPTO_SECURE_FREE
void ops_secure_free(void *provctx, void *ptr)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->CRYPTO_secure_free(ptr, __FILE__, __LINE__);
}
#endif

#ifdef OSSL_FUNC_CRYPTO_SECURE_CLEAR_FREE
void ops_secure_clear_free(void *provctx, void *ptr, size_t num)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->CRYPTO_secure_clear_free(ptr, num, __FILE__, __LINE__);
}
#endif

#ifdef OSSL_FUNC_CRYPTO_SECURE_ALLOCATED
int ops_secure_allocated(void *provctx, const void *ptr)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->CRYPTO_secure_allocated(ptr);
}
#endif

#ifdef OSSL_FUNC_OPENSSL_CLEANSE
void ops_cleanse(void *provctx, void *ptr, size_t len)
{
    ops_provider_ctx_t *ctx = provctx;

    ctx->OPENSSL_cleanse(ptr, len);
}
#endif
