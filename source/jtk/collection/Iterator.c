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

// Thursday, July 12, 2018

#include <jtk/collection/Iterator.h>

/*******************************************************************************
 * Iterator                                                                    *
 *******************************************************************************/

/* Constructor */

jtk_Iterator_t* jtk_Iterator_new() {
    return jtk_Iterator_newWithBundle(NULL);
}

jtk_Iterator_t* jtk_Iterator_newWithBundle(void* bundle) {
    jtk_Iterator_t* iterator = jtk_Memory_allocate(jtk_Iterator_t, 1);
    iterator->m_getNext = NULL;
    iterator->m_hasNext = NULL;
    iterator->m_destroy = NULL;
    iterator->m_bundle = bundle;

    return iterator;
}

/* Destructor */

/* An iterator always owns the object which created it. Therefore, destroying
 * the iterator is sufficient. This causes the iterator to destroy the origin
 * object.
 */
void jtk_Iterator_delete(jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    if (iterator->m_destroy != NULL) {
        iterator->m_destroy(iterator->m_bundle);
    }
    jtk_Memory_deallocate(iterator);
}

/* Bundle */

void* jtk_Iterator_getBundle(jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return iterator->m_bundle;
}

/* Next */

void* jtk_Iterator_getNext(jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    jtk_Assert_assertTrue(jtk_Iterator_hasNext(iterator), "The specified iterator is exhausted.");

    return (iterator->m_getNext != NULL)? iterator->m_getNext(iterator->m_bundle) : NULL;
}

bool jtk_Iterator_hasNext(jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return (iterator->m_hasNext != NULL)? iterator->m_hasNext(iterator->m_bundle) : false;
}