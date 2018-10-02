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
 
// Sunday, November 05, 2017

#ifndef JTK_ARRAY_LIST_H
#define JTK_ARRAY_LIST_H

#include <jtk/Configuration.h>
#include <jtk/collection/CollectionType.h>
#include <jtk/collection/Iterator.h>
#include <jtk/collection/array/Array.h>
#include <jtk/core/ObjectAdapter.h>
#include <jtk/function/PredicateFunction.h>
#include <jtk/function/ComparatorFunction.h>

/*******************************************************************************
 * ArrayList                                                                   *
 *******************************************************************************/

#define JTK_ARRAY_LIST_DEFAULT_CAPACITY 16

/**
 * The ArrayList class represents a list backed by an array. The internal
 * array grows and shrinks as needed. As of this version, no interface is
 * provided to extract a reference to the internal array (although an interface
 * to obtain a copy is provided).
 *
 * The ArrayList class provides fast random access with error checking, when
 * assertions are enabled. An element is accessed by its integer index, the
 * position in the list. An attempt to access an element with an invalid index,
 * results in an assertion failure, if enabled. The indices of a list are
 * of the form: `0, 1, 2, 3, 4, 5, 6, 7, ... n - 1`. The first item of
 * the sequence is at index `0`, the next at index `1`, and so on.
 * Thus, for a list containing ten elements, the valid indices range from
 * `0` (inclusive) to `10` (exclusive).
 *
 * The size of the internal array represents the capacity of the list, not
 * the size of the list. A simple interface is provided to manipulate the
 * capacity. The capacity is always greater or equal to the size of the list.
 * Further, it is automatically adjusted as needed. It may grow or shrink
 * contingent on the size of the list.
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
 * The ArrayList class is intended to be used by a single thread. It does not
 * implement a thread synchronization policy. In other words, it is not thread
 * safe. Concurrent invocation of a function against an instance without an
 * external synchronization results in undefined behaviour.
 *
 * Further, it is recommended that the user avoids accessing the fields of
 * this structure directly. They may be subjected to changes without any
 * notifications. Please employ appropriate interfaces with detailed
 * documentation.
 *
 * @class ArrayList
 * @ingroup jtk_collection_list
 * @author Samuel Rowe
 * @since JTK 1.0
 */
struct jtk_ArrayList_t {

    /**
     * The internal storage in which the elements are stored. The capacity of
     * this list is equal to the size of this array.
     */
    void** m_values;

    /**
     * The maximum number of elements that can be stored in the list.
     */
    int32_t m_capacity;

    /**
     * The number of elements this array list contains, initially zero.
     */
    int32_t m_size;

    /**
     * The adapter used to adapt elements as objects.
     */
    jtk_ObjectAdapter_t* m_adapter;
};

typedef struct jtk_ArrayList_t jtk_ArrayList_t;

/* Constructor */

/**
 * Creates an empty array list with the default initial capacity.
 *
 * @return The newly created array list. The user is responsible for destroying
 *         the list.
 * @memberof ArrayList
 */
jtk_ArrayList_t* jtk_ArrayList_new();

/**
 * Creates an empty ArrayList with the specified initial capacity.
 *
 * @param  capacity
 *         This argument specifies the initial capacity. All zero and negative
 *         integer values are considered illegal.
 * @return The newly created array list. The user is responsible for destroying
 *         the list.
 * @memberof ArrayList
 */
jtk_ArrayList_t* jtk_ArrayList_newWithCapacity(int32_t capacity);

/**
 * Creates an ArrayList with the specified initial content, that is, the
 * elements contained in the specified collection. The order of the elements
 * depends on the iterator returned by the specified collection.
 *
 * @param  type
 *         This argument specifies the type of the collection.
 * @param  collection
 *         This argument specifies the collection from which the initial content
 *         of this array list is extracted.
 * @return The newly created array list. The user is responsible for destroying
 *         the list.
 * @memberof ArrayList
 */
jtk_ArrayList_t* jtk_ArrayList_newFromCollection(jtk_CollectionType_t type, void* collection);

/**
 * Creates an ArrayList with the specified initial content, that is, the
 * elements return by the specified iterator. The order of the elements
 * depends on the iterator.
 *
 * @param  iterator
 *         This argument specifies the iterator from which the initial content
 *         of this array list is extracted.
 * @return The newly created array list. The user is responsible for destroying
 *         the list.
 * @memberof ArrayList
 */
jtk_ArrayList_t* jtk_ArrayList_newFromIterator(jtk_Iterator_t* iterator);

/**
 * Creates an empty array list with the default initial capacity. The specified
 * object adapter is attached to the list.
 *
 * @param  adapter
 *         This argument specifies the object adapter to attach.
 * @return The newly created array list. The user is responsible for destroying
 *         the list.
 * @memberof ArrayList
 */
jtk_ArrayList_t* jtk_ArrayList_newWithAdapter(jtk_ObjectAdapter_t* adapter);

/**
 * @memberof ArrayList
 */
jtk_ArrayList_t* jtk_ArrayList_newEx(int32_t capacity, jtk_Iterator_t* iterator, jtk_ObjectAdapter_t* adapter);

/* Destructor */

/**
 * Destroys the specified array list.
 *
 * @param  list
 *         This argument specifies the array list to destroy.
 * @memberof ArrayList
 */
void jtk_ArrayList_delete(jtk_ArrayList_t* list);

/* Add */

/**
 * The add() function adds the specified element to the end of this
 * list.
 *
 * @param  list
 *         This argument specifies the array list to modify.
 * @param  value
 *         This argument specifies the element to add.
 * @memberof ArrayList
 */
void jtk_ArrayList_add(jtk_ArrayList_t* list, void* value);

/**
 * The addIndex() function inserts the specified element at the specified
 * index. The current element and any subsequent elements to the right
 * of the specified index, if any, are shifted to right by adding one
 * to their indices.
 *
 * @param  list
 *         This argument specifies the array list to modify.
 * @param  index
 *         This argument specifies the index at which the element has to
 *         be inserted. An index should be greater than or equal to zero
 *         and lesser than or equal to the size of the list.
 * @param  value
 *         This argument specifies the element to add.
 * @memberof ArrayList
 */
void jtk_ArrayList_addIndex(jtk_ArrayList_t* list, int32_t index, void* value);

/**
 * The addAll() function adds all the elements contained in the specified
 * collection to the end of the specified array list. The order of the elements
 * inserted depends on the iterator returned by the specified collection.
 * It returns the total number of elements that were added; `0`, if none.
 *
 * The behaviour of this function is undefined, if the specified collection
 * is modified while this function is in progress. This problem may arise
 * if the specified collection is this collection.
 *
 * @param  list
 *         This argument specifies the array list to modify.
 * @param  type
 *         This argument specifies the type of the collection.
 * @param  collection
 *         This argument specifies the collection of elements to add.
 * @return The total number of elements that were added; `0`, if
 *         none.
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_addAll(jtk_ArrayList_t* list, jtk_CollectionType_t type, void* collection);

/**
 * The addAll() function adds all the elements contained in the specified
 * collection into the specified array list. The elements are inserted
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
 *         This argument specifies the array list to modify.
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
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_addAllAt(jtk_ArrayList_t* list, jtk_CollectionType_t type, void* collection, int32_t index);

/**
 * The addAllFromIterator() function adds all the elements returned from the
 * specified iterator to the end of the specified array list. The order of the
 * elements inserted depends on the iterator. It returns the total number of
 * elements that were added; `0`, if none.
 *
 * The behaviour of this function is undefined, if the source of the iterator
 * is modified while this function is in progress. This problem may arise
 * if the source of the specified iterator is this collection.
 *
 * @param  list
 *         This argument specifies the array list to modify.
 * @param  iterator
 *         This argument specifies the iterator from where the elements are
 *         extracted.
 * @return The total number of elements that were added; `0`, if
 *         none.
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_addAllFromIterator(jtk_ArrayList_t* list, jtk_Iterator_t* iterator);

/**
 * The addAll() function adds all the elements return from the specified
 * iterator into the specified array list. The elements are inserted
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
 *         This argument specifies the array list to modify.
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
 * @memberof ArrayList
 */
void jtk_ArrayList_addAllFromIteratorAt(jtk_ArrayList_t* list, jtk_Iterator_t* iterator, int32_t index);

/**
 * The addFirst() function adds the specified element to the start of this
 * list.
 *
 * @param  list
 *         This argument specifies the array list to modify.
 * @param  value
 *         This argument specifies the element to add.
 * @memberof ArrayList
 */
void jtk_ArrayList_addFirst(jtk_ArrayList_t* list, void* value);

/**
 * The addLast() function adds the specified element to the end of this
 * list. It is equivalent to invoking `jtk_ArrayList_add()` function.
 * It is provided for balancing consistency in function names.
 *
 * @param  list
 *         This argument specifies the array list to modify.
 * @param  value
 *         This argument specifies the element to add.
 * @memberof ArrayList
 */
void jtk_ArrayList_addLast(jtk_ArrayList_t* list, void* value);

/* Add Predicatively */

/**
 * @memberof ArrayList
 */
void jtk_ArrayList_addPredicatively(jtk_ArrayList_t* list, void* value, jtk_PredicateFunction_t predicate);

// void jtk_ArrayList_addAllPredicatively(jtk_ArrayList_t* list, jtk_CollectionType_t type, void* collection, jtk_PredicateFunction_t predicate);

// void jtk_ArrayList_addAllFromIteratorPredicatively(jtk_ArrayList_t* list, jtk_Iterator_t* iterator, jtk_PredicateFunction_t predicate);

/**
 * @memberof ArrayList
 */
void jtk_ArrayList_addFirstPredicatively(jtk_ArrayList_t* list, void* value, jtk_PredicateFunction_t predicate);

/**
 * @memberof ArrayList
 */
void jtk_ArrayList_addLastPredicatively(jtk_ArrayList_t* list, void* value, jtk_PredicateFunction_t predicate);

/* ArrayList-to-Array */

/**
 * @memberof ArrayList
 */
jtk_Array_t* jtk_ArrayList_toArray(jtk_ArrayList_t* list);

/**
 * @memberof ArrayList
 */
void** jtk_ArrayList_toRawArray(jtk_ArrayList_t* list);

/* Capacity */

/**
 * The setCapacity() function ensures the capacity of this array list
 * to be at least equal to the specified minimum capacity. Invoking this
 * function is effective only if the current capacity is smaller than the
 * specified minimum capacity. Depending on the larger value of, the new
 * capacity is equal to the specified minimum capacity or twice the old
 * capacity.
 *
 * If the specified minimum capacity is negative, no operation takes place.
 *
 * @param  list
 *         This argument specifies the list to modify.
 * @param  capacity
 *         This argument specifies the minimum capacity.
 * @memberof ArrayList
 */
void jtk_ArrayList_setCapacity(jtk_ArrayList_t* list, int32_t minimumCapacity);

/**
 * Returns the current capacity of this array list.
 *
 * Capacity is defined as the number of elements that can be inserted to
 * this array list before, internally, reallocation occurs. It may change
 * without any notification to the user.
 *
 * @param  list
 *         This argument specifies the array list whose capacity is required.
 * @return The current capacity of this array list.
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_getCapacity(jtk_ArrayList_t* list);

/**
 * The pack() function attempts to reduce the internal storage by reducing
 * the capacity. Invocation of this function may, but is not required to,
 * result in reduction of the capacity to the current size.
 *
 * @param  list
 *         This argument specifies the array list whose capacity is required.
 * @memberof ArrayList
 */
void jtk_ArrayList_pack(jtk_ArrayList_t* list);

/* Clear */

/**
 * The clear() function removes all the elements from this list. When this
 * function returns the capacity of this list remains unchanged.
 *
 * Internally, this function simply resets the size. The capacity of the list
 * remains unchanged. To reduce the memory footprint, invoke the `jtk_ArrayList_pack()`
 * function.
 *
 * @param  list
 *         This argument specifies the array list to clear.
 * @memberof ArrayList
 */
void jtk_ArrayList_clear(jtk_ArrayList_t* list);

/* Copy */

/**
 * @memberof ArrayList
 */
void jtk_ArrayList_copy(jtk_ArrayList_t* list, jtk_Array_t* array);

/**
 * @memberof ArrayList
 */
void jtk_ArrayList_copyEx(jtk_ArrayList_t* list, jtk_Array_t* array, int32_t index);

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
 * @memberof ArrayList
 */
bool jtk_ArrayList_contains(jtk_ArrayList_t* list, void* value);

/**
 * The containsAll() function returns `true` if the specified array
 * list contains all the elements contained in the specified collection;
 * `false` otherwise.
 *
 * @param  type
 *         This argument specifies the type of the collection.
 * @param  collection
 *         This argument specifies the collection of elements to test.
 * @return `true` if this list contains all the elements
 *         contained in the specified collection; `false` otherwise.
 * @memberof ArrayList
 */
bool jtk_ArrayList_containsAll(jtk_ArrayList_t* list, jtk_CollectionType_t type, void* collection);

/**
 * The containsAllFromIterator() function returns `true` if the specified
 * array list contains all the elements return from the specified iterator;
 * `false` otherwise.
 *
 * @param  iterator
 *         This argument specifies the iterator.
 * @return `true` if this list contains all the elements
 *         contained in the specified collection; `false` otherwise.
 * @memberof ArrayList
 */
bool jtk_ArrayList_containsAllFromIterator(jtk_ArrayList_t* list, jtk_Iterator_t* iterator);

/* Empty */

/**
 * The isEmpty() function returns `true` if this list contains no
 * elements; `false` otherwise.
 *
 * @param  list
 *         This argument specifies the array list to test.
 * @return `true` if this collection contains no elements;
 *         `false` otherwise.
 * @memberof ArrayList
 */
bool jtk_ArrayList_isEmpty(jtk_ArrayList_t* list);

/* Find */

/**
 * Finds the first occurrence of the specified element in the specified list.
 * It returns a valid index, if found using the linear search algorithm; a
 * negative integer otherwise.
 *
 * @param  list
 *         This argument specifies the array list to search.
 * @param  element
 *         This argument specifies the element to find.
 * @return The index of the first occurrence of the specified element,
 *         if found; a negative integer otherwise.
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_find(jtk_ArrayList_t* list, void* value);

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
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_findAfter(jtk_ArrayList_t* list, void* value, int32_t index);

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
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_findBefore(jtk_ArrayList_t* list, void* value, int32_t index);

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
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_findInRange(jtk_ArrayList_t* list, void* value, int32_t startIndex, int32_t stopIndex);

/* Find Last */

/**
 * Finds the last occurrence of the specified element in the specified list.
 * It returns a valid index, if found using the linear search algorithm; a
 * negative integer otherwise.
 *
 * @param  list
 *         This argument specifies the array list to search.
 * @param  element
 *         This argument specifies the element to find.
 * @return The index of the last occurrence of the specified element,
 *         if found; a negative integer otherwise.
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_findLast(jtk_ArrayList_t* list, void* value);

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
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_findLastAfter(jtk_ArrayList_t* list, void* value, int32_t index);

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
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_findLastBefore(jtk_ArrayList_t* list, void* value, int32_t index);

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
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_findLastInRange(jtk_ArrayList_t* list, void* value, int32_t startIndex, int32_t stopIndex);

/* Iterator */

/**
 * The getIterator() function returns an iterator that provides access to
 * all the elements in this list. The order of the elements corresponds
 * to the order in which they occur in this list.
 *
 * @param  list
 *         This argument specifies the array list.
 * @return An iterator that provides access to all the elements in this
 *         collection. The user is responsible for destroying the returned
 *         iterator.
 * @memberof ArrayList
 */
jtk_Iterator_t* jtk_ArrayList_getIterator(jtk_ArrayList_t* list);

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
 * @memberof ArrayList
 */
bool jtk_ArrayList_remove(jtk_ArrayList_t* list, void* value);

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
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_removeAll(jtk_ArrayList_t* list, jtk_CollectionType_t type, void* collection);

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
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_removeAllFromIterator(jtk_ArrayList_t* list, jtk_Iterator_t* iterator);

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
 * @memberof ArrayList
 */
void jtk_ArrayList_removeIndex(jtk_ArrayList_t* list, int32_t index);

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
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_removeRange(jtk_ArrayList_t* list, int32_t startIndex, int32_t stopIndex);

/* Retain */

// int32_t jtk_ArrayList_retain(jtk_ArrayList_t* list, void* value);
// int32_t jtk_ArrayList_retainAll(jtk_ArrayList_t* list, jtk_CollectionType_t type, void* collection);
// int32_t jtk_ArrayList_retainAllFromIterator(jtk_ArrayList_t* list, jtk_Iterator_t* iterator);

/* Size */

/**
 * The getSize() function returns the size of this list.
 *
 * @param  list
 *         This argument specifies the array list.
 * @return The size of this list.
 * @memberof ArrayList
 */
int32_t jtk_ArrayList_getSize(jtk_ArrayList_t* list);

/* Value */

/**
 * The getValue() function returns the element at the specified index.
 *
 * @param  list
 *         This argument specifies the array list.
 * @param  index
 *         This argument specifies the index of the element to retrieve.
 *         The index should be greater than or equal to zero and lesser than
 *         the size of the list.
 * @return The element at the specified index.
 * @memberof ArrayList
 */
void* jtk_ArrayList_getValue(jtk_ArrayList_t* list, int32_t index);

/**
 * The setValue() function replaces the element at the specified index with the
 * specified element.
 *
 * @param  list
 *         This argument specifies the array list to modify.
 * @param  index
 *         This argument specifies the index of the element to retrieve.
 *         The index should be greater than or equal to zero and lesser than
 *         the size of the list.
 * @param  element
 *         This argument specifies the new element that replaces the old
 *         element.
 * @memberof ArrayList
 */
void jtk_ArrayList_setValue(jtk_ArrayList_t* list, int32_t index, void* value);

#endif /* JTK_ARRAY_LIST_H */

// TODO: What happens to the list when all the elements are removed and packed?
// TODO: What happens when a newly initialized list is packed? Possibly the
//       framework tries to create an array with zero elements. Possible BUG!
// TODO: Change documentation for ranges.