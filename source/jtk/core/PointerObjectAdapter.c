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

// Monday, July 30, 2018

#include <jtk/core/PointerObjectAdapter.h>

/*******************************************************************************
 * PointerObjectAdapter                                                        *
 *******************************************************************************/

static jtk_ObjectAdapter_t s_pointerObjectAdapter = {
    (jtk_ObjectAdapter_CompareFunction_t)jtk_PointerObjectAdapter_compare,
    (jtk_ObjectAdapter_EqualsFunction_t)jtk_PointerObjectAdapter_equals,
    (jtk_ObjectAdapter_HashFunction_t)jtk_PointerObjectAdapter_hash
};

jtk_ObjectAdapter_t* jtk_PointerObjectAdapter_getInstance() {
    return &s_pointerObjectAdapter;
}

int32_t jtk_PointerObjectAdapter_compare(const void* pointer1, const void* pointer2) {
    return (pointer1 > pointer2)? -1 : ((pointer1 == pointer2)? 0 : 1);
}

bool jtk_PointerObjectAdapter_equals(const void* pointer1, const void* pointer2) {
    return pointer1 == pointer2;
}

int32_t jtk_PointerObjectAdapter_hash(const void* pointer) {
    // TODO: For 64 bit pointers!
    return (intptr_t)pointer;
}