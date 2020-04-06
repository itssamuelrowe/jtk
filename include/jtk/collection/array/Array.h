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

// Sunday, June 03, 2018

#ifndef JTK_COLLECTION_ARRAY_ARRAY_H
#define JTK_COLLECTION_ARRAY_ARRAY_H

#include <jtk/core/ObjectAdapter.h>
#include <jtk/function/PredicateFunction.h>
#include <jtk/collection/Iterator.h>

/*******************************************************************************
 * Array                                                                       *
 *******************************************************************************/

#define JTK_ARRAY_INTERNAL_FLAG_WRAPPER (1 << 0)
#define JTK_ARRAY_INTERNAL_FLAG_DESTROY_NATIVE_ARRAY (1 << 1)

/**
 * @memberof Array
 */
typedef struct jtk_Array_t jtk_Array_t;

/**
 * @memberof Arrays
 */
typedef void* (*jtk_Array_MigrateFunction_t)(void* value);

/**
 * The Array class represents an ordered sequence of objects of the same type,
 * known as its component type. Each item of an array is called an element.
 * An array has a fixed size that is set when the array is constructed. The size
 * determines the number of elements that can be stored in the array.
 *
 * The Array class provides fast random access with error checking. An element
 * is accessed by its integer index, the position in the array. An attempt to
 * access an element with an invalid index results in an assertion failure,
 * if enabled. The indices of an array are of the form: `0, 1, 2, 3, 4,
 * 5, 6, 7, ... n - 1}. The first item of the sequence is at index `0`,
 * the next at index `1`, and so on. Thus, for an array of ten elements,
 * the valid indices range from `0` (inclusive) to `10` (exclusive).
 *
 * To avoid confusion, the documentation of the Jez Toolkit (JTK) Framework
 * refers to instances of this class as "arrays" and native arrays provided by
 * the C programming language as "raw arrays" or "native arrays". Moreover,
 * the Array class is provided as an alternative to raw arrays. Where using a
 * raw array would result in undefined behaviour, as specified by the C standard,
 * using the `Array` class would result in assertion failures, if enabled.
 *
 * Unlike native arrays, arrays in JTK initialize all the elements to `NULL`
 * on creation.
 *
 * <blockquote><code>
 * jtk_Array_t* array = jtk_Array_new(10);
 * xyz_Object_t* object = xyz_Object_new();
 * jtk_Array_setValue(array, 0, object);
 *
 * </code></blockquote>
 *
 * @class  Array
 * @ingroup JtkCollectionModule
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_Array_t {

    /**
     * The internal array used to store the elements. If this array is empty,
     * it is `null`.
     */
    void** m_values;

    /**
     * The number of elements contained.
     */
    int32_t m_size;

    /**
     * Internal flags. The user should not directly access this field.
     * It may be subjected to undocumented changes in the upcoming versions.
     *
     * This field is unused as of this version.
     */
    int8_t m_internalFlags;

    /**
     * The adapter which provides object related operations over the elements
     * contained in the array.
     */
    jtk_ObjectAdapter_t* m_adapter;
};

/* Constructor */

/**
 * Creates an array of the specified size. The elements in the new array are
 * initialized to `NULL`. This behaviour can be altered by using
 * `jtk_Array_newWithDefaultValue()`.
 *
 * @param  size
 *         The size of the array.
 * @return The newly created array.
 * @memberof Array
 */
jtk_Array_t* jtk_Array_new(int32_t size);

/**
 * Creates an array from the specified native array. The elements in the new
 * array are initialized to the corresponding elements from the specified array.
 *
 * @param  other
 *         The native array.
 * @param  size
 *         The size of the native array.
 * @return The newly created array.
 * @memberof Array
 */
jtk_Array_t* jtk_Array_newFromRawArray(void** other, int32_t size);

/**
 * Creates an array of the specified size. The elements in the new array are
 * initialized to the specified default value.
 *
 * @param  size
 *         This argument specifies the size.
 * @param  defaultValue
 *         This argument specifies the default value.
 * @return The newly created array.
 * @memberof Array
 */
jtk_Array_t* jtk_Array_newWithDefaultValue(int32_t size, void* defaultValue);

// jtk_Array_t* jtk_Array_newWrapper(void** values, int32_t size, bool transfer);

/* Destructor */

/**
 * Destroys the specified array.
 *
 * @param  array
 *         The array to destroy.
 * @memberof Array
 */
void jtk_Array_delete(jtk_Array_t* array);

/* Binary Search */

/*
 * Searches the specified array for an occurrence of the specified key. To
 * state the obvious, it implements the binary search algorithm. The specified
 * array is expected to be sorted, otherwise the result is undefined. If found,
 * it returns an index of the key within the bounds of the array; a negative
 * integer otherwise.
 *
 * If an object adapter was previously attached to the array, then the
 * comparison is evaluated via the `compare()` function; otherwise
 * the comparison operators are employed.
 *
 * @param  array
 *         This argument specifies the array to search.
 * @param  key
 *         This argument specifies the value to search.
 * @return If found, an index of the key within the bounds of the array;
 *         `-1` otherwise.
 */
// int32_t jtk_Array_binarySearch(jtk_Array_t* array, void* key);

/* Binary Search Extended */

/*
 * Searches the specified array for an occurrence of the specified key, within
 * the specified range. To state the obvious, it implements the binary search
 * algorithm. The specified array is expected to be sorted, otherwise the result
 * is undefined. If found, it returns an index of the key within the bounds of
 * the array; a negative integer otherwise.
 *
 * The specified range should be subjected to the following constraints,
 * otherwise an assertion failure is triggered. The starting index should
 * greater than or equal to zero. The starting index should be lesser than
 * or equal to the stopping index. The stopping index should be lesser than the
 * or equal to the size of the array. The following fragment of code shows the
 * constraints:
 * `(startIndex >= 0) && (startIndex <= stopIndex) && (stopIndex <= size)`,
 * where `startIndex}, `stopIndex`, and `size` mean
 * the starting index of the range, the stopping index of the range, and the
 * size of the array, respectively.
 *
 * If an object adapter was previously attached to the array, then the
 * comparison is evaluated via the `compare()` function; otherwise
 * the comparison operators are employed.
 *
 * @param array
 *         This argument specifies the array to search.
 * @param  startIndex
 *         This argument specifies the starting index of the range,
 *         inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range,
 *         exclusive.
 * @param  key
 *         This argument specifies the value to search.
 * @return If found, an index of the key within the bounds of the array;
 *         a negative integer otherwise.
 */
// int32_t jtk_Array_binarySearchEx(jtk_Array_t* array, int32_t startIndex, int32_t stopIndex, void* key);

/* Copy */

/**
 * Copies the elements from the specified source array to the specified
 * destination array. It returns the number of elements that were copied.
 * If the specified source and destination arrays refer to the same array,
 * `0` is returned and the specified destination array is not modified.
 *
 * @param  source
 *         This argument specifies the source array.
 * @param  destination
 *         This argument specifies the destination array.
 * @return The number of elements that were copied.
 * @memberof Array
 */
int32_t jtk_Array_copy(jtk_Array_t* source, jtk_Array_t* destination);

/* Copy Extended */

/**
 * Copies the elements from the specified source array, beginning at the
 * specified index, to the specified destination array. The number of elements
 * copied is equal to the specified size. The elements from the specified
 * source index through `sourceIndex + size - 1` in the source array are
 * copied to the specified destination array from the specified destination
 * index through `destinationIndex + size - 1`.
 *
 * The following cases are considered illegal and cause an assertion failure,
 * when enabled.
 *         <ul>
 *         <li>The specified source index is negative.</li>
 *         <li>The specified destination index is negative.</li>
 *         <li>The specified size is negative.</li>
 *         <li>`sourceIndex + size` is greater than the size of the
 *             source array.</li>
 *         <li>`destinationIndex + size` is greater than the size
 *             of the destination array.</li>
 *         </ul>
 *
 * @param  source
 *         This argument specifies the source array.
 * @param  sourceIndex
 *         This argument specifies the index in the source array.
 * @param  destination
 *         This argument specifies the destination array.
 * @param  destinationIndex
 *         This argument specifies the index in the destination array.
 * @param  size
 *         This argument specifies the number of elements to copy.
 * @return The number of elements that were copied.
 * @memberof Array
 */
int32_t jtk_Array_copyEx(jtk_Array_t* source, int32_t sourceIndex, jtk_Array_t* destination, int32_t destinationIndex, int32_t size);

/* Copy Of */

/**
 * Returns a copy of the specified array, truncated or padded to obtain the
 * specified size.
 *
 * @param  source
 *         This argument specifies the source array.
 * @param  newSize
 *         This argument specifies the size of the resulting array.
 *         All negative values are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified source array of the specified size,
 *         if necessary, the returned array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Array
 */
jtk_Array_t* jtk_Array_copyOf(jtk_Array_t* source, int32_t newSize, void* defaultValue);

/* Copy Of Range */

/**
 * Returns a copy of the specified range of the specified array, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the source array.
 * @param  startIndex
 *         This argument specifies the starting index of the range,
 *         inclusive. All negative values are considered illegal. Further,
 *         the value of the starting index should not exceed the size of the
 *         source array or the stopping index.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range,
 *         exclusive. It may exceed the size of the array.
 * @param  defaultValue
 *         This argument specifies the default value used for padding,
 *         if necessary.
 * @return A copy of the specified range of the specified source array,
 *         if necessary, the returned array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Array
 */
jtk_Array_t* jtk_Array_copyOfRange(jtk_Array_t* source, int32_t startIndex, int32_t stopIndex, void* defaultValue);

jtk_Array_t* jtk_Array_clone(jtk_Array_t* other);

/* Destroy Native Array */

// void jtk_Array_setDestroyNativeArray(jtk_Array_t* array, bool destroyNativeArray);
// bool jtk_Array_destroysNativeArray(jtk_Array_t* array);

/* Empty */

/**
 * Determines whether the specified array is empty, or not.
 *
 * @param  array
 *         This argument specifies the array to test.
 * @return `true` if the specified array is empty; `false` otherwise.
 * @memberof Array
 */
bool jtk_Array_isEmpty(jtk_Array_t* array);

/* Equals */

/**
 * Determines whether the specified arrays are equal, or not.
 *
 * Two arrays are considered equal if both arrays contain the same number
 * of elements, and all corresponding elements in the two arrays are equal,
 * as determined by the comparator attached to the first array. If the first
 * array has no comparator, the comparison operators are employed.
 *
 * @param  array1
 *         This argument specifies the first array.
 * @param  array2
 *         This argument specifies the second array.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Array
 */
bool jtk_Array_equals(jtk_Array_t* array1, jtk_Array_t* array2);

/* Equals Extended */

/**
 * Determines whether the specified ranges within the specified arrays are
 * equal, or not.
 *
 * Two ranges within two arrays are considered equal if both the ranges contain
 * the same number of elements, and all corresponding elements in the two arrays
 * are equal, as determined by the comparator attached to the first array. If
 * the first array has no comparator, the comparison operators are employed.
 *
 * The following cases are considered illegal and cause an assertion failure,
 * when enabled.
 *         <ul>
 *         <li>The specified first index is negative.</li>
 *         <li>The specified second index is negative.</li>
 *         <li>The specified size is negative.</li>
 *         <li>`index1 + size` is greater than the size of the
 *             first array.</li>
 *         <li>`index2 + size` is greater than the size
 *             of the second array.</li>
 *         </ul>
 *
 * @param  array1
 *         This argument specifies the first array.
 * @param  array2
 *         This argument specifies the second array.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Array
 */
bool jtk_Array_equalsEx(jtk_Array_t* array1, int32_t index1, jtk_Array_t* array2, int32_t index2, int32_t size);

/* Fill */

/**
 * Sets all the elements in the specified array to the specified value.
 *
 * @param  array
 *         This argument specifies the array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Array
 */
void jtk_Array_fill(jtk_Array_t* array, void* value);

/* Fill Extended */

/**
 * Sets all the elements in the specified range within the specified array to
 * the specified value.
 *
 * The specified range should be subjected to the following constraints,
 * otherwise an assertion failure is triggered. The starting index should
 * greater than or equal to zero. The starting index should be lesser than
 * or equal to the stopping index. The stopping index should be lesser than the
 * size of the array. The following fragment of code shows the constraints:
 * `(startIndex >= 0) && (startIndex <= stopIndex) && (stopIndex < m_size)`,
 * where `startIndex}, `stopIndex`, and `size` mean
 * the starting index of the range, the stopping index of the range, and the
 * size of the array, respectively.
 *
 * @param  array
 *         This argument specifies the array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  startIndex
 *         This argument specifies the starting index of the range, inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range, exclusive.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Array
 */
void jtk_Array_fillEx(jtk_Array_t* array, int32_t startIndex, int32_t stopIndex, void* value);

/* Filter */

// void** jtk_Array_filter(jtk_Array_t* array, jtk_MixedPredicateFunction_t predicate);

/* Filter Extended */

// void** jtk_Array_filterEx(jtk_Array_t* array, int32_t startIndex, int32_t stopIndex, jtk_MixedPredicateFunction_t predicate);

/* Iterator */

/**
 * The getIterator() function returns an iterator that provides access to
 * all the elements in this array. The order of the elements corresponds
 * to the order in which they occur in this array.
 *
 * @param  array
 *         This argument specifies the array.
 * @return An iterator that provides access to all the elements in this
 *         array. The user is responsible for destroying the returned
 *         iterator.
 * @memberof Array
 */
jtk_Iterator_t* jtk_Array_getIterator(jtk_Array_t* array);

/* Migrate */

/**
 * @memberof Array
 * @since JTK 1.1
 */
jtk_Array_t* jtk_Array_migrate(jtk_Array_t* array, jtk_Array_MigrateFunction_t migrate);

/**
 * @memberof Array
 * @since JTK 1.1
 */
jtk_Array_t* jtk_Array_migrate_v(void** array, int32_t size,
    jtk_Array_MigrateFunction_t migrate);

/* Raw Array */

/**
 * A JTK array stores all the elements in a native array, internally. This
 * function returns that native array associated with the specified array.
 * Any modifications made to the native array are reflected by the array, too.
 * Futher, the native array is owned by the array and should not be destroyed.
 * Which goes to say, the native array is destroyed when the owning array is
 * destroyed.
 *
 * @return The native array associated with the specified array.
 * @memberof Array
 */
void** jtk_Array_getNativeArray(jtk_Array_t* array);
void** getRawArray(jtk_Array_t* array);
void** jtk_Array_toRawArray(jtk_Array_t* array);

/* Recycle */

/**
 * @memberof Array
 */
void jtk_Array_recycle(jtk_Array_t* array, jtk_Array_t* other);

/* Reverse */

/**
 * Reverses the order of the elements in the specified array.
 *
 * @param  array
 *         This argument specifies the array to reverse.
 * @memberof Array
 */
void jtk_Array_reverse(jtk_Array_t* array);

/* Reverse Extended */

/**
 * Reverses the order of the elements in the specified range within the
 * specified array.
 *
 * The specified range should be subjected to the following constraints,
 * otherwise an assertion failure is triggered. The starting index should
 * greater than or equal to zero. The starting index should be lesser than
 * or equal to the stopping index. The stopping index should be lesser than the
 * size of the array. The following fragment of code shows the constraints:
 * `(startIndex >= 0) && (startIndex <= stopIndex) && (stopIndex < m_size)`,
 * where `startIndex}, `stopIndex`, and `size` mean
 * the starting index of the range, the stopping index of the range, and the
 * size of the array, respectively.
 *
 * @param  array
 *         This argument specifies the array to reverse.
 * @param  startIndex
 *         This argument specifies the starting index of the range,
 *         inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range,
 *         exclusive.
 * @memberof Array
 */
void jtk_Array_reverseEx(jtk_Array_t* array, int32_t startIndex, int32_t stopIndex);

/* Rotate */

/**
 * Rotates the elements in the specified array by the specified distance.
 * For each shift, the element moved beyond one of the array end is brought in
 * on the opposite end. A negative distance moves the elements backward. On the
 * other hand, a positive distance moves the elements forward.
 *
 * @param  array
 *         This argument specifies the array to rotate.
 * @param  distance
 *         This argument specifies the distance to shift.
 * @memberof Array
 */
void jtk_Array_rotate(jtk_Array_t* array, int32_t distance);

/* Size */

/**
 * Returns the size of the array.
 *
 * @return The size of the array.
 * @memberof Array
 */
int32_t jtk_Array_getSize(jtk_Array_t* array);

/* Swap */

/**
 * Swaps the elements at the specified indexes in the specified array.
 *
 * @param  array
 *         This argument specifies the array to modify.
 * @param  index1
 *         This argument specifies the index of an element to swap. Further,
 *         the index should be greater or equal to zero and lesser than the
 *         size of the array.
 * @param  index2
 *         This argument specifies the index of another element to swap.
 *         All negative integers are considered illegal. Further, the index
 *         should be greater or equal to zero and lesser than the size of the
 *         array.
 * @memberof Array
 */
void jtk_Array_swap(jtk_Array_t* array, int32_t index1, int32_t index2);

/* Value */

/**
 * Sets the element at the specified index to the specified value.
 *
 * @param  array
 *         This argument specifies the array to modify.
 * @param  index
 *         This argument specifies the index to modify.
 *         All negative integers are considered illegal. Further, the index
 *         should be greater or equal to zero and lesser than the size of the
 *         array.
 * @param  value
 *         This argument specifies the new value.
 * @memberof Array
 */
void jtk_Array_setValue(jtk_Array_t* array, int32_t index, void* value);

/**
 * Returns the element at the specified index.
 *
 * @param  array
 *         This argument specifies the array.
 * @param  index
 *         This argument specifies the index of the element to retrieve.
 *         All negative integers are considered illegal. Further, the index
 *         should be greater or equal to zero and lesser than the size of the
 *         array.
 * @return The element at the specified index.
 * @memberof Array
 */
void* jtk_Array_getValue(jtk_Array_t* array, int32_t index);

/* Wrapper */

// bool jtk_Array_isWrapper(jtk_Array_t* array);

#endif /* JTK_COLLECTION_ARRAY_ARRAY_H */