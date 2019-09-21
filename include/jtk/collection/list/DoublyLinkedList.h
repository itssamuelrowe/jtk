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

// Sunday, January 08, 2018

#ifndef JTK_COLLECTION_DOUBLY_LINKED_LIST_H
#define JTK_COLLECTION_DOUBLY_LINKED_LIST_H

#include <jtk/Configuration.h>
#include <jtk/core/ObjectAdapter.h>
#include <jtk/function/PredicateFunction.h>
#include <jtk/collection/CollectionType.h>
#include <jtk/collection/Iterator.h>
#include <jtk/collection/array/Array.h>
#include <jtk/collection/list/DoublyLinkedNode.h>

/*******************************************************************************
 * DoublyLinkedList                                                            *
 *******************************************************************************/

/**
 * The DoublyLinkedList class represents a list backed by doubly-linked nodes.
 *
 * The DoublyLinkedList class does not provide fast random access to elements.
 * Although error checking is implemented, only when assertions are enabled.
 * An element is accessed by its integer index, the position in the list.
 * An attempt to access an element with an invalid index, usually, results in
 * the failure of an assertion. The indices of a list are of the form:
 * `0, 1, 2, 3, 4, 5, 6, 7, ... n - 1`. The first item of the sequence is
 * at index `0`, the next at index `1`, and so on.
 * Thus, for a list containing ten elements, the valid indices range from
 * `0` (inclusive) to `10` (exclusive).
 *
 * Optionally, an object adapter may be attached to the list. The adapter
 * helps the implementation adapt elements as objects. Custom implementations
 * of algorithms for converting elements to strings, computing hashes, etc.
 * may be provided. If an object adapter is absent, the implementation falls
 * back to the default hard coded algorithms. Please refer the documentation
 * of specific functions which employ the object adapter for more information.
 * As of this version, the object adapter should be initialized during the
 * creation of the list. This behaviour may become less rigid in the future
 * releases.
 *
 * The DoublyLinkedList class is intended to be used by a single thread. It does
 * not implement a thread synchronization policy. In other words, it is not thread
 * safe. Concurrent invocation of a function against an instance without an
 * external synchronization results in undefined behaviour.
 *
 * Further, it is recommended that the user avoids accessing the fields of
 * this structure directly. They may be subjected to changes without any
 * notifications. Please employ appropriate interfaces with detailed
 * documentation.
 *
 * @class DoublyLinkedList
 * @ingroup jtk_collection_list
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_DoublyLinkedList_t {
    /**
     * The number of elements this linked list contains, initially zero.
     */
    int32_t m_size;

    /**
     * The pointer to the first node in the linked list, also known as the
     * head. If the list is empty it points to `null`. There are no
     * nodes prior to this node. Hence, `m_first->m_previous` always
     * points to `null`. If this linked list contains only one element,
     * `m_first == m_last` evaluates to `true`.
     */
    jtk_DoublyLinkedNode_t* m_first;

    /**
     * The pointer to the last node in the linked list, also known as the
     * tail. If the list is empty it points to `null`. There are no
     * nodes after this node. Hence, `last->next` always points to
     * `null`. If this linked list contains only one element,
     * `this->first == this->last` evaluates to `true`.
     */
    jtk_DoublyLinkedNode_t* m_last;

    /**
     * The adapter used to adapt elements as objects.
     */
    jtk_ObjectAdapter_t* m_adapter;
};

typedef struct jtk_DoublyLinkedList_t jtk_DoublyLinkedList_t;

/* Destructor */

/**
 * Creates an empty doubly-linked list with no elements.
 *
 * @return The newly created doubly-linked list. The user is responsible for
 *         destroying the list.
 * @memberof DoublyLinkedList
 */
jtk_DoublyLinkedList_t* jtk_DoublyLinkedList_new();

/**
 * Creates an DoublyLinkedList with the specified initial content, that is, the
 * elements contained in the specified collection. The order of the elements
 * depends on the iterator returned by the specified collection.
 *
 * @param  type
 *         This argument specifies the type of the collection.
 * @param  collection
 *         This argument specifies the collection from which the initial content
 *         of this doubly-linked list is extracted.
 * @return The newly created doubly-linked list. The user is responsible for
 *         destroying the list.
 * @memberof DoublyLinkedList
 */
jtk_DoublyLinkedList_t* jtk_DoublyLinkedList_newFromCollection(jtk_CollectionType_t type, void* collection);

/**
 * Creates an DoublyLinkedList with the specified initial content, that is, the
 * elements return by the specified iterator. The order of the elements
 * depends on the iterator.
 *
 * @param  iterator
 *         This argument specifies the iterator from which the initial content
 *         of this doubly-linked list is extracted.
 * @return The newly created doubly-linked list. The user is responsible for
 *         destroying the list.
 * @memberof DoublyLinkedList
 */
jtk_DoublyLinkedList_t* jtk_DoublyLinkedList_newFromIterator(jtk_Iterator_t* iterator);

/**
 * Creates an empty doubly-linked list with no elements. The specified object
 * adapter is attached to the list.
 *
 * @param  adapter
 *         This argument specifies the object adapter to attach.
 * @return The newly created doubly-linked list. The user is responsible for
 *         destroying the list.
 * @memberof DoublyLinkedList
 */
jtk_DoublyLinkedList_t* jtk_DoublyLinkedList_newWithAdapter(jtk_ObjectAdapter_t* adapter);

/**
 * @memberof DoublyLinkedList
 */
jtk_DoublyLinkedList_t* jtk_DoublyLinkedList_newEx(jtk_ObjectAdapter_t* adapter, jtk_Iterator_t* iterator);

/* Destructor */

/**
 * Destroys the specified doubly-linked list.
 *
 * @param  list
 *         This argument specifies the doubly-linked list to destroy.
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_delete(jtk_DoublyLinkedList_t* list);

/* Link (Private) */

/**
 * @private
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedNode_linkBefore(jtk_DoublyLinkedList_t* list, void* value, jtk_DoublyLinkedNode_t* node);

/**
 * @private
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_linkFirst(jtk_DoublyLinkedList_t* list, void* value);

/**
 * @private
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_linkLast(jtk_DoublyLinkedList_t* list, void* value);

/* Node (Private) */

/**
 * @private
 * @memberof DoublyLinkedList
 */
jtk_DoublyLinkedNode_t* jtk_DoublyLinkedList_getNode(jtk_DoublyLinkedList_t* list, int32_t index);

/* Unlink (Private) */

/**
 * @private
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_unlink(jtk_DoublyLinkedList_t* list, jtk_DoublyLinkedNode_t* node);

/**
 * @private
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_unlinkFirst(jtk_DoublyLinkedList_t* list);

/**
 * @private
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_unlinkLast(jtk_DoublyLinkedList_t* list);

/* Add */

/**
 * The add() function adds the specified element to the end of this
 * list.
 *
 * @param  list
 *         This argument specifies the doubly-linked list to modify.
 * @param  value
 *         This argument specifies the element to add.
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_add(jtk_DoublyLinkedList_t* list, void* value);

/**
 * The addIndex() function inserts the specified element at the specified
 * index. The current element and any subsequent elements to the right
 * of the specified index, if any, are shifted to right by adding one
 * to their indices.
 *
 * @param  list
 *         This argument specifies the doubly-linked list to modify.
 * @param  index
 *         This argument specifies the index at which the element has to
 *         be inserted. An index should be greater than or equal to zero
 *         and lesser than or equal to the size of the list.
 * @param  value
 *         This argument specifies the element to add.
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_addIndex(jtk_DoublyLinkedList_t* list, int32_t index, void* value);

/**
 * The addAll() function adds all the elements contained in the specified
 * collection to the end of the specified doubly-linked list. The order of the
 * elements inserted depends on the iterator returned by the specified collection.
 * It returns the total number of elements that were added; `0`, if none.
 *
 * The behaviour of this function is undefined, if the specified collection
 * is modified while this function is in progress. This problem may arise
 * if the specified collection is this collection.
 *
 * @param  list
 *         This argument specifies the doubly-linked list to modify.
 * @param  type
 *         This argument specifies the type of the collection.
 * @param  collection
 *         This argument specifies the collection of elements to add.
 * @return The total number of elements that were added; `0`, if
 *         none.
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_addAll(jtk_DoublyLinkedList_t* list, jtk_CollectionType_t type, void* collection);

/**
 * The addAll() function adds all the elements contained in the specified
 * collection into the specified doubly-linked list. The elements are inserted
 * at the specified index. The current element and any subsequent elements to
 * the right of the specified index, if any, are shifted to right by adding
 * `n` to their indices, where `n` is the size of the specified
 * collection. The order of the elements inserted depends on the iterator
 * returned by the specified collection.
 *
 * It returns the total number of elements that were added; `0`, if none.
 *
 * The behaviour of this function is undefined, if the specified collection
 * is modified while this function is in progress. This problem may arise
 * if the specified collection is this collection.
 *
 * @param  list
 *         This argument specifies the doubly-linked list to modify.
 * @param  type
 *         This argument specifies the type of the collection.
 * @param  collection
 *         This argument specifies the collection of elements to add.
 * @param  index
 *         This argument specifies the index at which the elements are inserted.
 *         All negative values are considered illegal. Further, it should be
 *         greater or equal to zero and lesser than or equal to the size of the
 *         list.
 * @return The total number of elements that were added; `0`, if
 *         none.
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_addAllAt(jtk_DoublyLinkedList_t* list, jtk_CollectionType_t type, void* collection, int32_t index);

/**
 * The addAllFromIterator() function adds all the elements returned from the
 * specified iterator to the end of the specified doubly-linked list. The order
 * of the elements inserted depends on the iterator. It returns the total number
 * of elements that were added; `0`, if none.
 *
 * The behaviour of this function is undefined, if the source of the iterator
 * is modified while this function is in progress. This problem may arise
 * if the source of the specified iterator is this collection.
 *
 * @param  list
 *         This argument specifies the doubly-linked list to modify.
 * @param  iterator
 *         This argument specifies the iterator from where the elements are
 *         extracted.
 * @return The total number of elements that were added; `0`, if
 *         none.
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_addAllFromIterator(jtk_DoublyLinkedList_t* list, jtk_Iterator_t* iterator);

/**
 * The addAll() function adds all the elements return from the specified
 * iterator into the specified doubly-linked list. The elements are inserted
 * at the specified index. The current element and any subsequent elements to
 * the right of the specified index, if any, are shifted to right by adding
 * `n` to their indices, where `n` is the total number of elements
 * return from the specified iterator. The order of the elements inserted
 * depends on the iterator.
 *
 * It returns the total number of elements that were added; `0`, if none.
 *
 * The behaviour of this function is undefined, if the source of the iterator
 * is modified while this function is in progress. This problem may arise
 * if the source of the specified iterator is this collection.
 *
 * @param  list
 *         This argument specifies the doubly-linked list to modify.
 * @param  iterator
 *         This argument specifies the iterator from where the elements are
 *         extracted.
 * @param  index
 *         This argument specifies the index at which the elements are inserted.
 *         All negative values are considered illegal. Further, it should be
 *         greater or equal to zero and lesser than or equal to the size of the
 *         list.
 * @return The total number of elements that were added; `0`, if
 *         none.
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_addAllFromIteratorAt(jtk_DoublyLinkedList_t* list, jtk_Iterator_t* iterator, int32_t index);

/**
 * The addFirst() function adds the specified element to the start of this
 * list.
 *
 * @param  list
 *         This argument specifies the doubly-linked list to modify.
 * @param  value
 *         This argument specifies the element to add.
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_addFirst(jtk_DoublyLinkedList_t* list, void* value);

/**
 * The addLast() function adds the specified element to the end of this
 * list. It is equivalent to invoking `jtk_DoublyLinkedList_add()` function.
 * It is provided for balancing consistency in function names.
 *
 * @param  list
 *         This argument specifies the doubly-linked list to modify.
 * @param  value
 *         This argument specifies the element to add.
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_addLast(jtk_DoublyLinkedList_t* list, void* value);

/* Add Predicatively */

/**
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_addPredicatively(jtk_DoublyLinkedList_t* list, void* value, jtk_MixedPredicateFunction_t predicate);

// void jtk_DoublyLinkedList_addAllPredicatively(jtk_DoublyLinkedList_t* list, jtk_CollectionType_t type, void* collection, jtk_MixedPredicateFunction_t predicate);

// void jtk_DoublyLinkedList_addAllFromIteratorPredicatively(jtk_DoublyLinkedList_t* list, jtk_Iterator_t* iterator, jtk_MixedPredicateFunction_t predicate);

/**
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_addFirstPredicatively(jtk_DoublyLinkedList_t* list, void* value, jtk_MixedPredicateFunction_t predicate);

/**
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_addLastPredicatively(jtk_DoublyLinkedList_t* list, void* value, jtk_MixedPredicateFunction_t predicate);

/* DoublyLinkedList-to-Array */

/**
 * @memberof DoublyLinkedList
 */
jtk_Array_t* jtk_DoublyLinkedList_toArray(jtk_DoublyLinkedList_t* list);

/**
 * @memberof DoublyLinkedList
 */
void** jtk_DoublyLinkedList_toRawArray(jtk_DoublyLinkedList_t* list);

/* Clear */

/**
 * The clear() function removes all the elements from this list.
 *
 * @param  list
 *         This argument specifies the doubly-linked list whose capacity is
 *         required.
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_clear(jtk_DoublyLinkedList_t* list);

/* Copy */

/**
 * @memberof DoublyLinkedList
 */
int32_t jtk_DoublyLinkedList_copy(jtk_DoublyLinkedList_t* list, jtk_Array_t* array);

/**
 * @memberof DoublyLinkedList
 */
int32_t jtk_DoublyLinkedList_copyEx(jtk_DoublyLinkedList_t* list, jtk_Array_t* array, int32_t index);

/* Contains */

/**
 * The contains() function returns `true` if this list contains the
 * specified element; `false` otherwise.
 *
 * @param  list
 *         This argument specifies the list.
 * @param  element
 *         This argument specifies the element to test.
 * @return `true` if this list contains the specified element;
 *         `false` otherwise.
 * @memberof DoublyLinkedList
 */
bool jtk_DoublyLinkedList_contains(jtk_DoublyLinkedList_t* list, void* value);

/**
 * The containsAll() function returns `true` if the specified doubly-linked
 * list contains all the elements contained in the specified collection;
 * `false` otherwise.
 *
 * @param  type
 *         This argument specifies the type of the collection.
 * @param  collection
 *         This argument specifies the collection of elements to test.
 * @return `true` if this list contains all the elements
 *         contained in the specified collection; `false` otherwise.
 * @memberof DoublyLinkedList
 */
bool jtk_DoublyLinkedList_containsAll(jtk_DoublyLinkedList_t* list, jtk_CollectionType_t type, void* collection);

/**
 * The containsAllFromIterator() function returns `true` if the specified
 * doubly-linked list contains all the elements return from the specified iterator;
 * `false` otherwise.
 *
 * @param  iterator
 *         This argument specifies the iterator.
 * @return `true` if this list contains all the elements
 *         contained in the specified collection; `false` otherwise.
 * @memberof DoublyLinkedList
 */
bool jtk_DoublyLinkedList_containsAllFromIterator(jtk_DoublyLinkedList_t* list, jtk_Iterator_t* iterator);

/* Empty */

/**
 * The isEmpty() function returns `true` if this list contains no
 * elements; `false` otherwise.
 *
 * @param  list
 *         This argument specifies the doubly-linked list to test.
 * @return `true` if this collection contains no elements;
 *         `false` otherwise.
 * @memberof DoublyLinkedList
 */
bool jtk_DoublyLinkedList_isEmpty(jtk_DoublyLinkedList_t* list);

/* Find */

/**
 * Finds the first occurrence of the specified element in the specified list.
 * It returns a valid index, if found using the linear search algorithm; a
 * negative integer otherwise.
 *
 * @param  list
 *         This argument specifies the doubly-linked list to search.
 * @param  element
 *         This argument specifies the element to find.
 * @return The index of the first occurrence of the specified element,
 *         if found; a negative integer otherwise.
 * @memberof DoublyLinkedList
 */
int32_t jtk_DoublyLinkedList_find(jtk_DoublyLinkedList_t* list, void* value);

/**
 * Finds the first occurrence of the specified element in the specified list,
 * beginning the search at the specified index. It returns a valid index, if
 * found using the linear search algorithm; a negative integer otherwise.
 *
 * @param  element
 *         This argument specifies the element to find.
 * @param  index
 *         This argument specifies the index at which the search begins.
 *         The index should be greater than or equal to zero and lesser than
 *         the size of the list. It is exclusive.
 * @return The index of the first occurrence of the specified element,
 *         if found; a negative integer otherwise.
 * @memberof DoublyLinkedList
 */
int32_t jtk_DoublyLinkedList_findAfter(jtk_DoublyLinkedList_t* list, void* value, int32_t index);

/**
 * Finds the first occurrence of the specified element in the specified list,
 * terminating the search at the specified index. It returns a valid index, if
 * found using the linear search algorithm; a negative integer otherwise.
 *
 * @param  element
 *         This argument specifies the element to find.
 * @param  index
 *         This argument specifies the index at which the search terminates.
 *         The index should be greater than or equal to zero and lesser than
 *         or equal to the size of the list. It is exclusive.
 * @return The index of the first occurrence of the specified element,
 *         if found; a negative integer otherwise.
 * @memberof DoublyLinkedList
 */
int32_t jtk_DoublyLinkedList_findBefore(jtk_DoublyLinkedList_t* list, void* value, int32_t index);

/**
 * Finds the first occurrence of the specified element in the specified list,
 * beginning the search at the specified start index and terminating the search
 * at the specified stop index. It returns a valid index, if found using the
 * linear search algorithm; a negative integer otherwise.
 *
 * The specified range should be subjected to the following constraints,
 * otherwise an assertion failure is triggered. The starting index should
 * greater than or equal to zero. The starting index should be lesser than
 * or equal to the stopping index. The stopping index should be lesser than the
 * or equal to the size of the list. The following fragment of code shows the
 * constraints:
 * `(startIndex >= 0) && (startIndex <= stopIndex) && (stopIndex <= size)`,
 * where `startIndex}, `stopIndex`, and `size` mean
 * the starting index of the range, the stopping index of the range, and the
 * size of the list, respectively.
 *
 * @param  element
 *         This argument specifies the element to find.
 * @param  startIndex
 *         This argument specifies the index at which the search begins,
 *         inclusive.
 * @param  stopIndex
 *         This argument specifies the index at which the search terminates,
 *         exclusive.
 * @return The index of the first occurrence of the specified element,
 *         if found; a negative integer otherwise.
 * @memberof DoublyLinkedList
 */
int32_t jtk_DoublyLinkedList_findInRange(jtk_DoublyLinkedList_t* list, void* value, int32_t startIndex, int32_t stopIndex);

/* Find Last */

/**
 * Finds the last occurrence of the specified element in the specified list.
 * It returns a valid index, if found using the linear search algorithm; a
 * negative integer otherwise.
 *
 * @param  list
 *         This argument specifies the doubly-linked list to search.
 * @param  element
 *         This argument specifies the element to find.
 * @return The index of the last occurrence of the specified element,
 *         if found; a negative integer otherwise.
 * @memberof DoublyLinkedList
 */
int32_t jtk_DoublyLinkedList_findLast(jtk_DoublyLinkedList_t* list, void* value);

/**
 * Finds the last occurrence of the specified element in the specified list,
 * beginning the search at the specified index. It returns a valid index, if
 * found using the linear search algorithm; a negative integer otherwise.
 *
 * @param  element
 *         This argument specifies the element to find.
 * @param  index
 *         This argument specifies the index at which the search begins.
 *         The index should be greater than or equal to zero and lesser than
 *         the size of the list. It is exclusive.
 * @return The index of the last occurrence of the specified element,
 *         if found; a negative integer otherwise.
 * @memberof DoublyLinkedList
 */
int32_t jtk_DoublyLinkedList_findLastAfter(jtk_DoublyLinkedList_t* list, void* value, int32_t index);

/**
 * Finds the last occurrence of the specified element in the specified list,
 * terminating the search at the specified index. It returns a valid index, if
 * found using the linear search algorithm; a negative integer otherwise.
 *
 * @param  element
 *         This argument specifies the element to find.
 * @param  index
 *         This argument specifies the index at which the search terminates.
 *         The index should be greater than or equal to zero and lesser than
 *         or equal to the size of the list. It is exclusive.
 * @return The index of the last occurrence of the specified element,
 *         if found; a negative integer otherwise.
 * @memberof DoublyLinkedList
 */
int32_t jtk_DoublyLinkedList_findLastBefore(jtk_DoublyLinkedList_t* list, void* value, int32_t index);

/**
 * Finds the last occurrence of the specified element in the specified list,
 * beginning the search at the specified start index and terminating the search
 * at the specified stop index. It returns a valid index, if found using the
 * linear search algorithm; a negative integer otherwise.
 *
 * The specified range should be subjected to the following constraints,
 * otherwise an assertion failure is triggered. The starting index should
 * greater than or equal to zero. The starting index should be lesser than
 * or equal to the stopping index. The stopping index should be lesser than the
 * or equal to the size of the list. The following fragment of code shows the
 * constraints:
 * `(startIndex >= 0) && (startIndex <= stopIndex) && (stopIndex <= size)`,
 * where `startIndex}, `stopIndex`, and `size` mean
 * the starting index of the range, the stopping index of the range, and the
 * size of the list, respectively.
 *
 * @param  element
 *         This argument specifies the element to find.
 * @param  startIndex
 *         This argument specifies the index at which the search begins,
 *         inclusive.
 * @param  stopIndex
 *         This argument specifies the index at which the search terminates,
 *         exclusive.
 * @return The index of the last occurrence of the specified element,
 *         if found; a negative integer otherwise.
 * @memberof DoublyLinkedList
 */
int32_t jtk_DoublyLinkedList_findLastInRange(jtk_DoublyLinkedList_t* list, void* value, int32_t startIndex, int32_t stopIndex);

/* Iterator */

/**
 * The getIterator() function returns an iterator that provides access to
 * all the elements in this list. The order of the elements corresponds
 * to the order in which they occur in this list.
 *
 * @param  list
 *         This argument specifies the doubly-linked list.
 * @return An iterator that provides access to all the elements in this
 *         collection. The user is responsible for destroying the returned
 *         iterator.
 * @memberof DoublyLinkedList
 */
jtk_Iterator_t* jtk_DoublyLinkedList_getIterator(jtk_DoublyLinkedList_t* list);

/* Remove */

/**
 * The remove() function removes the first occurrence of the specified
 * element from the specified list, provided that it is present. It returns
 * `true` if the specified element was successfully removed;
 * `false` otherwise.
 *
 * @param  list
 *         This argument specifies the list to modify.
 * @param  element
 *         This argument specifies the element to remove.
 * @return `true`, if the specified element was successfully removed;
 *         `false`, otherwise.
 * @memberof DoublyLinkedList
 */
bool jtk_DoublyLinkedList_remove(jtk_DoublyLinkedList_t* list, void* value);

/**
 * The removeAll() function removes every instance of the elements
 * contained in the specified collection from the specified list. It returns
 * the number of elements that were removed; `0`, if none.
 *
 * @param  list
 *         This argument specifies the list to modify.
 * @param  type
 *         This argument specifies the type of the collection.
 * @param  collection
 *         This argument specifies the collection of elements to remove.
 * @return The total number of elements that were removed; `0`, if
 *         none.
 * @memberof DoublyLinkedList
 */
int32_t jtk_DoublyLinkedList_removeAll(jtk_DoublyLinkedList_t* list, jtk_CollectionType_t type, void* collection);

/**
 * The removeAllFromIterator() function removes every instance of the elements
 * returned from the specified iterator from the specified list. It returns
 * the number of elements that were removed; `0`, if none.
 *
 * @param  list
 *         This argument specifies the list to modify.
 * @param  collection
 *         This argument specifies the iterator.
 * @return The total number of elements that were removed; `0`, if
 *         none.
 * @memberof DoublyLinkedList
 */
int32_t jtk_DoublyLinkedList_removeAllFromIterator(jtk_DoublyLinkedList_t* list, jtk_Iterator_t* iterator);

/**
 * The removeIndex() function removes the element at the specified index.
 * Any subsequent elements to the right of the element, if any, are shifted
 * to left by subtracting one from their indices.
 *
 * @param  list
 *         This argument specifies the list to modify.
 * @param  index
 *         This argument specifies the index of the element to remove.
 *         The index should be greater than or equal to zero and lesser than
 *         the size of the list.
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_removeIndex(jtk_DoublyLinkedList_t* list, int32_t index);

/**
 * The removeRange() function removes the elements in the specified range.
 * The range begins at the specified start index (inclusive) and extends
 * to the specified stop index (exclusive).
 *
 * The specified range should be subjected to the following constraints,
 * otherwise an assertion failure is triggered. The starting index should
 * greater than or equal to zero. The starting index should be lesser than
 * or equal to the stopping index. The stopping index should be lesser than the
 * or equal to the size of the list. The following fragment of code shows the
 * constraints:
 * `(startIndex >= 0) && (startIndex <= stopIndex) && (stopIndex <= size)`,
 * where `startIndex}, `stopIndex`, and `size` mean
 * the starting index of the range, the stopping index of the range, and the
 * size of the list, respectively.
 *
 * @param  startIndex
 *         This argument specifies the starting index of the range,
 *         inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range,
 *         exclusive.
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_removeRange(jtk_DoublyLinkedList_t* list, int32_t startIndex, int32_t stopIndex);

/**
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_removeFirst(jtk_DoublyLinkedList_t* list);

/**
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_removeLast(jtk_DoublyLinkedList_t* list);

/* Retain */

// int32_t jtk_DoublyLinkedList_retain(jtk_DoublyLinkedList_t* list, void* value);
// int32_t jtk_DoublyLinkedList_retainAll(jtk_DoublyLinkedList_t* list, jtk_CollectionType_t type, void* collection);
// int32_t jtk_DoublyLinkedList_retainAllFromIterator(jtk_DoublyLinkedList_t* list, jtk_Iterator_t* iterator);

/* Size */

/**
 * The getSize() function returns the size of this list.
 *
 * @param  list
 *         This argument specifies the doubly-linked list.
 * @return The size of this list.
 * @memberof DoublyLinkedList
 */
int32_t jtk_DoublyLinkedList_getSize(jtk_DoublyLinkedList_t* list);

/* Value */

/**
 * The getValue() function returns the element at the specified index.
 *
 * @param  list
 *         This argument specifies the doubly-linked list.
 * @param  index
 *         This argument specifies the index of the element to retrieve.
 *         The index should be greater than or equal to zero and lesser than
 *         the size of the list.
 * @return The element at the specified index.
 * @memberof DoublyLinkedList
 */
void* jtk_DoublyLinkedList_getValue(jtk_DoublyLinkedList_t* list, int32_t index);

/**
 * The setValue() function replaces the element at the specified index with the
 * specified element.
 *
 * @param  list
 *         This argument specifies the doubly-linked list to modify.
 * @param  index
 *         This argument specifies the index of the element to retrieve.
 *         The index should be greater than or equal to zero and lesser than
 *         the size of the list.
 * @param  element
 *         This argument specifies the new element that replaces the old
 *         element.
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_setValue(jtk_DoublyLinkedList_t* list, int32_t index, void* value);

/**
 * @memberof DoublyLinkedList
 */
void* jtk_DoublyLinkedList_getFirst(jtk_DoublyLinkedList_t* list);

/**
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_setFirst(jtk_DoublyLinkedList_t* list, int32_t index, void* value);

/**
 * @memberof DoublyLinkedList
 */
void* jtk_DoublyLinkedList_getLast(jtk_DoublyLinkedList_t* list);

/**
 * @memberof DoublyLinkedList
 */
void jtk_DoublyLinkedList_setLast(jtk_DoublyLinkedList_t* list, int32_t index, void* value);

#endif /* JTK_COLLECTION_DOUBLY_LINKED_LIST_H */