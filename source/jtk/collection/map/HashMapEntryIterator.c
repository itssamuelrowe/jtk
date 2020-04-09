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

// Monday, July 23, 2018

#include <jtk/collection/map/HashMapEntryIterator.h>

/*******************************************************************************
 * HashMapEntryIterator                                                        *
 *******************************************************************************/

/* Constructor */

jtk_HashMapEntryIterator_t* jtk_HashMapEntryIterator_new(jtk_HashMap_t* map) {
    jtk_HashMapEntryIterator_t* hashMapEntryIterator = jtk_Memory_allocate(jtk_HashMapEntryIterator_t, 1);

    jtk_Iterator_t* iterator = jtk_Iterator_new();
    iterator->m_destroy = (jtk_Iterator_DestroyFunction_t)jtk_HashMapEntryIterator_destroy;
    iterator->m_getNext = (jtk_Iterator_GetNextFunction_t)jtk_HashMapEntryIterator_getNext;
    iterator->m_hasNext = (jtk_Iterator_HasNextFunction_t)jtk_HashMapEntryIterator_hasNext;
    iterator->m_bundle = hashMapEntryIterator;

    int32_t index = 0;
    jtk_HashMapEntry_t* next = NULL;

    if (map->m_size > 0) {
        do {
            next = map->m_table[index++];
        }
        while ((index < map->m_tableSize) && (next == NULL));
    }

    hashMapEntryIterator->m_map = map;
    hashMapEntryIterator->m_iterator = iterator;
    hashMapEntryIterator->m_index = index;
    hashMapEntryIterator->m_next = next;

    return hashMapEntryIterator;
}

/* Destructor */

void jtk_HashMapEntryIterator_delete(jtk_HashMapEntryIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    if (iterator->m_iterator != NULL) {
        iterator->m_iterator->m_destroy = NULL;
        jtk_Iterator_delete(iterator->m_iterator);
    }
    jtk_Memory_deallocate(iterator);
}

/* Destroy */

void jtk_HashMapEntryIterator_destroy(jtk_HashMapEntryIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    iterator->m_iterator = NULL;
    jtk_HashMapEntryIterator_delete(iterator);
}

/* Iterator */

jtk_Iterator_t* jtk_HashMapEntryIterator_getIterator(jtk_HashMapEntryIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return iterator->m_iterator;
}

/* Next */

bool jtk_HashMapEntryIterator_hasNext(jtk_HashMapEntryIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return iterator->m_next != NULL;
}

void* jtk_HashMapEntryIterator_getNext(jtk_HashMapEntryIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    jtk_Assert_assertTrue(jtk_HashMapEntryIterator_hasNext(iterator), "The specified iterator is empty.");

    jtk_HashMapEntry_t* entry = iterator->m_next;
    iterator->m_next = entry->m_next;
    if (iterator->m_next == NULL) {
        int32_t index = iterator->m_index + 1;
        while ((index < iterator->m_map->m_tableSize) &&
            (iterator->m_next == NULL)) {
            iterator->m_next = iterator->m_map->m_table[index++];
        }
        iterator->m_index = index - 1;
    }
    return entry;
}
