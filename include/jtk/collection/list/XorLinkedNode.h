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

// Thursday, June 07, 2018

#ifndef JTK_COLLECTION_LIST_XOR_LINKED_NODE_H
#define JTK_COLLECTION_LIST_XOR_LINKED_NODE_H

/*******************************************************************************
 * XorLinkedNode                                                               *
 *******************************************************************************/

struct jtk_XorLinkedNode_t {
    void* m_element;
    intptr_t m_links;
};

typedef struct jtk_XorLinkedNode_t jtk_XorLinkedNode_t;

/* Constructor */

jtk_XorLinkedNode_t* jtk_XorLinkedNode_new(void* element);
jtk_XorLinkedNode_t* jtk_XorLinkedNode_newWithLinks(jtk_XorLinkedNode_t* previous, void* element, jtk_XorLinkedNode_t* next);

/* Destructor */

void jtk_XorLinkedNode_delete(jtk_XorLinkedNode_t* element);

#endif /* JTK_COLLECTION_LIST_XOR_LINKED_NODE_H */