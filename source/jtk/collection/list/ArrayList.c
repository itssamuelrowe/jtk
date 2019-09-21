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

// Sunday, November 05, 2017

#include <jtk/collection/array/Array.h>
#include <jtk/collection/array/Arrays.h>
#include <jtk/collection/list/ArrayList.h>
#include <jtk/collection/list/ArrayListIterator.h>
#include <jtk/collection/CollectionHelper.h>

/*******************************************************************************
 * ArrayList                                                                   *
 *******************************************************************************/

/* Constructor */

jtk_ArrayList_t* jtk_ArrayList_new() {
    return jtk_ArrayList_newEx(JTK_ARRAY_LIST_DEFAULT_CAPACITY, NULL, NULL);
}

jtk_ArrayList_t* jtk_ArrayList_newFromCollection(jtk_CollectionType_t type,
    void* collection) {
    jtk_Assert_assertObject(collection, "The specified collection is empty.");

    jtk_Iterator_t* iterator = jtk_CollectionHelper_getIterator(type, collection);
    jtk_ArrayList_t* result = jtk_ArrayList_newEx(JTK_ARRAY_LIST_DEFAULT_CAPACITY, iterator, NULL);
    jtk_Iterator_delete(iterator);

    return result;
}

jtk_ArrayList_t* jtk_ArrayList_newWithCapacity(int32_t capacity) {
    return jtk_ArrayList_newEx(capacity, NULL, NULL);
}

jtk_ArrayList_t* jtk_ArrayList_newFromIterator(jtk_Iterator_t* iterator) {
    return jtk_ArrayList_newEx(JTK_ARRAY_LIST_DEFAULT_CAPACITY, iterator, NULL);
}

jtk_ArrayList_t* jtk_ArrayList_newWithAdapter(jtk_ObjectAdapter_t* adapter) {
    return jtk_ArrayList_newEx(JTK_ARRAY_LIST_DEFAULT_CAPACITY, NULL, adapter);
}

jtk_ArrayList_t* jtk_ArrayList_newEx(int32_t capacity, jtk_Iterator_t* iterator,
    jtk_ObjectAdapter_t* adapter) {
    jtk_Assert_assertTrue(capacity > 0, "The specified capacity is invalid.");

    jtk_ArrayList_t* list = jtk_Memory_allocate(jtk_ArrayList_t, 1);
    list->m_values = jtk_Memory_allocate(void*, capacity);
    list->m_capacity = capacity;
    list->m_size = 0;
    list->m_adapter = adapter;

    if (iterator != NULL) {
        /* Iterate over the elements provided by the iterator. Add each element
         * to the array list.
         */
        while (jtk_Iterator_hasNext(iterator)) {
            void* value = jtk_Iterator_getNext(iterator);
            jtk_ArrayList_add(list, value);
        }
    }

    /* Return the newly created list. It may be initialized with the elements
     * returned from the iterator.
     */
    return list;
}

/* Destructor */

void jtk_ArrayList_delete(jtk_ArrayList_t* list) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    jtk_Memory_deallocate(list->m_values);
    jtk_Memory_deallocate(list);
}

/* Add */

void jtk_ArrayList_add(jtk_ArrayList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    jtk_ArrayList_addLast(list, value);
}

void jtk_ArrayList_addIndex(jtk_ArrayList_t* list, int32_t index, void* value) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertTrue((index >= 0) && (index <= list->m_size), "The specified index is invalid.");

    jtk_ArrayList_setCapacity(list, list->m_size + 1);
    jtk_Arrays_copyEx_v(list->m_values, list->m_capacity, index, list->m_values,
        list->m_capacity, index + 1, list->m_size - index);
    list->m_values[index] = value;
}

/*
 * WARNING: The specified source array list should not be the destination array list.
 */
int32_t jtk_ArrayList_addAll(jtk_ArrayList_t* list, jtk_CollectionType_t type,
    void* collection) {
    jtk_Assert_assertObject(list, "The specified destination array list is null.");
    jtk_Assert_assertObject(collection, "The specified collection is null.");
    jtk_Assert_assertTrue(list != collection, "The results are undefined when the destination and source collections are the same.");

    jtk_Iterator_t* iterator = jtk_CollectionHelper_getIterator(type, collection);
    return jtk_ArrayList_addAllFromIterator(list, iterator);
}

void jtk_ArrayList_addAllEx(jtk_ArrayList_t* list, jtk_CollectionType_t type,
    void* collection, int32_t index) {
    jtk_Assert_assertObject(list, "The specified destination array list is null.");
    jtk_Assert_assertObject(collection, "The specified collection is null.");
    jtk_Assert_assertTrue(list != collection, "The results are undefined when the destination and source collections are the same.");
    jtk_Assert_assertTrue((index >= 0) && (index <= list->m_size), "The specified index is invalid.");

    int32_t otherSize = 0;
    int32_t otherCapacity = 0;
    void** otherValues = NULL;
    bool destroyOther = false;
    jtk_ArrayList_t* other = NULL;
    if (type == JTK_COLLECTION_ARRAY_LIST) {
        other = (jtk_ArrayList_t*)collection;
        otherSize = other->m_size;
        otherCapacity = other->m_capacity;
        otherValues = other->m_values;
        destroyOther = false;
    }
    else {
        other = jtk_ArrayList_newFromCollection(type, collection);
        otherSize = other->m_size;
        otherCapacity = other->m_capacity;
        otherValues = other->m_values;
        destroyOther = true;
    }

    jtk_ArrayList_setCapacity(list, list->m_size + otherSize);
    jtk_Arrays_copyEx_v(list->m_values, list->m_capacity, index,
        list->m_values, list->m_capacity, index + otherSize, list->m_size - index);
    jtk_Arrays_copyEx_v(otherValues, otherCapacity, 0, list->m_values,
        list->m_capacity, index, otherSize);
    list->m_size += otherSize;

    if (destroyOther) {
        jtk_ArrayList_delete(other);
    }
}

int32_t jtk_ArrayList_addAllFromIterator(jtk_ArrayList_t* list,
    jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(list, "The specified destination array list is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    /* Currently, the implementation adds each element returned from the iterator
     * via jtk_ArrayList_add() function. This causes the library to invoke
     * jtk_ArrayList_setCapacity() multiple times. This may reduce performance
     * negligibly.
     *
     * A solution along the lines of a temporary array may help the
     * implementation increase performance. I am yet to figure it out.
     */

    int32_t result = 0;
    while (jtk_Iterator_hasNext(iterator)) {
        void* value = jtk_Iterator_getNext(iterator);
        jtk_ArrayList_add(list, value);
        result++;
    }
    return result;
}

void jtk_ArrayList_addAllFromIteratorAt(jtk_ArrayList_t* list,
    jtk_Iterator_t* iterator, int32_t index) {
    jtk_Assert_assertObject(list, "The specified destination array list is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    jtk_Assert_assertTrue((index >= 0) && (index <= list->m_size), "The specified index is invalid.");

    /* Currently, the implementation adds each element returned from the iterator
     * into a temporary array list. Later, we invoke the jtk_ArrayList_addAllEx()
     * function which performs the actual operation of inserting the elements
     * into this array list.
     */

    jtk_ArrayList_t* temporary = jtk_ArrayList_newFromIterator(iterator);
    jtk_ArrayList_addAllEx(list, JTK_COLLECTION_ARRAY_LIST, temporary, index);
}

void jtk_ArrayList_addFirst(jtk_ArrayList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_ArrayList_setCapacity(list, list->m_size + 1);

    jtk_ArrayList_setCapacity(list, list->m_size + 1);
    jtk_Arrays_copyEx_v(list->m_values, list->m_capacity, 0,
        list->m_values, list->m_capacity, 1, list->m_size);
    list->m_values[0] = value;
    list->m_size++;
}

void jtk_ArrayList_addLast(jtk_ArrayList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    jtk_ArrayList_setCapacity(list, list->m_size + 1);
    list->m_values[list->m_size] = value;
    list->m_size++;
}

/* Add Predicatively */

void jtk_ArrayList_addPredicatively(jtk_ArrayList_t* list, void* element,
    jtk_MixedPredicateFunction_t predicate) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertObject((void*)predicate, "The specified predicate is null.");

    if (predicate(element)) {
        jtk_ArrayList_add(list, element);
    }
}

void jtk_ArrayList_addAllPredicatively(jtk_ArrayList_t* list,
    jtk_CollectionType_t type, void* collection, jtk_MixedPredicateFunction_t predicate) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertObject((void*)predicate, "The specified predicate is null.");


}

void jtk_ArrayList_addAllFromIteratorPredicatively(jtk_ArrayList_t* list,
    jtk_Iterator_t* iterator, jtk_MixedPredicateFunction_t predicate) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertObject((void*)predicate, "The specified predicate is null.");

}

void jtk_ArrayList_addFirstPredicatively(jtk_ArrayList_t* list, void* value,
    jtk_MixedPredicateFunction_t predicate) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertObject((void*)predicate, "The specified predicate is null.");

    if (predicate(value)) {
        jtk_ArrayList_addFirst(list, value);
    }
}

void jtk_ArrayList_addLastPredicatively(jtk_ArrayList_t* list, void* value,
    jtk_MixedPredicateFunction_t predicate) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertObject((void*)predicate, "The specified predicate is null.");

    if (predicate(value)) {
        jtk_ArrayList_addLast(list, value);
    }
}

/* ArrayList-to-Array */

jtk_Array_t* jtk_ArrayList_toArray(jtk_ArrayList_t* list) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    return jtk_Array_newFromRawArray(list->m_values, list->m_size);
}

void** jtk_ArrayList_toRawArray(jtk_ArrayList_t* list) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    return jtk_Arrays_clone_v(list->m_values, list->m_size);
}

/* Capacity */

int32_t jtk_ArrayList_getCapacity(jtk_ArrayList_t* list) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    return list->m_capacity;
}

void jtk_ArrayList_setCapacity(jtk_ArrayList_t* list, int32_t minimumCapacity) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    if (minimumCapacity > 0) {
        int32_t currentCapacity = list->m_capacity;
        int32_t requireCapacity = minimumCapacity - currentCapacity;
        if (requireCapacity > 0) {
            int32_t newCapacity = currentCapacity * 2;
            if ((newCapacity - minimumCapacity) < 0) {
                newCapacity = minimumCapacity;
            }
            if (newCapacity < 0) {
                // Check if the requested capacity is too big.
                jtk_Assert_assertFalse(minimumCapacity < 0, "An int32_t overflow occurred, the requested capacity is too big.");
                // Fall back, the new capacity was recommended by this function.
                // Oops!
                newCapacity = 0x7FFFFFFF;
            }

            void** temporary = list->m_values;

            list->m_values = jtk_Memory_allocate(void*, newCapacity);
            list->m_capacity = newCapacity;

            int32_t i;
            for (i = 0; i < list->m_size; i++) {
                list->m_values[i] = temporary[i];
            }

            jtk_Memory_deallocate(temporary);
        }
    }
}

void jtk_ArrayList_pack(jtk_ArrayList_t* list) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    if (list->m_size < list->m_capacity) {
        void** temporary = list->m_values;
        list->m_values = jtk_Arrays_clone_v(list->m_values, list->m_size);
        jtk_Memory_deallocate(temporary);
    }
}

/* Clear */

/* WARNING: This function marks the size as zero. The values within the internal
 * array remains the unaltered.
 */
void jtk_ArrayList_clear(jtk_ArrayList_t* list) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    list->m_size = 0;
}

/* Copy to Array */

void jtk_ArrayList_copy(jtk_ArrayList_t* list, jtk_Array_t* array) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertObject(array, "The specified array is null.");

    jtk_ArrayList_copyEx(list, array, 0);
}

void jtk_ArrayList_copyEx(jtk_ArrayList_t* list, jtk_Array_t* array,
    int32_t index) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertObject(array, "The specified array is null.");

    int32_t arraySize = jtk_Array_getSize(array);
    jtk_Assert_assertTrue((index >= 0) && (index < arraySize), "The specified index is invalid.");

    int32_t i;
    for (i = index; (i < list->m_size) && (i < arraySize); i++) {
        void* value = list->m_values[i];
        jtk_Array_setValue(array, i, value);
    }
}

/* Empty */

bool jtk_ArrayList_isEmpty(jtk_ArrayList_t* list) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    return list->m_size == 0;
}

/* Contains */

bool jtk_ArrayList_contains(jtk_ArrayList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    for (int32_t i = 0; i < list->m_size; i++) {
        if (list->m_adapter->compare(list->m_values[i], value) == 0) {
            return true;
        }
    }
    return false;
}

bool jtk_ArrayList_containsAll(jtk_ArrayList_t* list, jtk_CollectionType_t type,
    void* collection) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertObject(collection, "The specified collection is null.");

    bool result = false;

    /* Obtain an iterator for the specified collection type and collection. */
    jtk_Iterator_t* iterator = jtk_CollectionHelper_getIterator(type, collection);

    /* If an unknown collection type is specified, the functions returns false. */
    if (iterator != NULL) {
        /* Delegate the search to jtk_ArrayList_containsAllFromIterator()
         * function which applies a specialized linear search over the elements
         * in the list.
         */
        result = jtk_ArrayList_containsAllFromIterator(list, iterator);

        /* Destroy the iterator. */
        jtk_Iterator_delete(iterator);
    }

    /* Return the result. */
    return result;
}

bool jtk_ArrayList_containsAllFromIterator(jtk_ArrayList_t* list,
    jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    bool result = true;
    while (jtk_Iterator_hasNext(iterator)) {
        void* value = jtk_Iterator_getNext(iterator);
        if (!jtk_ArrayList_contains(list, value)) {
            result = false;
            break;
        }
    }
    return result;
}

/* Find */

int32_t jtk_ArrayList_find(jtk_ArrayList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    return (list->m_size != 0)? jtk_ArrayList_findInRange(list, value, 0, list->m_size) : -1;
}

int32_t jtk_ArrayList_findAfter(jtk_ArrayList_t* list, void* value,
    int32_t index) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertTrue((index >= 0) && (index < list->m_size), "The specified index is invalid.");

    /* jtk_ArrayList_findInRange() states that the start index is inclusive
     * in the linear search algorithm it implements. Therefore, increment
     * the index by one before delegating the search.
     */
    return (list->m_size != 0)? jtk_ArrayList_findInRange(list, value, index + 1, list->m_size) : -1;
}

int32_t jtk_ArrayList_findBefore(jtk_ArrayList_t* list, void* value,
    int32_t index) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertTrue((index >= 0) && (index <= list->m_size), "The specified index is invalid.");

    return (list->m_size != 0)? jtk_ArrayList_findInRange(list, value, 0, index) : -1;
}

int32_t jtk_ArrayList_findInRange(jtk_ArrayList_t* list, void* value,
    int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex <= stopIndex) &&
        (stopIndex <= list->m_size), "The specified range is invalid.");

    int32_t result = -1;
    for (int32_t i = startIndex; i < stopIndex; i++) {
        /* The documentation for the comparator function states that an
         * implementation of a comparator is required to provide comparison
         * of two objects for equivality, at least. Further, the equals()
         * and compare() function should return consistent values for equal
         * values. Thus, they are interchangeable.
         */
        if (list->m_adapter->equals(list->m_values[i], value)) {
            result = i;
            break;
        }
    }
    return result;
}

/* Find Last */

int32_t jtk_ArrayList_findLast(jtk_ArrayList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    return (list->m_size != 0)? jtk_ArrayList_findLastInRange(list, value, 0, list->m_size) : -1;
}

int32_t jtk_ArrayList_findLastAfter(jtk_ArrayList_t* list, void* value,
    int32_t index) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertTrue((index >= 0) && (index < list->m_size), "The specified index is invalid.");

    /* jtk_ArrayList_findLastInRange() states that the start index is inclusive
     * in the linear search algorithm it implements. Therefore, increment
     * the index by one before delegating the search.
     */
    return (list->m_size != 0)? jtk_ArrayList_findLastInRange(list, value, index + 1, list->m_size) : -1;
}

int32_t jtk_ArrayList_findLastBefore(jtk_ArrayList_t* list, void* value,
    int32_t index) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertTrue((index >= 0) && (index <= list->m_size), "The specified index is invalid.");

    return (list->m_size != 0)? jtk_ArrayList_findLastInRange(list, value, 0, index) : -1;
}

int32_t jtk_ArrayList_findLastInRange(jtk_ArrayList_t* list, void* value,
    int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex <= stopIndex) &&
        (stopIndex <= list->m_size), "The specified range is invalid.");

    int32_t result = -1;
    for (int32_t i = stopIndex - 1; i >= startIndex; i--) {
        /* The documentation for the comparator function states that an
         * implementation of a comparator is required to provide comparison
         * of two objects for equivality, at least. Further, the equals()
         * and compare() function should return consistent values for equal
         * values. Thus, they are interchangeable.
         */
        if (list->m_adapter->equals(list->m_values[i], value)) {
            result = i;
            break;
        }
    }
    return result;
}

/* Iterator */

jtk_Iterator_t* jtk_ArrayList_getIterator(jtk_ArrayList_t* list) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    jtk_ArrayListIterator_t* iterator = jtk_ArrayListIterator_new(list);
    return jtk_ArrayListIterator_getIterator(iterator);
}

/* Remove */

bool jtk_ArrayList_remove(jtk_ArrayList_t* list, void* element) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    bool result = false;
    int32_t index;
    for (index = 0; index < list->m_size; index++) {
        if (list->m_adapter->equals(element, list->m_values[index])) {
            int32_t moved = list->m_size - index - 1;
            if (moved > 0) {
                jtk_Arrays_copyEx_v(list->m_values, list->m_capacity, index + 1,
                    list->m_values, list->m_capacity, index, moved);
            }
            list->m_size--;

            result = true;
            break;
        }
    }
    return result;
}

static int32_t jtk_ArrayList_removeAll0(jtk_ArrayList_t* list, jtk_ArrayList_t* temporary) {
    int32_t result = 0;
    int32_t index;
    for (index = 0; index < list->m_size; index++) {
        if (jtk_ArrayList_contains(temporary, list->m_values[index])) {
            int32_t moved = list->m_size - index - 1;
            if (moved > 0) {
                jtk_Arrays_copyEx_v(list->m_values, list->m_capacity, index + 1,
                    list->m_values, list->m_capacity, index, moved);
            }
            result++;
        }
    }
    list->m_size -= result;

    return result;
}

int32_t jtk_ArrayList_removeAll(jtk_ArrayList_t* list, jtk_CollectionType_t type,
    void* collection) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertObject(collection, "The specified collection is null.");

    jtk_ArrayList_t* temporary = jtk_ArrayList_newFromCollection(type, collection);
    int32_t result = jtk_ArrayList_removeAll0(list, temporary);
    jtk_ArrayList_delete(temporary);

    return result;
}

int32_t jtk_ArrayList_removeAllFromIterator(jtk_ArrayList_t* list,
    jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    jtk_ArrayList_t* temporary = jtk_ArrayList_newFromIterator(iterator);
    int32_t result = jtk_ArrayList_removeAll0(list, temporary);
    jtk_ArrayList_delete(temporary);

    return result;
}

void jtk_ArrayList_removeIndex(jtk_ArrayList_t* list, int32_t index) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertTrue((index >= 0) && (index < list->m_size), "The specified index is invalid.");

    int32_t moved = list->m_size - index - 1;
    if (moved > 0) {
        jtk_Arrays_copyEx_v(list->m_values, list->m_capacity,
            index + 1, list->m_values, list->m_capacity,
            index, moved);
    }
    list->m_size--;
}

void jtk_ArrayList_removeLat(jtk_ArrayList_t* list) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertTrue(list->m_size >= 1, "The specified index is invalid.");

    list->m_values[--list->m_size] = NULL;
}

int32_t jtk_ArrayList_removeRange(jtk_ArrayList_t* list, int32_t startIndex,
    int32_t stopIndex) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex <= stopIndex) &&
        (stopIndex <= list->m_size), "The specified range is invalid.");

    int32_t moved = list->m_size - stopIndex;
    jtk_Arrays_copyEx_v(list->m_values, list->m_capacity, stopIndex,
        list->m_values, list->m_capacity, startIndex, moved);
    int32_t removed = stopIndex - startIndex;
    list->m_size = list->m_size - removed;

    return removed;
}

/* Size */

int32_t jtk_ArrayList_getSize(jtk_ArrayList_t* list) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    return list->m_size;
}

/* Value */

void* jtk_ArrayList_getValue(jtk_ArrayList_t* list, int32_t index) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertFalse(((index < 0) || (index >= list->m_size)), "The specified index is invalid.");

    return list->m_values[index];
}

void jtk_ArrayList_setValue(jtk_ArrayList_t* list, int32_t index, void* value) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertFalse(((index < 0) || (index >= list->m_size)), "The specified index is invalid.");

    list->m_values[index] = value;
}