#ifndef OPS_DEFINES_H_
#define OPS_DEFINES_H_

/**
 * @brief Marks a declaration as part of the public SDK API.
 * @note Documentation-only annotation; deliberately expands to nothing.
 *     It does not change visibility, calling convention, or symbol linkage.
 */
#define OPS_API

/**
 * @brief Marks a hook whose SDK default can be replaced by a user definition.
 * @note Documentation-only annotation; deliberately expands to nothing.
 *     It does not make the declaration or user definition weak. Actual weak
 *     linkage (or its platform equivalent) belongs only to the SDK default.
 */
#define OPS_WEAK

#endif
