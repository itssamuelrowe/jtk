// Saturday, November 04, 2017

#ifndef JTK_CORE_C_STRING_H
#define JTK_CORE_C_STRING_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * String                                                                      *
 *******************************************************************************/

/**
 * @memberof String
 */
uint8_t* jtk_CString_new(const uint8_t* string);

/**
 * @memberof String
 */
uint8_t* jtk_CString_newWithSize(const uint8_t* string, int32_t size);

/**
 * @memberof String
 */
void jtk_CString_delete(uint8_t* string);

/**
 * @memberof String
 */
bool jtk_CString_equals(const uint8_t* string1, int32_t size1, const uint8_t* string2, int32_t size2);

/**
 * @memberof String
 */
int32_t jtk_CString_getLength(const uint8_t* string);

/**
 * @memberof String
 */
int32_t jtk_CString_hash(const uint8_t* string);

// Null Terminate

uint8_t* jtk_CString_nullTerminate(uint8_t* string, int32_t size);

#endif /* JTK_CORE_C_STRING_H */