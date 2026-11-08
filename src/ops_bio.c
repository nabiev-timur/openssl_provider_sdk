#include "openssl_provider_sdk/ops_bio.h"
#include "ops_provider_ctx_internal.h"

#ifdef OSSL_FUNC_BIO_NEW_FILE
OSSL_CORE_BIO *ops_bio_new_file(void *provctx, const char *filename, const char *mode)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->BIO_new_file(filename, mode);
}
#endif

#ifdef OSSL_FUNC_BIO_NEW_MEMBUF
OSSL_CORE_BIO *ops_bio_new_membuf(void *provctx, const void *buf, int len)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->BIO_new_membuf(buf, len);
}
#endif

#ifdef OSSL_FUNC_BIO_READ_EX
int ops_bio_read_ex(
    void *provctx,
    OSSL_CORE_BIO *bio,
    void *data,
    size_t data_len,
    size_t *bytes_read)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->BIO_read_ex(bio, data, data_len, bytes_read);
}
#endif

#ifdef OSSL_FUNC_BIO_WRITE_EX
int ops_bio_write_ex(
    void *provctx,
    OSSL_CORE_BIO *bio,
    const void *data,
    size_t data_len,
    size_t *written)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->BIO_write_ex(bio, data, data_len, written);
}
#endif

#ifdef OSSL_FUNC_BIO_GETS
int ops_bio_gets(void *provctx, OSSL_CORE_BIO *bio, char *buf, int size)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->BIO_gets(bio, buf, size);
}
#endif

#ifdef OSSL_FUNC_BIO_PUTS
int ops_bio_puts(void *provctx, OSSL_CORE_BIO *bio, const char *str)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->BIO_puts(bio, str);
}
#endif

#ifdef OSSL_FUNC_BIO_UP_REF
int ops_bio_up_ref(void *provctx, OSSL_CORE_BIO *bio)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->BIO_up_ref(bio);
}
#endif

#ifdef OSSL_FUNC_BIO_FREE
int ops_bio_free(void *provctx, OSSL_CORE_BIO *bio)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->BIO_free(bio);
}
#endif

#ifdef OSSL_FUNC_BIO_VPRINTF
int ops_bio_vprintf(void *provctx, OSSL_CORE_BIO *bio, const char *format, va_list args)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->BIO_vprintf(bio, format, args);
}
#endif

#ifdef OSSL_FUNC_BIO_VSNPRINTF
int ops_bio_vsnprintf(void *provctx, char *buf, size_t n, const char *fmt, va_list args)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->BIO_vsnprintf(buf, n, fmt, args);
}
#endif

#ifdef OSSL_FUNC_BIO_CTRL
int ops_bio_ctrl(void *provctx, OSSL_CORE_BIO *bio, int cmd, long num, void *ptr)
{
    ops_provider_ctx_t *ctx = provctx;

    return ctx->BIO_ctrl(bio, cmd, num, ptr);
}
#endif
