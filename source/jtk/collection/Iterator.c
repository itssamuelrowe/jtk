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