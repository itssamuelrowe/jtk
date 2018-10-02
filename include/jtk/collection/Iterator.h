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

// Saturday, February 24, 2018

#ifndef JTK_COLLECTION_ITERATOR_H
#define JTK_COLLECTION_ITERATOR_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * Iterator                                                                    *
 *******************************************************************************/

/**
 * @memberof Iterator
 */
typedef void (*jtk_Iterator_DestroyFunction_t)(void* bundle);

/**
 * @memberof Iterator
 */
typedef void* (*jtk_Iterator_GetNextFunction_t)(void* bundle);

/**
 * @memberof Iterator
 */
typedef bool (*jtk_Iterator_HasNextFunction_t)(void* bundle);

/**
 * For the sake of this documentation, when we say iterator we mean an object
 * which provides a common iterface for extracting data from a source iterator.
 * A source iterator is an object which extracts data from an underlying source
 * such as array list, doubly-linked list, etc.
 *
 * Every iterator has a lifecycle. Unlike other objects with lifecycle, an 
 * iterator does not notify listeners regarding its states. An iterator is
 * created by a source iterator when the latter is created.
 *
 * When an element is requested (i.e., the next element), the iterator
 * delegates the task of extracting the element to the associated source
 * iterator. Although the source iterator may provide a direct interface
 * to extract elements, we recommend to avoid such designs.
 *
 * The iterator and the source iterator maintain a bidirectional ownership.
 * The pair is always created and destroyed together. The user is required
 * to create only the source iterator. After creation, a bidirectional ownership
 * is established. The user has to destroy either the iterator or the source
 * iterator.
 * 
 * Internally, the iterator and source iterator communicate through the
 * availibility of the `m_destroy` function within the `jtk_Iterator_t`
 * structure. When the destructor of the iterator is invoked, the iterator invokes
 * the `m_destroy` function, if available. The `m_destroy` function
 * unreferences any references made to the iterator from the internal data
 * structure of the source iterator. After which, the destructor is invoked
 * against the source iterator.
 *
 * Similarly, when the destructor of the source iterator is invoked directly, the
 * reference to the `m_destroy` function pointer within the `jtk_Iterator_t`
 * structure is unreferenced before invoking the destructor against the
 * iterator.
 *
 * @class Iterator
 * @ingroup jtk_collection
 * @author Samuel Rowe
 * @since JTK 1.0
 */
struct jtk_Iterator_t {
    jtk_Iterator_DestroyFunction_t m_destroy;
    jtk_Iterator_GetNextFunction_t m_getNext;
    jtk_Iterator_HasNextFunction_t m_hasNext;
    void* m_bundle;
};

/**
 * @memberof Iterator
 */
typedef struct jtk_Iterator_t jtk_Iterator_t;

/* Constructor */

/**
 * @memberof Iterator
 */
jtk_Iterator_t* jtk_Iterator_new();

/**
 * @memberof Iterator
 */
jtk_Iterator_t* jtk_Iterator_newWithBundle(void* bundle);

/* Destructor */

/**
 * @memberof Iterator
 */
void jtk_Iterator_delete(jtk_Iterator_t* iterator);

/* Bundle */

/**
 * @memberof Iterator
 */
void* jtk_Iterator_getBundle(jtk_Iterator_t* iterator);

/* Next */

/**
 * @memberof Iterator
 */
void* jtk_Iterator_getNext(jtk_Iterator_t* iterator);

/**
 * @memberof Iterator
 */
bool jtk_Iterator_hasNext(jtk_Iterator_t* iterator);

#endif /* JTK_COLLECTION_ITERATOR_H */