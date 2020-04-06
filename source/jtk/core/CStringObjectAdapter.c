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

// Monday, February 26, 2018

#include <jtk/core/CString.h>
#include <jtk/core/ObjectAdapter.h>
#include <jtk/core/CStringObjectAdapter.h>

/*******************************************************************************
 * CStringObjectAdapter                                                         *
 *******************************************************************************/

static jtk_ObjectAdapter_t s_stringObjectAdapter = {
    NULL, // TODO: compare
    (jtk_ObjectAdapter_EqualsFunction_t)jtk_CStringObjectAdapter_equals,
    (jtk_ObjectAdapter_HashFunction_t)jtk_CStringObjectAdapter_hash
};

jtk_ObjectAdapter_t* jtk_CStringObjectAdapter_getInstance() {
    return &s_stringObjectAdapter;
}

bool jtk_CStringObjectAdapter_equals(const uint8_t* string1, const uint8_t* string2) {
    int32_t i = 0;
    bool result = true;
    while (true) {
        if (string1[i] != string2[i]) {
            result = false;
            break;
        }
        if (string1[i] == '\0' || string2[i] == '\0') {
            break;
        }
        i++;
    }
    return result;
    /*int32_t string1Length = jtk_CString_getSize(string1);
    int32_t string2Length = jtk_CString_getSize(string2);
    return jtk_CString_equals(string1, string1Length, string2, string2Length);
    */
}

int32_t jtk_CStringObjectAdapter_hash(const uint8_t* string) {
    return jtk_CString_hash(string);
}