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

// Wednesday, June 06, 2018

#ifndef JTK_COLLECTION_LIST_DOUBLY_LINKED_NODE_H
#define JTK_COLLECTION_LIST_DOUBLY_LINKED_NODE_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * DoublyLinkedNode                                                            *
 *******************************************************************************/

typedef struct jtk_DoublyLinkedNode_t jtk_DoublyLinkedNode_t;

/**
 * @class DoublyLinkedNode
 * @ingroup jtk_collection_list
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_DoublyLinkedNode_t {
    jtk_DoublyLinkedNode_t* m_previous;
    void* m_element;
    jtk_DoublyLinkedNode_t* m_next;
};

/**
 * @memberof DoublyLinkedNode
 */
jtk_DoublyLinkedNode_t* jtk_DoublyLinkedNode_new(void* element);

/**
 * @memberof DoublyLinkedNode
 */
jtk_DoublyLinkedNode_t* jtk_DoublyLinkedNode_newWithLinks(jtk_DoublyLinkedNode_t* previous, void* element, jtk_DoublyLinkedNode_t* next);

/**
 * @memberof DoublyLinkedNode
 */
void jtk_DoublyLinkedNode_delete(jtk_DoublyLinkedNode_t* element);

#endif /* JTK_COLLECTION_LIST_DOUBLY_LINKED_NODE_H */