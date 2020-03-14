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

/*******************************************************************************
 * CCString                                                                      *
 *******************************************************************************/

// Constructor

uint8_t* jtk_CString_new(const uint8_t* string) {
    return jtk_CString_newWithSize(string, jtk_CString_getSize(string));
}

uint8_t* jtk_CString_newWithSize(const uint8_t* string, int32_t size) {
    uint8_t* result = jtk_Memory_allocate(uint8_t, size + 1);
    int32_t i;
    for (i = 0; i < size; i++) {
        result[i] = string[i];
    }
    result[size] = '\0';
    return result;
}

// Destructor

void jtk_CString_delete(uint8_t* string) {
    jtk_Memory_deallocate(string);
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
        for (i = 0; i < size1; i++) {
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