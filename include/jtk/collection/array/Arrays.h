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

// Sunday, December 03, 2017

#ifndef JTK_COLLECTION_ARRAY_ARRAYS_H
#define JTK_COLLECTION_ARRAY_ARRAYS_H

#include <jtk/Configuration.h>
#include <jtk/function/ComparatorFunction.h>
#include <jtk/function/PredicateFunction.h>

/**
 * @class Arrays
 * @ingroup JtkCollectionModule
 */

/*******************************************************************************
 * Arrays                                                                      *
 *******************************************************************************/

/* Binary Search */

/**
 * Searches the specified array of pointers for an occurrence of the specified
 * key. To state the obvious, it implements the binary search algorithm. The
 * specified array is expected to be sorted, otherwise the result is undefined.
 * If found, it returns an index of the key within the bounds of the array; a
 * negative integer otherwise.
 *
 * If a comparator function is specified, then is it employed to compare elements
 * within the array; otherwise the comparison operators are employed.
 *
 * @param  array
 *         This argument specifies the array to search.
 * @param  key
 *         This argument specifies the value to search.
 * @param  comparator
 *         The comparator employed to compare elements within the array.
 * @return If found, an index of the key within the bounds of the array;
 *         `-1` otherwise.
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearch_v(const void** array, int32_t size, void* key, jtk_ComparatorFunction_t comparator);

/**
 * Searches the specified array of 8-bit integers for an occurrence of the specified
 * key. To state the obvious, it implements the binary search algorithm. The
 * specified array is expected to be sorted, otherwise the result is undefined.
 * If found, it returns an index of the key within the bounds of the array; a
 * negative integer otherwise.
 *
 * @param  array
 *         This argument specifies the array to search.
 * @param  key
 *         This argument specifies the value to search.
 * @return If found, an index of the key within the bounds of the array;
 *         `-1` otherwise.
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearch_b(const int8_t* array, int32_t size, int8_t key);

/**
 * Searches the specified array of 16-bit integers for an occurrence of the specified
 * key. To state the obvious, it implements the binary search algorithm. The
 * specified array is expected to be sorted, otherwise the result is undefined.
 * If found, it returns an index of the key within the bounds of the array; a
 * negative integer otherwise.
 *
 * @param  array
 *         This argument specifies the array to search.
 * @param  key
 *         This argument specifies the value to search.
 * @return If found, an index of the key within the bounds of the array;
 *         `-1` otherwise.
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearch_s(const int16_t* array, int32_t size, int16_t key);

/**
 * Searches the specified array of 32-bit integers for an occurrence of the specified
 * key. To state the obvious, it implements the binary search algorithm. The
 * specified array is expected to be sorted, otherwise the result is undefined.
 * If found, it returns an index of the key within the bounds of the array; a
 * negative integer otherwise.
 *
 * @param  array
 *         This argument specifies the array to search.
 * @param  key
 *         This argument specifies the value to search.
 * @return If found, an index of the key within the bounds of the array;
 *         `-1` otherwise.
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearch_i(const int32_t* array, int32_t size, int32_t key);

/**
 * Searches the specified array of 64-bit integers for an occurrence of the specified
 * key. To state the obvious, it implements the binary search algorithm. The
 * specified array is expected to be sorted, otherwise the result is undefined.
 * If found, it returns an index of the key within the bounds of the array; a
 * negative integer otherwise.
 *
 * @param  array
 *         This argument specifies the array to search.
 * @param  key
 *         This argument specifies the value to search.
 * @return If found, an index of the key within the bounds of the array;
 *         `-1` otherwise.
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearch_l(const int64_t* array, int32_t size, int64_t key);

/**
 * Searches the specified array of 32-bit decimals for an occurrence of the specified
 * key. To state the obvious, it implements the binary search algorithm. The
 * specified array is expected to be sorted, otherwise the result is undefined.
 * If found, it returns an index of the key within the bounds of the array; a
 * negative integer otherwise.
 *
 * @param  array
 *         This argument specifies the array to search.
 * @param  key
 *         This argument specifies the value to search.
 * @return If found, an index of the key within the bounds of the array;
 *         `-1` otherwise.
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearch_f(const float* array, int32_t size, float key);

/**
 * Searches the specified array of 64-bit decimals for an occurrence of the specified
 * key. To state the obvious, it implements the binary search algorithm. The
 * specified array is expected to be sorted, otherwise the result is undefined.
 * If found, it returns an index of the key within the bounds of the array; a
 * negative integer otherwise.
 *
 * @param  array
 *         This argument specifies the array to search.
 * @param  key
 *         This argument specifies the value to search.
 * @return If found, an index of the key within the bounds of the array;
 *         `-1` otherwise.
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearch_d(const double* array, int32_t size, double key);

/* Binary Search Extended */

/**
 * Searches the specified array of pointers for an occurrence of the specified
 * key, within the specified range. To state the obvious, it implements the
 * binary search algorithm. The specified array is expected to be sorted,
 * otherwise the result is undefined. If found, it returns an index of the key
 * within the bounds of the array; a negative integer otherwise.
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
 * If a comparator function is specified, then is it employed to compare elements
 * within the array; otherwise the comparison operators are employed.
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
 * @param  comparator
 *         The comparator employed to compare elements within the array.
 * @return If found, an index of the key within the bounds of the array;
 *         a negative integer otherwise.
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearchEx_v(const void** array, int32_t size, int32_t startIndex, int32_t stopIndex, void* key, jtk_ComparatorFunction_t comparator);

/**
 * Searches the specified array of 8-bit integers for an occurrence of the specified
 * key, within the specified range. To state the obvious, it implements the
 * binary search algorithm. The specified array is expected to be sorted,
 * otherwise the result is undefined. If found, it returns an index of the key
 * within the bounds of the array; a negative integer otherwise.
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
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearchEx_b(const int8_t* array, int32_t size, int32_t startIndex, int32_t stopIndex, int8_t key);

/**
 * Searches the specified array of 16-bit integers for an occurrence of the specified
 * key, within the specified range. To state the obvious, it implements the
 * binary search algorithm. The specified array is expected to be sorted,
 * otherwise the result is undefined. If found, it returns an index of the key
 * within the bounds of the array; a negative integer otherwise.
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
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearchEx_s(const int16_t* array, int32_t size, int32_t startIndex, int32_t stopIndex, int16_t key);

/**
 * Searches the specified array of 32-bit integers for an occurrence of the specified
 * key, within the specified range. To state the obvious, it implements the
 * binary search algorithm. The specified array is expected to be sorted,
 * otherwise the result is undefined. If found, it returns an index of the key
 * within the bounds of the array; a negative integer otherwise.
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
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearchEx_i(const int32_t* array, int32_t size, int32_t startIndex, int32_t stopIndex, int32_t key);

/**
 * Searches the specified array of 64-bit integers for an occurrence of the specified
 * key, within the specified range. To state the obvious, it implements the
 * binary search algorithm. The specified array is expected to be sorted,
 * otherwise the result is undefined. If found, it returns an index of the key
 * within the bounds of the array; a negative integer otherwise.
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
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearchEx_l(const int64_t* array, int32_t size, int32_t startIndex, int32_t stopIndex, int64_t key);

/**
 * Searches the specified array of 32-bit decimals for an occurrence of the specified
 * key, within the specified range. To state the obvious, it implements the
 * binary search algorithm. The specified array is expected to be sorted,
 * otherwise the result is undefined. If found, it returns an index of the key
 * within the bounds of the array; a negative integer otherwise.
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
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearchEx_f(const float* array, int32_t size, int32_t startIndex, int32_t stopIndex, float key);

/**
 * Searches the specified array of 64-bit decimals for an occurrence of the specified
 * key, within the specified range. To state the obvious, it implements the
 * binary search algorithm. The specified array is expected to be sorted,
 * otherwise the result is undefined. If found, it returns an index of the key
 * within the bounds of the array; a negative integer otherwise.
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
 * @memberof Arrays
 */
int32_t jtk_Arrays_binarySearchEx_d(const double* array, int32_t size, int32_t startIndex, int32_t stopIndex, double key);

/* Check Index */

/**
 * Checks whether the specified index is within the bounds an array with
 * the specified size. An assertion failure is triggered if the index is invalid,
 * when enabled.
 *
 * An index is considered valid if the index is greater or equal to zero and
 * lesser than the size of the array.
 *
 * @param  size
 *         This argument specifies the size of the array.
 * @param  index
 *         This argument specifies the index to test.
 * @return `true` if the specified index is valid; `false` otherwise.
 * @memberof Arrays
 */
void jtk_Arrays_checkIndex(int32_t size, int32_t index);

/* Check Range */

/**
 * Checks whether the specified range is within the bounds an array with
 * the specified size. An assertion failure is triggered if the range is invalid,
 * when enabled.
 *
 * The specified range is subjected to the following constraints; on failure
 * an assertion failure is triggered. The starting index should
 * greater than or equal to zero. The starting index should be lesser than
 * or equal to the stopping index. The stopping index should be lesser than the
 * size of the array. The following fragment of code shows the constraints:
 * `(startIndex >= 0) && (startIndex <= stopIndex) && (stopIndex < m_size)`,
 * where `startIndex}, `stopIndex`, and `size` mean
 * the starting index of the range, the stopping index of the range, and the
 * size of the array, respectively.
 *
 * @param  size
 *         This argument specifies the size of the array.
* @param  startIndex
 *         This argument specifies the starting index of the range,
 *         inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range,
 *         exclusive.
 * @memberof Arrays
 */
void jtk_Arrays_checkRange(int32_t size, int32_t startIndex, int32_t stopIndex);

/* Clone */

/**
 * Creates a copy of the specified native array of pointers. The elements in
 * the new native array are initialized to the corresponding elements from the
 * specified native array.
 *
 * The behaviour of this function can be exploited to create truncated arrays,
 * too. Please go through the example programs and the source of JTK Framework
 * to find such examples.
 *
 * @param  other
 *         The native array to clone.
 * @param  size
 *         The size of the native array.
 * @return The newly created native array.
 * @memberof Arrays
 */
void** jtk_Arrays_clone_v(const void** source, int32_t size);

/**
 * Creates a copy of the specified native array of 8-bit integers. The elements in
 * the new native array are initialized to the corresponding elements from the
 * specified native array.
 *
 * The behaviour of this function can be exploited to create truncated arrays,
 * too. Please go through the example programs and the source of JTK Framework
 * to find such examples.
 *
 * @param  other
 *         The native array to clone.
 * @param  size
 *         The size of the native array.
 * @return The newly created native array.
 * @memberof Arrays
 */
int8_t* jtk_Arrays_clone_b(const int8_t* source, int32_t size);

/**
 * Creates a copy of the specified native array of 16-bit integers. The elements in
 * the new native array are initialized to the corresponding elements from the
 * specified native array.
 *
 * The behaviour of this function can be exploited to create truncated arrays,
 * too. Please go through the example programs and the source of JTK Framework
 * to find such examples.
 *
 * @param  other
 *         The native array to clone.
 * @param  size
 *         The size of the native array.
 * @return The newly created native array.
 * @memberof Arrays
 */
int16_t* jtk_Arrays_clone_s(const int16_t* source, int32_t size);

/**
 * Creates a copy of the specified native array of 32-bit integers. The elements in
 * the new native array are initialized to the corresponding elements from the
 * specified native array.
 *
 * The behaviour of this function can be exploited to create truncated arrays,
 * too. Please go through the example programs and the source of JTK Framework
 * to find such examples.
 *
 * @param  other
 *         The native array to clone.
 * @param  size
 *         The size of the native array.
 * @return The newly created native array.
 * @memberof Arrays
 */
int32_t* jtk_Arrays_clone_i(const int32_t* source, int32_t size);

/**
 * Creates a copy of the specified native array of 64-bit integers. The elements in
 * the new native array are initialized to the corresponding elements from the
 * specified native array.
 *
 * The behaviour of this function can be exploited to create truncated arrays,
 * too. Please go through the example programs and the source of JTK Framework
 * to find such examples.
 *
 * @param  other
 *         The native array to clone.
 * @param  size
 *         The size of the native array.
 * @return The newly created native array.
 * @memberof Arrays
 */
int64_t* jtk_Arrays_clone_l(const int64_t* source, int32_t size);

/**
 * Creates a copy of the specified native array of 32-bit decimals. The elements in
 * the new native array are initialized to the corresponding elements from the
 * specified native array.
 *
 * The behaviour of this function can be exploited to create truncated arrays,
 * too. Please go through the example programs and the source of JTK Framework
 * to find such examples.
 *
 * @param  other
 *         The native array to clone.
 * @param  size
 *         The size of the native array.
 * @return The newly created native array.
 * @memberof Arrays
 */
float* jtk_Arrays_clone_f(const float* source, int32_t size);

/**
 * Creates a copy of the specified native array of 64-bit decimals. The elements in
 * the new native array are initialized to the corresponding elements from the
 * specified native array.
 *
 * The behaviour of this function can be exploited to create truncated arrays,
 * too. Please go through the example programs and the source of JTK Framework
 * to find such examples.
 *
 * @param  other
 *         The native array to clone.
 * @param  size
 *         The size of the native array.
 * @return The newly created native array.
 * @memberof Arrays
 */
double* jtk_Arrays_clone_d(const double* source, int32_t size);

/* Copy */

/**
 * Copies the elements from the specified native source array of pointers to
 * the specified native destination array of pointers. It returns the number
 * of elements that were copied. If the specified source and destination native
 * arrays refer to the same native array, `0` is returned and the specified
 * native destination array is not modified.
 *
 * If the specified native destination array cannot hold all the elements from
 * the native source array, then the elements are truncated.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
 *         Zero and all negative integers are considered illegal.
 * @param  destination
 *         This argument specifies the native destination array.
 * @param  destinationSize
 *         This argument specifies the size of the native destination array.
 *         Zero and all negative integers are considered illegal.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copy_v(const void** source, int32_t sourceSize, void** destination, int32_t destinationSize);

/**
 * Copies the elements from the specified native source array of 8-bit integers to
 * the specified native destination array of 8-bit integers. It returns the number
 * of elements that were copied. If the specified source and destination native
 * arrays refer to the same native array, `0` is returned and the specified
 * native destination array is not modified.
 *
 * If the specified native destination array cannot hold all the elements from
 * the native source array, then the elements are truncated.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
 *         Zero and all negative integers are considered illegal.
 * @param  destination
 *         This argument specifies the native destination array.
 * @param  destinationSize
 *         This argument specifies the size of the native destination array.
 *         Zero and all negative integers are considered illegal.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copy_b(const int8_t* source, int32_t sourceSize, int8_t* destination, int32_t destinationSize);

/**
 * Copies the elements from the specified native source array of 16-bit integers to
 * the specified native destination array of 16-bit integers. It returns the number
 * of elements that were copied. If the specified source and destination native
 * arrays refer to the same native array, `0` is returned and the specified
 * native destination array is not modified.
 *
 * If the specified native destination array cannot hold all the elements from
 * the native source array, then the elements are truncated.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
 *         Zero and all negative integers are considered illegal.
 * @param  destination
 *         This argument specifies the native destination array.
 * @param  destinationSize
 *         This argument specifies the size of the native destination array.
 *         Zero and all negative integers are considered illegal.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copy_s(const int16_t* source, int32_t sourceSize, int16_t* destination, int32_t destinationSize);

/**
 * Copies the elements from the specified native source array of 32-bit integers to
 * the specified native destination array of 32-bit integers. It returns the number
 * of elements that were copied. If the specified source and destination native
 * arrays refer to the same native array, `0` is returned and the specified
 * native destination array is not modified.
 *
 * If the specified native destination array cannot hold all the elements from
 * the native source array, then the elements are truncated.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
 *         Zero and all negative integers are considered illegal.
 * @param  destination
 *         This argument specifies the native destination array.
 * @param  destinationSize
 *         This argument specifies the size of the native destination array.
 *         Zero and all negative integers are considered illegal.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copy_i(const int32_t* source, int32_t sourceSize, int32_t* destination, int32_t destinationSize);

/**
 * Copies the elements from the specified native source array of 64-bit integers to
 * the specified native destination array of 64-bit integers. It returns the number
 * of elements that were copied. If the specified source and destination native
 * arrays refer to the same native array, `0` is returned and the specified
 * native destination array is not modified.
 *
 * If the specified native destination array cannot hold all the elements from
 * the native source array, then the elements are truncated.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
 *         Zero and all negative integers are considered illegal.
 * @param  destination
 *         This argument specifies the native destination array.
 * @param  destinationSize
 *         This argument specifies the size of the native destination array.
 *         Zero and all negative integers are considered illegal.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copy_l(const int64_t* source, int32_t sourceSize, int64_t* destination, int32_t destinationSize);

/**
 * Copies the elements from the specified native source array of 32-bit decimals to
 * the specified native destination array of 32-bit decimals. It returns the number
 * of elements that were copied. If the specified source and destination native
 * arrays refer to the same native array, `0` is returned and the specified
 * native destination array is not modified.
 *
 * If the specified native destination array cannot hold all the elements from
 * the native source array, then the elements are truncated.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
 *         Zero and all negative integers are considered illegal.
 * @param  destination
 *         This argument specifies the native destination array.
 * @param  destinationSize
 *         This argument specifies the size of the native destination array.
 *         Zero and all negative integers are considered illegal.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copy_f(const float* source, int32_t sourceSize, float* destination, int32_t destinationSize);

/**
 * Copies the elements from the specified native source array of 32-bit decimals to
 * the specified native destination array of 64-bit decimals. It returns the number
 * of elements that were copied. If the specified source and destination native
 * arrays refer to the same native array, `0` is returned and the specified
 * native destination array is not modified.
 *
 * If the specified native destination array cannot hold all the elements from
 * the native source array, then the elements are truncated.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
 *         Zero and all negative integers are considered illegal.
 * @param  destination
 *         This argument specifies the native destination array.
 * @param  destinationSize
 *         This argument specifies the size of the native destination array.
 *         Zero and all negative integers are considered illegal.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copy_d(const double* source, int32_t sourceSize, double* destination, int32_t destinationSize);

/* Copy Extended */

/**
 * Copies the elements from the specified native source array of pointers,
 * beginning at the specified index, to the specified native destination array
 * of pointers.
 *
 * The number of elements copied is equal to the specified size. The elements
 * from the specified source index through `sourceIndex + size - 1` in
 * the native source array are copied to the specified native destination array
 * from the specified destination index through `destinationIndex + size - 1`.
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
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the source array.
 * @param  sourceIndex
 *         This argument specifies the index in the source array.
 * @param  destination
 *         This argument specifies the destination array.
 * @param  destinationSize
 *         This argument specifies the size of the destination array.
 * @param  destinationIndex
 *         This argument specifies the index in the destination array.
 * @param  size
 *         This argument specifies the number of elements to copy.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copyEx_v(const void** source, int32_t sourceSize, int32_t sourceIndex,
    void** destination, int32_t destinationSize, int32_t destinationIndex, int32_t size);

/**
 * Copies the elements from the specified native source array of 8-bit integers,
 * beginning at the specified index, to the specified native destination array
 * of 8-bit integers.
 *
 * The number of elements copied is equal to the specified size. The elements
 * from the specified source index through `sourceIndex + size - 1` in
 * the native source array are copied to the specified native destination array
 * from the specified destination index through `destinationIndex + size - 1`.
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
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the source array.
 * @param  sourceIndex
 *         This argument specifies the index in the source array.
 * @param  destination
 *         This argument specifies the destination array.
 * @param  destinationSize
 *         This argument specifies the size of the destination array.
 * @param  destinationIndex
 *         This argument specifies the index in the destination array.
 * @param  size
 *         This argument specifies the number of elements to copy.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copyEx_b(const int8_t* source, int32_t sourceSize, int32_t sourceIndex, int8_t* destination, int32_t destinationSize, int32_t destinationIndex, int32_t size);

/**
 * Copies the elements from the specified native source array of 16-bit integers,
 * beginning at the specified index, to the specified native destination array
 * of 16-bit integers.
 *
 * The number of elements copied is equal to the specified size. The elements
 * from the specified source index through `sourceIndex + size - 1` in
 * the native source array are copied to the specified native destination array
 * from the specified destination index through `destinationIndex + size - 1`.
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
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the source array.
 * @param  sourceIndex
 *         This argument specifies the index in the source array.
 * @param  destination
 *         This argument specifies the destination array.
 * @param  destinationSize
 *         This argument specifies the size of the destination array.
 * @param  destinationIndex
 *         This argument specifies the index in the destination array.
 * @param  size
 *         This argument specifies the number of elements to copy.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copyEx_s(const int16_t* source, int32_t sourceSize, int32_t sourceIndex, int16_t* destination, int32_t destinationSize, int32_t destinationIndex, int32_t size);

/**
 * Copies the elements from the specified native source array of 32-bit integers,
 * beginning at the specified index, to the specified native destination array
 * of 32-bit integers.
 *
 * The number of elements copied is equal to the specified size. The elements
 * from the specified source index through `sourceIndex + size - 1` in
 * the native source array are copied to the specified native destination array
 * from the specified destination index through `destinationIndex + size - 1`.
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
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the source array.
 * @param  sourceIndex
 *         This argument specifies the index in the source array.
 * @param  destination
 *         This argument specifies the destination array.
 * @param  destinationSize
 *         This argument specifies the size of the destination array.
 * @param  destinationIndex
 *         This argument specifies the index in the destination array.
 * @param  size
 *         This argument specifies the number of elements to copy.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copyEx_i(const int32_t* source, int32_t sourceSize, int32_t sourceIndex, int32_t* destination, int32_t destinationSize, int32_t destinationIndex, int32_t size);

/**
 * Copies the elements from the specified native source array of 64-bit integers,
 * beginning at the specified index, to the specified native destination array
 * of 64-bit integers.
 *
 * The number of elements copied is equal to the specified size. The elements
 * from the specified source index through `sourceIndex + size - 1` in
 * the native source array are copied to the specified native destination array
 * from the specified destination index through `destinationIndex + size - 1`.
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
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the source array.
 * @param  sourceIndex
 *         This argument specifies the index in the source array.
 * @param  destination
 *         This argument specifies the destination array.
 * @param  destinationSize
 *         This argument specifies the size of the destination array.
 * @param  destinationIndex
 *         This argument specifies the index in the destination array.
 * @param  size
 *         This argument specifies the number of elements to copy.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copyEx_l(const int64_t* source, int32_t sourceSize, int32_t sourceIndex, int64_t* destination, int32_t destinationSize, int32_t destinationIndex, int32_t size);

/**
 * Copies the elements from the specified native source array of 32-bit decimals,
 * beginning at the specified index, to the specified native destination array
 * of 32-bit decimals.
 *
 * The number of elements copied is equal to the specified size. The elements
 * from the specified source index through `sourceIndex + size - 1` in
 * the native source array are copied to the specified native destination array
 * from the specified destination index through `destinationIndex + size - 1`.
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
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the source array.
 * @param  sourceIndex
 *         This argument specifies the index in the source array.
 * @param  destination
 *         This argument specifies the destination array.
 * @param  destinationSize
 *         This argument specifies the size of the destination array.
 * @param  destinationIndex
 *         This argument specifies the index in the destination array.
 * @param  size
 *         This argument specifies the number of elements to copy.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copyEx_f(const float* source, int32_t sourceSize, int32_t sourceIndex, float* destination, int32_t destinationSize, int32_t destinationIndex, int32_t size);

/**
 * Copies the elements from the specified native source array of 64-bit decimals,
 * beginning at the specified index, to the specified native destination array
 * of 64-bit decimals.
 *
 * The number of elements copied is equal to the specified size. The elements
 * from the specified source index through `sourceIndex + size - 1` in
 * the native source array are copied to the specified native destination array
 * from the specified destination index through `destinationIndex + size - 1`.
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
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the source array.
 * @param  sourceIndex
 *         This argument specifies the index in the source array.
 * @param  destination
 *         This argument specifies the destination array.
 * @param  destinationSize
 *         This argument specifies the size of the destination array.
 * @param  destinationIndex
 *         This argument specifies the index in the destination array.
 * @param  size
 *         This argument specifies the number of elements to copy.
 * @return The number of elements that were copied.
 * @memberof Arrays
 */
int32_t jtk_Arrays_copyEx_d(const double* source, int32_t sourceSize, int32_t sourceIndex, double* destination, int32_t destinationSize, int32_t destinationIndex, int32_t size);

/* Copy Of */

/**
 * Returns a copy of the specified native array of pointers, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 */
void** jtk_Arrays_copyOf_v(const void** source, int32_t sourceSize, int32_t newSize, void* defaultValue);

/**
 * Returns a copy of the specified native array of 8-bit integers, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 */
int8_t* jtk_Arrays_copyOf_b(const int8_t* source, int32_t sourceSize, int32_t newSize, int8_t defaultValue);

/**
 * Returns a copy of the specified native array of 16-bit integers, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 */
int16_t* jtk_Arrays_copyOf_s(const int16_t* source, int32_t sourceSize, int32_t newSize, int16_t defaultValue);

/**
 * Returns a copy of the specified native array of 32-bit integers, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 */
int32_t* jtk_Arrays_copyOf_i(const int32_t* source, int32_t sourceSize, int32_t newSize, int32_t defaultValue);

/**
 * Returns a copy of the specified native array of 64-bit integers, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 */
int64_t* jtk_Arrays_copyOf_l(const int64_t* source, int32_t sourceSize, int32_t newSize, int64_t defaultValue);

/**
 * Returns a copy of the specified native array of 32-bit decimals, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 */
float* jtk_Arrays_copyOf_f(const float* source, int32_t sourceSize, int32_t newSize, float defaultValue);

/**
 * Returns a copy of the specified native array of 64-bit decimals, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 */
double* jtk_Arrays_copyOf_d(const double* source, int32_t sourceSize, int32_t newSize, double defaultValue);

/* Copy Of Extended */

/**
 * Returns a copy of the specified native array of pointers, truncated or
 * padded to obtain the specified size.
 *
 * This function allows the user to skip the padding. It is always recommended
 * to pad extended arrays. Skipping this step improves slight performance,
 * especially when the difference between the old and new array sizes are very
 * large. In case you choose to skip the padding, make sure your code is aware
 * of the garbage values, which begins at `sourceSize`.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @param  overwrite
 *         This argument specifies whether to pad with the specified default
 *         value, or not.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 * @since JTK 1.1
 */
void** jtk_Arrays_copyOfEx_v(const void** source, int32_t sourceSize, int32_t newSize, void* defaultValue, bool overwrite);

/**
 * Returns a copy of the specified native array of 8-bit integers, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 * @since JTK 1.1
 */
int8_t* jtk_Arrays_copyOfEx_b(const int8_t* source, int32_t sourceSize, int32_t newSize, int8_t defaultValue, bool overwrite);

/**
 * Returns a copy of the specified native array of 16-bit integers, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 * @since JTK 1.1
 */
int16_t* jtk_Arrays_copyOfEx_s(const int16_t* source, int32_t sourceSize, int32_t newSize, int16_t defaultValue, bool overwrite);

/**
 * Returns a copy of the specified native array of 32-bit integers, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 * @since JTK 1.1
 */
int32_t* jtk_Arrays_copyOfEx_i(const int32_t* source, int32_t sourceSize, int32_t newSize, int32_t defaultValue, bool overwrite);

/**
 * Returns a copy of the specified native array of 64-bit integers, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 * @since JTK 1.1
 */
int64_t* jtk_Arrays_copyOfEx_l(const int64_t* source, int32_t sourceSize, int32_t newSize, int64_t defaultValue, bool overwrite);

/**
 * Returns a copy of the specified native array of 32-bit decimals, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 * @since JTK 1.1
 */
float* jtk_Arrays_copyOfEx_f(const float* source, int32_t sourceSize, int32_t newSize, float defaultValue, bool overwrite);

/**
 * Returns a copy of the specified native array of 64-bit decimals, truncated or
 * padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native array.
 *         zero All negative values are considered illegal.
 * @param  newSize
 *         This argument specifies the size of the resulting native array.
 *         Zero and all negative integers are considered illegal.
 * @param  defaultValue
 *         This argument specifies the value used for padding, if necessary.
 * @return A copy of the specified native source array of the specified size,
 *         if necessary, the returned native array is truncated or padded with
 *         the specified default value so the copy has the specified
 *         size. The user is responsible for destroying the returned
 *         array.
 * @memberof Arrays
 * @since JTK 1.1
 */
double* jtk_Arrays_copyOfEx_d(const double* source, int32_t sourceSize, int32_t newSize, double defaultValue, bool overwrite);

/* Copy Of Range */

/**
 * Returns a copy of the specified range of the specified native array of
 * pointers, truncated or padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
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
 * @memberof Arrays
 */
void** jtk_Arrays_copyOfRange_v(const void** source, int32_t sourceSize, int32_t startIndex, int32_t stopIndex, void* defaultValue);

/**
 * Returns a copy of the specified range of the specified native array of
 * 8-bit integers, truncated or padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
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
 * @memberof Arrays
 */
int8_t* jtk_Arrays_copyOfRange_b(const int8_t* source, int32_t sourceSize, int32_t startIndex, int32_t stopIndex, int8_t defaultValue);

/**
 * Returns a copy of the specified range of the specified native array of
 * 16-bit integers, truncated or padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
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
 * @memberof Arrays
 */
int16_t* jtk_Arrays_copyOfRange_s(const int16_t* source, int32_t sourceSize, int32_t startIndex, int32_t stopIndex, int16_t defaultValue);

/**
 * Returns a copy of the specified range of the specified native array of
 * 32-bit integers, truncated or padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
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
 * @memberof Arrays
 */
int32_t* jtk_Arrays_copyOfRange_i(const int32_t* source, int32_t sourceSize, int32_t startIndex, int32_t stopIndex, int32_t defaultValue);

/**
 * Returns a copy of the specified range of the specified native array of
 * 64-bit integers, truncated or padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
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
 * @memberof Arrays
 */
int64_t* jtk_Arrays_copyOfRange_l(const int64_t* source, int32_t sourceSize, int32_t startIndex, int32_t stopIndex, int64_t defaultValue);

/**
 * Returns a copy of the specified range of the specified native array of
 * 32-bit decimals, truncated or padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
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
 * @memberof Arrays
 */
float* jtk_Arrays_copyOfRange_f(const float* source, int32_t sourceSize, int32_t startIndex, int32_t stopIndex, float defaultValue);

/**
 * Returns a copy of the specified range of the specified native array of
 * 64-bit decimals, truncated or padded to obtain the specified size.
 *
 * @param  source
 *         This argument specifies the native source array.
 * @param  sourceSize
 *         This argument specifies the size of the native source array.
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
 * @memberof Arrays
 */
double* jtk_Arrays_copyOfRange_d(const double* source, int32_t sourceSize, int32_t startIndex, int32_t stopIndex, double defaultValue);

/* Equals */

/**
 * Determines whether the specified native arrays of pointers are equal, or not.
 *
 * Two native arrays are considered equal if both arrays contain the same number
 * of elements, and all corresponding elements in the two arrays are equal,
 * as determined by the specified comparator function. If the specified comparator
 * function is `null`, then the comparison operators are employed.
 *
 * @param  array1
 *         This argument specifies the first array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  comparator
 *         This argument specifies the comparator function employed to compare
 *         the elements. If `null`, the comparison operators are employed.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equals_v(void** array1, int32_t size1, void** array2, int32_t size2, jtk_ComparatorFunction_t comparator);

/**
 * Determines whether the specified native arrays of 8-bit integers are equal,
 * or not.
 *
 * Two native arrays are considered equal if both arrays contain the same number
 * of elements, and all corresponding elements in the two arrays are equal,
 * as determined by comparison operators.
 *
 * @param  array1
 *         This argument specifies the first array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  comparator
 *         This argument specifies the comparator function employed to compare
 *         the elements. If `null`, the comparison operators are employed.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equals_b(int8_t* array1, int32_t size1, int8_t* array2, int32_t size2);

/**
 * Determines whether the specified native arrays of 16-bit integers are equal,
 * or not.
 *
 * Two native arrays are considered equal if both arrays contain the same number
 * of elements, and all corresponding elements in the two arrays are equal,
 * as determined by comparison operators.
 *
 * @param  array1
 *         This argument specifies the first array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  comparator
 *         This argument specifies the comparator function employed to compare
 *         the elements. If `null`, the comparison operators are employed.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equals_s(int16_t* array1, int32_t size1, int16_t* array2, int32_t size2);

/**
 * Determines whether the specified native arrays of 32-bit integers are equal,
 * or not.
 *
 * Two native arrays are considered equal if both arrays contain the same number
 * of elements, and all corresponding elements in the two arrays are equal,
 * as determined by comparison operators.
 *
 * @param  array1
 *         This argument specifies the first array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  comparator
 *         This argument specifies the comparator function employed to compare
 *         the elements. If `null`, the comparison operators are employed.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equals_i(int32_t* array1, int32_t size1, int32_t* array2, int32_t size2);

/**
 * Determines whether the specified native arrays of 64-bit integers are equal,
 * or not.
 *
 * Two native arrays are considered equal if both arrays contain the same number
 * of elements, and all corresponding elements in the two arrays are equal,
 * as determined by comparison operators.
 *
 * @param  array1
 *         This argument specifies the first array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  comparator
 *         This argument specifies the comparator function employed to compare
 *         the elements. If `null`, the comparison operators are employed.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equals_l(int64_t* array1, int32_t size1, int64_t* array2, int32_t size2);

/**
 * Determines whether the specified native arrays of 32-bit decimals are equal,
 * or not.
 *
 * Two native arrays are considered equal if both arrays contain the same number
 * of elements, and all corresponding elements in the two arrays are equal,
 * as determined by comparison operators.
 *
 * @param  array1
 *         This argument specifies the first array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  comparator
 *         This argument specifies the comparator function employed to compare
 *         the elements. If `null`, the comparison operators are employed.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equals_f(float* array1, int32_t size1, float* array2, int32_t size2);

/**
 * Determines whether the specified native arrays of 64-bit decimals are equal,
 * or not.
 *
 * Two native arrays are considered equal if both arrays contain the same number
 * of elements, and all corresponding elements in the two arrays are equal,
 * as determined by comparison operators.
 *
 * @param  array1
 *         This argument specifies the first array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  comparator
 *         This argument specifies the comparator function employed to compare
 *         the elements. If `null`, the comparison operators are employed.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equals_d(double* array1, int32_t size1, double* array2, int32_t size2);

/* Equals Extended */

/**
 * Determines whether the specified ranges within the specified native arrays
 * of pointers are equal, or not.
 *
 * Two ranges within two arrays are considered equal if both the ranges contain
 * the same number of elements, and all corresponding elements in the two arrays
 * are equal, as determined by the specified comparator function. If
 * the specified comparator is `null`, then the comparison operators are
 * employed.
 *
 * The following cases are considered illegal and cause an assertion failure,
 * when enabled.
 *         <ul>
 *         <li>The specified first index is negative.</li>
 *         <li>The specified second index is negative.</li>
 *         <li>The specified size is negative.</li>
 *         <li>`index1 + size` is greater than the size of the
 *             first native array.</li>
 *         <li>`index2 + size` is greater than the size
 *             of the second native array.</li>
 *         </ul>
 *
 * @param  array1
 *         This argument specifies the first native array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  index1
 *         This argument specifies the index within the bounds of the first
 *         native array, where the first range begins.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  index2
 *         This argument specifies the index within the bounds of the second
 *         native array, where the second range begins.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equalsEx_v(void** array1, int32_t size1, int32_t index1, void** array2, int32_t size2, int32_t index2, int32_t size, jtk_ComparatorFunction_t comparator);

/**
 * Determines whether the specified ranges within the specified native arrays
 * of 8-bit integers are equal, or not.
 *
 * Two ranges within two arrays are considered equal if both the ranges contain
 * the same number of elements, and all corresponding elements in the two arrays
 * are equal, as determined by the specified comparator function. If
 * the specified comparator is `null`, then the comparison operators are
 * employed.
 *
 * The following cases are considered illegal and cause an assertion failure,
 * when enabled.
 *         <ul>
 *         <li>The specified first index is negative.</li>
 *         <li>The specified second index is negative.</li>
 *         <li>The specified size is negative.</li>
 *         <li>`index1 + size` is greater than the size of the
 *             first native array.</li>
 *         <li>`index2 + size` is greater than the size
 *             of the second native array.</li>
 *         </ul>
 *
 * @param  array1
 *         This argument specifies the first native array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  index1
 *         This argument specifies the index within the bounds of the first
 *         native array, where the first range begins.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  index2
 *         This argument specifies the index within the bounds of the second
 *         native array, where the second range begins.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equalsEx_b(int8_t* array1, int32_t size1, int32_t index1, int8_t* array2, int32_t size2, int32_t index2, int32_t size);

/**
 * Determines whether the specified ranges within the specified native arrays
 * of 16-bit integers are equal, or not.
 *
 * Two ranges within two arrays are considered equal if both the ranges contain
 * the same number of elements, and all corresponding elements in the two arrays
 * are equal, as determined by the specified comparator function. If
 * the specified comparator is `null`, then the comparison operators are
 * employed.
 *
 * The following cases are considered illegal and cause an assertion failure,
 * when enabled.
 *         <ul>
 *         <li>The specified first index is negative.</li>
 *         <li>The specified second index is negative.</li>
 *         <li>The specified size is negative.</li>
 *         <li>`index1 + size` is greater than the size of the
 *             first native array.</li>
 *         <li>`index2 + size` is greater than the size
 *             of the second native array.</li>
 *         </ul>
 *
 * @param  array1
 *         This argument specifies the first native array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  index1
 *         This argument specifies the index within the bounds of the first
 *         native array, where the first range begins.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  index2
 *         This argument specifies the index within the bounds of the second
 *         native array, where the second range begins.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equalsEx_s(int16_t* array1, int32_t size1, int32_t index1, int16_t* array2, int32_t size2, int32_t index2, int32_t size);

/**
 * Determines whether the specified ranges within the specified native arrays
 * of 32-bit integers are equal, or not.
 *
 * Two ranges within two arrays are considered equal if both the ranges contain
 * the same number of elements, and all corresponding elements in the two arrays
 * are equal, as determined by the specified comparator function. If
 * the specified comparator is `null`, then the comparison operators are
 * employed.
 *
 * The following cases are considered illegal and cause an assertion failure,
 * when enabled.
 *         <ul>
 *         <li>The specified first index is negative.</li>
 *         <li>The specified second index is negative.</li>
 *         <li>The specified size is negative.</li>
 *         <li>`index1 + size` is greater than the size of the
 *             first native array.</li>
 *         <li>`index2 + size` is greater than the size
 *             of the second native array.</li>
 *         </ul>
 *
 * @param  array1
 *         This argument specifies the first native array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  index1
 *         This argument specifies the index within the bounds of the first
 *         native array, where the first range begins.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  index2
 *         This argument specifies the index within the bounds of the second
 *         native array, where the second range begins.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equalsEx_i(int32_t* array1, int32_t size1, int32_t index1, int32_t* array2, int32_t size2, int32_t index2, int32_t size);

/**
 * Determines whether the specified ranges within the specified native arrays
 * of 64-bit integers are equal, or not.
 *
 * Two ranges within two arrays are considered equal if both the ranges contain
 * the same number of elements, and all corresponding elements in the two arrays
 * are equal, as determined by the specified comparator function. If
 * the specified comparator is `null`, then the comparison operators are
 * employed.
 *
 * The following cases are considered illegal and cause an assertion failure,
 * when enabled.
 *         <ul>
 *         <li>The specified first index is negative.</li>
 *         <li>The specified second index is negative.</li>
 *         <li>The specified size is negative.</li>
 *         <li>`index1 + size` is greater than the size of the
 *             first native array.</li>
 *         <li>`index2 + size` is greater than the size
 *             of the second native array.</li>
 *         </ul>
 *
 * @param  array1
 *         This argument specifies the first native array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  index1
 *         This argument specifies the index within the bounds of the first
 *         native array, where the first range begins.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  index2
 *         This argument specifies the index within the bounds of the second
 *         native array, where the second range begins.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equalsEx_l(int64_t* array1, int32_t size1, int32_t index1, int64_t* array2, int32_t size2, int32_t index2, int32_t size);

/**
 * Determines whether the specified ranges within the specified native arrays
 * of 32-bit decimals are equal, or not.
 *
 * Two ranges within two arrays are considered equal if both the ranges contain
 * the same number of elements, and all corresponding elements in the two arrays
 * are equal, as determined by the specified comparator function. If
 * the specified comparator is `null`, then the comparison operators are
 * employed.
 *
 * The following cases are considered illegal and cause an assertion failure,
 * when enabled.
 *         <ul>
 *         <li>The specified first index is negative.</li>
 *         <li>The specified second index is negative.</li>
 *         <li>The specified size is negative.</li>
 *         <li>`index1 + size` is greater than the size of the
 *             first native array.</li>
 *         <li>`index2 + size` is greater than the size
 *             of the second native array.</li>
 *         </ul>
 *
 * @param  array1
 *         This argument specifies the first native array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  index1
 *         This argument specifies the index within the bounds of the first
 *         native array, where the first range begins.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  index2
 *         This argument specifies the index within the bounds of the second
 *         native array, where the second range begins.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equalsEx_f(float* array1, int32_t size1, int32_t index1, float* array2, int32_t size2, int32_t index2, int32_t size);

/**
 * Determines whether the specified ranges within the specified native arrays
 * of 64-bit decimals are equal, or not.
 *
 * Two ranges within two arrays are considered equal if both the ranges contain
 * the same number of elements, and all corresponding elements in the two arrays
 * are equal, as determined by the specified comparator function. If
 * the specified comparator is `null`, then the comparison operators are
 * employed.
 *
 * The following cases are considered illegal and cause an assertion failure,
 * when enabled.
 *         <ul>
 *         <li>The specified first index is negative.</li>
 *         <li>The specified second index is negative.</li>
 *         <li>The specified size is negative.</li>
 *         <li>`index1 + size` is greater than the size of the
 *             first native array.</li>
 *         <li>`index2 + size` is greater than the size
 *             of the second native array.</li>
 *         </ul>
 *
 * @param  array1
 *         This argument specifies the first native array.
 * @param  size1
 *         This argument specifies the size of the first native array.
 * @param  index1
 *         This argument specifies the index within the bounds of the first
 *         native array, where the first range begins.
 * @param  array2
 *         This argument specifies the second array.
 * @param  size2
 *         This argument specifies the size of the second native array.
 * @param  index2
 *         This argument specifies the index within the bounds of the second
 *         native array, where the second range begins.
 * @return `true` if the specified bool arrays are equal;
 *         `false` otherwise.
 * @memberof Arrays
 */
bool jtk_Arrays_equalsEx_d(double* array1, int32_t size1, int32_t index1, double* array2, int32_t size2, int32_t index2, int32_t size);

/* Fill */

/**
 * Sets all the elements in the specified native array of pointers to the
 * specified value.
 *
 * @param  array
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fill_v(void** array, int32_t size, void* value);

/**
 * Sets all the elements in the specified native array of 8-bit integers to the
 * specified value.
 *
 * @param  array
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fill_b(int8_t* array, int32_t size, int8_t value);

/**
 * Sets all the elements in the specified native array of 16-bit integers to the
 * specified value.
 *
 * @param  array
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fill_s(int16_t* array, int32_t size, int16_t value);

/**
 * Sets all the elements in the specified native array of 32-bit integers to the
 * specified value.
 *
 * @param  array
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fill_i(int32_t* array, int32_t size, int32_t value);

/**
 * Sets all the elements in the specified native array of 64-bit integers to the
 * specified value.
 *
 * @param  array
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fill_l(int64_t* array, int32_t size, int64_t value);

/**
 * Sets all the elements in the specified native array of 32-bit decimals to the
 * specified value.
 *
 * @param  array
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fill_f(float* array, int32_t size, float value);

/**
 * Sets all the elements in the specified native array of 64-bit decimals to the
 * specified value.
 *
 * @param  array
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fill_d(double* array, int32_t size, double value);

/* Fill Extended */

/**
 * Sets all the elements in the specified range within the specified native
 * array of pointers to the specified value.
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
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  startIndex
 *         This argument specifies the starting index of the range, inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range, exclusive.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fillEx_v(void** array, int32_t size, int32_t startIndex, int32_t stopIndex, void* value);

/**
 * Sets all the elements in the specified range within the specified native
 * array of 8-bit integers to the specified value.
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
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  startIndex
 *         This argument specifies the starting index of the range, inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range, exclusive.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fillEx_b(int8_t* array, int32_t size, int32_t startIndex, int32_t stopIndex, int8_t value);

/**
 * Sets all the elements in the specified range within the specified native
 * array of 16-bit integers to the specified value.
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
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  startIndex
 *         This argument specifies the starting index of the range, inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range, exclusive.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fillEx_s(int16_t* array, int32_t size, int32_t startIndex, int32_t stopIndex, int16_t value);

/**
 * Sets all the elements in the specified range within the specified native
 * array of 32-bit integers to the specified value.
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
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  startIndex
 *         This argument specifies the starting index of the range, inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range, exclusive.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fillEx_i(int32_t* array, int32_t size, int32_t startIndex, int32_t stopIndex, int32_t value);

/**
 * Sets all the elements in the specified range within the specified native
 * array of 64-bit integers to the specified value.
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
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  startIndex
 *         This argument specifies the starting index of the range, inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range, exclusive.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fillEx_l(int64_t* array, int32_t size, int32_t startIndex, int32_t stopIndex, int64_t value);

/**
 * Sets all the elements in the specified range within the specified native
 * array of 32-bit decimals to the specified value.
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
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  startIndex
 *         This argument specifies the starting index of the range, inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range, exclusive.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fillEx_f(float* array, int32_t size, int32_t startIndex, int32_t stopIndex, float value);

/**
 * Sets all the elements in the specified range within the specified native
 * array of 64-bit decimals to the specified value.
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
 *         This argument specifies the native array to fill.
 * @param  size
 *         This argument specifies the size of the array. All negative integers
 *         are considered illegal.
 * @param  startIndex
 *         This argument specifies the starting index of the range, inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range, exclusive.
 * @param  value
 *         This argument specifies the value to fill with.
 * @memberof Arrays
 */
void jtk_Arrays_fillEx_d(double* array, int32_t size, int32_t startIndex, int32_t stopIndex, double value);

/* Filter */

/**
 * @since JTK 1.1
 */
void jtk_Array_filter_v(const void** source, int32_t sourceSize, jtk_MixedPredicateFunction_t predicate,
    void** destination, int32_t destinationSize);

/**
 * @since JTK 1.1
 */
void jtk_Array_filter_b(const int8_t* source, int32_t sourceSize, jtk_IntegerPredicateFunction_t predicate,
    int8_t* destination, int32_t destinationSize);

/**
 * @since JTK 1.1
 */
void jtk_Array_filter_s(const int16_t* source, int32_t sourceSize, jtk_IntegerPredicateFunction_t predicate,
    int16_t* destination, int32_t destinationSize);

/**
 * @since JTK 1.1
 */
void jtk_Array_filter_i(const int32_t* source, int32_t sourceSize, jtk_IntegerPredicateFunction_t predicate,
    int32_t* destination, int32_t destinationSize);

/**
 * @since JTK 1.1
 */
void jtk_Array_filter_l(const int64_t* source, int32_t sourceSize, jtk_LongPredicateFunction_t predicate,
    int64_t* destination, int32_t destinationSize);

/**
 * @since JTK 1.1
 */
void jtk_Array_filter_f(const float* source, int32_t sourceSize, jtk_FloatPredicateFunction_t predicate,
    float* destination, int32_t destinationSize);

/**
 * @since JTK 1.1
 */
void jtk_Array_filter_d(const double* source, int32_t sourceSize, jtk_DoublePredicateFunction_t predicate,
    double* destination, int32_t destinationSize);

/* Filter Extended */
/*
void** jtk_Arrays_filterEx_v(void** array, int32_t size, int32_t startIndex, int32_t stopIndex, jtk_MixedPredicateFunction_t predicate);
int8_t* jtk_Arrays_filterEx_b(int8_t* array, int32_t size, int32_t startIndex, int32_t stopIndex, jtk_BytePredicateFunction_t predicate);
int16_t* jtk_Arrays_filterEx_s(int16_t* array, int32_t size, int32_t startIndex, int32_t stopIndex, jtk_ShortPredicateFunction_t predicate);
int32_t* jtk_Arrays_filterEx_i(int32_t* array, int32_t size, int32_t startIndex, int32_t stopIndex, jtk_IntegerPredicateFunction_t predicate);
int64_t* jtk_Arrays_filterEx_l(int64_t* array, int32_t size, int32_t startIndex, int32_t stopIndex, jtk_LongPredicateFunction_t predicate);
float* jtk_Arrays_filterEx_f(float* array, int32_t size, int32_t startIndex, int32_t stopIndex, jtk_FloatPredicateFunction_t predicate);
double* jtk_Arrays_filterEx_d(double* array, int32_t size, int32_t startIndex, int32_t stopIndex, jtk_DoublePredicateFunction_t predicate);
*/

/* Reverse */

/**
 * Reverses the order of the elements in the specified native array of
 * pointers.
 *
 * @param  array
 *         This argument specifies the native array to reverse.
 * @param  size
 *         This argument specifies the size of the array.
 * @memberof Arrays
 */
void jtk_Arrays_reverse_v(void** array, int32_t size);

/**
 * Reverses the order of the elements in the specified native array of
 * 8-bit integers.
 *
 * @param  array
 *         This argument specifies the native array to reverse.
 * @param  size
 *         This argument specifies the size of the array.
 * @memberof Arrays
 */
void jtk_Arrays_reverse_b(int8_t* array, int32_t size);

/**
 * Reverses the order of the elements in the specified native array of
 * 16-bit integers.
 *
 * @param  array
 *         This argument specifies the native array to reverse.
 * @param  size
 *         This argument specifies the size of the array.
 * @memberof Arrays
 */
void jtk_Arrays_reverse_s(int16_t* array, int32_t size);

/**
 * Reverses the order of the elements in the specified native array of
 * 32-bit integers.
 *
 * @param  array
 *         This argument specifies the native array to reverse.
 * @param  size
 *         This argument specifies the size of the array.
 * @memberof Arrays
 */
void jtk_Arrays_reverse_i(int32_t* array, int32_t size);

/**
 * Reverses the order of the elements in the specified native array of
 * 64-bit integers.
 *
 * @param  array
 *         This argument specifies the native array to reverse.
 * @param  size
 *         This argument specifies the size of the array.
 * @memberof Arrays
 */
void jtk_Arrays_reverse_l(int64_t* array, int32_t size);

/**
 * Reverses the order of the elements in the specified native array of
 * 32-bit decimals.
 *
 * @param  array
 *         This argument specifies the native array to reverse.
 * @param  size
 *         This argument specifies the size of the array.
 * @memberof Arrays
 */
void jtk_Arrays_reverse_f(float* array, int32_t size);

/**
 * Reverses the order of the elements in the specified native array of
 * 64-bit decimals.
 *
 * @param  array
 *         This argument specifies the native array to reverse.
 * @param  size
 *         This argument specifies the size of the array.
 * @memberof Arrays
 */
void jtk_Arrays_reverse_d(double* array, int32_t size);

/* Reverse Extended */

/**
 * Reverses the order of the elements in the specified range within the
 * specified native array of pointers.
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
 * @param  size
 *         This argument specifies the size of the array.
 * @param  startIndex
 *         This argument specifies the starting index of the range,
 *         inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range,
 *         exclusive.
 * @memberof Arrays
 */
void jtk_Arrays_reverseEx_v(void** array, int32_t size, int32_t startIndex, int32_t stopIndex);

/**
 * Reverses the order of the elements in the specified range within the
 * specified native array of 8-bit integers.
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
 * @param  size
 *         This argument specifies the size of the array.
 * @param  startIndex
 *         This argument specifies the starting index of the range,
 *         inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range,
 *         exclusive.
 * @memberof Arrays
 */
void jtk_Arrays_reverseEx_b(int8_t* array, int32_t size, int32_t startIndex, int32_t stopIndex);

/**
 * Reverses the order of the elements in the specified range within the
 * specified native array of 16-bit integers.
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
 * @param  size
 *         This argument specifies the size of the array.
 * @param  startIndex
 *         This argument specifies the starting index of the range,
 *         inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range,
 *         exclusive.
 * @memberof Arrays
 */
void jtk_Arrays_reverseEx_s(int16_t* array, int32_t size, int32_t startIndex, int32_t stopIndex);

/**
 * Reverses the order of the elements in the specified range within the
 * specified native array of 32-bit integers.
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
 * @param  size
 *         This argument specifies the size of the array.
 * @param  startIndex
 *         This argument specifies the starting index of the range,
 *         inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range,
 *         exclusive.
 * @memberof Arrays
 */
void jtk_Arrays_reverseEx_i(int32_t* array, int32_t size, int32_t startIndex, int32_t stopIndex);

/**
 * Reverses the order of the elements in the specified range within the
 * specified native array of 64-bit integers.
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
 * @param  size
 *         This argument specifies the size of the array.
 * @param  startIndex
 *         This argument specifies the starting index of the range,
 *         inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range,
 *         exclusive.
 * @memberof Arrays
 */
void jtk_Arrays_reverseEx_l(int64_t* array, int32_t size, int32_t startIndex, int32_t stopIndex);

/**
 * Reverses the order of the elements in the specified range within the
 * specified native array of 32-bit decimals.
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
 * @param  size
 *         This argument specifies the size of the array.
 * @param  startIndex
 *         This argument specifies the starting index of the range,
 *         inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range,
 *         exclusive.
 * @memberof Arrays
 */
void jtk_Arrays_reverseEx_f(float* array, int32_t size, int32_t startIndex, int32_t stopIndex);

/**
 * Reverses the order of the elements in the specified range within the
 * specified native array of 64-bit decimals.
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
 * @param  size
 *         This argument specifies the size of the array.
 * @param  startIndex
 *         This argument specifies the starting index of the range,
 *         inclusive.
 * @param  stopIndex
 *         This argument specifies the stopping index of the range,
 *         exclusive.
 * @memberof Arrays
 */
void jtk_Arrays_reverseEx_d(double* array, int32_t size, int32_t startIndex, int32_t stopIndex);

/* Rotate */

/**
 * Rotates the elements in the specified native array of pointers by the
 * specified distance. For each shift, the element moved beyond one of the
 * array end is brought in on the opposite end. A negative distance moves the
 * elements backward. On the other hand, a positive distance moves the elements
 * forward.
 *
 * @param  array
 *         This argument specifies the native array to rotate.
 * @param  size
 *         This argument specifies the size of the array.
 * @param  distance
 *         This argument specifies the distance to shift.
 * @memberof Arrays
 */
void jtk_Arrays_rotate_v(void** array, int32_t size, int32_t distance);

/**
 * Rotates the elements in the specified native array of 8-bit integers by the
 * specified distance. For each shift, the element moved beyond one of the
 * array end is brought in on the opposite end. A negative distance moves the
 * elements backward. On the other hand, a positive distance moves the elements
 * forward.
 *
 * @param  array
 *         This argument specifies the native array to rotate.
 * @param  size
 *         This argument specifies the size of the array.
 * @param  distance
 *         This argument specifies the distance to shift.
 * @memberof Arrays
 */
void jtk_Arrays_rotate_b(int8_t* array, int32_t size, int32_t distance);

/**
 * Rotates the elements in the specified native array of 16-bit integers by the
 * specified distance. For each shift, the element moved beyond one of the
 * array end is brought in on the opposite end. A negative distance moves the
 * elements backward. On the other hand, a positive distance moves the elements
 * forward.
 *
 * @param  array
 *         This argument specifies the native array to rotate.
 * @param  size
 *         This argument specifies the size of the array.
 * @param  distance
 *         This argument specifies the distance to shift.
 * @memberof Arrays
 */
void jtk_Arrays_rotate_s(int16_t* array, int32_t size, int32_t distance);

/**
 * Rotates the elements in the specified native array of 32-bit integers by the
 * specified distance. For each shift, the element moved beyond one of the
 * array end is brought in on the opposite end. A negative distance moves the
 * elements backward. On the other hand, a positive distance moves the elements
 * forward.
 *
 * @param  array
 *         This argument specifies the native array to rotate.
 * @param  size
 *         This argument specifies the size of the array.
 * @param  distance
 *         This argument specifies the distance to shift.
 * @memberof Arrays
 */
void jtk_Arrays_rotate_i(int32_t* array, int32_t size, int32_t distance);

/**
 * Rotates the elements in the specified native array of 64-bit integers by the
 * specified distance. For each shift, the element moved beyond one of the
 * array end is brought in on the opposite end. A negative distance moves the
 * elements backward. On the other hand, a positive distance moves the elements
 * forward.
 *
 * @param  array
 *         This argument specifies the native array to rotate.
 * @param  size
 *         This argument specifies the size of the array.
 * @param  distance
 *         This argument specifies the distance to shift.
 * @memberof Arrays
 */
void jtk_Arrays_rotate_l(int64_t* array, int32_t size, int32_t distance);

/**
 * Rotates the elements in the specified native array of 32-bit decimals by the
 * specified distance. For each shift, the element moved beyond one of the
 * array end is brought in on the opposite end. A negative distance moves the
 * elements backward. On the other hand, a positive distance moves the elements
 * forward.
 *
 * @param  array
 *         This argument specifies the native array to rotate.
 * @param  size
 *         This argument specifies the size of the array.
 * @param  distance
 *         This argument specifies the distance to shift.
 * @memberof Arrays
 */
void jtk_Arrays_rotate_f(float* array, int32_t size, int32_t distance);

/**
 * Rotates the elements in the specified native array of 64-bit decimals by the
 * specified distance. For each shift, the element moved beyond one of the
 * array end is brought in on the opposite end. A negative distance moves the
 * elements backward. On the other hand, a positive distance moves the elements
 * forward.
 *
 * @param  array
 *         This argument specifies the native array to rotate.
 * @param  size
 *         This argument specifies the size of the array.
 * @param  distance
 *         This argument specifies the distance to shift.
 * @memberof Arrays
 */
void jtk_Arrays_rotate_d(double* array, int32_t size, int32_t distance);

/* Swap */

/**
 * Swaps the elements at the specified indexes in the specified native array
 * of pointers.
 *
 * @param  array
 *         This argument specifies the native array to modify.
 * @param  size
 *         This argument specifies the size of the native array.
 * @param  index1
 *         This argument specifies the index of an element to swap. Further,
 *         the index should be greater or equal to zero and lesser than the
 *         size of the array.
 * @param  index2
 *         This argument specifies the index of another element to swap.
 *         All negative integers are considered illegal. Further, the index
 *         should be greater or equal to zero and lesser than the size of the
 *         array.
 * @memberof Arrays
 */
void jtk_Arrays_swap_v(void** array, int32_t size, int32_t index1, int32_t index2);

/**
 * Swaps the elements at the specified indexes in the specified native array
 * of 8-bit integers.
 *
 * @param  array
 *         This argument specifies the native array to modify.
 * @param  size
 *         This argument specifies the size of the native array.
 * @param  index1
 *         This argument specifies the index of an element to swap. Further,
 *         the index should be greater or equal to zero and lesser than the
 *         size of the array.
 * @param  index2
 *         This argument specifies the index of another element to swap.
 *         All negative integers are considered illegal. Further, the index
 *         should be greater or equal to zero and lesser than the size of the
 *         array.
 * @memberof Arrays
 */
void jtk_Arrays_swap_b(int8_t* array, int32_t size, int32_t index1, int32_t index2);

/**
 * Swaps the elements at the specified indexes in the specified native array
 * of 16-bit integers.
 *
 * @param  array
 *         This argument specifies the native array to modify.
 * @param  size
 *         This argument specifies the size of the native array.
 * @param  index1
 *         This argument specifies the index of an element to swap. Further,
 *         the index should be greater or equal to zero and lesser than the
 *         size of the array.
 * @param  index2
 *         This argument specifies the index of another element to swap.
 *         All negative integers are considered illegal. Further, the index
 *         should be greater or equal to zero and lesser than the size of the
 *         array.
 * @memberof Arrays
 */
void jtk_Arrays_swap_s(int16_t* array, int32_t size, int32_t index1, int32_t index2);

/**
 * Swaps the elements at the specified indexes in the specified native array
 * of 32-bit integers.
 *
 * @param  array
 *         This argument specifies the native array to modify.
 * @param  size
 *         This argument specifies the size of the native array.
 * @param  index1
 *         This argument specifies the index of an element to swap. Further,
 *         the index should be greater or equal to zero and lesser than the
 *         size of the array.
 * @param  index2
 *         This argument specifies the index of another element to swap.
 *         All negative integers are considered illegal. Further, the index
 *         should be greater or equal to zero and lesser than the size of the
 *         array.
 * @memberof Arrays
 */
void jtk_Arrays_swap_i(int32_t* array, int32_t size, int32_t index1, int32_t index2);

/**
 * Swaps the elements at the specified indexes in the specified native array
 * of 64-bit integers.
 *
 * @param  array
 *         This argument specifies the native array to modify.
 * @param  size
 *         This argument specifies the size of the native array.
 * @param  index1
 *         This argument specifies the index of an element to swap. Further,
 *         the index should be greater or equal to zero and lesser than the
 *         size of the array.
 * @param  index2
 *         This argument specifies the index of another element to swap.
 *         All negative integers are considered illegal. Further, the index
 *         should be greater or equal to zero and lesser than the size of the
 *         array.
 * @memberof Arrays
 */
void jtk_Arrays_swap_l(int64_t* array, int32_t size, int32_t index1, int32_t index2);

/**
 * Swaps the elements at the specified indexes in the specified native array
 * of 32-bit decimals.
 *
 * @param  array
 *         This argument specifies the native array to modify.
 * @param  size
 *         This argument specifies the size of the native array.
 * @param  index1
 *         This argument specifies the index of an element to swap. Further,
 *         the index should be greater or equal to zero and lesser than the
 *         size of the array.
 * @param  index2
 *         This argument specifies the index of another element to swap.
 *         All negative integers are considered illegal. Further, the index
 *         should be greater or equal to zero and lesser than the size of the
 *         array.
 * @memberof Arrays
 */
void jtk_Arrays_swap_f(float* array, int32_t size, int32_t index1, int32_t index2);

/**
 * Swaps the elements at the specified indexes in the specified native array
 * of 64-bit decimals.
 *
 * @param  array
 *         This argument specifies the native array to modify.
 * @param  size
 *         This argument specifies the size of the native array.
 * @param  index1
 *         This argument specifies the index of an element to swap. Further,
 *         the index should be greater or equal to zero and lesser than the
 *         size of the array.
 * @param  index2
 *         This argument specifies the index of another element to swap.
 *         All negative integers are considered illegal. Further, the index
 *         should be greater or equal to zero and lesser than the size of the
 *         array.
 * @memberof Arrays
 */
void jtk_Arrays_swap_d(double* array, int32_t size, int32_t index1, int32_t index2);

/* Select */

/**
 * @since JTK 1.1
 */
void jtk_Arrays_select_b(const int8_t* source, int32_t sourceSize, bool* selection,
    int8_t* destination, int32_t destinationSize);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_select_s(const int16_t* source, int32_t sourceSize, bool* selection,
    int16_t* destination, int32_t destinationSize);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_select_i(const int32_t* source, int32_t sourceSize, bool* selection,
    int32_t* destination, int32_t destinationSize);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_select_l(const int64_t* source, int32_t sourceSize, bool* selection,
    int64_t* destination, int32_t destinationSize);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_select_f(const float* source, int32_t sourceSize, bool* selection,
    float* destination, int32_t destinationSize);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_select_d(const double* source, int32_t sourceSize, bool* selection,
    double* destination, int32_t destinationSize);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_select_v(const void** source, int32_t sourceSize, bool* selection,
    void** destination, int32_t destinationSize);

/* Tim Sort */

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSort_b(int8_t* array, int32_t size);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSort_s(int16_t* array, int32_t size);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSort_i(int32_t* array, int32_t size);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSort_l(int64_t* array, int32_t size);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSort_f(float* array, int32_t size);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSort_d(double* array, int32_t size);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSort_v(void** array, int32_t size, jtk_ComparatorFunction_t comparator);

/* Tim Sort Extended */

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSortEx_b(int8_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSortEx_s(int16_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSortEx_i(int32_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSortEx_l(int64_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSortEx_f(float* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSortEx_d(double* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending);

/**
 * @since JTK 1.1
 */
void jtk_Arrays_timSortEx_v(void** array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending, jtk_ComparatorFunction_t comparator);

#endif /* JTK_COLLECTION_ARRAY_ARRAYS_H */

// TODO: jtk_Arrays_rotateEx_*()
// TODO: jtk_Arrays_toString_*()