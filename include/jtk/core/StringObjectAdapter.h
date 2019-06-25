// Monday, February 26, 2018

#ifndef JTK_CORE_STRING_OBJECT_ADAPTER_H
#define JTK_CORE_STRING_OBJECT_ADAPTER_H

#include <jtk/core/ObjectAdapter.h>
#include <jtk/core/String.h>

/*******************************************************************************
 * StringObjectAdapter                                                         *
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
jtk_ObjectAdapter_t* jtk_StringObjectAdapter_getInstance();

/**
 * @memberof jtk_core
 */
bool jtk_StringObjectAdapter_equals(jtk_String_t* string1, jtk_String_t* string2);

/**
 * @memberof jtk_core
 */
int32_t jtk_StringObjectAdapter_hash(jtk_String_t* string);

#endif /* JTK_CORE_STRING_OBJECT_ADAPTER_H */