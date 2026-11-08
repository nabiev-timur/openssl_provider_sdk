#include "openssl_provider_sdk/ops_algorithm.h"

#include <stdio.h>
#include <string.h>

static int check_dispatch(const OSSL_DISPATCH *dispatch)
{
    static const int expected_ids[] = {
        OSSL_FUNC_DIGEST_NEWCTX,
        OSSL_FUNC_DIGEST_FREECTX,
        OSSL_FUNC_DIGEST_INIT,
        OSSL_FUNC_DIGEST_UPDATE,
        OSSL_FUNC_DIGEST_FINAL,
        OSSL_FUNC_DIGEST_GET_PARAMS,
        OSSL_FUNC_DIGEST_GETTABLE_PARAMS
    };

    unsigned int seen = 0;
    size_t i;
    size_t j;

    if (dispatch == NULL)
    {
        return 0;
    }

    for (i = 0; i < sizeof expected_ids / sizeof expected_ids[0]; ++i)
    {
        if (dispatch[i].function == NULL)
        {
            return 0;
        }

        for (j = 0; j < sizeof expected_ids / sizeof expected_ids[0]; ++j)
        {
            if (dispatch[i].function_id == expected_ids[j])
            {
                break;
            }
        }

        if (j == sizeof expected_ids / sizeof expected_ids[0]
            || (seen & (1u << j)) != 0)
        {
            return 0;
        }

        seen |= 1u << j;
    }

    return dispatch[i].function_id == 0 && dispatch[i].function == NULL;
}

int main(void)
{
    const OSSL_ALGORITHM *algorithms = ops_digest_algorithms();
    unsigned int seen = 0;
    size_t i;

    if (algorithms == NULL || algorithms != ops_digest_algorithms())
    {
        fprintf(stderr, "Registry must return stable non-NULL storage\n");
        return 1;
    }

    /* Порядок разных translation units не является частью контракта. */
    for (i = 0; i < 2; ++i)
    {
        unsigned int bit;

        if (algorithms[i].algorithm_names == NULL)
        {
            fprintf(stderr, "Registry terminated before both algorithms\n");
            return 1;
        }

        if (strcmp(algorithms[i].algorithm_names, "OPS-TEST-SHA256-A") == 0)
        {
            bit = 1;
        }
        else if (strcmp(algorithms[i].algorithm_names, "OPS-TEST-SHA256-B") == 0)
        {
            bit = 2;
        }
        else
        {
            fprintf(stderr, "Unexpected algorithm in registry\n");
            return 1;
        }

        if ((seen & bit) != 0
            || algorithms[i].property_definition == NULL
            || strcmp(algorithms[i].property_definition, "provider=ops-test") != 0
            || algorithms[i].algorithm_description == NULL
            || !check_dispatch(algorithms[i].implementation))
        {
            fprintf(stderr, "Invalid or duplicate algorithm record\n");
            return 1;
        }

        seen |= bit;
    }

    if (seen != 3
        || algorithms[2].algorithm_names != NULL
        || algorithms[2].property_definition != NULL
        || algorithms[2].implementation != NULL
        || algorithms[2].algorithm_description != NULL)
    {
        fprintf(stderr, "Expected exactly two records and a zero terminator\n");
        return 1;
    }

    return 0;
}
