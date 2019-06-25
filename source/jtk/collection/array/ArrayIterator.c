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

// Friday, July 27, 2018

#include <jtk/collection/array/ArrayIterator.h>

/*******************************************************************************
 * ArrayIterator                                                               *
 *******************************************************************************/

/* Constructor */

jtk_ArrayIterator_t* jtk_ArrayIterator_new(void** array, int32_t size) {
    jtk_ArrayIterator_t* arrayIterator = jtk_Memory_allocate(jtk_ArrayIterator_t, 1);

    jtk_Iterator_t* iterator = jtk_Iterator_new();
    iterator->m_destroy = (jtk_Iterator_DestroyFunction_t)jtk_ArrayIterator_destroy;
    iterator->m_getNext = (jtk_Iterator_GetNextFunction_t)jtk_ArrayIterator_getNext;
    iterator->m_hasNext = (jtk_Iterator_HasNextFunction_t)jtk_ArrayIterator_hasNext;
    iterator->m_bundle = arrayIterator;

    arrayIterator->m_array = array;
    arrayIterator->m_size = size;
    arrayIterator->m_index = 0;
    arrayIterator->m_iterator = iterator;

    return arrayIterator;
}

/* Destructor */

void jtk_ArrayIterator_delete(jtk_ArrayIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    if (iterator->m_iterator != NULL) {
        iterator->m_iterator->m_destroy = NULL;
        jtk_Iterator_delete(iterator->m_iterator);
    }
    jtk_Memory_deallocate(iterator);
}

/* Destroy */

void jtk_ArrayIterator_destroy(jtk_ArrayIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    iterator->m_iterator = NULL;
    jtk_ArrayIterator_delete(iterator);
}

/* Iterator */

jtk_Iterator_t* jtk_ArrayIterator_getIterator(jtk_ArrayIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return iterator->m_iterator;
}

/* Next */

bool jtk_ArrayIterator_hasNext(jtk_ArrayIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return iterator->m_index < (iterator->m_size - 1);
}

void* jtk_ArrayIterator_getNext(jtk_ArrayIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    jtk_Assert_assertTrue(jtk_ArrayIterator_hasNext(iterator), "The specified iterator is empty.");

    return iterator->m_array[iterator->m_index++];
}