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

#ifndef JTK_COLLECTION_LINKED_QUEUE_H
#define JTK_COLLECTION_LINKED_QUEUE_H

#include <jtk/collection/Iterator.h>
#include <jtk/collection/array/Array.h>
#include <jtk/collection/list/DoublyLinkedList.h>

/*******************************************************************************
 * LinkedQueue                                                                 *
 *******************************************************************************/

/**
 * @class LinkedQueue
 * @ingroup jtk_collection_queue
 * @author Samuel Rowe
 * @since JTK 1.0
 */
struct jtk_LinkedQueue_t {
    jtk_DoublyLinkedList_t* m_list;
};

/**
 * @memberof LinkedQueue
 */
typedef struct jtk_LinkedQueue_t jtk_LinkedQueue_t;

/* Constructor */

/**
 * @memberof LinkedQueue
 */
jtk_LinkedQueue_t* jtk_LinkedQueue_new();

/**
 * @memberof LinkedQueue
 */
jtk_LinkedQueue_t* jtk_LinkedQueue_newFromCollection(jtk_CollectionType_t type, void* collection);

/**
 * @memberof LinkedQueue
 */
jtk_LinkedQueue_t* jtk_LinkedQueue_newFromIterator(jtk_Iterator_t* iterator);

/**
 * @memberof LinkedQueue
 */
jtk_LinkedQueue_t* jtk_LinkedQueue_newWithAdapter(jtk_ObjectAdapter_t* adapter);

/**
 * @memberof LinkedQueue
 */
jtk_LinkedQueue_t* jtk_LinkedQueue_newEx(jtk_Iterator_t* iterator, jtk_ObjectAdapter_t* adapter);

/* Destructor */

/**
 * @memberof LinkedQueue
 */
void jtk_LinkedQueue_delete(jtk_LinkedQueue_t* queue);

/* LinkedQueue-to-Array */

/**
 * @memberof LinkedQueue
 */
jtk_Array_t* jtk_LinkedQueue_toArray(jtk_LinkedQueue_t* queue);

/**
 * @memberof LinkedQueue
 */
void** jtk_LinkedQueue_toRawArray(jtk_LinkedQueue_t* queue);

/* Clear */

/**
 * @memberof LinkedQueue
 */
void jtk_LinkedQueue_clear(jtk_LinkedQueue_t* queue);

/* Copy */

/**
 * @memberof LinkedQueue
 */
void jtk_LinkedQueue_copy(jtk_LinkedQueue_t* queue, jtk_Array_t* array);

/**
 * @memberof LinkedQueue
 */
void jtk_LinkedQueue_copyEx(jtk_LinkedQueue_t* queue, jtk_Array_t* array, int32_t index);

/* Contains */

/**
 * @memberof LinkedQueue
 */
bool jtk_LinkedQueue_contains(jtk_LinkedQueue_t* queue, void* value);

/**
 * @memberof LinkedQueue
 */
bool jtk_LinkedQueue_containsAll(jtk_LinkedQueue_t* queue, jtk_CollectionType_t type, void* collection);

/**
 * @memberof LinkedQueue
 */
bool jtk_LinkedQueue_containsAllFromIterator(jtk_LinkedQueue_t* queue, jtk_Iterator_t* iterator);

/* Dequeue */

/**
 * @memberof LinkedQueue
 */
void* jtk_LinkedQueue_dequeue(jtk_LinkedQueue_t* queue);

/* Empty */

/**
 * @memberof LinkedQueue
 */
bool jtk_LinkedQueue_isEmpty(jtk_LinkedQueue_t* queue);

/* Enqueue */

/**
 * @memberof LinkedQueue
 */
void jtk_LinkedQueue_enqueue(jtk_LinkedQueue_t* queue, void* value);

/**
 * @memberof LinkedQueue
 */
void jtk_LinkedQueue_enqueueAll(jtk_LinkedQueue_t* queue, jtk_CollectionType_t type, void* collection);

/**
 * @memberof LinkedQueue
 */
void jtk_LinkedQueue_enqueueAllFromIterator(jtk_LinkedQueue_t* queue, jtk_Iterator_t* iterator);

/* Enqueue Predicatively */

/**
 * @memberof LinkedQueue
 */
void jtk_LinkedQueue_enqueuePredicatively(jtk_LinkedQueue_t* queue, void* value, jtk_PredicateFunction_t predicate);

/* Peek */

/**
 * @memberof LinkedQueue
 */
void* jtk_LinkedQueue_peek(jtk_LinkedQueue_t* queue);

/* Remove */

/**
 * @memberof LinkedQueue
 */
bool jtk_LinkedQueue_remove(jtk_LinkedQueue_t* queue, void* value);

/**
 * @memberof LinkedQueue
 */
int32_t jtk_LinkedQueue_removeAll(jtk_LinkedQueue_t* queue, jtk_CollectionType_t type, void* collection);

/**
 * @memberof LinkedQueue
 */
int32_t jtk_LinkedQueue_removeAllFromIterator(jtk_LinkedQueue_t* queue, jtk_Iterator_t* iterator);

/* Size */

/**
 * @memberof LinkedQueue
 */
int32_t jtk_LinkedQueue_getSize(jtk_LinkedQueue_t* queue);

#endif /* JTK_COLLECTION_LINKED_QUEUE_H */