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

// Saturday, December 02, 2017

#ifndef JTK_COLLECTION_ARRAY_QUEUE_H
#define JTK_COLLECTION_ARRAY_QUEUE_H

#include <jtk/collection/Iterator.h>
#include <jtk/collection/array/Array.h>
#include <jtk/collection/list/ArrayList.h>

/*******************************************************************************
 * ArrayQueue                                                                  *
 *******************************************************************************/

/**
 * @class ArrayQueue
 * @ingroup jtk_collection_queue
 * @author Samuel Rowe
 * @since JTK 1.0
 */
struct jtk_ArrayQueue_t {
    jtk_ArrayList_t* m_list;
};

/**
 * @memberof ArrayQueue
 */
typedef struct jtk_ArrayQueue_t jtk_ArrayQueue_t;

/* Constructor */

/**
 * @memberof ArrayQueue
 */
jtk_ArrayQueue_t* jtk_ArrayQueue_new();

/**
 * @memberof ArrayQueue
 */
jtk_ArrayQueue_t* jtk_ArrayQueue_newFromCollection(jtk_CollectionType_t type, void* collection);

/**
 * @memberof ArrayQueue
 */
jtk_ArrayQueue_t* jtk_ArrayQueue_newFromIterator(jtk_Iterator_t* iterator);

/**
 * @memberof ArrayQueue
 */
jtk_ArrayQueue_t* jtk_ArrayQueue_newWithAdapter(jtk_ObjectAdapter_t* adapter);

/**
 * @memberof ArrayQueue
 */
jtk_ArrayQueue_t* jtk_ArrayQueue_newEx(jtk_Iterator_t* iterator, jtk_ObjectAdapter_t* adapter);

/* Destructor */

/**
 * @memberof ArrayQueue
 */
void jtk_ArrayQueue_delete(jtk_ArrayQueue_t* queue);

/* ArrayQueue-to-Array */

/**
 * @memberof ArrayQueue
 */
jtk_Array_t* jtk_ArrayQueue_toArray(jtk_ArrayQueue_t* queue);

/**
 * @memberof ArrayQueue
 */
void** jtk_ArrayQueue_toRawArray(jtk_ArrayQueue_t* queue);

/* Clear */

/**
 * @memberof ArrayQueue
 */
void jtk_ArrayQueue_clear(jtk_ArrayQueue_t* queue);

/* Copy */

/**
 * @memberof ArrayQueue
 */
void jtk_ArrayQueue_copy(jtk_ArrayQueue_t* queue, jtk_Array_t* array);

/**
 * @memberof ArrayQueue
 */
void jtk_ArrayQueue_copyEx(jtk_ArrayQueue_t* queue, jtk_Array_t* array, int32_t index);

/* Contains */

/**
 * @memberof ArrayQueue
 */
bool jtk_ArrayQueue_contains(jtk_ArrayQueue_t* queue, void* value);

/**
 * @memberof ArrayQueue
 */
bool jtk_ArrayQueue_containsAll(jtk_ArrayQueue_t* queue, jtk_CollectionType_t type, void* collection);

/**
 * @memberof ArrayQueue
 */
bool jtk_ArrayQueue_containsAllFromIterator(jtk_ArrayQueue_t* queue, jtk_Iterator_t* iterator);

/* Dequeue */

/**
 * @memberof ArrayQueue
 */
void* jtk_ArrayQueue_dequeue(jtk_ArrayQueue_t* queue);

/* Empty */

/**
 * @memberof ArrayQueue
 */
bool jtk_ArrayQueue_isEmpty(jtk_ArrayQueue_t* queue);

/* Enqueue */

/**
 * @memberof ArrayQueue
 */
void jtk_ArrayQueue_enqueue(jtk_ArrayQueue_t* queue, void* value);

/**
 * @memberof ArrayQueue
 */
void jtk_ArrayQueue_enqueueAll(jtk_ArrayQueue_t* queue, jtk_CollectionType_t type, void* collection);

/**
 * @memberof ArrayQueue
 */
void jtk_ArrayQueue_enqueueAllFromIterator(jtk_ArrayQueue_t* queue, jtk_Iterator_t* iterator);

/* Enqueue Predicatively */

/**
 * @memberof ArrayQueue
 */
void jtk_ArrayQueue_enqueuePredicatively(jtk_ArrayQueue_t* queue, void* value, jtk_PredicateFunction_t predicate);

/* Peek */

void* jtk_ArrayQueue_peek(jtk_ArrayQueue_t* queue);

/* Remove */

/**
 * @memberof ArrayQueue
 */
bool jtk_ArrayQueue_remove(jtk_ArrayQueue_t* queue, void* value);

/**
 * @memberof ArrayQueue
 */
int32_t jtk_ArrayQueue_removeAll(jtk_ArrayQueue_t* queue, jtk_CollectionType_t type, void* collection);

/**
 * @memberof ArrayQueue
 */
int32_t jtk_ArrayQueue_removeAllFromIterator(jtk_ArrayQueue_t* queue, jtk_Iterator_t* iterator);

/* Size */

/**
 * @memberof ArrayQueue
 */
int32_t jtk_ArrayQueue_getSize(jtk_ArrayQueue_t* queue);

#endif /* JTK_COLLECTION_ARRAY_QUEUE_H */