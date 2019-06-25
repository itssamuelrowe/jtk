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

// Monday, July 02, 2018

#include <jtk/collection/list/DoublyLinkedNode.h>

/*******************************************************************************
 * DoublyLinkedNode                                                        *
 *******************************************************************************/

/* Constructor */
 
jtk_DoublyLinkedNode_t* jtk_DoublyLinkedNode_new(void* element) {
    jtk_DoublyLinkedNode_t* node = jtk_Memory_allocate(jtk_DoublyLinkedNode_t, 1);
    node->m_previous = NULL;
    node->m_element = element;
    node->m_next = NULL;
    return node;
}

jtk_DoublyLinkedNode_t* jtk_DoublyLinkedNode_newWithLinks(
    jtk_DoublyLinkedNode_t* previous, void* element,
    jtk_DoublyLinkedNode_t* next) {
    jtk_DoublyLinkedNode_t* node = jtk_Memory_allocate(jtk_DoublyLinkedNode_t, 1);
    node->m_previous = previous;
    node->m_element = element;
    node->m_next = next;

    return node;
}

/* Destructor */

void jtk_DoublyLinkedNode_delete(jtk_DoublyLinkedNode_t* node) {
    jtk_Assert_assertObject(node, "The specified doubly-linked node is null.");

    jtk_Memory_deallocate(node);
}