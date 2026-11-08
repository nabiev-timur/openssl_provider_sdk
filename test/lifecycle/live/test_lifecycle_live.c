#include "openssl_provider_sdk/ops_provider.h"
#include "../state.h"

#include <openssl/crypto.h>
#include <openssl/provider.h>
#include <stdio.h>

#define CHECK(condition) \
    do \
    { \
        if (!(condition)) \
        { \
            fprintf(stderr, "Check failed at line %d: %s\n", __LINE__, #condition); \
            goto cleanup; \
        } \
    } while (0)

int main(int argc, char **argv)
{
    OSSL_LIB_CTX *a = NULL;
    OSSL_LIB_CTX *b = NULL;
    OSSL_PROVIDER *pa = NULL;
    OSSL_PROVIDER *pb = NULL;
    ops_test_user_state *sa;
    ops_test_user_state *sb;
    int result = 1;

    CHECK(argc == 3);
    a = OSSL_LIB_CTX_new();
    b = OSSL_LIB_CTX_new();
    CHECK(a != NULL && b != NULL);
    CHECK(OSSL_PROVIDER_set_default_search_path(a, argv[1]));
    CHECK(OSSL_PROVIDER_set_default_search_path(b, argv[1]));
    pa = OSSL_PROVIDER_load(a, argv[2]);
    pb = OSSL_PROVIDER_load(b, argv[2]);
    CHECK(pa != NULL && pb != NULL);
    sa = ops_provider_get_user_data(OSSL_PROVIDER_get0_provider_ctx(pa));
    sb = ops_provider_get_user_data(OSSL_PROVIDER_get0_provider_ctx(pb));
    CHECK(sa != NULL && sb != NULL && sa != sb);
    CHECK(sa->value == 42 && sb->value == 42);
    sa->value = 7;
    CHECK(sb->value == 42);
    CHECK(OSSL_PROVIDER_unload(pa));
    pa = NULL;
    OSSL_LIB_CTX_free(a);
    a = NULL;
    CHECK(sb->value == 42);
    CHECK(ops_provider_get_user_data(OSSL_PROVIDER_get0_provider_ctx(pb)) == sb);
    result = 0;

cleanup:
    OSSL_PROVIDER_unload(pa);
    OSSL_PROVIDER_unload(pb);
    OSSL_LIB_CTX_free(a);
    OSSL_LIB_CTX_free(b);
    return result;
}
