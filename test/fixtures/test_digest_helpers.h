#ifndef OPS_TEST_DIGEST_HELPERS_H_
#define OPS_TEST_DIGEST_HELPERS_H_

#include <openssl/core_dispatch.h>

/* Реальные SHA256 callbacks тестового провайдера, использующие provider=default. */
OSSL_FUNC_digest_newctx_fn ops_test_digest_newctx;
OSSL_FUNC_digest_freectx_fn ops_test_digest_freectx;
OSSL_FUNC_digest_init_fn ops_test_digest_init;
OSSL_FUNC_digest_update_fn ops_test_digest_update;
OSSL_FUNC_digest_final_fn ops_test_digest_final;
OSSL_FUNC_digest_get_params_fn ops_test_digest_get_params;
OSSL_FUNC_digest_gettable_params_fn ops_test_digest_gettable_params;

#endif /* OPS_TEST_DIGEST_HELPERS_H_ */
