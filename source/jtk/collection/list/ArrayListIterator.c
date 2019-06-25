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

#include <jtk/collection/list/ArrayList.h>
#include <jtk/collection/list/ArrayListIterator.h>

/*******************************************************************************
 * ArrayListIterator                                                           *
 *******************************************************************************/

/* Constructor */

jtk_ArrayListIterator_t* jtk_ArrayListIterator_new(jtk_ArrayList_t* list) {
    jtk_ArrayListIterator_t* arrayListIterator = jtk_Memory_allocate(jtk_ArrayListIterator_t, 1);

    jtk_Iterator_t* iterator = jtk_Iterator_new();
    iterator->m_destroy = (jtk_Iterator_DestroyFunction_t)jtk_ArrayListIterator_destroy;
    iterator->m_getNext = (jtk_Iterator_GetNextFunction_t)jtk_ArrayListIterator_getNext;
    iterator->m_hasNext = (jtk_Iterator_HasNextFunction_t)jtk_ArrayListIterator_hasNext;
    iterator->m_bundle = arrayListIterator;

    arrayListIterator->m_list = list;
    arrayListIterator->m_index = 0;
    arrayListIterator->m_iterator = iterator;

    return arrayListIterator;
}

/* Destructor */

void jtk_ArrayListIterator_delete(jtk_ArrayListIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    if (iterator->m_iterator != NULL) {
        iterator->m_iterator->m_destroy = NULL;
        jtk_Iterator_delete(iterator->m_iterator);
    }
    jtk_Memory_deallocate(iterator);
}

/* Destroy */

void jtk_ArrayListIterator_destroy(jtk_ArrayListIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    iterator->m_iterator = NULL;
    jtk_ArrayListIterator_delete(iterator);
}

/* Iterator */

jtk_Iterator_t* jtk_ArrayListIterator_getIterator(jtk_ArrayListIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return iterator->m_iterator;
}

/* Next */

bool jtk_ArrayListIterator_hasNext(jtk_ArrayListIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return iterator->m_index < iterator->m_list->m_size;
}

void* jtk_ArrayListIterator_getNext(jtk_ArrayListIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    jtk_Assert_assertTrue(jtk_ArrayListIterator_hasNext(iterator), "The specified iterator is empty.");

    return iterator->m_list->m_values[iterator->m_index++];
}