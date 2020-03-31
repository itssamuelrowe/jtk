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

// Saturday, November 04, 2017

#ifndef JTK_CORE_C_STRING_H
#define JTK_CORE_C_STRING_H

#include <jtk/Configuration.h>

#define jtk_stringLiteral(s) (const uint8_t*)(s)

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
uint8_t* jtk_CString_newEx(const uint8_t* string, int32_t size);

/**
 * @memberof String
 */
uint8_t* jtk_CString_make(const uint8_t* string, int32_t* size);

/**
 * @memberof String
 */
void jtk_CString_delete(uint8_t* string);

// Compare

int32_t jtk_CString_compare(const uint8_t* string1,
    const uint8_t* string2);

int32_t jtk_CString_comparePtr(const uint8_t** string1,
    const uint8_t** string2);

int32_t jtk_CString_compareEx(const uint8_t* string1, int32_t size1,
    const uint8_t* string2, int32_t size2);

/**
 * @memberof String
 */
bool jtk_CString_equals(const uint8_t* string1, int32_t size1, const uint8_t* string2, int32_t size2);

// Hash

/**
 * @memberof String
 */
int32_t jtk_CString_hash(const uint8_t* string);

/**
 * @memberof String
 */
int32_t jtk_CString_hashEx(const uint8_t* string, int32_t size);

// Join

uint8_t* jtk_CString_join(const uint8_t* value1,
    const uint8_t* value2, int32_t* resultSize);

uint8_t* jtk_CString_joinEx(const uint8_t* value1, int32_t size1,
    const uint8_t* value2, int32_t size2, int32_t* resultSize);

uint8_t* jtk_CString_joinAll(const uint8_t** strings, int32_t* sizes,
    int32_t count, int32_t* resultSize);

uint8_t* jtk_CString_joinAllEx(const uint8_t** strings, int32_t* sizes,
    int32_t count, const uint8_t* prefix, int32_t prefixSize, const uint8_t* suffix,
    int32_t suffixSize, const uint8_t* separator, int32_t separatorSize,
    int32_t* resultSize);

// Null Terminate

uint8_t* jtk_CString_nullTerminate(uint8_t* string, int32_t size);

// Size

/**
 * @memberof String
 */
int32_t jtk_CString_getSize(const uint8_t* string);

#endif /* JTK_CORE_C_STRING_H */