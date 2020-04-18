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

// Monday, May 27, 2019

#include <jtk/core/Error.h>
#include <jtk/core/System.h>
#include <jtk/io/InputStreamHelper.h>

/*******************************************************************************
 * InputStreamHelper                                                           *
 *******************************************************************************/

// Read Fully

bool jtk_InputStreamHelper_readFully(jtk_InputStream_t* stream, uint8_t* buffer,
    int32_t size) {
    jtk_Assert_assertObject(stream, "The specified input stream is null.");
    jtk_Assert_assertObject(buffer, "The specified buffer is null.");

    return jtk_InputStreamHelper_readFullyEx(stream, buffer, size, 0, size);
}

bool jtk_InputStreamHelper_readFullyEx(jtk_InputStream_t* stream, uint8_t* buffer,
    int32_t size, int32_t index, int32_t limit) {
    jtk_Assert_assertObject(stream, "The specified input stream is null.");
    jtk_Assert_assertObject(buffer, "The specified buffer is null.");
    jtk_Assert_assertTrue(size > 0, "The specified buffer is invalid.");
    jtk_Assert_assertTrue(index >= 0, "The specified index is invalid.");
    jtk_Assert_assertTrue(limit > 0, "The specified limit is invalid.");

    bool result = true;
    int32_t n = 0;
    while (n < limit) {
        int32_t count = jtk_InputStream_readBytesEx(stream, buffer, size,
            index + n, size - n);
        if (count < 0) {
            jtk_System_t* system = jtk_System_getInstance();
            jtk_System_setErrorEx(system, JTK_ERROR_END_OF_STREAM,
                JTK_ERROR_FLAG_SOURCE_LIBRARY);
            result = false;
        }
        n += count;
    }
    return result;
}

jtk_ByteArray_t* jtk_InputStreamHelper_toByteArray(jtk_InputStream_t* stream) {
    uint8_t* result = jtk_Memory_allocate(uint8_t, 1024);
    int32_t size = 1024;
    int32_t index = 0;
    while (true) {
        int32_t count = jtk_InputStream_readBytesEx(stream, result, size,
            index, size);

        if (count <= 0) {
            break;
        }

        index += count;

        if (index >= (int32_t)(size * 0.85f)) {
            uint8_t* temporary = result;
            int32_t newSize = size * 2;
            result = jtk_Arrays_copyOfEx_b(result, size, newSize, 0, false);
            jtk_Memory_deallocate(temporary);

            size = newSize;
        }
    }
    jtk_ByteArray_t* array = (index == 0)? NULL : jtk_ByteArray_fromRawArray(result, index);

    jtk_Memory_deallocate(result);

    return array;
}
