// Saturday, May 11, 2019

#ifndef JTK_CORE_STRING_H
#define JTK_CORE_STRING_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * String                                                                      *
 *******************************************************************************/

/**
 * @class String
 * @ingroup jtk_core
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
struct jtk_String_t {
    uint8_t* m_value;
    int32_t m_size;
    int32_t m_hashCode;
};

/**
 * @memberof String
 */
typedef struct jtk_String_t jtk_String_t;

// Constructor

/**
 * @memberof String
 */
jtk_String_t* jtk_String_new(const uint8_t* value);

jtk_String_t* jtk_String_newFromJoin(const uint8_t* value1, const uint8_t* value2);

jtk_String_t* jtk_String_newFromJoinEx(const uint8_t* value1, int32_t size1,
    const uint8_t* value2, int32_t size2);

/**
 * @memberof String
 */
jtk_String_t* jtk_String_newEx(const uint8_t* value, int32_t size);

// Destructor

/**
 * @memberof String
 */
void jtk_String_delete(jtk_String_t* string);

// Clone

/**
 * @memberof String
 */
jtk_String_t* jtk_String_clone(jtk_String_t* string);

// Equals

/**
 * @memberof String
 */
bool jtk_String_equals(jtk_String_t* string, jtk_String_t* other);

// Hash

/**
 * @memberof String
 */
int32_t jtk_String_hash(jtk_String_t* string);

// Size

/**
 * @memberof String
 */
int32_t jtk_String_getSize(jtk_String_t* string);

#endif /* JTK_CORE_STRING_H */