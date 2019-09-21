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

// Thursday, June 07, 2018

#ifndef JTK_COLLECTION_XOR_LINKED_LIST_H
#define JTK_COLLECTION_XOR_LINKED_LIST_H

#include <jtk/Configuration.h>
#include <jtk/core/ObjectAdapter.h>
#include <jtk/collection/Iterator.h>

/*******************************************************************************
 * XorLinkedList                                                               *
 *******************************************************************************/
 
struct jtk_XorLinkedList_t {
    int32_t m_size;
    jtk_DoublyLinkedNode_t* m_first;
    jtk_DoublyLinkedNode_t* m_last;
    jtk_ObjectAdapter_t* m_adapter;
};

typedef struct jtk_XorLinkedList_t jtk_XorLinkedList_t;

/* Destructor */

jtk_XorLinkedList_t* jtk_XorLinkedList_new();
jtk_XorLinkedList_t* jtk_XorLinkedList_newWithAdapter(jtk_ObjectAdapter_t* adapter);
jtk_XorLinkedList_t* jtk_XorLinkedList_newFromIterator(jtk_Iterator_t* iterator);
jtk_XorLinkedList_t* jtk_XorLinkedList_newEx(jtk_ObjectAdapter_t* adapter, jtk_Iterator_t* iterator);

/* Destructor */

void jtk_XorLinkedList_delete(jtk_XorLinkedList_t* list);

/* Link (Private) */

void jtk_DoublyLinkedNode_linkBefore(jtk_XorLinkedList_t* list, void* element, jtk_DoublyLinkedNode_t* node);
void jtk_XorLinkedList_linkFirst(jtk_XorLinkedList_t* list, void* element);
void jtk_XorLinkedList_linkLast(jtk_XorLinkedList_t* list, void* element);

/* Node (Private) */

jtk_DoublyLinkedNode_t* jtk_XorLinkedList_getNode(jtk_XorLinkedList_t* list, int32_t index);

/* Unlink (Private) */

void jtk_XorLinkedList_unlink(jtk_XorLinkedList_t* list, jtk_DoublyLinkedNode_t* node);
void jtk_XorLinkedList_unlinkFirst(jtk_XorLinkedList_t* list);
void jtk_XorLinkedList_unlinkLast(jtk_XorLinkedList_t* list);

/* Add */

void jtk_XorLinkedList_add(jtk_XorLinkedList_t* list, void* element);
void jtk_XorLinkedList_addAfter(jtk_XorLinkedList_t* list, int32_t index, void* element);
void jtk_XorLinkedList_addBefore(jtk_XorLinkedList_t* list, int32_t index, void* element);
void jtk_XorLinkedList_addAll(jtk_XorLinkedList_t* list, jtk_CollectionType_t type, void* collection);
void jtk_XorLinkedList_addAllAfter(jtk_XorLinkedList_t* list, int32_t index, jtk_CollectionType_t type, void* collection);
void jtk_XorLinkedList_addAllBefore(jtk_XorLinkedList_t* list, int32_t index, jtk_CollectionType_t type, void* collection);
void jtk_XorLinkedList_addAllFromIterator(jtk_XorLinkedList_t* list, jtk_Iterator_t* iterator);
void jtk_XorLinkedList_addAllFromIteratorAfter(jtk_XorLinkedList_t* list, int32_t index, jtk_Iterator_t* iterator);
void jtk_XorLinkedList_addAllFromIteratorBefore(jtk_XorLinkedList_t* list, int32_t index, jtk_Iterator_t* iterator);
void jtk_XorLinkedList_addFirst(jtk_XorLinkedList_t* list, void* element)
void jtk_XorLinkedList_addLast(jtk_XorLinkedList_t* list, void* element);

/* Add Predicatively */

void jtk_XorLinkedList_addPredicatively(jtk_XorLinkedList_t* list, void* element, jtk_MixedPredicateFunction_t predicate);
void jtk_XorLinkedList_addAllPredicatively(jtk_XorLinkedList_t* list, jtk_CollectionType_t type, void* collection, jtk_MixedPredicateFunction_t predicate);
void jtk_XorLinkedList_addAllFromIteratorPredicatively(jtk_XorLinkedList_t* list, jtk_Iterator_t* iterator, jtk_MixedPredicateFunction_t predicate);
void jtk_XorLinkedList_addFirstPredicatively(jtk_XorLinkedList_t* list, void* value, jtk_MixedPredicateFunction_t predicate);
void jtk_XorLinkedList_addLastPredicatively(jtk_XorLinkedList_t* list, void* value, jtk_MixedPredicateFunction_t predicate);

/* XorLinkedList-to-Array */

jtk_Array_t* jtk_XorLinkedList_toArray(jtk_XorLinkedList_t* list);

/* Clear */

void jtk_XorLinkedList_clear(jtk_XorLinkedList_t* list);
/* Copy to Array */

jtk_XorLinkedList_copyToArray(jtk_XorLinkedList_t* list, jtk_Array_t* array);

/* Copy to Array Extended */

jtk_XorLinkedList_copyToArrayEx(jtk_XorLinkedList_t* list, jtk_Array_t* array, int32_t index);

/* Contains */

bool jtk_XorLinkedList_contains(jtk_XorLinkedList_t* list, void* element, jtk_ComparatorFunction_t comparator);
bool jtk_XorLinkedList_containsAll(jtk_XorLinkedList_t* list, jtk_CollectionType_t type, void* collection, jtk_ComparatorFunction_t comparator);
bool jtk_XorLinkedList_containsAllFromIterator(jtk_XorLinkedList_t* list, jtk_Iterator_t* iterator, jtk_ComparatorFunction_t comparator);

/* Empty */

bool jtk_XorLinkedList_isEmpty(jtk_XorLinkedList_t* list);

/* Find */

int32_t jtk_XorLinkedList_find(jtk_XorLinkedList_t* list, void* element, jtk_ComparatorFunction_t comparator);
int32_t jtk_XorLinkedList_findAfter(jtk_XorLinkedList_t* list, void* element, int32_t index);
int32_t jtk_XorLinkedList_findBefore(jtk_XorLinkedList_t* list, void* element, int32_t index);

/* Find Last */

int32_t jtk_XorLinkedList_findLast(jtk_XorLinkedList_t* list, void* element, jtk_ComparatorFunction_t comparator);
int32_t jtk_XorLinkedList_findLastAfter(jtk_XorLinkedList_t* list, void* element, int32_t index);
int32_t jtk_XorLinkedList_findLastBefore(jtk_XorLinkedList_t* list, void* element, int32_t index);

/* Iterator */

jtk_Iterator_t* jtk_XorLinkedList_getIterator(jtk_XorLinkedList_t* list);

/* Remove */

bool jtk_XorLinkedList_remove(jtk_XorLinkedList_t* list, void* element, jtk_ComparatorFunction_t comparator);
int32_t jtk_XorLinkedList_removeAll(jtk_XorLinkedList_t* list, jtk_CollectionType_t type, void* collection, jtk_ComparatorFunction_t comparator);
int32_t jtk_XorLinkedList_removeAllFromIterator(jtk_XorLinkedList_t* list, jtk_Iterator_t* iterator, jtk_ComparatorFunction_t comparator);
void jtk_XorLinkedList_removeIndex(jtk_XorLinkedList_t* list, int32_t index);
void jtk_XorLinkedList_removeRange(jtk_XorLinkedList_t* list, int32_t startIndex, int32_t stopIndex);

/* Retain */

int32_t jtk_XorLinkedList_retain(jtk_XorLinkedList_t* list, void* element, jtk_ComparatorFunction_t comparator);
int32_t jtk_XorLinkedList_retainAll(jtk_XorLinkedList_t* list, jtk_CollectionType_t type, void* collection, jtk_ComparatorFunction_t comparator);
int32_t jtk_XorLinkedList_retainAllFromIterator(jtk_XorLinkedList_t* list, jtk_Iterator_t* iterator, jtk_ComparatorFunction_t comparator);

/* Size */

int32_t jtk_XorLinkedList_getSize(jtk_XorLinkedList_t* list);

/* Value */

void* jtk_XorLinkedList_getValue(jtk_XorLinkedList_t* list, int32_t index);
void jtk_XorLinkedList_setValue(jtk_XorLinkedList_t* list, int32_t index, void* value);

#endif /* JTK_COLLECTION_XOR_LINKED_LIST_H */