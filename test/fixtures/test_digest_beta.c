#include "openssl_provider_sdk/ops_algorithm.h"

#include "test_digest_helpers.h"

OPS_DECLARE_ALGORITHM_DISPATCH(ops_test_beta_dispatch,
    OPS_FUNCTION(OSSL_FUNC_DIGEST_NEWCTX, ops_test_digest_newctx),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_FREECTX, ops_test_digest_freectx),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_INIT, ops_test_digest_init),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_UPDATE, ops_test_digest_update),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_FINAL, ops_test_digest_final),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_GET_PARAMS, ops_test_digest_get_params),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_GETTABLE_PARAMS, ops_test_digest_gettable_params)
);

OPS_DECLARE_DIGEST(ops_test_beta_algorithm,
    "OPS-TEST-SHA256-B",
    "provider=ops-test",
    ops_test_beta_dispatch,
    "Test SHA256 forwarding implementation B"
);
