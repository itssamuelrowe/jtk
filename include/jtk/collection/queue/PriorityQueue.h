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

// Saturday, October 13, 2018

#ifndef JTK_COLLECTION_QUEUE_PRIORITY_QUEUE_H
#define JTK_COLLECTION_QUEUE_PRIORITY_QUEUE_H

#include <jtk/Configuration.h>
#include <jtk/core/ObjectAdapter.h>
#include <jtk/collection/CollectionType.h>
#include <jtk/collection/Iterator.h>

/*******************************************************************************
 * PriorityQueue                                                               *
 *******************************************************************************/

#define JTK_PRIORITY_QUEUE_DEFAULT_CAPACITY 11

/**
 * The value of a parent node is always greater than or equal to all its children.
 *
 * @class PriorityQueue
 * @ingroup jtk_collection_queue
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_PriorityQueue_t {
    void** m_values;
    int32_t m_capacity;
    int32_t m_size;
    jtk_ObjectAdapter_t* m_adapter;
};

/**
 * @memberof PriorityQueue
 */
typedef struct jtk_PriorityQueue_t jtk_PriorityQueue_t;

/* Constructor */

/**
 * @memberof PriorityQueue
 */
jtk_PriorityQueue_t* jtk_PriorityQueue_new(jtk_ObjectAdapter_t* adapter);

/**
 * @memberof PriorityQueue
 */
jtk_PriorityQueue_t* jtk_PriorityQueue_newWithCapacity(jtk_ObjectAdapter_t* adapter, int32_t capacity);

/**
 * @memberof PriorityQueue
 */
jtk_PriorityQueue_t* jtk_PriorityQueue_newFromCollection(jtk_ObjectAdapter_t* adapter, jtk_CollectionType_t type, void* collection);

/**
 * @memberof PriorityQueue
 */
jtk_PriorityQueue_t* jtk_PriorityQueue_newFromIterator(jtk_ObjectAdapter_t* adapter, jtk_Iterator_t* iterator);

/**
 * @memberof PriorityQueue
 */
jtk_PriorityQueue_t* jtk_PriorityQueue_newEx(jtk_ObjectAdapter_t* adapter, jtk_Iterator_t* iterator, int32_t capacity);

/* Destructor */

/**
 * @memberof PriorityQueue
 */
void jtk_PriorityQueue_delete(jtk_PriorityQueue_t* queue);

/* Enqueue */

void jtk_PriorityQueue_enqueue(jtk_PriorityQueue_t* queue, void* value);

/* PriorityQueue-to-Array */

/**
 * @memberof PriorityQueue
 */
jtk_Array_t* jtk_PriorityQueue_toArray(jtk_ArrayQueue_t* queue);

/**
 * @memberof PriorityQueue
 */

void** jtk_PriorityQueue_toRawArray(jtk_ArrayQueue_t* queue);

/* Remove */

void jtk_PriorityQueue_remove(jtk_PriorityQueue_t* queue, void* value);

/* -- Private -- */

/* Insert */

void jtk_PriorityQueue_insert(jtk_PriorityQueue_t* queue, int32_t index,
    void* element) {
    while (index > 0) {
        int32_t parentIndex = (uint32_t)(index - 1) >> 1;
        void* parent = queue->m_values[parentIndex];
        if (jtk_ObjectAdapter_compare(parent, value) >= 0) {
            break;
        }
        queue[index] = parent;
        index = parentIndex;
    }
    queue->m_values[index] = value;
}

/* -- Public -- */

/* Clear */

void jtk_PriorityQueue_clear(jtk_PriorityQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified priority queue is null.");

    queue->m_size = 0;
}

/* Contains */

bool jtk_PriorityQueue_contains(jtk_PriorityQueue_t* queue, void* value) {
    jtk_Assert_assertObject(queue, "The specified priority queue is null.");

    return jtk_PriorityQueue_find(queue, value) >= 0;
}

/* Dequeue */

void* jtk_PriorityQueue_dequeue(jtk_PriorityQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified priority queue is null.");
    jtk_Assert_assertTrue(queue->m_size, "The specified priority queue is empty.");

    int32_t updateIndex = --queue->m_size;
    void* result = queue->m_values[0];
    if (updateIndex == 0
    void* updateValue = queue->m_values[updateIndex];

    /* Find the index where the next down sifting begins. */
    int32_t updateIndex = --size;
    /* Save the result, that is, the head of this queue. */
    void* result = queue->m_values[0];
    void* updateValue = queue->m_values[updateIndex];
    queue->m_values[updateIndex] = NULL;

    if (updateIndex != 0) {
        jtk_PriorityQueue_siftDown(queue, 0, updateValue);
    }

    return result;
}

/* Enqueue */

void jtk_PriorityQueue_enqueue(jtk_PriorityQueue_t* queue, void* value) {
    jtk_Assert_assertObject(queue, "The specified priority queue is null.");

    int32_t newSize = queue->m_size + 1;
    if (queue->m_capacity >= newSize) {
        jtk_PriorityQueue_requestCapacity(queue, newSize);
    }
    if (queue->m_size == 0) {
        queue->m_values[0] = value;
    }
    else {
        jtk_PriorityQueue_insert(queue, queue->m_size, value);
    }
    queue->m_size = newSize;
}

/* Find */

int32_t jtk_PriorityQueue_find(jtk_PriorityQueue_t* queue, void* value) {
    jtk_Assert_assertObject(queue, "The specified priority queue is null.");

    return jtk_Arrays_findIndexEx(queue->m_values, queue->m_size, value, 0,
        queue->m_size, (jtk_Object_CompareFunction_t)queue->m_objectAdapter->m_compare);
}

/* Iterator */

jtk_Iterator_t* jtk_PriorityQueue_getIterator(jtk_PriorityQueue_t* queue, void* value) {
    jtk_Assert_assertObject(queue, "The specified priority queue is null.");

    return jtk_PriorityQueueIterator_getIterator(queue);
}

/* Peek */

void* jtk_PriorityQueue_peek(jtk_PriorityQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified priority queue is null.");
    jtk_Assert_assertTrue(queue->m_size > 0, "The specified priority queue is empty.");

    return queue->m_values[0];
}

/* PriorityQueue-to-Array */

jtk_Array_t* jtk_PriorityQueue_toArray(jtk_ArrayQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified priority queue is null.");

    return jtk_Array_newFromRawArray(queue->m_values, queue->m_size);
}

void** jtk_PriorityQueue_toRawArray(jtk_ArrayQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified priority queue is null.");

    return jtk_Arrays_clone_v(queue->m_values, queue->m_size);
}

/* Remove */

bool jtk_PriorityQueue_remove(jtk_PriorityQueue_t* queue, void* value) {
    jtk_Assert_assertObject(queue, "The specified priority queue is null.");

    int32_t index = jtk_PriorityQueue_find(queue, value);
    bool result = false;
    if (index >= 0) {
        jtk_PriorityQueue_removeIndex(queue, index);
        result = true;
    }
    return result;
}

/* Size */

int32_t jtk_PriorityQueue_getSize(jtk_PriorityQueue_t* queue) {
    jtk_Assert_assertObject(queue, "The specified priority queue is null.");

    return queue->m_size;
}

#endif /* JTK_COLLECTION_QUEUE_PRIORITY_QUEUE_H */