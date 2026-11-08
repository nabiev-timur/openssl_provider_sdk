#ifndef OPS_PROVIDER_H_
#define OPS_PROVIDER_H_

#include "ops_defines.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Returns the borrowed user pointer associated with provctx.
 * @param provctx Unchanged context received from an SDK provider callback.
 * @return User pointer, or NULL if none has been assigned (also for NULL provctx).
 * @note The SDK never frees this pointer. Initialization and cleanup own its
 *     lifetime. Available during user init and cleanup; do not use after teardown.
 *     Synchronizing mutable user state is the user's responsibility.
 */
OPS_API void *ops_provider_get_user_data(void *provctx);

/**
 * @brief Initializes optional user state after core services are ready.
 * @param provctx SDK context; core wrappers and the getter are already usable.
 * @param user_data Borrowed output slot, initially holding NULL.
 *     Assign your user pointer here; do not retain the slot's address.
 * @return 1 on success, 0 on failure.
 * @note Supply an ordinary external definition in your provider source to
 *     override the SDK default, which sets *user_data to NULL and succeeds.
 *     The header declaration intentionally has no weak attribute.
 *     On failure, release partial resources yourself: cleanup is not called.
 */
OPS_WEAK int ops_provider_user_init(void *provctx, void **user_data);

/**
 * @brief Releases optional user state during provider teardown.
 * @param provctx Same SDK context used by init; core services remain available.
 * @param user_data Pointer assigned by successful init, possibly NULL.
 * @note Called exactly once after successful init, before SDK context release.
 *     Supply an ordinary external definition to override the no-op default.
 *     The SDK does not free user_data automatically. Pair allocations with
 *     the matching allocator and synchronize access to mutable state yourself.
 *     Hooks in archives require explicit object inclusion; see the lifecycle guide.
 */
OPS_WEAK void ops_provider_user_cleanup(void *provctx, void *user_data);

#ifdef __cplusplus
}
#endif

#endif
