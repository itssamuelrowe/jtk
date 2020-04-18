/*
 * Copyright 2017-2020 Samuel Rowe
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

// Tuesday, March 17, 2020

#ifndef JTK_COLLECTION_ARRAY_BYTE_ARRAY_H
#define JTK_COLLECTION_ARRAY_BYTE_ARRAY_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * ByteArray                                                                   *
 *******************************************************************************/

/**
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_ByteArray_t {
    int8_t* m_values;
    int32_t m_size;
};

/**
 * @memberof ByteArray
 */
typedef struct jtk_ByteArray_t jtk_ByteArray_t;

jtk_ByteArray_t* jtk_ByteArray_fromRawArray(int8_t* array, int32_t size);
void jtk_ByteArray_delete(jtk_ByteArray_t* array);

#endif /* JTK_COLLECTION_ARRAY_BYTE_ARRAY_H */