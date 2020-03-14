/*
 * Copyright 2018-2019 OneCube
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

jtk_String_t* jtk_String_wrap(uint8_t* value, int32_t size, int32_t hashCode);

/**
 * @memberof String
 */
jtk_String_t* jtk_String_new(const uint8_t* value);

/**
 * @memberof String
 */
jtk_String_t* jtk_String_newEx(const uint8_t* value, int32_t size);

jtk_String_t* jtk_String_newFromJoin(const uint8_t* value1, const uint8_t* value2);

jtk_String_t* jtk_String_newFromJoinEx(const uint8_t* value1, int32_t size1,
    const uint8_t* value2, int32_t size2);

jtk_String_t* jtk_String_fromJoin(const uint8_t** strings, int32_t* sizes, int32_t count);

jtk_String_t* jtk_String_fromJoinEx(const uint8_t** strings, int32_t* sizes,
    int32_t count, const uint8_t* prefix, int32_t prefixSize, const uint8_t* suffix,
    int32_t suffixSize, const uint8_t* separator, int32_t separatorSize);

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

// Value

/**
 * @memberof String
 */
uint8_t* jtk_String_getValue(jtk_String_t* string);

#endif /* JTK_CORE_STRING_H */