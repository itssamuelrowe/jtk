/*
 *                              Jez Toolkit (JTK)
 *     Copyright (C) 2018 OneCube Software Solutions. All rights reserved.
 *
 * This file is part of Jez Toolkit Free Edition, version 1.0.
 *
 * See the file "LICENSE" included in the distribution for the terms and conditions,
 * or visit http://www.onecube.in/jtk/free-license.
 *
 * IMPORTANT NOTE: You may NOT copy the content of this file, either partially
 * or fully, into your source code.
 */

// Saturday, November 04, 2017

#include <jtk/core/String.h>

/*******************************************************************************
 * String                                                                      *
 *******************************************************************************/

uint8_t* jtk_String_new(const uint8_t* string) {
    return jtk_String_newWithSize(string, jtk_String_getLength(string));
}

uint8_t* jtk_String_newWithSize(const uint8_t* string, int32_t size) {
    uint8_t* result = jtk_Memory_allocate(uint8_t, size + 1);
    int32_t i;
    for (i = 0; i < size; i++) {
        result[i] = string[i];
    }
    result[size] = '\0';
    return result;
}

void jtk_String_delete(uint8_t* string) {
    jtk_Memory_deallocate(string);
}

bool jtk_String_equals(const uint8_t* string1, int32_t size1, const uint8_t* string2, int32_t size2) {
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

int32_t jtk_String_getLength(const uint8_t* string) {
    int32_t i = 0;
    while (string[i++] != '\0');
    return i - 1;
}