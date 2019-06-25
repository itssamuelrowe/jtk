// Monday, February 26, 2018

#ifndef JTK_CORE_POINTER_OBJECT_ADAPTER_H
#define JTK_CORE_POINTER_OBJECT_ADAPTER_H

#include <jtk/core/ObjectAdapter.h>

/*******************************************************************************
 * PointerObjectAdapter                                                        *
 *******************************************************************************/

/**
 * @class PointerObjectAdapter
 * @ingroup jtk_core
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */

/**
 * @memberof PointerObjectAdapter
 */
jtk_ObjectAdapter_t* jtk_PointerObjectAdapter_getInstance();

/**
 * @memberof PointerObjectAdapter
 */
int32_t jtk_PointerObjectAdapter_compare(const void* pointer1, const void* pointer2);

/**
 * @memberof PointerObjectAdapter
 */
bool jtk_PointerObjectAdapter_equals(const void* pointer1, const void* pointer2);

/**
 * @memberof PointerObjectAdapter
 */
int32_t jtk_PointerObjectAdapter_hash(const void* pointer);

#endif /* JTK_CORE_POINTER_OBJECT_ADAPTER_H */