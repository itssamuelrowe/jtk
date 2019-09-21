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

// Saturday, December 02, 2017

#include <jtk/collection/CollectionHelper.h>
#include <jtk/collection/queue/ArrayQueue.h>

/*******************************************************************************
 * ArrayQueue                                                                  *
 *******************************************************************************/

/* Constructor */

jtk_ArrayQueue_t* jtk_ArrayQueue_new() {
    return jtk_ArrayQueue_newEx(NULL, NULL);
}

jtk_ArrayQueue_t* jtk_ArrayQueue_newFromCollection(jtk_CollectionType_t type,
    void* collection) {
    jtk_Iterator_t* iterator = jtk_CollectionHelper_getIterator(type, collection);
    jtk_ArrayQueue_t* result = jtk_ArrayQueue_newEx(iterator, NULL);
    jtk_Iterator_delete(iterator);

    return result;
}

jtk_ArrayQueue_t* jtk_ArrayQueue_newFromIterator(jtk_Iterator_t* iterator) {
    return jtk_ArrayQueue_newEx(iterator, NULL);
}

jtk_ArrayQueue_t* jtk_ArrayQueue_newWithAdapter(jtk_ObjectAdapter_t* adapter) {
    return jtk_ArrayQueue_newEx(NULL, adapter);
}

jtk_ArrayQueue_t* jtk_ArrayQueue_newEx(jtk_Iterator_t* iterator,
    jtk_ObjectAdapter_t* adapter) {
    /*
     * All the functions defined in the ArrayQueue simply provide a thin
     * layer of abstraction over the ArrayList class. In other words, all the
     * operations supported by the ArrayQueue class are delegations to the
     * ArrayList.
     */
    jtk_ArrayQueue_t* queue = jtk_Memory_allocate(jtk_ArrayQueue_t, 1);
    queue->m_list = jtk_ArrayList_newEx(JTK_ARRAY_LIST_DEFAULT_CAPACITY, iterator,
        adapter);
    return queue;
}

/* Destructor */

void jtk_ArrayQueue_delete(jtk_ArrayQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    jtk_ArrayList_delete(queue->m_list);
    jtk_Memory_deallocate(queue);
}

/* Clear */

void jtk_ArrayQueue_clear(jtk_ArrayQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    jtk_ArrayList_clear(queue->m_list);
}

/* Copy */

void jtk_ArrayQueue_copy(jtk_ArrayQueue_t* queue, jtk_Array_t* array) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    jtk_ArrayList_copy(queue->m_list, array);
}

void jtk_ArrayQueue_copyEx(jtk_ArrayQueue_t* queue, jtk_Array_t* array,
    int32_t index) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    jtk_ArrayList_copyEx(queue->m_list, array, index);
}

/* Contains */

bool jtk_ArrayQueue_contains(jtk_ArrayQueue_t* queue, void* value) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    return jtk_ArrayList_contains(queue->m_list, value);
}

bool jtk_ArrayQueue_containsAll(jtk_ArrayQueue_t* queue,
    jtk_CollectionType_t type, void* collection) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject(collection, "The specified collection is null.");

    return jtk_ArrayList_containsAll(queue->m_list, type, collection);
}

bool jtk_ArrayQueue_containsAllFromIterator(jtk_ArrayQueue_t* queue,
    jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return jtk_ArrayList_containsAllFromIterator(queue->m_list, iterator);
}

/* Dequeue */

void* jtk_ArrayQueue_dequeue(jtk_ArrayQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertFalse(jtk_ArrayList_isEmpty(queue->m_list), "The specified queue is empty.");

    void* temporary = jtk_ArrayList_getValue(queue->m_list, 0);
    jtk_ArrayList_removeIndex(queue->m_list, 0);
    return temporary;
}

/* Empty */

bool jtk_ArrayQueue_isEmpty(jtk_ArrayQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    return jtk_ArrayList_isEmpty(queue->m_list);
}

/* Enqueue */

void jtk_ArrayQueue_enqueue(jtk_ArrayQueue_t* queue, void* element) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    jtk_ArrayList_addLast(queue->m_list, element);
}

void jtk_ArrayQueue_enqueueAll(jtk_ArrayQueue_t* queue, jtk_CollectionType_t type,
    void* collection) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject(collection, "The specified collection is null.");

    jtk_ArrayList_addAll(queue->m_list, type, collection);
}

void jtk_ArrayQueue_enqueueAllFromIterator(jtk_ArrayQueue_t* queue,
    jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    jtk_ArrayList_addAllFromIterator(queue->m_list, iterator);
}

/* Enqueue Predicatively */

void jtk_ArrayQueue_enqueuePredicatively(jtk_ArrayQueue_t* queue, void* value,
    jtk_MixedPredicateFunction_t predicate) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject((void*)predicate, "The specified predicate is null.");

    jtk_ArrayList_addPredicatively(queue->m_list, value, predicate);
}

/* Peek */

void* jtk_ArrayQueue_peek(jtk_ArrayQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertFalse(jtk_ArrayList_isEmpty(queue->m_list), "The specified queue is empty.");

    return jtk_ArrayList_getValue(queue->m_list, 0);
}

/* Remove */

bool jtk_ArrayQueue_remove(jtk_ArrayQueue_t* queue, void* value) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    return jtk_ArrayList_remove(queue->m_list, value);
}

int32_t jtk_ArrayQueue_removeAll(jtk_ArrayQueue_t* queue, jtk_CollectionType_t type,
    void* collection) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject(collection, "The specified collection is null.");

    return jtk_ArrayList_removeAll(queue->m_list, type, collection);
}

int32_t jtk_ArrayQueue_removeAllFromIterator(jtk_ArrayQueue_t* queue,
    jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return jtk_ArrayList_removeAllFromIterator(queue->m_list, iterator);

}

/* Size */

int32_t jtk_ArrayQueue_getSize(jtk_ArrayQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified queue is null.");

    return jtk_ArrayList_getSize(queue->m_list);
}