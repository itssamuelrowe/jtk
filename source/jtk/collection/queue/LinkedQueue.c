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

#include <jtk/collection/CollectionHelper.h>
#include <jtk/collection/queue/LinkedQueue.h>

/*******************************************************************************
 * LinkedQueue                                                                  *
 *******************************************************************************/

/* Constructor */

jtk_LinkedQueue_t* jtk_LinkedQueue_new() {
    return jtk_LinkedQueue_newEx(NULL, NULL);
}

jtk_LinkedQueue_t* jtk_LinkedQueue_newFromCollection(jtk_CollectionType_t type,
    void* collection) {
    jtk_Iterator_t* iterator = jtk_CollectionHelper_getIterator(type, collection);
    jtk_LinkedQueue_t* result = jtk_LinkedQueue_newEx(iterator, NULL);
    jtk_Iterator_delete(iterator);

    return result;
}

jtk_LinkedQueue_t* jtk_LinkedQueue_newFromIterator(jtk_Iterator_t* iterator) {
    return jtk_LinkedQueue_newEx(iterator, NULL);
}

jtk_LinkedQueue_t* jtk_LinkedQueue_newWithAdapter(jtk_ObjectAdapter_t* adapter) {
    return jtk_LinkedQueue_newEx(NULL, adapter);
}

jtk_LinkedQueue_t* jtk_LinkedQueue_newEx(jtk_Iterator_t* iterator,
    jtk_ObjectAdapter_t* adapter) {
    /*
     * All the functions defined in the LinkedQueue simply provide a thin
     * layer of abstraction over the DoublyLinkedList class. In other words, all the
     * operations supported by the LinkedQueue class are delegations to the
     * DoublyLinkedList.
     */
    jtk_LinkedQueue_t* queue = jtk_Memory_allocate(jtk_LinkedQueue_t, 1);
    queue->m_list = jtk_DoublyLinkedList_newEx(iterator, adapter);
    return queue;
}

/* Destructor */

void jtk_LinkedQueue_delete(jtk_LinkedQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    jtk_DoublyLinkedList_delete(queue->m_list);
    jtk_Memory_deallocate(queue);
}

/* Clear */

void jtk_LinkedQueue_clear(jtk_LinkedQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    jtk_DoublyLinkedList_clear(queue->m_list);
}

/* Copy */

void jtk_LinkedQueue_copy(jtk_LinkedQueue_t* queue, jtk_Array_t* array) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    jtk_DoublyLinkedList_copy(queue->m_list, array);
}

void jtk_LinkedQueue_copyEx(jtk_LinkedQueue_t* queue, jtk_Array_t* array,
    int32_t index) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    jtk_DoublyLinkedList_copyEx(queue->m_list, array, index);
}

/* Contains */

bool jtk_LinkedQueue_contains(jtk_LinkedQueue_t* queue, void* value) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    return jtk_DoublyLinkedList_contains(queue->m_list, value);
}

bool jtk_LinkedQueue_containsAll(jtk_LinkedQueue_t* queue,
    jtk_CollectionType_t type, void* collection) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject(collection, "The specified collection is null.");

    return jtk_DoublyLinkedList_containsAll(queue->m_list, type, collection);
}

bool jtk_LinkedQueue_containsAllFromIterator(jtk_LinkedQueue_t* queue,
    jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return jtk_DoublyLinkedList_containsAllFromIterator(queue->m_list, iterator);
}

/* Dequeue */

void* jtk_LinkedQueue_dequeue(jtk_LinkedQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertFalse(jtk_DoublyLinkedList_isEmpty(queue->m_list), "The specified queue is empty.");

    void* temporary = jtk_DoublyLinkedList_getValue(queue->m_list, 0);
    jtk_DoublyLinkedList_removeIndex(queue->m_list, 0);
    return temporary;
}

/* Empty */

bool jtk_LinkedQueue_isEmpty(jtk_LinkedQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    return jtk_DoublyLinkedList_isEmpty(queue->m_list);
}

/* Enqueue */

void jtk_LinkedQueue_enqueue(jtk_LinkedQueue_t* queue, void* element) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    jtk_DoublyLinkedList_addLast(queue->m_list, element);
}

void jtk_LinkedQueue_enqueueAll(jtk_LinkedQueue_t* queue, jtk_CollectionType_t type,
    void* collection) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject(collection, "The specified collection is null.");

    jtk_DoublyLinkedList_addAll(queue->m_list, type, collection);
}

void jtk_LinkedQueue_enqueueAllFromIterator(jtk_LinkedQueue_t* queue,
    jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    jtk_DoublyLinkedList_addAllFromIterator(queue->m_list, iterator);
}

/* Enqueue Predicatively */

void jtk_LinkedQueue_enqueuePredicatively(jtk_LinkedQueue_t* queue, void* value,
    jtk_PredicateFunction_t predicate) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject((void*)predicate, "The specified predicate is null.");

    jtk_DoublyLinkedList_addPredicatively(queue->m_list, value, predicate);
}

/* Peek */

void* jtk_LinkedQueue_peek(jtk_LinkedQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertFalse(jtk_DoublyLinkedList_isEmpty(queue->m_list), "The specified queue is empty.");

    return jtk_DoublyLinkedList_getValue(queue->m_list, 0);
}

/* Remove */

bool jtk_LinkedQueue_remove(jtk_LinkedQueue_t* queue, void* value) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    return jtk_DoublyLinkedList_remove(queue->m_list, value);
}

int32_t jtk_LinkedQueue_removeAll(jtk_LinkedQueue_t* queue, jtk_CollectionType_t type,
    void* collection) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject(collection, "The specified collection is null.");

    return jtk_DoublyLinkedList_removeAll(queue->m_list, type, collection);
}

int32_t jtk_LinkedQueue_removeAllFromIterator(jtk_LinkedQueue_t* queue,
    jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return jtk_DoublyLinkedList_removeAllFromIterator(queue->m_list, iterator);

}

/* Size */

int32_t jtk_LinkedQueue_getSize(jtk_LinkedQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    return jtk_DoublyLinkedList_getSize(queue->m_list);
}