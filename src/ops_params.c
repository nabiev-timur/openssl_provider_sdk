#include "openssl_provider_sdk/ops_params.h"

int ops_params_has(const OSSL_PARAM params[], const char *key)
{
    return params != NULL && key != NULL
        && OSSL_PARAM_locate_const(params, key) != NULL;
}

int ops_params_get_int(const OSSL_PARAM params[], const char *key, int *val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_int(param, val);
}

int ops_params_get_uint(const OSSL_PARAM params[], const char *key, unsigned int *val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_uint(param, val);
}

int ops_params_get_long(const OSSL_PARAM params[], const char *key, long int *val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_long(param, val);
}

int ops_params_get_ulong(const OSSL_PARAM params[], const char *key, unsigned long int *val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_ulong(param, val);
}

int ops_params_get_int32(const OSSL_PARAM params[], const char *key, int32_t *val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_int32(param, val);
}

int ops_params_get_uint32(const OSSL_PARAM params[], const char *key, uint32_t *val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_uint32(param, val);
}

int ops_params_get_int64(const OSSL_PARAM params[], const char *key, int64_t *val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_int64(param, val);
}

int ops_params_get_uint64(const OSSL_PARAM params[], const char *key, uint64_t *val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_uint64(param, val);
}

int ops_params_get_size_t(const OSSL_PARAM params[], const char *key, size_t *val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_size_t(param, val);
}

int ops_params_get_time_t(const OSSL_PARAM params[], const char *key, time_t *val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_time_t(param, val);
}

int ops_params_set_int(OSSL_PARAM params[], const char *key, int val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    return OSSL_PARAM_set_int(param, val);
}

int ops_params_set_uint(OSSL_PARAM params[], const char *key, unsigned int val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    return OSSL_PARAM_set_uint(param, val);
}

int ops_params_set_long(OSSL_PARAM params[], const char *key, long int val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    return OSSL_PARAM_set_long(param, val);
}

int ops_params_set_ulong(OSSL_PARAM params[], const char *key, unsigned long int val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    return OSSL_PARAM_set_ulong(param, val);
}

int ops_params_set_int32(OSSL_PARAM params[], const char *key, int32_t val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    return OSSL_PARAM_set_int32(param, val);
}

int ops_params_set_uint32(OSSL_PARAM params[], const char *key, uint32_t val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    return OSSL_PARAM_set_uint32(param, val);
}

int ops_params_set_int64(OSSL_PARAM params[], const char *key, int64_t val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    return OSSL_PARAM_set_int64(param, val);
}

int ops_params_set_uint64(OSSL_PARAM params[], const char *key, uint64_t val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    return OSSL_PARAM_set_uint64(param, val);
}

int ops_params_set_size_t(OSSL_PARAM params[], const char *key, size_t val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    return OSSL_PARAM_set_size_t(param, val);
}

int ops_params_set_time_t(OSSL_PARAM params[], const char *key, time_t val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    return OSSL_PARAM_set_time_t(param, val);
}

int ops_params_get_double(const OSSL_PARAM params[], const char *key, double *val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_double(param, val);
}

int ops_params_set_double(OSSL_PARAM params[], const char *key, double val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    return OSSL_PARAM_set_double(param, val);
}

int ops_params_get_bn(const OSSL_PARAM params[], const char *key, BIGNUM **val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_BN(param, val);
}

int ops_params_set_bn(OSSL_PARAM params[], const char *key, const BIGNUM *val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_set_BN(param, val);
}

int ops_params_get_utf8_string(
    const OSSL_PARAM params[],
    const char *key,
    char **val,
    size_t max_len)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_utf8_string(param, val, max_len);
}

int ops_params_set_utf8_string(OSSL_PARAM params[], const char *key, const char *val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_set_utf8_string(param, val);
}

int ops_params_get_octet_string(
    const OSSL_PARAM params[],
    const char *key,
    void **val,
    size_t max_len,
    size_t *used_len)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_octet_string(param, val, max_len, used_len);
}

int ops_params_set_octet_string(OSSL_PARAM params[], const char *key, const void *val, size_t len)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (val == NULL && len != 0)
    {
        return 0;
    }

    return OSSL_PARAM_set_octet_string(param, val, len);
}

int ops_params_get_utf8_ptr(const OSSL_PARAM params[], const char *key, const char **val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_utf8_ptr(param, val);
}

int ops_params_set_utf8_ptr(OSSL_PARAM params[], const char *key, const char *val)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    return OSSL_PARAM_set_utf8_ptr(param, val);
}

int ops_params_get_octet_ptr(
    const OSSL_PARAM params[],
    const char *key,
    const void **val,
    size_t *used_len)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_octet_ptr(param, val, used_len);
}

int ops_params_set_octet_ptr(
    OSSL_PARAM params[],
    const char *key,
    const void *val,
    size_t used_len)
{
    OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate(params, key);
    if (param == NULL)
    {
        return 1;
    }

    return OSSL_PARAM_set_octet_ptr(param, val, used_len);
}

int ops_params_get_utf8_string_ptr(const OSSL_PARAM params[], const char *key, const char **val)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_utf8_string_ptr(param, val);
}

int ops_params_get_octet_string_ptr(
    const OSSL_PARAM params[],
    const char *key,
    const void **val,
    size_t *used_len)
{
    const OSSL_PARAM *param;

    if (key == NULL)
    {
        return 0;
    }

    if (params == NULL)
    {
        return 1;
    }

    param = OSSL_PARAM_locate_const(params, key);
    if (param == NULL)
    {
        return 1;
    }

    if (param->data == NULL || val == NULL)
    {
        return 0;
    }

    return OSSL_PARAM_get_octet_string_ptr(param, val, used_len);
}
