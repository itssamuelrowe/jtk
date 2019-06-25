// Saturday, May 25, 2019

#ifndef JTK_CORE_C_STRING_OBJECT_ADAPTER_H
#define JTK_CORE_C_STRING_OBJECT_ADAPTER_H

#include <jtk/core/ObjectAdapter.h>

/*******************************************************************************
 * CStringObjectAdapter                                                        *
 *******************************************************************************/

/**
 * @class StringObjectAdapter
 * @ingroup jtk_core
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
 
/**
 * @memberof jtk_core
 */
jtk_ObjectAdapter_t* jtk_CStringObjectAdapter_getInstance();

/**
 * @memberof jtk_core
 */
bool jtk_CStringObjectAdapter_equals(const uint8_t* string1, const uint8_t* string2);

/**
 * @memberof jtk_core
 */
int32_t jtk_CStringObjectAdapter_hash(const uint8_t* string);

#endif /* JTK_CORE_C_STRING_OBJECT_ADAPTER_H */