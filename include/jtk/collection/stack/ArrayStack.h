/*
 * Copyright 2017-2020 Samuel Rowe
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

#ifndef JTK_COLLECTION_ARRAY_STACK_H
#define JTK_COLLECTION_ARRAY_STACK_H

#include <jtk/collection/list/ArrayList.h>
#include <jtk/collection/CollectionType.h>

/*******************************************************************************
 * ArrayStack                                                                  *
 *******************************************************************************/

/**
 * As of version 1.1, the previous algorithm has been updated. Previously, the
 * elements were added at the beginning of the internal array list. This caused
 * the "original" elements to be shifted causing a performance lag. However,
 * this has been fixed by storing new elements at the end of the list.
 *
 * @class ArrayStack
 * @ingroup jtk_collection_stack
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_ArrayStack_t {
    jtk_ArrayList_t* m_list;
};

/**
 * @memberof ArrayStack
 */
typedef struct jtk_ArrayStack_t jtk_ArrayStack_t;

/**
 * @memberof ArrayStack
 */
jtk_ArrayStack_t* jtk_ArrayStack_new();

/**
 * @memberof ArrayStack
 */
void jtk_ArrayStack_delete(jtk_ArrayStack_t* stack);

/**
 * @memberof ArrayStack
 */
void jtk_ArrayStack_push(jtk_ArrayStack_t* stack, void* element);

/**
 * @memberof ArrayStack
 */
void jtk_ArrayStack_pop(jtk_ArrayStack_t* stack);

/**
 * @memberof ArrayStack
 */
void* jtk_ArrayStack_peek(jtk_ArrayStack_t* stack);

/**
 * @memberof ArrayStack
 */
bool jtk_ArrayStack_isEmpty(jtk_ArrayStack_t* stack);

/**
 * @memberof ArrayStack
 */
int32_t jtk_ArrayStack_getSize(jtk_ArrayStack_t* stack);

/**
 * @memberof ArrayStack
 */
void jtk_ArrayStack_addAll(jtk_ArrayStack_t* stack, jtk_CollectionType_t type, void* collection);

#endif /* JTK_COLLECTION_ARRAY_STACK_H */