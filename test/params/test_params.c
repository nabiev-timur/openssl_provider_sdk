#include "openssl_provider_sdk/ops_params.h"

#include <openssl/crypto.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define CHECK(condition) \
    do \
    { \
        if (!(condition)) \
        { \
            fprintf(stderr, "Check failed at line %d: %s\n", __LINE__, #condition); \
            return 1; \
        } \
    } while (0)

/* Exercise each public scalar type with its matching native representation. */
#define CHECK_SCALAR(type, suffix) \
    do \
    { \
        type stored = 0; \
        type output = 11; \
        OSSL_PARAM values[] = { OSSL_PARAM_##suffix("value", &stored), OSSL_PARAM_END }; \
        CHECK(ops_params_set_##suffix(values, "value", (type)7)); \
        CHECK(ops_params_get_##suffix(values, "value", &output)); \
        CHECK(stored == (type)7 && output == (type)7); \
        CHECK(ops_params_get_##suffix(values, "missing", &output)); \
        CHECK(output == (type)7); \
    } while (0)

int main(void)
{
    unsigned int rounds = 8;
    unsigned int output = 99;
    int negative = -1;
    uint64_t wide = UINT64_MAX;
    char text[8] = {0};
    char short_text[2] = {0};
    char *text_copy = NULL;
    const char *borrowed = NULL;
    const char *stored_pointer = NULL;
    unsigned char bytes[4] = {0};
    unsigned char copied[4] = {0};
    void *copy = copied;
    const void *borrowed_bytes = NULL;
    const void *stored_byte_pointer = NULL;
    size_t used = 99;
    size_t query_size = 0;
    unsigned char bn_data[8] = {0};
    BIGNUM *bn = NULL;
    OSSL_PARAM params[] = {
        OSSL_PARAM_uint("rounds", &rounds),
        OSSL_PARAM_int("negative", &negative),
        OSSL_PARAM_uint64("wide", &wide),
        OSSL_PARAM_utf8_string("name", text, sizeof text),
        OSSL_PARAM_utf8_string("short", short_text, sizeof short_text),
        OSSL_PARAM_octet_string("bytes", bytes, sizeof bytes),
        OSSL_PARAM_utf8_ptr("pointer", &stored_pointer, 0),
        OSSL_PARAM_octet_ptr("byte-pointer", &stored_byte_pointer, sizeof bytes),
        OSSL_PARAM_size_t("query", NULL),
        OSSL_PARAM_BN("bn", bn_data, sizeof bn_data),
        OSSL_PARAM_END
    };

    OSSL_PARAM duplicates[] = {
        OSSL_PARAM_uint("same", &rounds),
        OSSL_PARAM_uint("same", &output),
        OSSL_PARAM_END
    };

    OSSL_PARAM empty[] = { OSSL_PARAM_END };

    CHECK_SCALAR(int, int);
    CHECK_SCALAR(unsigned int, uint);
    CHECK_SCALAR(long, long);
    CHECK_SCALAR(unsigned long, ulong);
    CHECK_SCALAR(int32_t, int32);
    CHECK_SCALAR(uint32_t, uint32);
    CHECK_SCALAR(int64_t, int64);
    CHECK_SCALAR(uint64_t, uint64);
    CHECK_SCALAR(size_t, size_t);
    CHECK_SCALAR(time_t, time_t);
    CHECK_SCALAR(double, double);

    CHECK(ops_params_has(params, "rounds"));
    CHECK(!ops_params_has(params, "Rounds"));
    CHECK(!ops_params_has(params, "missing"));
    CHECK(!ops_params_has(NULL, "rounds"));
    CHECK(!ops_params_has(params, NULL));
    CHECK(!ops_params_has(empty, "rounds"));
    CHECK(ops_params_get_uint(NULL, "rounds", &output));
    CHECK(ops_params_get_uint(empty, "rounds", &output));
    CHECK(output == 99);
    CHECK(ops_params_set_uint(NULL, "rounds", 0));
    CHECK(ops_params_set_uint(params, "missing", 0));
    CHECK(rounds == 8);
    CHECK(!ops_params_get_uint(params, NULL, &output));
    CHECK(!ops_params_set_uint(params, NULL, 0));
    CHECK(!ops_params_get_uint(params, "rounds", NULL));
    CHECK(!ops_params_get_uint(params, "negative", &output));
    CHECK(output == 99);
    CHECK(!ops_params_get_uint(params, "wide", &output));
    CHECK(!ops_params_set_int(params, "rounds", -1));
    CHECK(rounds == 8);
    CHECK(!ops_params_get_uint(params, "name", &output));
    CHECK(ops_params_set_uint(duplicates, "same", 12));
    CHECK(rounds == 12 && output == 99);
    if (!ops_params_get_uint(params, "negative", &output)
        || !ops_params_set_uint(params, "rounds", 44))
    {
        CHECK(rounds == 12); /* The second operation must not run after failure. */
    }
    else
    {
        CHECK(0);
    }

    CHECK(ops_params_set_size_t(params, "query", 32));
    CHECK(params[8].return_size == sizeof(size_t));
    CHECK(!ops_params_get_size_t(params, "query", &query_size));
    CHECK(query_size == 0);
    CHECK(ops_params_set_utf8_string(params, "name", "hello"));
    CHECK(strcmp(text, "hello") == 0);
    CHECK(!ops_params_set_utf8_string(params, "short", "hello"));
    CHECK(params[4].return_size == 5);
    CHECK(ops_params_get_utf8_string(params, "name", &text_copy, 0));
    CHECK(strcmp(text_copy, "hello") == 0);
    OPENSSL_free(text_copy);
    text_copy = NULL;
    CHECK(ops_params_set_utf8_ptr(params, "pointer", text));
    CHECK(stored_pointer == text);
    CHECK(ops_params_get_utf8_ptr(params, "pointer", &borrowed));
    CHECK(borrowed == text);
    CHECK(ops_params_get_utf8_string_ptr(params, "name", &borrowed));
    CHECK(borrowed == text);

    CHECK(ops_params_set_octet_string(params, "bytes", "abcd", 4));
    CHECK(ops_params_get_octet_string(params, "bytes", &copy, sizeof copied, &used));
    CHECK(used == 4 && memcmp(copied, "abcd", 4) == 0);
    CHECK(!ops_params_get_octet_string(params, "bytes", &copy, 2, &used));
    CHECK(ops_params_get_octet_string(params, "bytes", NULL, 0, &used));
    CHECK(used == 4);
    CHECK(ops_params_get_octet_string_ptr(params, "bytes", &borrowed_bytes, &used));
    CHECK(borrowed_bytes == bytes && used == 4);
    CHECK(ops_params_set_octet_ptr(params, "byte-pointer", bytes, 4));
    CHECK(ops_params_get_octet_ptr(params, "byte-pointer", &borrowed_bytes, &used));
    CHECK(borrowed_bytes == bytes && used == 4);

    bn = BN_new();
    CHECK(bn != NULL && BN_set_word(bn, 42));
    CHECK(ops_params_set_bn(params, "bn", bn));
    CHECK(BN_set_word(bn, 0));
    CHECK(ops_params_get_bn(params, "bn", &bn));
    CHECK(BN_get_word(bn) == 42);
    BN_free(bn);
    return 0;
}
