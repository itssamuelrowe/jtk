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