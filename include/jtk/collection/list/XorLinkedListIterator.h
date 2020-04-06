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

#ifndef JTK_COLLECTION_LIST_XOR_LINKED_LIST_ITERATOR_H
#define JTK_COLLECTION_LIST_XOR_LINKED_LIST_ITERATOR_H

/*******************************************************************************
 * XorLinkedListIterator                                                    *
 *******************************************************************************/

struct jtk_XorLinkedListIterator_t {
    jtk_XorLinkedList_t* m_list;
    jtk_XorLinkedNode_t* m_current;
    jtk_XorLinkedNode_t* m_next;
    int32_t m_index;
    jtk_Iterator_t* m_iterator;
};

typedef struct jtk_XorLinkedListIterator_t jtk_XorLinkedListIterator_t;

jtk_XorLinkedListIterator_t* jtk_XorLinkedListIterator_new(jtk_XorLinkedList_t* list);
void jtk_XorLinkedListIterator_delete(jtk_XorLinkedListIterator_t* list);

#endif /* JTK_COLLECTION_LIST_XOR_LINKED_LIST_ITERATOR_H */