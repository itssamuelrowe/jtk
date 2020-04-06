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

// Friday, June 08, 2018

#include <jtk/collection/map/HashMapEntry.h>

/*******************************************************************************
 * HashMapEntry                                                                *
 *******************************************************************************/

// Constructor

jtk_HashMapEntry_t* jtk_HashMapEntry_new(void* key, void* value,
    int32_t hashCode, jtk_HashMapEntry_t* next) {
    jtk_HashMapEntry_t* entry = jtk_Memory_allocate(jtk_HashMapEntry_t, 1);
    entry->m_key = key;
    entry->m_value = value;
    entry->m_hashCode = hashCode;
    entry->m_next = next;
    return entry;
}

// Destructor

void jtk_HashMapEntry_delete(jtk_HashMapEntry_t* entry) {
    jtk_Assert_assertObject(entry, "The specified entry is null.");

    jtk_Memory_deallocate(entry);
}

// Hash Code

int32_t jtk_HashMapEntry_getHashCode(jtk_HashMapEntry_t* entry) {
    jtk_Assert_assertObject(entry, "The specified entry is null.");

    return entry->m_hashCode;
}

// Key

void* jtk_HashMapEntry_getKey(jtk_HashMapEntry_t* entry) {
    jtk_Assert_assertObject(entry, "The specified entry is null.");

    return entry->m_key;
}

// Value

void* jtk_HashMapEntry_getValue(jtk_HashMapEntry_t* entry) {
    jtk_Assert_assertObject(entry, "The specified entry is null.");

    return entry->m_value;
}