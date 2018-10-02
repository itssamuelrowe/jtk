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

// Tuesday, July 03, 2018

#include <jtk/collection/CollectionHelper.h>
#include <jtk/collection/list/ArrayList.h>
#include <jtk/collection/list/DoublyLinkedList.h>

/*******************************************************************************
 * CollectionHelper                                                            *
 *******************************************************************************/

jtk_Iterator_t* jtk_CollectionHelper_getIterator(jtk_CollectionType_t type,
    void* collection) {
    jtk_Assert_assertObject(collection, "The specified collection is null.");

    jtk_Iterator_t* iterator = NULL;
    switch (type) {
        case JTK_COLLECTION_ARRAY_LIST: {
            jtk_ArrayList_t* other = (jtk_ArrayList_t*)collection;
            iterator = jtk_ArrayList_getIterator(other);

            break;
        }

        case JTK_COLLECTION_DOUBLY_LINKED_LIST: {
            jtk_DoublyLinkedList_t* other = (jtk_DoublyLinkedList_t*)collection;
            iterator = jtk_DoublyLinkedList_getIterator(other);

            break;
        }

        default: {
            /* This is a handy hack. Basically, the library does not print any
             * error if the specified collection type is invalid. It forces
             * an assertion failure.
             */
            jtk_Assert_assertTrue(false, "The specified collection type is invalid.");

            break;
        }
    }
    return iterator;
}
