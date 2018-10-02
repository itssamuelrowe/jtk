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

// Monday, February 26, 2018

#include <jtk/core/String.h>
#include <jtk/core/ObjectAdapter.h>
#include <jtk/core/StringObjectAdapter.h>

/*******************************************************************************
 * StringObjectAdapter                                                         *
 *******************************************************************************/

static jtk_ObjectAdapter_t s_stringObjectAdapter = {
    NULL, // TODO: compare
    jtk_StringObjectAdapter_equals,
    jtk_StringObjectAdapter_hash
};

jtk_ObjectAdapter_t* jtk_StringObjectAdapter_getInstance() {
    return &s_stringObjectAdapter;
}

bool jtk_StringObjectAdapter_equals(const uint8_t* string1, const uint8_t* string2) {
    int32_t string1Length = jtk_String_getLength(string1);
    int32_t string2Length = jtk_String_getLength(string2);
    return jtk_String_equals(string1, string1Length, string2, string2Length);
}

int32_t jtk_StringObjectAdapter_hash(const uint8_t* string) {
    /* Horner's method */
    int32_t hashCode = 0;
    int32_t i = 0;
    while (string[i] != '\0') {
        /* Multiplying 31, a prime number, ensures that the bits of all
         * the characters play a role.
         */
        hashCode = 31 * hashCode + string[i];
        i++;
    }
    return hashCode;
}