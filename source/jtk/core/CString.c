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

#include <jtk/core/CString.h>
#include <jtk/collection/array/Arrays.h>
#include <jtk/core/StringBuilder.h>

/*******************************************************************************
 * CCString                                                                      *
 *******************************************************************************/

// Constructor

uint8_t* jtk_CString_new(const uint8_t* string) {
    return jtk_CString_newEx(string, jtk_CString_getSize(string));
}

uint8_t* jtk_CString_newEx(const uint8_t* string, int32_t size) {
    uint8_t* result = jtk_Memory_allocate(uint8_t, size + 1);
    int32_t i;
    for (i = 0; i < size; i++) {
        result[i] = string[i];
    }
    result[size] = '\0';
    return result;
}

uint8_t* jtk_CString_make(const uint8_t* string, int32_t* size) {
    if (*size < 0) {
        *size = jtk_CString_getSize(string);
    }

    uint8_t* result = jtk_Memory_allocate(uint8_t, *size + 1);
    int32_t i;
    for (i = 0; i < *size; i++) {
        result[i] = string[i];
    }
    result[i] = '\0';
    return result;
}

// Destructor

void jtk_CString_delete(uint8_t* string) {
    jtk_Memory_deallocate(string);
}

// Compare

int32_t jtk_CString_compare(const uint8_t* string1,
    const uint8_t* string2) {
    int32_t i = 0;
    int32_t result;
    while (true) {
        char c1 = string1[i];
        char c2 = string2[i];
        if (c1 == '\0' && c2 == '\0') {
            result = 0;
            break;
        }

        if (c1 == '\0') {
            result = -1;
            break;
        }

        if (c2 == '\0') {
            result = 1;
            break;
        }

        if (c1 != c2) {
            result = c1 - c2;
            break;
        }

        i++;
    }

    return result;
}

int32_t jtk_CString_comparePtr(const uint8_t** string1,
    const uint8_t** string2) {
    return jtk_CString_compare(*string1, *string2);
}

int32_t jtk_CString_compareEx(const uint8_t* string1, int32_t size1,
    const uint8_t* string2, int32_t size2) {
    int limit = jtk_Integer_min(size1, size2);

    int k = 0;
    int32_t result = size1 - size2;
    while (k < limit) {
        char c1 = string1[k];
        char c2 = string2[k];
        if (c1 != c2) {
            result = c1 - c2;
            break;
        }
        k++;
    }
    return result;
}

// Equals

bool jtk_CString_equals(const uint8_t* string1, int32_t size1, const uint8_t* string2, int32_t size2) {
    if (string1 == string2) {
        return 1;
    }
    if ((string1 == NULL) ^ (string2 == NULL)) {
        return false;
    }
    if (size1 == size2) {
        int32_t i;
        for (i = size1 - 1; i >= 0; i--) {
            if (string1[i] != string2[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

// Hash

int32_t jtk_CString_hash(const uint8_t* string) {
    /* Horner's method */
    int32_t hashCode = 0;
    if (string != NULL) {
        int32_t i = 0;
        while (string[i] != '\0') {
            /* Multiplying 31, a prime number, ensures that the bits of all
             * the characters play a role.
             */
            hashCode = 31 * hashCode + string[i];
            i++;
        }
    }
    return hashCode;
}

int32_t jtk_CString_hashEx(const uint8_t* string, int32_t size) {
    jtk_Assert_assertObject(string, "The specified string is null.");

    int32_t hashCode = 0;
    for (int32_t i = 0; i < size; i++) {
        /* Multiplying 31, a prime number, ensures that the bits of all
         * the characters play a role.
         */
        hashCode = 31 * hashCode + string[i];
    }
    return hashCode;
}

// Join

uint8_t* jtk_CString_join(const uint8_t* value1,
    const uint8_t* value2, int32_t* resultSize) {
    return jtk_CString_joinEx(value1, -1, value2, -1, resultSize);
}

uint8_t* jtk_CString_joinEx(const uint8_t* value1, int32_t size1,
    const uint8_t* value2, int32_t size2, int32_t* resultSize) {
    jtk_Assert_assertObject(value1, "The specified first string is null.");
    jtk_Assert_assertObject(value2, "The specified second string is null.");

    jtk_StringBuilder_t* builder = jtk_StringBuilder_new();
    jtk_StringBuilder_appendEx_z(builder, value1, size1);
    jtk_StringBuilder_appendEx_z(builder, value2, size2);

    uint8_t* result = jtk_StringBuilder_toCString(builder, resultSize);

    jtk_StringBuilder_delete(builder);

    return result;
}

/* If the specified size is negative for a string entry, that particular string
 * is considered as null-terminated. The jtk_CString_getSize() function is invoked
 * against that string to determine its size.
 *
 * If a string is null, then the string literal "null" is appended.
 */
uint8_t* jtk_CString_joinAll(const uint8_t** strings, int32_t* sizes,
    int32_t count, int32_t* resultSize) {
    jtk_Assert_assertObject(strings, "The specified strings array is null.");
    jtk_Assert_assertObject(sizes, "The specified sizes array is null.");
    jtk_Assert_assertTrue(count >= 0, "The specified count is invalid.");

    uint8_t* result = NULL;
    if (count > 0) {
        jtk_StringBuilder_t* builder = jtk_StringBuilder_new();
        int32_t i;
        for (i = 0; i < count; i++) {
            jtk_StringBuilder_appendEx_z(builder, strings[i], sizes[i]);
        }
        result = jtk_StringBuilder_toCString(builder, resultSize);
        jtk_StringBuilder_delete(builder);
    }
    else {
        if (resultSize != NULL) {
            *resultSize = 0;
        }
    }

    return result;
}

/* If the specified size is negative for a string entry, that particular string
 * is considered as null-terminated. The jtk_CString_getSize() function is invoked
 * against that string to determine its size.
 *
 * If a string is null, then the string literal "null" is appended.
 *
 * The prefix, the suffix, and the separator parameters remain unused if the
 * number strings specified to join is zero.
 */
uint8_t* jtk_CString_joinAllEx(const uint8_t** strings, int32_t* sizes,
    int32_t count, const uint8_t* prefix, int32_t prefixSize, const uint8_t* suffix,
    int32_t suffixSize, const uint8_t* separator, int32_t separatorSize,
    int32_t* resultSize) {
    jtk_Assert_assertObject(strings, "The specified strings array is null.");
    jtk_Assert_assertObject(sizes, "The specified sizes array is null.");
    jtk_Assert_assertTrue(count >= 0, "The specified count is invalid.");

    uint8_t* result = NULL;

    if (count > 0) {
        jtk_StringBuilder_t* builder = jtk_StringBuilder_new();
        jtk_StringBuilder_appendEx_z(builder, prefix, prefixSize);
        int32_t i;
        for (i = 0; i < count; i++) {
            jtk_StringBuilder_appendEx_z(builder, strings[i], sizes[i]);
            if (i + 1 < count) {
                jtk_StringBuilder_appendEx_z(builder, separator, separatorSize);
            }
        }
        jtk_StringBuilder_appendEx_z(builder, suffix, suffixSize);
        result = jtk_StringBuilder_toCString(builder, resultSize);
        jtk_StringBuilder_delete(builder);
    }
    else {
        if (resultSize != NULL) {
            *resultSize = 0;
        }
    }

    return result;
}

// Size

int32_t jtk_CString_getSize(const uint8_t* string) {
    int32_t i = 0;
    while (string[i++] != '\0');
    return i - 1;
}

// Null Terminate

uint8_t* jtk_CString_nullTerminate(uint8_t* string, int32_t size) {
    jtk_Assert_assertObject(string, "The specified string is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    uint8_t* result = jtk_Memory_allocate(uint8_t, size + 1);
    jtk_Arrays_copy_b((int8_t*)string, size, (int8_t*)result, size);
    result[size] = '\0';

    return result;
}