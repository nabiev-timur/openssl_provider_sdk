#include "openssl_provider_sdk/ops_algorithm.h"

#include <stdio.h>

int main(void)
{
    const OSSL_ALGORITHM *algorithms = ops_digest_algorithms();

    if (algorithms == NULL
        || algorithms != ops_digest_algorithms()
        || algorithms[0].algorithm_names != NULL
        || algorithms[0].property_definition != NULL
        || algorithms[0].implementation != NULL
        || algorithms[0].algorithm_description != NULL)
    {
        fprintf(stderr, "Empty registry must contain a single zero terminator\n");
        return 1;
    }

    return 0;
}
