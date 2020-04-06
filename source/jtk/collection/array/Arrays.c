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

// Sunday, December 03, 2017

// TODO: Range checks are very buggy!

#include <jtk/collection/array/Arrays.h>
#include <jtk/core/Integer.h>
#include <jtk/core/Long.h>
#include <jtk/core/Float.h>
#include <jtk/core/Double.h>

/* Binary Search (private) */

int32_t jtk_Arrays_binarySearch0_b(const int8_t* array, int32_t startIndex,
    int32_t stopIndex, int8_t key) {
    int32_t low = startIndex;
    int32_t high = stopIndex - 1;
    while (low <= high) {
        int32_t middle = (uint32_t)(low + high) >> 1;
        int8_t value = array[middle];
        if (value < key) {
            low = middle + 1;
        }
        else if (value > key) {
            high = middle - 1;
        }
        else {
            return middle;
        }
    }
    return -1;
}

int32_t jtk_Arrays_binarySearch0_s(const int16_t* array, int32_t startIndex,
    int32_t stopIndex, int16_t key) {
    int32_t low = startIndex;
    int32_t high = stopIndex - 1;
    while (low <= high) {
        int32_t middle = (uint32_t)(low + high) >> 1;
        int16_t value = array[middle];
        if (value < key) {
            low = middle + 1;
        }
        else if (value > key) {
            high = middle - 1;
        }
        else {
            return middle;
        }
    }
    return -1;
}

int32_t jtk_Arrays_binarySearch0_i(const int32_t* array, int32_t startIndex,
    int32_t stopIndex, int32_t key) {
    int32_t low = startIndex;
    int32_t high = stopIndex - 1;
    while (low <= high) {
        int32_t middle = (uint32_t)(low + high) >> 1;
        int32_t value = array[middle];
        if (value < key) {
            low = middle + 1;
        }
        else if (value > key) {
            high = middle - 1;
        }
        else {
            return middle;
        }
    }
    return -1;
}

int32_t jtk_Arrays_binarySearch0_l(const int64_t* array, int32_t startIndex,
    int32_t stopIndex, int64_t key) {
    int32_t low = startIndex;
    int32_t high = stopIndex - 1;
    while (low <= high) {
        int32_t middle = (uint32_t)(low + high) >> 1;
        int64_t value = array[middle];
        if (value < key) {
            low = middle + 1;
        }
        else if (value > key) {
            high = middle - 1;
        }
        else {
            return middle;
        }
    }
    return -1;
}

int32_t jtk_Arrays_binarySearch0_f(const float* array, int32_t startIndex,
    int32_t stopIndex, float key) {
    int32_t low = startIndex;
    int32_t high = stopIndex - 1;
    while (low <= high) {
        int32_t middle = (uint32_t)(low + high) >> 1;
        float value = array[middle];
        if (value < key) {
            low = middle + 1;
        }
        else if (value > key) {
            high = middle - 1;
        }
        else {
            int32_t value0 = jtk_Float_unpack(middle);
            int32_t key0 = jtk_Float_unpack(key);
            if (value0 == key0) {
                return middle;
            }
            else if (value0 < key0) {
                low = middle + 1;
            }
            else {
                high = middle - 1;
            }
        }
    }
    return -1;
}

int32_t jtk_Arrays_binarySearch0_d(const double* array, int32_t startIndex,
    int32_t stopIndex, double key) {
    int32_t low = startIndex;
    int32_t high = stopIndex - 1;
    while (low <= high) {
        int32_t middle = (uint32_t)(low + high) >> 1;
        double value = array[middle];
        if (value < key) {
            low = middle + 1;
        }
        else if (value > key) {
            high = middle - 1;
        }
        else {
            int32_t value0 = jtk_Double_unpack(middle);
            int32_t key0 = jtk_Double_unpack(key);
            if (value0 == key0) {
                return middle;
            }
            else if (value0 < key0) {
                low = middle + 1;
            }
            else {
                high = middle - 1;
            }
        }
    }
    return -1;
}

/* Binary Search */

int32_t jtk_Arrays_binarySearch_b(const int8_t* array, int32_t size, int8_t key) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    /* According to my knowledge, an array of size zero is undefined in C.
     * Therefore, array size should are required to be greater than zero.
     */
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    return jtk_Arrays_binarySearch0_b(array, 0, size, key);
}

int32_t jtk_Arrays_binarySearch_s(const int16_t* array, int32_t size, int16_t key) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    return jtk_Arrays_binarySearch0_s(array, 0, size, key);
}

int32_t jtk_Arrays_binarySearch_i(const int32_t* array, int32_t size, int32_t key) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    return jtk_Arrays_binarySearch0_i(array, 0, size, key);
}

int32_t jtk_Arrays_binarySearch_l(const int64_t* array, int32_t size, int64_t key) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    return jtk_Arrays_binarySearch0_l(array, 0, size, key);
}

int32_t jtk_Arrays_binarySearch_f(const float* array, int32_t size, float key) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    return jtk_Arrays_binarySearch0_f(array, 0, size, key);
}

int32_t jtk_Arrays_binarySearch_d(const double* array, int32_t size, double key) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    return jtk_Arrays_binarySearch0_d(array, 0, size, key);
}

/* Binary Search Extended */

int32_t jtk_Arrays_binarySearchEx_b(const int8_t* array, int32_t size,
    int32_t startIndex, int32_t stopIndex, int8_t key) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    return jtk_Arrays_binarySearch0_b(array, startIndex, stopIndex, key);
}

int32_t jtk_Arrays_binarySearchEx_s(const int16_t* array, int32_t size,
    int32_t startIndex, int32_t stopIndex, int16_t key) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    return jtk_Arrays_binarySearch0_s(array, startIndex, stopIndex, key);
}

int32_t jtk_Arrays_binarySearchEx_i(const int32_t* array, int32_t size,
    int32_t startIndex, int32_t stopIndex, int32_t key) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    return jtk_Arrays_binarySearch0_i(array, startIndex, stopIndex, key);
}

int32_t jtk_Arrays_binarySearchEx_l(const int64_t* array, int32_t size,
    int32_t startIndex, int32_t stopIndex, int64_t key) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    return jtk_Arrays_binarySearch0_l(array, startIndex, stopIndex, key);
}

int32_t jtk_Arrays_binarySearchEx_f(const float* array, int32_t size,
    int32_t startIndex, int32_t stopIndex, float key) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    return jtk_Arrays_binarySearch0_f(array, startIndex, stopIndex, key);
}

int32_t jtk_Arrays_binarySearchEx_d(const double* array, int32_t size,
    int32_t startIndex, int32_t stopIndex, double key) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    return jtk_Arrays_binarySearch0_d(array, startIndex, stopIndex, key);
}

/* Check Index */

void jtk_Arrays_checkIndex(int32_t size, int32_t index) {
    jtk_Assert_assertFalse(size < 0, "The specified array size is negative.");
    jtk_Assert_assertFalse((index < 0) || (index >= size), "The specified index is invalid.");
}

/* Check Range */

void jtk_Arrays_checkRange(int32_t size, int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertFalse(size < 0, "The specified array size is negative.");
    jtk_Assert_assertFalse(startIndex > stopIndex, "The specified range is invalid.");
    jtk_Assert_assertFalse(startIndex < 0, "The specified start index is invalid.");
    jtk_Assert_assertFalse(stopIndex > size, "The specified stop index is invalid.");
}

/* Clone */

void** jtk_Arrays_clone_v(const void** array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    void** result = jtk_Memory_allocate(void*, size);
    jtk_Arrays_copy_v(array, size, result, size);
    return result;
}

int8_t* jtk_Arrays_clone_b(const int8_t* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    int8_t* result = jtk_Memory_allocate(int8_t, size);
    jtk_Arrays_copy_b(array, size, result, size);
    return result;
}

int16_t* jtk_Arrays_clone_s(const int16_t* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    int16_t* result = jtk_Memory_allocate(int16_t, size);
    jtk_Arrays_copy_s(array, size, result, size);
    return result;
}

int32_t* jtk_Arrays_clone_i(const int32_t* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    int32_t* result = jtk_Memory_allocate(int32_t, size);
    jtk_Arrays_copy_i(array, size, result, size);
    return result;
}

int64_t* jtk_Arrays_clone_l(const int64_t* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    int64_t* result = jtk_Memory_allocate(int64_t, size);
    jtk_Arrays_copy_l(array, size, result, size);
    return result;
}

float* jtk_Arrays_clone_f(const float* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    float* result = jtk_Memory_allocate(float, size);
    jtk_Arrays_copy_f(array, size, result, size);
    return result;
}

double* jtk_Arrays_clone_d(const double* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    double* result = jtk_Memory_allocate(double, size);
    jtk_Arrays_copy_d(array, size, result, size);
    return result;
}

/* Copy */

int32_t jtk_Arrays_copy_v(const void** source, int32_t sourceSize, void** destination,
    int32_t destinationSize) {
    jtk_Assert_assertObject(source, "The specified source array is null.");
    jtk_Assert_assertObject(destination, "The specified destination array is null.");
    jtk_Assert_assertTrue(sourceSize > 0, "The specified source array size is invalid.");
    jtk_Assert_assertTrue(destinationSize > 0, "The specified destination array size is invalid.");

    /* The copying operation is delegated to jtk_Arrays_copyEx_v() function. */
    return jtk_Arrays_copyEx_v(source, sourceSize, 0, destination, destinationSize, 0,
        destinationSize);
}

int32_t jtk_Arrays_copy_b(const int8_t* source, int32_t sourceSize, int8_t* destination,
    int32_t destinationSize) {
    jtk_Assert_assertObject(source, "The specified source array is null.");
    jtk_Assert_assertObject(destination, "The specified destination array is null.");
    jtk_Assert_assertTrue(sourceSize > 0, "The specified source array size is invalid.");
    jtk_Assert_assertTrue(destinationSize > 0, "The specified destination array size is invalid.");

    /* The copying operation is delegated to jtk_Arrays_copyEx_b() function. */
    return jtk_Arrays_copyEx_b(source, sourceSize, 0, destination, destinationSize, 0,
        destinationSize);
}

int32_t jtk_Arrays_copy_s(const int16_t* source, int32_t sourceSize, int16_t* destination,
    int32_t destinationSize) {
    jtk_Assert_assertObject(source, "The specified source array is null.");
    jtk_Assert_assertObject(destination, "The specified destination array is null.");
    jtk_Assert_assertTrue(sourceSize > 0, "The specified source array size is invalid.");
    jtk_Assert_assertTrue(destinationSize > 0, "The specified destination array size is invalid.");

    /* The copying operation is delegated to jtk_Arrays_copyEx_s() function. */
    return jtk_Arrays_copyEx_s(source, sourceSize, 0, destination, destinationSize, 0,
        destinationSize);
}

int32_t jtk_Arrays_copy_i(const int32_t* source, int32_t sourceSize, int32_t* destination,
    int32_t destinationSize) {
    jtk_Assert_assertObject(source, "The specified source array is null.");
    jtk_Assert_assertObject(destination, "The specified destination array is null.");
    jtk_Assert_assertTrue(sourceSize > 0, "The specified source array size is invalid.");
    jtk_Assert_assertTrue(destinationSize > 0, "The specified destination array size is invalid.");

    /* The copying operation is delegated to jtk_Arrays_copyEx_i() function. */
    return jtk_Arrays_copyEx_i(source, sourceSize, 0, destination, destinationSize, 0,
        destinationSize);
}

int32_t jtk_Arrays_copy_l(const int64_t* source, int32_t sourceSize, int64_t* destination,
    int32_t destinationSize) {
    jtk_Assert_assertObject(source, "The specified source array is null.");
    jtk_Assert_assertObject(destination, "The specified destination array is null.");
    jtk_Assert_assertTrue(sourceSize > 0, "The specified source array size is invalid.");
    jtk_Assert_assertTrue(destinationSize > 0, "The specified destination array size is invalid.");

    /* The copying operation is delegated to jtk_Arrays_copyEx_l() function. */
    return jtk_Arrays_copyEx_l(source, sourceSize, 0, destination, destinationSize, 0,
        destinationSize);
}

int32_t jtk_Arrays_copy_f(const float* source, int32_t sourceSize, float* destination,
    int32_t destinationSize) {
    jtk_Assert_assertObject(source, "The specified source array is null.");
    jtk_Assert_assertObject(destination, "The specified destination array is null.");
    jtk_Assert_assertTrue(sourceSize > 0, "The specified source array size is invalid.");
    jtk_Assert_assertTrue(destinationSize > 0, "The specified destination array size is invalid.");

    /* The copying operation is delegated to jtk_Arrays_copyEx_f() function. */
    return jtk_Arrays_copyEx_f(source, sourceSize, 0, destination, destinationSize, 0,
        destinationSize);
}

int32_t jtk_Arrays_copy_d(const double* source, int32_t sourceSize, double* destination,
    int32_t destinationSize) {
    jtk_Assert_assertObject(source, "The specified source array is null.");
    jtk_Assert_assertObject(destination, "The specified destination array is null.");
    jtk_Assert_assertTrue(sourceSize > 0, "The specified source array size is invalid.");
    jtk_Assert_assertTrue(destinationSize > 0, "The specified destination array size is invalid.");

    /* The copying operation is delegated to jtk_Arrays_copyEx_d() function. */
    return jtk_Arrays_copyEx_d(source, sourceSize, 0, destination, destinationSize, 0,
        destinationSize);
}

/* Copy Extended */

int32_t jtk_Arrays_copyEx_v(const void** source, int32_t sourceSize, int32_t sourceIndex,
    void** destination, int32_t destinationSize, int32_t destinationIndex,
    int32_t size) {
    jtk_Assert_assertTrue(size >= 0, "The specified size is invalid.");

    jtk_Arrays_checkRange(sourceSize, sourceIndex, sourceIndex + size);
    jtk_Arrays_checkRange(destinationSize, destinationIndex, destinationIndex + size);

    int32_t result = 0;
    /* A temporary array is created when the source and the destination arrays
     * are the same. All the elements from the source array are copied to the
     * temporary array first. This behaviour is unnecessary when the elements
     * do not change their index after copying.
     */
    if ((source == destination) && (sourceIndex != destinationIndex)) {
        void** temporary = jtk_Memory_allocate(void*, size);
        int32_t limit = sourceIndex + size;
        int32_t j = 0;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            temporary[j] = (void*)source[i];
            j++;
        }
        int32_t limit0 = destinationIndex + size;
        int32_t j0 = 0;
        for (i = destinationIndex; i < limit0; i++) {
            destination[i] = temporary[j0];
            result++;
            j0++;
        }
        jtk_Memory_deallocate(temporary);
    }
    else {
        int32_t limit = sourceIndex + size;
        int32_t j = destinationIndex;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            destination[j] = source[i];
            j++;
            result++;
        }
    }
    return result;
}

int32_t jtk_Arrays_copyEx_b(const int8_t* source, int32_t sourceSize, int32_t sourceIndex,
    int8_t* destination, int32_t destinationSize, int32_t destinationIndex,
    int32_t size) {
    jtk_Assert_assertTrue(size >= 0, "The specified size is invalid.");

    jtk_Arrays_checkRange(sourceSize, sourceIndex, sourceIndex + size);
    jtk_Arrays_checkRange(destinationSize, destinationIndex, destinationIndex + size);

    int32_t result = 0;
    /* A temporary array is created when the source and the destination arrays
     * are the same. All the elements from the source array are copied to the
     * temporary array first. This behaviour is unnecessary when the elements
     * do not change their index after copying.
     */
    if ((source == destination) && (sourceIndex != destinationIndex)) {
        int8_t* temporary = jtk_Memory_allocate(int8_t, size);
        int32_t limit = sourceIndex + size;
        int32_t j = 0;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            temporary[j] = source[i];
            j++;
        }
        int32_t limit0 = destinationIndex + size;
        int32_t j0 = 0;
        for (i = destinationIndex; i < limit0; i++) {
            destination[i] = temporary[j0];
            result++;
            j0++;
        }
        jtk_Memory_deallocate(temporary);
    }
    else {
        int32_t limit = sourceIndex + size;
        int32_t j = destinationIndex;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            destination[j] = source[i];
            j++;
            result++;
        }

    }
    return result;
}

int32_t jtk_Arrays_copyEx_s(const int16_t* source, int32_t sourceSize, int32_t sourceIndex,
    int16_t* destination, int32_t destinationSize, int32_t destinationIndex,
    int32_t size) {
    jtk_Assert_assertTrue(size >= 0, "The specified size is invalid.");

    jtk_Arrays_checkRange(sourceSize, sourceIndex, sourceIndex + size);
    jtk_Arrays_checkRange(destinationSize, destinationIndex, destinationIndex + size);

    int32_t result = 0;
    /* A temporary array is created when the source and the destination arrays
     * are the same. All the elements from the source array are copied to the
     * temporary array first. This behaviour is unnecessary when the elements
     * do not change their index after copying.
     */
    if ((source == destination) && (sourceIndex != destinationIndex)) {
        int16_t* temporary = jtk_Memory_allocate(int16_t, size);
        int32_t limit = sourceIndex + size;
        int32_t j = 0;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            temporary[j] = source[i];
            j++;
        }
        int32_t limit0 = destinationIndex + size;
        int32_t j0 = 0;
        for (i = destinationIndex; i < limit0; i++) {
            destination[i] = temporary[j0];
            result++;
            j0++;
        }
    }
    else {
        int32_t limit = sourceIndex + size;
        int32_t j = destinationIndex;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            destination[j] = source[i];
            j++;
            result++;
        }

    }
    return result;
}

int32_t jtk_Arrays_copyEx_i(const int32_t* source, int32_t sourceSize, int32_t sourceIndex,
    int32_t* destination, int32_t destinationSize, int32_t destinationIndex,
    int32_t size) {
    jtk_Assert_assertTrue(size >= 0, "The specified size is invalid.");

    jtk_Arrays_checkRange(sourceSize, sourceIndex, sourceIndex + size);
    jtk_Arrays_checkRange(destinationSize, destinationIndex, destinationIndex + size);

    int32_t result = 0;
    /* A temporary array is created when the source and the destination arrays
     * are the same. All the elements from the source array are copied to the
     * temporary array first. This behaviour is unnecessary when the elements
     * do not change their index after copying.
     */
    if ((source == destination) && (sourceIndex != destinationIndex)) {
        int32_t* temporary = jtk_Memory_allocate(int32_t, size);
        int32_t limit = sourceIndex + size;
        int32_t j = 0;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            temporary[j] = source[i];
            j++;
        }
        int32_t limit0 = destinationIndex + size;
        int32_t j0 = 0;
        for (i = destinationIndex; i < limit0; i++) {
            destination[i] = temporary[j0];
            result++;
            j0++;
        }
    }
    else {
        int32_t limit = sourceIndex + size;
        int32_t j = destinationIndex;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            destination[j] = source[i];
            j++;
            result++;
        }

    }
    return result;
}

int32_t jtk_Arrays_copyEx_l(const int64_t* source, int32_t sourceSize, int32_t sourceIndex,
    int64_t* destination, int32_t destinationSize, int32_t destinationIndex,
    int32_t size) {
    jtk_Assert_assertTrue(size >= 0, "The specified size is invalid.");

    jtk_Arrays_checkRange(sourceSize, sourceIndex, sourceIndex + size);
    jtk_Arrays_checkRange(destinationSize, destinationIndex, destinationIndex + size);

    int32_t result = 0;
    /* A temporary array is created when the source and the destination arrays
     * are the same. All the elements from the source array are copied to the
     * temporary array first. This behaviour is unnecessary when the elements
     * do not change their index after copying.
     */
    if ((source == destination) && (sourceIndex != destinationIndex)) {
        int64_t* temporary = jtk_Memory_allocate(int64_t, size);
        int32_t limit = sourceIndex + size;
        int32_t j = 0;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            temporary[j] = source[i];
            j++;
        }
        int32_t limit0 = destinationIndex + size;
        int32_t j0 = 0;
        for (i = destinationIndex; i < limit0; i++) {
            destination[i] = temporary[j0];
            result++;
            j0++;
        }
    }
    else {
        int32_t limit = sourceIndex + size;
        int32_t j = destinationIndex;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            destination[j] = source[i];
            j++;
            result++;
        }

    }
    return result;
}

int32_t jtk_Arrays_copyEx_f(const float* source, int32_t sourceSize, int32_t sourceIndex,
    float* destination, int32_t destinationSize, int32_t destinationIndex,
    int32_t size) {
    jtk_Assert_assertTrue(size >= 0, "The specified size is invalid.");

    jtk_Arrays_checkRange(sourceSize, sourceIndex, sourceIndex + size);
    jtk_Arrays_checkRange(destinationSize, destinationIndex, destinationIndex + size);

    int32_t result = 0;
    /* A temporary array is created when the source and the destination arrays
     * are the same. All the elements from the source array are copied to the
     * temporary array first. This behaviour is unnecessary when the elements
     * do not change their index after copying.
     */
    if ((source == destination) && (sourceIndex != destinationIndex)) {
        float* temporary = jtk_Memory_allocate(float, size);
        int32_t limit = sourceIndex + size;
        int32_t j = 0;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            temporary[j] = source[i];
            j++;
        }
        int32_t limit0 = destinationIndex + size;
        int32_t j0 = 0;
        for (i = destinationIndex; i < limit0; i++) {
            destination[i] = temporary[j0];
            result++;
            j0++;
        }
    }
    else {
        int32_t limit = sourceIndex + size;
        int32_t j = destinationIndex;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            destination[j] = source[i];
            j++;
            result++;
        }

    }
    return result;
}

int32_t jtk_Arrays_copyEx_d(const double* source, int32_t sourceSize, int32_t sourceIndex,
    double* destination, int32_t destinationSize, int32_t destinationIndex,
    int32_t size) {
    jtk_Assert_assertTrue(size >= 0, "The specified size is invalid.");

    jtk_Arrays_checkRange(sourceSize, sourceIndex, sourceIndex + size);
    jtk_Arrays_checkRange(destinationSize, destinationIndex, destinationIndex + size);

    int32_t result = 0;
    /* A temporary array is created when the source and the destination arrays
     * are the same. All the elements from the source array are copied to the
     * temporary array first. This behaviour is unnecessary when the elements
     * do not change their index after copying.
     */
    if ((source == destination) && (sourceIndex != destinationIndex)) {
        double* temporary = jtk_Memory_allocate(double, size);
        int32_t limit = sourceIndex + size;
        int32_t j = 0;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            temporary[j] = source[i];
            j++;
        }
        int32_t limit0 = destinationIndex + size;
        int32_t j0 = 0;
        for (i = destinationIndex; i < limit0; i++) {
            destination[i] = temporary[j0];
            result++;
            j0++;
        }
    }
    else {
        int32_t limit = sourceIndex + size;
        int32_t j = destinationIndex;
        int32_t i;
        for (i = sourceIndex; i < limit; i++) {
            destination[j] = source[i];
            j++;
            result++;
        }

    }
    return result;
}

/* Copy Of */

void** jtk_Arrays_copyOf_v(const void** source, int32_t size, int32_t newSize,
    void* defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    void** result = jtk_Memory_allocate(void*, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_v(source, size, 0, result, newSize, 0, size0);
    if (newSize > size0) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

int8_t* jtk_Arrays_copyOf_b(const int8_t* source, int32_t size, int32_t newSize,
    int8_t defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    int8_t* result = jtk_Memory_allocate(int8_t, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_b(source, size, 0, result, newSize, 0, size0);
    if (newSize > size0) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

int16_t* jtk_Arrays_copyOf_s(const int16_t* source, int32_t size, int32_t newSize,
    int16_t defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    int16_t* result = jtk_Memory_allocate(int16_t, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_s(source, size, 0, result, newSize, 0, size0);
    if (newSize > size0) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

int32_t* jtk_Arrays_copyOf_i(const int32_t* source, int32_t size, int32_t newSize,
    int32_t defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    int32_t* result = jtk_Memory_allocate(int32_t, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_i(source, size, 0, result, newSize, 0, size0);
    if (newSize > size0) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

int64_t* jtk_Arrays_copyOf_l(const int64_t* source, int32_t size, int32_t newSize,
    int64_t defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    int64_t* result = jtk_Memory_allocate(int64_t, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_l(source, size, 0, result, newSize, 0, size0);
    if (newSize > size0) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

float* jtk_Arrays_copyOf_f(const float* source, int32_t size, int32_t newSize,
    float defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    float* result = jtk_Memory_allocate(float, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_f(source, size, 0, result, newSize, 0, size0);
    if (newSize > size0) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

double* jtk_Arrays_copyOf_d(const double* source, int32_t size, int32_t newSize,
    double defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    double* result = jtk_Memory_allocate(double, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_d(source, size, 0, result, newSize, 0, size0);
    if (newSize > size0) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

/* Copy of Extended */

/* NOTE: An ideal implementation for the jtk_Arrays_copyOf_*() functions would be to
 * delegate the operation to their corresponding jtk_Arrays_copyOfEx_*() functions.
 * Unfortunately, time does not permit for the rewrite of the code. End of the day,
 * the code works and no changes will be made in the near future.
 */

void** jtk_Arrays_copyOfEx_v(const void** source, int32_t size, int32_t newSize,
    void* defaultValue, bool overwrite) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    void** result = jtk_Memory_allocate(void*, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_v(source, size, 0, result, newSize, 0, size0);
    if ((newSize > size0) && overwrite) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

int8_t* jtk_Arrays_copyOfEx_b(const int8_t* source, int32_t size, int32_t newSize,
    int8_t defaultValue, bool overwrite) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    int8_t* result = jtk_Memory_allocate(int8_t, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_b(source, size, 0, result, newSize, 0, size0);
    if ((newSize > size0) && overwrite) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

int16_t* jtk_Arrays_copyOfEx_s(const int16_t* source, int32_t size, int32_t newSize,
    int16_t defaultValue, bool overwrite) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    int16_t* result = jtk_Memory_allocate(int16_t, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_s(source, size, 0, result, newSize, 0, size0);
    if ((newSize > size0) && overwrite) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

int32_t* jtk_Arrays_copyOfEx_i(const int32_t* source, int32_t size, int32_t newSize,
    int32_t defaultValue, bool overwrite) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    int32_t* result = jtk_Memory_allocate(int32_t, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_i(source, size, 0, result, newSize, 0, size0);
    if ((newSize > size0) && overwrite) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

int64_t* jtk_Arrays_copyOfEx_l(const int64_t* source, int32_t size, int32_t newSize,
    int64_t defaultValue, bool overwrite) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    int64_t* result = jtk_Memory_allocate(int64_t, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_l(source, size, 0, result, newSize, 0, size0);
    if ((newSize > size0) && overwrite) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

float* jtk_Arrays_copyOfEx_f(const float* source, int32_t size, int32_t newSize,
    float defaultValue, bool overwrite) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    float* result = jtk_Memory_allocate(float, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_f(source, size, 0, result, newSize, 0, size0);
    if ((newSize > size0) && overwrite) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

double* jtk_Arrays_copyOfEx_d(const double* source, int32_t size, int32_t newSize,
    double defaultValue, bool overwrite) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    double* result = jtk_Memory_allocate(double, newSize);
    int32_t size0 = jtk_Integer_min(size, newSize);
    jtk_Arrays_copyEx_d(source, size, 0, result, newSize, 0, size0);
    if ((newSize > size0) && overwrite) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

/* Copy of Range */

void** jtk_Arrays_copyOfRange_v(const void** source, int32_t sourceSize,
    int32_t startIndex, int32_t stopIndex, void* defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    /* The start index should be lesser than stop index. This prevents zero
     * sized arrays in results.
     */
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex), "The specified range is invalid.");

    int32_t newSize = stopIndex - startIndex;
    void** result = jtk_Memory_allocate(void*, newSize);
    int32_t size0 = jtk_Integer_min(sourceSize - startIndex, newSize);
    jtk_Arrays_copyEx_v(source, sourceSize, startIndex, result, newSize, 0, size0);
    if (size0 < newSize) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

int8_t* jtk_Arrays_copyOfRange_b(const int8_t* source, int32_t sourceSize,
    int32_t startIndex, int32_t stopIndex, int8_t defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    /* The start index should be lesser than stop index. This prevents zero
     * sized arrays in results.
     */
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex), "The specified range is invalid.");

    int32_t newSize = stopIndex - startIndex;
    int8_t* result = jtk_Memory_allocate(int8_t, newSize);
    int32_t size0 = jtk_Integer_min(sourceSize - startIndex, newSize);
    jtk_Arrays_copyEx_b(source, sourceSize, startIndex, result, newSize, 0, size0);
    if (size0 < newSize) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

int16_t* jtk_Arrays_copyOfRange_s(const int16_t* source, int32_t sourceSize,
    int32_t startIndex, int32_t stopIndex, int16_t defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    /* The start index should be lesser than stop index. This prevents zero
     * sized arrays in results.
     */
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex), "The specified range is invalid.");

    int32_t newSize = stopIndex - startIndex;
    int16_t* result = jtk_Memory_allocate(int16_t, newSize);
    int32_t size0 = jtk_Integer_min(sourceSize - startIndex, newSize);
    jtk_Arrays_copyEx_s(source, sourceSize, startIndex, result, newSize, 0, size0);
    if (size0 < newSize) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

int32_t* jtk_Arrays_copyOfRange_i(const int32_t* source, int32_t sourceSize,
    int32_t startIndex, int32_t stopIndex, int32_t defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    /* The start index should be lesser than stop index. This prevents zero
     * sized arrays in results.
     */
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex), "The specified range is invalid.");

    int32_t newSize = stopIndex - startIndex;
    int32_t* result = jtk_Memory_allocate(int32_t, newSize);
    int32_t size0 = jtk_Integer_min(sourceSize - startIndex, newSize);
    jtk_Arrays_copyEx_i(source, sourceSize, startIndex, result, newSize, 0, size0);
    if (size0 < newSize) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

int64_t* jtk_Arrays_copyOfRange_l(const int64_t* source, int32_t sourceSize,
    int32_t startIndex, int32_t stopIndex, int64_t defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    /* The start index should be lesser than stop index. This prevents zero
     * sized arrays in results.
     */
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex), "The specified range is invalid.");

    int32_t newSize = stopIndex - startIndex;
    int64_t* result = jtk_Memory_allocate(int64_t, newSize);
    int32_t size0 = jtk_Integer_min(sourceSize - startIndex, newSize);
    jtk_Arrays_copyEx_l(source, sourceSize, startIndex, result, newSize, 0, size0);
    if (size0 < newSize) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

float* jtk_Arrays_copyOfRange_f(const float* source, int32_t sourceSize,
    int32_t startIndex, int32_t stopIndex, float defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    /* The start index should be lesser than stop index. This prevents zero
     * sized arrays in results.
     */
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex), "The specified range is invalid.");

    int32_t newSize = stopIndex - startIndex;
    float* result = jtk_Memory_allocate(float, newSize);
    int32_t size0 = jtk_Integer_min(sourceSize - startIndex, newSize);
    jtk_Arrays_copyEx_f(source, sourceSize, startIndex, result, newSize, 0, size0);
    if (size0 < newSize) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

double* jtk_Arrays_copyOfRange_d(const double* source, int32_t sourceSize,
    int32_t startIndex, int32_t stopIndex, double defaultValue) {
    jtk_Assert_assertObject(source, "The specified array is null.");
    /* The start index should be lesser than stop index. This prevents zero
     * sized arrays in results.
     */
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex), "The specified range is invalid.");

    int32_t newSize = stopIndex - startIndex;
    double* result = jtk_Memory_allocate(double, newSize);
    int32_t size0 = jtk_Integer_min(sourceSize - startIndex, newSize);
    jtk_Arrays_copyEx_d(source, sourceSize, startIndex, result, newSize, 0, size0);
    if (size0 < newSize) {
        int32_t i;
        for (i = size0; i < newSize; i++) {
            result[i] = defaultValue;
        }
    }
    return result;
}

/* Equals */

bool jtk_Arrays_equals_v(void** array1, int32_t size1, void** array2,
    int32_t size2, jtk_ComparatorFunction_t comparator) {
    if (array1 == array2) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }
    if (size1 != size2) {
        return false;
    }

    bool result = true;
    for (int32_t i = 0; i < size1; i++) {
        if (array1[i] != array2[i]) {
            result = false;
            break;
        }
    }
    return result;
}

bool jtk_Arrays_equals_b(int8_t* array1, int32_t size1,
    int8_t* array2, int32_t size2) {
    if (array1 == array2) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }
    if (size1 != size2) {
        return false;
    }

    bool result = true;
    for (int32_t i = 0; i < size1; i++) {
        if (array1[i] != array2[i]) {
            result = false;
            break;
        }
    }
    return result;
}

bool jtk_Arrays_equals_s(int16_t* array1, int32_t size1,
    int16_t* array2, int32_t size2) {
    if (array1 == array2) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }
    if (size1 != size2) {
        return false;
    }

    bool result = true;
    for (int32_t i = 0; i < size1; i++) {
        if (array1[i] != array2[i]) {
            result = false;
            break;
        }
    }
    return result;
}

bool jtk_Arrays_equals_i(int32_t* array1, int32_t size1,
    int32_t* array2, int32_t size2) {
    if (array1 == array2) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }
    if (size1 != size2) {
        return false;
    }

    bool result = true;
    for (int32_t i = 0; i < size1; i++) {
        if (array1[i] != array2[i]) {
            result = false;
            break;
        }
    }
    return result;
}

bool jtk_Arrays_equals_l(int64_t* array1, int32_t size1,
    int64_t* array2, int32_t size2) {
    if (array1 == array2) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }
    if (size1 != size2) {
        return false;
    }

    bool result = true;
    for (int32_t i = 0; i < size1; i++) {
        if (array1[i] != array2[i]) {
            result = false;
            break;
        }
    }
    return result;
}

bool jtk_Arrays_equals_f(float* array1, int32_t size1,
    float* array2, int32_t size2) {
    if (array1 == array2) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }
    if (size1 != size2) {
        return false;
    }

    bool result = true;
    for (int32_t i = 0; i < size1; i++) {
        if (array1[i] != array2[i]) {
            result = false;
            break;
        }
    }
    return result;
}

bool jtk_Arrays_equals_d(double* array1, int32_t size1,
    double* array2, int32_t size2) {
    if (array1 == array2) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }
    if (size1 != size2) {
        return false;
    }

    bool result = true;
    for (int32_t i = 0; i < size1; i++) {
        if (array1[i] != array2[i]) {
            result = false;
            break;
        }
    }
    return result;
}

/* Equals Extended */

/* If any one of the arrays is {@code null}, it returns {@code false}
 * regardless of both the arrays being {@code null}.
 */
bool jtk_Arrays_equalsEx_v(void** array1, int32_t size1, int32_t index1,
    void** array2, int32_t size2, int32_t index2, int32_t size,
    jtk_ComparatorFunction_t comparator) {
    jtk_Assert_assertObject(array1, "The specified first array is null.");
    jtk_Assert_assertObject(array2, "The specified second array is null.");
    jtk_Assert_assertTrue(size1 > 0, "The specified first array size is invalid.");
    jtk_Assert_assertTrue(size2 > 0, "The specified second array size is invalid.");
    jtk_Assert_assertTrue(index1 >= 0, "The specified first index is invalid.");
    jtk_Assert_assertTrue(index1 + size <= size1, "With respect to the first array, the specified range size results in an invalid range.");
    jtk_Assert_assertTrue(index2 >= 0, "The specified second index is invalid.");
    jtk_Assert_assertTrue(index2 + size <= size2, "With respect to the second array, the specified range size results in an invalid range.");

    if ((array1 == array2) && (index1 == index2)) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }

    bool result = true;
    int32_t i;
    if (comparator != NULL) {
        for (i = 0; i < size; i++) {
            if (comparator(array1[index1 + i], array2[index2 + i]) != 0) {
                result = false;
                break;
            }
        }
    }
    else {
        for (i = 0; i < size; i++) {
            if (array1[index1 + i] != array2[index2 + i]) {
                result = false;
                break;
            }
        }
    }
    return result;
}

bool jtk_Arrays_equalsEx_b(int8_t* array1, int32_t size1, int32_t index1,
    int8_t* array2, int32_t size2, int32_t index2, int32_t size) {
    jtk_Assert_assertObject(array1, "The specified first array is null.");
    jtk_Assert_assertObject(array2, "The specified second array is null.");
    jtk_Assert_assertTrue(size1 > 0, "The specified first array size is invalid.");
    jtk_Assert_assertTrue(size2 > 0, "The specified second array size is invalid.");
    jtk_Assert_assertTrue(index1 >= 0, "The specified first index is invalid.");
    jtk_Assert_assertTrue(index1 + size <= size1, "With respect to the first array, the specified range size results in an invalid range.");
    jtk_Assert_assertTrue(index2 >= 0, "The specified second index is invalid.");
    jtk_Assert_assertTrue(index2 + size <= size2, "With respect to the second array, the specified range size results in an invalid range.");

    if ((array1 == array2) && (index1 == index2)) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }

    bool result = true;
    int32_t i;
    for (i = 0; i < size; i++) {
        if (array1[index1 + i] != array2[index2 + i]) {
            result = false;
            break;
        }
    }
    return result;
}

bool jtk_Arrays_equalsEx_s(int16_t* array1, int32_t size1, int32_t index1,
    int16_t* array2, int32_t size2, int32_t index2, int32_t size) {
    jtk_Assert_assertObject(array1, "The specified first array is null.");
    jtk_Assert_assertObject(array2, "The specified second array is null.");
    jtk_Assert_assertTrue(size1 > 0, "The specified first array size is invalid.");
    jtk_Assert_assertTrue(size2 > 0, "The specified second array size is invalid.");
    jtk_Assert_assertTrue(index1 >= 0, "The specified first index is invalid.");
    jtk_Assert_assertTrue(index1 + size <= size1, "With respect to the first array, the specified range size results in an invalid range.");
    jtk_Assert_assertTrue(index2 >= 0, "The specified second index is invalid.");
    jtk_Assert_assertTrue(index2 + size <= size2, "With respect to the second array, the specified range size results in an invalid range.");

    if ((array1 == array2) && (index1 == index2)) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }

    bool result = true;
    int32_t i;
    for (i = 0; i < size; i++) {
        if (array1[index1 + i] != array2[index2 + i]) {
            result = false;
            break;
        }
    }
    return result;
}

bool jtk_Arrays_equalsEx_i(int32_t* array1, int32_t size1, int32_t index1,
    int32_t* array2, int32_t size2, int32_t index2, int32_t size) {
    jtk_Assert_assertObject(array1, "The specified first array is null.");
    jtk_Assert_assertObject(array2, "The specified second array is null.");
    jtk_Assert_assertTrue(size1 > 0, "The specified first array size is invalid.");
    jtk_Assert_assertTrue(size2 > 0, "The specified second array size is invalid");
    jtk_Assert_assertTrue(index1 >= 0, "The specified first index is invalid.");
    jtk_Assert_assertTrue(index1 + size <= size1, "With respect to the first array, the specified range size results in an invalid range.");
    jtk_Assert_assertTrue(index2 >= 0, "The specified second index is invalid.");
    jtk_Assert_assertTrue(index2 + size <= size2, "With respect to the second array, the specified range size results in an invalid range.");

    if ((array1 == array2) && (index1 == index2)) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }

    bool result = true;
    int32_t i;
    for (i = 0; i < size; i++) {
        if (array1[index1 + i] != array2[index2 + i]) {
            result = false;
            break;
        }
    }
    return result;
}

bool jtk_Arrays_equalsEx_l(int64_t* array1, int32_t size1, int32_t index1,
    int64_t* array2, int32_t size2, int32_t index2, int32_t size) {
    jtk_Assert_assertObject(array1, "The specified first array is null.");
    jtk_Assert_assertObject(array2, "The specified second array is null.");
    jtk_Assert_assertTrue(size1 > 0, "The specified first array size is invalid.");
    jtk_Assert_assertTrue(size2 > 0, "The specified second array size is invalid");
    jtk_Assert_assertTrue(index1 >= 0, "The specified first index is invalid.");
    jtk_Assert_assertTrue(index1 + size <= size1, "With respect to the first array, the specified range size results in an invalid range.");
    jtk_Assert_assertTrue(index2 >= 0, "The specified second index is invalid.");
    jtk_Assert_assertTrue(index2 + size <= size2, "With respect to the second array, the specified range size results in an invalid range.");

    if ((array1 == array2) && (index1 == index2)) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }

    bool result = true;
    int32_t i;
    for (i = 0; i < size; i++) {
        if (array1[index1 + i] != array2[index2 + i]) {
            result = false;
            break;
        }
    }
    return result;
}

bool jtk_Arrays_equalsEx_f(float* array1, int32_t size1, int32_t index1,
    float* array2, int32_t size2, int32_t index2, int32_t size) {
    jtk_Assert_assertObject(array1, "The specified first array is null.");
    jtk_Assert_assertObject(array2, "The specified second array is null.");
    jtk_Assert_assertTrue(size1 > 0, "The specified first array size is invalid.");
    jtk_Assert_assertTrue(size2 > 0, "The specified second array size is invalid");
    jtk_Assert_assertTrue(index1 >= 0, "The specified first index is invalid.");
    jtk_Assert_assertTrue(index1 + size <= size1, "With respect to the first array, the specified range size results in an invalid range.");
    jtk_Assert_assertTrue(index2 >= 0, "The specified second index is invalid.");
    jtk_Assert_assertTrue(index2 + size <= size2, "With respect to the second array, the specified range size results in an invalid range.");

    if ((array1 == array2) && (index1 == index2)) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }

    bool result = true;
    int32_t i;
    for (i = 0; i < size; i++) {
        if (array1[index1 + i] != array2[index2 + i]) {
            result = false;
            break;
        }
    }
    return result;
}

bool jtk_Arrays_equalsEx_d(double* array1, int32_t size1, int32_t index1,
    double* array2, int32_t size2, int32_t index2, int32_t size) {
    jtk_Assert_assertObject(array1, "The specified first array is null.");
    jtk_Assert_assertObject(array2, "The specified second array is null.");
    jtk_Assert_assertTrue(size1 > 0, "The specified first array size is invalid.");
    jtk_Assert_assertTrue(size2 > 0, "The specified second array size is invalid");
    jtk_Assert_assertTrue(index1 >= 0, "The specified first index is invalid.");
    jtk_Assert_assertTrue(index1 + size <= size1, "With respect to the first array, the specified range size results in an invalid range.");
    jtk_Assert_assertTrue(index2 >= 0, "The specified second index is invalid.");
    jtk_Assert_assertTrue(index2 + size <= size2, "With respect to the second array, the specified range size results in an invalid range.");

    if ((array1 == array2) && (index1 == index2)) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }

    bool result = true;
    int32_t i;
    for (i = 0; i < size; i++) {
        if (array1[index1 + i] != array2[index2 + i]) {
            result = false;
            break;
        }
    }
    return result;
}

/* Fill */

void jtk_Arrays_fill_v(void** array, int32_t size, void* value) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    jtk_Arrays_fillEx_v(array, size, 0, size, value);
}

void jtk_Arrays_fill_b(int8_t* array, int32_t size, int8_t value) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    jtk_Arrays_fillEx_b(array, size, 0, size, value);
}

void jtk_Arrays_fill_s(int16_t* array, int32_t size, int16_t value) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    jtk_Arrays_fillEx_s(array, size, 0, size, value);
}

void jtk_Arrays_fill_i(int32_t* array, int32_t size, int32_t value) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    jtk_Arrays_fillEx_i(array, size, 0, size, value);
}

void jtk_Arrays_fill_l(int64_t* array, int32_t size, int64_t value) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    jtk_Arrays_fillEx_l(array, size, 0, size, value);
}

void jtk_Arrays_fill_f(float* array, int32_t size, float value) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    jtk_Arrays_fillEx_f(array, size, 0, size, value);
}

void jtk_Arrays_fill_d(double* array, int32_t size, double value) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    jtk_Arrays_fillEx_d(array, size, 0, size, value);
}


/* Fill Extended */

void jtk_Arrays_fillEx_v(void** array, int32_t size, int32_t startIndex,
    int32_t stopIndex, void* value) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex)
        && (stopIndex <= size), "The specified range is invalid.");

    int32_t i;
    for (i = startIndex; i < stopIndex; i++) {
        array[i] = value;
    }
}

void jtk_Arrays_fillEx_b(int8_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, int8_t value) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex)
        && (stopIndex <= size), "The specified range is invalid.");

    int32_t i;
    for (i = startIndex; i < stopIndex; i++) {
        array[i] = value;
    }
}

void jtk_Arrays_fillEx_s(int16_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, int16_t value) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex)
        && (stopIndex <= size), "The specified range is invalid.");

    int32_t i;
    for (i = startIndex; i < stopIndex; i++) {
        array[i] = value;
    }
}

void jtk_Arrays_fillEx_i(int32_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, int32_t value) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex)
        && (stopIndex <= size), "The specified range is invalid.");

    int32_t i;
    for (i = startIndex; i < stopIndex; i++) {
        array[i] = value;
    }
}

void jtk_Arrays_fillEx_l(int64_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, int64_t value) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex)
        && (stopIndex <= size), "The specified range is invalid.");

    int32_t i;
    for (i = startIndex; i < stopIndex; i++) {
        array[i] = value;
    }
}

void jtk_Arrays_fillEx_f(float* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, float value) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex)
        && (stopIndex <= size), "The specified range is invalid.");

    int32_t i;
    for (i = startIndex; i < stopIndex; i++) {
        array[i] = value;
    }
}

void jtk_Arrays_fillEx_d(double* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, double value) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex)
        && (stopIndex <= size), "The specified range is invalid.");

    int32_t i;
    for (i = startIndex; i < stopIndex; i++) {
        array[i] = value;
    }
}

/* Filter */

void jtk_Array_filter_v(const void** source, int32_t sourceSize, jtk_MixedPredicateFunction_t predicate,
    void** destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (predicate(source[i])) {
            destination[j] = source[i];
            j++;
        }
    }
}

void jtk_Array_filter_b(const int8_t* source, int32_t sourceSize, jtk_IntegerPredicateFunction_t predicate,
    int8_t* destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (predicate(source[i])) {
            destination[j] = source[i];
            j++;
        }
    }
}

void jtk_Array_filter_s(const int16_t* source, int32_t sourceSize, jtk_IntegerPredicateFunction_t predicate,
    int16_t* destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (predicate(source[i])) {
            destination[j] = source[i];
            j++;
        }
    }
}

void jtk_Array_filter_i(const int32_t* source, int32_t sourceSize, jtk_IntegerPredicateFunction_t predicate,
    int32_t* destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (predicate(source[i])) {
            destination[j] = source[i];
            j++;
        }
    }
}

void jtk_Array_filter_l(const int64_t* source, int32_t sourceSize, jtk_LongPredicateFunction_t predicate,
    int64_t* destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (predicate(source[i])) {
            destination[j] = source[i];
            j++;
        }
    }
}

void jtk_Array_filter_f(const float* source, int32_t sourceSize, jtk_FloatPredicateFunction_t predicate,
    float* destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (predicate(source[i])) {
            destination[j] = source[i];
            j++;
        }
    }
}

void jtk_Array_filter_d(const double* source, int32_t sourceSize, jtk_DoublePredicateFunction_t predicate,
    double* destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (predicate(source[i])) {
            destination[j] = source[i];
            j++;
        }
    }
}

/* Reverse */

/* I wrote the jtk_Arrays_reverse_*() and jtk_Arrays_reverseEx_*()
 * functions a very long time ago. I did not bother refactoring them.
 * jtk_Arrays_reverse_*() can be simplified by delegating the operation
 * to equivalent jtk_Arrays_reverseEx_*(). In the case of jtk_Arrays_reverseEx_*(),
 * it can be simplified by delegating the swapping operation to jtk_Arrays_swap_*().
 * I may refactor, *if** I ever find time and inspiration.
 */

void jtk_Arrays_reverse_v(void** array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    int32_t left = 0;
    int32_t right = size - 1;
    int32_t middle = size >> 1;
    while (left < middle) {
        void* temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right--;
    }
}

void jtk_Arrays_reverse_b(int8_t* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    int32_t left = 0;
    int32_t right = size - 1;
    int32_t middle = size >> 1;
    while (left < middle) {
        int8_t temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right--;
    }
}
void jtk_Arrays_reverse_s(int16_t* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    int32_t left = 0;
    int32_t right = size - 1;
    int32_t middle = size >> 1;
    while (left < middle) {
        int16_t temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right--;
    }
}
void jtk_Arrays_reverse_i(int32_t* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    int32_t left = 0;
    int32_t right = size - 1;
    int32_t middle = size >> 1;
    while (left < middle) {
        int32_t temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right--;
    }
}
void jtk_Arrays_reverse_l(int64_t* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    int32_t left = 0;
    int32_t right = size - 1;
    int32_t middle = size >> 1;
    while (left < middle) {
        int64_t temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right--;
    }
}
void jtk_Arrays_reverse_f(float* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    int32_t left = 0;
    int32_t right = size - 1;
    int32_t middle = size >> 1;
    while (left < middle) {
        float temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right--;
    }
}
void jtk_Arrays_reverse_d(double* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    int32_t left = 0;
    int32_t right = size - 1;
    int32_t middle = size >> 1;
    while (left < middle) {
        double temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right--;
    }
}

/* Reverse Extended */

void jtk_Arrays_reverseEx_v(void** array, int32_t size, int32_t startIndex,
    int32_t stopIndex) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    int32_t left = startIndex;
    int32_t right = stopIndex - 1;
    int32_t middle = (stopIndex - startIndex) >> 1;
    while (left < middle) {
        void* temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right++;
    }
}

void jtk_Arrays_reverseEx_b(int8_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    int32_t left = startIndex;
    int32_t right = stopIndex - 1;
    int32_t middle = (stopIndex - startIndex) >> 1;
    while (left < middle) {
        int8_t temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right++;
    }
}

void jtk_Arrays_reverseEx_s(int16_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    int32_t left = startIndex;
    int32_t right = stopIndex - 1;
    int32_t middle = (stopIndex - startIndex) >> 1;
    while (left < middle) {
        int16_t temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right++;
    }
}

void jtk_Arrays_reverseEx_i(int32_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    int32_t left = startIndex;
    int32_t right = stopIndex - 1;
    int32_t middle = (stopIndex - startIndex) >> 1;
    while (left < middle) {
        int32_t temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right++;
    }
}

void jtk_Arrays_reverseEx_l(int64_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    int32_t left = startIndex;
    int32_t right = stopIndex - 1;
    int32_t middle = (stopIndex - startIndex) >> 1;
    while (left < middle) {
        int64_t temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right++;
    }
}

void jtk_Arrays_reverseEx_f(float* array, int32_t size, int32_t startIndex,
    int32_t stopIndex) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    int32_t left = startIndex;
    int32_t right = stopIndex - 1;
    int32_t middle = (stopIndex - startIndex) >> 1;
    while (left < middle) {
        float temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right++;
    }
}

void jtk_Arrays_reverseEx_d(double* array, int32_t size, int32_t startIndex,
    int32_t stopIndex) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    int32_t left = startIndex;
    int32_t right = stopIndex - 1;
    int32_t middle = (stopIndex - startIndex) >> 1;
    while (left < middle) {
        double temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        left++;
        right++;
    }
}

/* Rotate */

void jtk_Arrays_rotate_v(void** array, int32_t size, int32_t distance) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    if (size != 0) {
        distance = distance % size;
        if (distance < 0) {
            distance += size;
        }
        if (distance != 0) {
            int32_t cycle = 0;
            int32_t moved = 0;
            while (moved != size) {
                void* current = array[cycle];
                int i = cycle;
                do {
                    i += distance;
                    if (i >= size) {
                        i -= size;
                    }

                    void* temporary = array[i];
                    array[i] = current;
                    current = temporary;

                    moved++;
                }
                while (i != cycle);
                cycle++;
            }
        }
    }
}

void jtk_Arrays_rotate_b(int8_t* array, int32_t size, int32_t distance) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    if (size != 0) {
        distance = distance % size;
        if (distance < 0) {
            distance += size;
        }
        if (distance != 0) {
            int32_t cycle = 0;
            int32_t moved = 0;
            while (moved != size) {
                int8_t current = array[cycle];
                int i = cycle;
                do {
                    i += distance;
                    if (i >= size) {
                        i -= size;
                    }

                    int8_t temporary = array[i];
                    array[i] = current;
                    current = temporary;

                    moved++;
                }
                while (i != cycle);
                cycle++;
            }
        }
    }
}

void jtk_Arrays_rotate_s(int16_t* array, int32_t size, int32_t distance) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    if (size != 0) {
        distance = distance % size;
        if (distance < 0) {
            distance += size;
        }
        if (distance != 0) {
            int32_t cycle = 0;
            int32_t moved = 0;
            while (moved != size) {
                int16_t current = array[cycle];
                int i = cycle;
                do {
                    i += distance;
                    if (i >= size) {
                        i -= size;
                    }

                    int16_t temporary = array[i];
                    array[i] = current;
                    current = temporary;

                    moved++;
                }
                while (i != cycle);
                cycle++;
            }
        }
    }
}

void jtk_Arrays_rotate_i(int32_t* array, int32_t size, int32_t distance) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    if (size != 0) {
        distance = distance % size;
        if (distance < 0) {
            distance += size;
        }
        if (distance != 0) {
            int32_t cycle = 0;
            int32_t moved = 0;
            while (moved != size) {
                int32_t current = array[cycle];
                int i = cycle;
                do {
                    i += distance;
                    if (i >= size) {
                        i -= size;
                    }

                    int32_t temporary = array[i];
                    array[i] = current;
                    current = temporary;

                    moved++;
                }
                while (i != cycle);
                cycle++;
            }
        }
    }
}

void jtk_Arrays_rotate_l(int64_t* array, int32_t size, int32_t distance) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    if (size != 0) {
        distance = distance % size;
        if (distance < 0) {
            distance += size;
        }
        if (distance != 0) {
            int32_t cycle = 0;
            int32_t moved = 0;
            while (moved != size) {
                int64_t current = array[cycle];
                int i = cycle;
                do {
                    i += distance;
                    if (i >= size) {
                        i -= size;
                    }

                    int64_t temporary = array[i];
                    array[i] = current;
                    current = temporary;

                    moved++;
                }
                while (i != cycle);
                cycle++;
            }
        }
    }
}

void jtk_Arrays_rotate_f(float* array, int32_t size, int32_t distance) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    if (size != 0) {
        distance = distance % size;
        if (distance < 0) {
            distance += size;
        }
        if (distance != 0) {
            int32_t cycle = 0;
            int32_t moved = 0;
            while (moved != size) {
                float current = array[cycle];
                int i = cycle;
                do {
                    i += distance;
                    if (i >= size) {
                        i -= size;
                    }

                    float temporary = array[i];
                    array[i] = current;
                    current = temporary;

                    moved++;
                }
                while (i != cycle);
                cycle++;
            }
        }
    }
}

void jtk_Arrays_rotate_d(double* array, int32_t size, int32_t distance) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size > 0, "The specified size is invalid.");

    if (size != 0) {
        distance = distance % size;
        if (distance < 0) {
            distance += size;
        }
        if (distance != 0) {
            int32_t cycle = 0;
            int32_t moved = 0;
            while (moved != size) {
                double current = array[cycle];
                int i = cycle;
                do {
                    i += distance;
                    if (i >= size) {
                        i -= size;
                    }

                    double temporary = array[i];
                    array[i] = current;
                    current = temporary;

                    moved++;
                }
                while (i != cycle);
                cycle++;
            }
        }
    }
}

/* Swap */

void jtk_Arrays_swap_v(void** array, int32_t size, int32_t index1, int32_t index2) {
    jtk_Assert_assertObject(array, "The specified object is null.");
    jtk_Arrays_checkIndex(size, index1);
    jtk_Arrays_checkIndex(size, index2);

    void* temporary = array[index1];
    array[index1] = array[index2];
    array[index2] = temporary;
}

void jtk_Arrays_swap_b(int8_t* array, int32_t size, int32_t index1, int32_t index2) {
    jtk_Assert_assertObject(array, "The specified object is null.");
    jtk_Arrays_checkIndex(size, index1);
    jtk_Arrays_checkIndex(size, index2);

    int8_t temporary = array[index1];
    array[index1] = array[index2];
    array[index2] = temporary;
}

void jtk_Arrays_swap_s(int16_t* array, int32_t size, int32_t index1, int32_t index2) {
    jtk_Assert_assertObject(array, "The specified object is null.");
    jtk_Arrays_checkIndex(size, index1);
    jtk_Arrays_checkIndex(size, index2);

    int16_t temporary = array[index1];
    array[index1] = array[index2];
    array[index2] = temporary;
}

void jtk_Arrays_swap_i(int32_t* array, int32_t size, int32_t index1, int32_t index2) {
    jtk_Assert_assertObject(array, "The specified object is null.");
    jtk_Arrays_checkIndex(size, index1);
    jtk_Arrays_checkIndex(size, index2);

    int32_t temporary = array[index1];
    array[index1] = array[index2];
    array[index2] = temporary;
}

void jtk_Arrays_swap_l(int64_t* array, int32_t size, int32_t index1, int32_t index2) {
    jtk_Assert_assertObject(array, "The specified object is null.");
    jtk_Arrays_checkIndex(size, index1);
    jtk_Arrays_checkIndex(size, index2);

    int64_t temporary = array[index1];
    array[index1] = array[index2];
    array[index2] = temporary;
}

void jtk_Arrays_swap_f(float* array, int32_t size, int32_t index1, int32_t index2) {
    jtk_Assert_assertObject(array, "The specified object is null.");
    jtk_Arrays_checkIndex(size, index1);
    jtk_Arrays_checkIndex(size, index2);

    float temporary = array[index1];
    array[index1] = array[index2];
    array[index2] = temporary;
}

void jtk_Arrays_swap_d(double* array, int32_t size, int32_t index1, int32_t index2) {
    jtk_Assert_assertObject(array, "The specified object is null.");
    jtk_Arrays_checkIndex(size, index1);
    jtk_Arrays_checkIndex(size, index2);

    double temporary = array[index1];
    array[index1] = array[index2];
    array[index2] = temporary;
}

// Select

void jtk_Arrays_select_b(const int8_t* source, int32_t sourceSize, bool* selection,
    int8_t* destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (selection[i]) {
            destination[j] = source[i];
            j++;
        }
    }
}

void jtk_Arrays_select_s(const int16_t* source, int32_t sourceSize, bool* selection,
    int16_t* destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (selection[i]) {
            destination[j] = source[i];
            j++;
        }
    }
}

void jtk_Arrays_select_i(const int32_t* source, int32_t sourceSize, bool* selection,
    int32_t* destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (selection[i]) {
            destination[j] = source[i];
            j++;
        }
    }
}

void jtk_Arrays_select_l(const int64_t* source, int32_t sourceSize, bool* selection,
    int64_t* destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (selection[i]) {
            destination[j] = source[i];
            j++;
        }
    }
}

void jtk_Arrays_select_f(const float* source, int32_t sourceSize, bool* selection,
    float* destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (selection[i]) {
            destination[j] = source[i];
            j++;
        }
    }
}

void jtk_Arrays_select_d(const double* source, int32_t sourceSize, bool* selection,
    double* destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (selection[i]) {
            destination[j] = source[i];
            j++;
        }
    }
}

void jtk_Arrays_select_v(const void** source, int32_t sourceSize, bool* selection,
    void** destination, int32_t destinationSize) {
    int32_t j = 0;
    int32_t i;
    for (i = 0; (i < sourceSize) && (j < destinationSize); i++) {
        if (selection[i]) {
            destination[j] = (void*)source[i];
            j++;
        }
    }
}

/* Tim Sort */

void jtk_Arrays_timSort_b(int8_t* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size >= 0, "The specified array size is invalid.");

    jtk_Arrays_timSortEx_b(array, size, 0, size, true);
}

void jtk_Arrays_timSort_s(int16_t* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size >= 0, "The specified array size is invalid.");

    jtk_Arrays_timSortEx_s(array, size, 0, size, true);
}

void jtk_Arrays_timSort_i(int32_t* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size >= 0, "The specified array size is invalid.");

    jtk_Arrays_timSortEx_i(array, size, 0, size, true);
}

void jtk_Arrays_timSort_l(int64_t* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size >= 0, "The specified array size is invalid.");
}

void jtk_Arrays_timSort_f(float* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size >= 0, "The specified array size is invalid.");

    jtk_Arrays_timSortEx_f(array, size, 0, size, true);
}

void jtk_Arrays_timSort_d(double* array, int32_t size) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size >= 0, "The specified array size is invalid.");

    jtk_Arrays_timSortEx_d(array, size, 0, size, true);
}

void jtk_Arrays_timSort_v(void** array, int32_t size, jtk_ComparatorFunction_t comparator) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size >= 0, "The specified array size is invalid.");

    jtk_Arrays_timSortEx_v(array, size, 0, size, comparator);
}

/* Tim Sort Extended */

int32_t jtk_Byte_comparePtr(const int8_t* value1, const int8_t* value2) {
    return *value1 - *value2;
}

int32_t jtk_Byte_compareReversePtr(const int8_t* value1, const int8_t* value2) {
    return *value2 - *value1;
}

int32_t jtk_Short_comparePtr(const int16_t* value1, const int16_t* value2) {
    return *value1 - *value2;
}

int32_t jtk_Short_compareReversePtr(const int16_t* value1, const int16_t* value2) {
    return *value2 - *value1;
}

int32_t jtk_Integer_comparePtr(const int32_t* value1, const int32_t* value2) {
    return *value1 - *value2;
}

int32_t jtk_Integer_compareReversePtr(const int32_t* value1, const int32_t* value2) {
    return *value2 - *value1;
}

int32_t jtk_Long_comparePtr(const int64_t* value1, const int64_t* value2) {
    return *value1 - *value2;
}

int32_t jtk_Long_compareReversePtr(const int64_t* value1, const int64_t* value2) {
    return *value2 - *value1;
}

int32_t jtk_Float_comparePtr(const int64_t* value1, const int64_t* value2) {
    return jtk_Float_compare(*value1, *value2);
}

int32_t jtk_Float_compareReversePtr(const int64_t* value1, const int64_t* value2) {
    return jtk_Float_compare(*value2, *value1);
}

int32_t jtk_Double_comparePtr(const int64_t* value1, const int64_t* value2) {
    return jtk_Double_compare(*value1, *value2);
}

int32_t jtk_Double_compareReversePtr(const int64_t* value1, const int64_t* value2) {
    return jtk_Double_compare(*value2, *value1);
}

bool jtk_Timsort_sort(void* array, int32_t size, size_t width, jtk_ComparatorFunction_t compare);

void jtk_Arrays_timSortEx_b(int8_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    jtk_Timsort_sort(array + startIndex, stopIndex - startIndex, sizeof (int8_t),
        ascending? jtk_Byte_comparePtr : jtk_Byte_compareReversePtr);
}

void jtk_Arrays_timSortEx_s(int16_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    jtk_Timsort_sort(array + startIndex, stopIndex - startIndex, sizeof (int16_t),
        ascending? jtk_Short_comparePtr : jtk_Short_compareReversePtr);
}

void jtk_Arrays_timSortEx_i(int32_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size >= 0, "The specified array size is invalid.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    jtk_Timsort_sort(array + startIndex, stopIndex - startIndex, sizeof (int32_t),
        ascending? jtk_Integer_comparePtr : jtk_Integer_compareReversePtr);
}

void jtk_Arrays_timSortEx_l(int64_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    jtk_Timsort_sort(array + startIndex, stopIndex - startIndex, sizeof (int64_t),
        ascending? jtk_Long_comparePtr : jtk_Long_compareReversePtr);
}

void jtk_Arrays_timSortEx_f(float* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    jtk_Timsort_sort(array + startIndex, stopIndex - startIndex, sizeof (float),
        ascending? jtk_Float_comparePtr : jtk_Float_compareReversePtr);
}

void jtk_Arrays_timSortEx_d(double* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);

    jtk_Timsort_sort(array + startIndex, stopIndex - startIndex, sizeof (double),
        ascending? jtk_Double_comparePtr : jtk_Double_compareReversePtr);
}

void jtk_Arrays_timSortEx_v(void** array, int32_t size, int32_t startIndex,
    int32_t stopIndex, jtk_ComparatorFunction_t comparator) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);
    jtk_Assert_assertObject(comparator, "The specified comparator is null.");

    jtk_Timsort_sort(array + startIndex, stopIndex - startIndex, sizeof (void*),
        comparator);
}

/* The following implementation of the Timsort algorithm was adopted from the
 * port created by Patrick O. Perry. The original source code can be found at
 * [https://github.com/patperry/timsort].
 */

/* Copyright (C) 2020 Samuel Rowe
 * Copyright (C) 2011 Patrick O. Perry
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <assert.h>		// assert
#include <errno.h>		// EINVAL
#if defined(_MSC_VER)
# include <malloc.h>		// _alloca
#endif
#include <stddef.h>		// size_t, NULL
#include <stdlib.h>		// malloc, free
#include <string.h>		// memcpy, memmove

/**
 * This is the minimum sized sequence that will be merged. Shorter
 * sequences will be lengthened by calling binarySort. If the entire
 * array is less than this length, no merges will be performed.
 *
 * This constant should be a power of two. It was 64 in Tim Peter's C
 * implementation, but 32 was empirically determined to work better in
 * [Android's Java] implementation. In the unlikely event that you set
 * this constant to be a number that's not a power of two, you'll need
 * to change the {@link #minRunLength} computation.
 *
 * If you decrease this constant, you must change the stackLen
 * computation in the TimSort constructor, or you risk an
 * ArrayOutOfBounds exception. See listsort.txt for a discussion
 * of the minimum stack length required as a function of the length
 * of the array being sorted and the minimum merge sequence length.
 */
#define MIN_MERGE 32

/**
 * When we get into galloping mode, we stay there until both runs win less
 * often than MIN_GALLOP consecutive times.
 */
#define MIN_GALLOP 7

/**
 * Maximum initial size of tmp array, which is used for merging. The array
 * can grow to accommodate demand.
 *
 * Unlike Tim's original C version, we do not allocate this much storage
 * when sorting smaller arrays. This change was required for performance.
 */
#define INITIAL_TMP_STORAGE_LENGTH 256

/**
 * Maximum stack size. This depends on MIN_MERGE and sizeof(size_t).
 */
#define MAX_STACK 85

/**
 * Define MALLOC_STACK if you want to allocate the run stack on the heap.
 * Otherwise, 2 * MAX_STACK * sizeof(size_t) ~ 1.3K gets reserved on the
 * call stack.
 */
/* #undef MALLOC_STACK */

#if defined(_MSC_VER)
    #define DEFINE_TEMP(temp) void* temp = _alloca(WIDTH)
#else
    #define DEFINE_TEMP(temp) char temp[WIDTH]
#endif

#define ASSIGN(x, y) memcpy(x, y, WIDTH)
#define INCPTR(x) ((void *)((char *)(x) + WIDTH))
#define DECPTR(x) ((void *)((char *)(x) - WIDTH))
#define ELEM(a,i) ((char *)(a) + (i) * WIDTH)
#define LEN(n) ((n) * WIDTH)

#define MIN(a,b) ((a) <= (b) ? (a) : (b))
#define SUCCESS 0
#define FAILURE (-1)

#define CONCAT(x, y) x ## _ ## y
#define MAKE_STR(x, y) CONCAT(x,y)
#define NAME(x) MAKE_STR(x, WIDTH)
#define CALL(x) NAME(x)

#ifdef IS_TIMSORT_R
/*
 * Note order of elements to comparator matches that of C11 qsort_s,
 * not BSD qsort_r or Windows qsort_s
 */
typedef int (*comparator) (const void *x, const void *y, void *thunk);
#define CMPPARAMS(compar, thunk) jtk_ComparatorFunction_t compare compar, void *thunk
#define CMPARGS(compar, thunk) (compar), (thunk)
#define CMP(compar, thunk, x, y) (compar((x), (y), (thunk)))
#define TIMSORT timsort_r
#else

#define CMPPARAMS(compar, thunk) jtk_ComparatorFunction_t compar
#define CMPARGS(compar, thunk) (compar)
#define CMP(compar, thunk, x, y) (compar((x), (y)))

#endif /* IS_TIMSORT_R */

struct timsort_run {
	void *base;
	size_t len;
};

struct timsort {
	/**
	 * The array being sorted.
	 */
	void *a;
	size_t a_length;

	/**
	 * The comparator for this sort.
	 */
	jtk_ComparatorFunction_t c;
#ifdef IS_TIMSORT_R
	void *carg;
#endif

	/**
	 * This controls when we get *into* galloping mode.  It is initialized
	 * to MIN_GALLOP.  The mergeLo and mergeHi methods nudge it higher for
	 * random data, and lower for highly structured data.
	 */
	size_t minGallop;

	/**
	 * Temp storage for merges.
	 */
	void *tmp;
	size_t tmp_length;

	/**
	 * A stack of pending runs yet to be merged.  Run i starts at
	 * address base[i] and extends for len[i] elements.  It's always
	 * true (so long as the indices are in bounds) that:
	 *
	 *     runBase[i] + runLen[i] == runBase[i + 1]
	 *
	 * so we could cut the storage for this, but it's a minor amount,
	 * and keeping all the info explicit simplifies the code.
	 */
	size_t stackSize;	// Number of pending runs on stack
	size_t stackLen;	// maximum stack size
#ifdef MALLOC_STACK
	struct timsort_run *run;
#else
	struct timsort_run run[MAX_STACK];
#endif
};

static int timsort_init(struct timsort *ts, void *a, size_t len,
			CMPPARAMS(c, carg),
			size_t width);
static void timsort_deinit(struct timsort *ts);
static size_t minRunLength(size_t n);
static void pushRun(struct timsort *ts, void *runBase, size_t runLen);
static void *ensureCapacity(struct timsort *ts, size_t minCapacity,
			    size_t width);

/**
 * Creates a TimSort instance to maintain the state of an ongoing sort.
 *
 * @param a the array to be sorted
 * @param nel the length of the array
 * @param c the comparator to determine the order of the sort
 * @param width the element width
 */
static int timsort_init(struct timsort *ts, void *a, size_t len,
			CMPPARAMS(c, carg),
			size_t width)
{
	int err = 0;

	assert(ts);
	assert(a || !len);
	assert(c);
	assert(width);

	ts->minGallop = MIN_GALLOP;
	ts->stackSize = 0;

	ts->a = a;
	ts->a_length = len;
	ts->c = c;
#ifdef IS_TIMSORT_R
	ts->carg = carg;
#endif

	// Allocate temp storage (which may be increased later if necessary)
	ts->tmp_length = (len < 2 * INITIAL_TMP_STORAGE_LENGTH ?
			  len >> 1 : INITIAL_TMP_STORAGE_LENGTH);
	if (ts->tmp_length) {
		ts->tmp = malloc(ts->tmp_length * width);
		err |= ts->tmp == NULL;
	} else {
		ts->tmp = NULL;
	}

	/*
	 * Allocate runs-to-be-merged stack (which cannot be expanded).  The
	 * stack length requirements are described in listsort.txt.  The C
	 * version always uses the same stack length (85), but this was
	 * measured to be too expensive when sorting "mid-sized" arrays (e.g.,
	 * 100 elements) in Java.  Therefore, we use smaller (but sufficiently
	 * large) stack lengths for smaller arrays.  The "magic numbers" in the
	 * computation below must be changed if MIN_MERGE is decreased.  See
	 * the MIN_MERGE declaration above for more information.
	 */

	/* POP:
	 * In listsort.txt, Tim argues that the run lengths form a decreasing
	 * sequence, and each run length is greater than the previous two.
	 * Thus, lower bounds on the minimum runLen numbers on the stack are:
	 *
	 *   [      1           = b[1]
	 *   ,      minRun      = b[2]
	 *   ,  1 * minRun +  2 = b[3]
	 *   ,  2 * minRun +  3 = b[4]
	 *   ,  3 * minRun +  6 = b[5]
	 *   , ...
	 *   ],
	 *
	 * Moreover, minRun >= MIN_MERGE / 2.  Also, note that the sum of the
	 * run lenghts is less than or equal to the length of the array.
	 *
	 * Let s be the stack length and n be the array length.  If s >= 2, then n >= b[1] + b[2].
	 * More generally, if s >= m, then n >= b[1] + b[2] + ... + b[m] = B[m].  Conversely, if
	 * n < B[m], then s < m.
	 *
	 * In Haskell, we can compute the bin sizes using the fibonacci numbers
	 *
	 *     fibs = 1:1:(zipWith (+) fibs (tail fibs))
	 *
	 *     cumSums a = case a of { [] -> [] ; (x:xs) -> x:(map (x+) (cumSums xs)) }
	 *
	 *     fibSums = cumSums fibs
	 *
	 *     binSizes minRun = ([ 1, minRun, minRun + 2 ]
	 *                        ++ [ (1 + minRun) * (fibs !! (i+2))
	 *                             + fibSums !! (i+1) - fibs !! i | i <- [0..] ])
	 *
	 *     arraySizes minRun = cumSums (binSizes minRun)
	 *
	 * We these funcitons, we can compute a table with minRun = MIN_MERGE / 2 = 16:
	 *
	 *     m          B[m]
	 *   ---------------------------
	 *      1                    17
	 *      2                    35
	 *      3                    70
	 *      4                   124
	 *      5                   214
	 *      6                   359
	 *     11                  4220
	 *     17                 76210 # > 2^16 - 1
	 *     40            4885703256 # > 2^32 - 1
	 *     86  20061275507500957239 # > 2^64 - 1
	 *
	 * If len < B[m], then stackLen < m:
	 */
#ifdef MALLOC_STACK
	ts->stackLen = (len < 359 ? 5
			: len < 4220 ? 10
			: len < 76210 ? 16 : len < 4885703256ULL ? 39 : 85);

	/* Note that this is slightly more liberal than in the Java
	 * implementation.  The discrepancy might be because the Java
	 * implementation uses a less accurate lower bound.
	 */
	//stackLen = (len < 120 ? 5 : len < 1542 ? 10 : len < 119151 ? 19 : 40);

	ts->run = malloc(ts->stackLen * sizeof(ts->run[0]));
	err |= ts->run == NULL;
#else
	ts->stackLen = MAX_STACK;
#endif

	if (!err) {
		return SUCCESS;
	} else {
		timsort_deinit(ts);
		return FAILURE;
	}
}

static void timsort_deinit(struct timsort *ts)
{
	free(ts->tmp);
#ifdef MALLOC_STACK
	free(ts->run);
#endif
}

/**
 * Returns the minimum acceptable run length for an array of the specified
 * length. Natural runs shorter than this will be extended with
 * {@link #binarySort}.
 *
 * Roughly speaking, the computation is:
 *
 *  If n < MIN_MERGE, return n (it's too small to bother with fancy stuff).
 *  Else if n is an exact power of 2, return MIN_MERGE/2.
 *  Else return an int k, MIN_MERGE/2 <= k <= MIN_MERGE, such that n/k
 *   is close to, but strictly less than, an exact power of 2.
 *
 * For the rationale, see listsort.txt.
 *
 * @param n the length of the array to be sorted
 * @return the length of the minimum run to be merged
 */
static size_t minRunLength(size_t n)
{
	size_t r = 0;		// Becomes 1 if any 1 bits are shifted off
	while (n >= MIN_MERGE) {
		r |= (n & 1);
		n >>= 1;
	}
	return n + r;
}

/**
 * Pushes the specified run onto the pending-run stack.
 *
 * @param runBase index of the first element in the run
 * @param runLen  the number of elements in the run
 */
static void pushRun(struct timsort *ts, void *runBase, size_t runLen)
{
	assert(ts->stackSize < ts->stackLen);

	ts->run[ts->stackSize].base = runBase;
	ts->run[ts->stackSize].len = runLen;
	ts->stackSize++;
}

/**
 * Ensures that the external array tmp has at least the specified
 * number of elements, increasing its size if necessary.  The size
 * increases exponentially to ensure amortized linear time complexity.
 *
 * @param minCapacity the minimum required capacity of the tmp array
 * @return tmp, whether or not it grew
 */
static void *ensureCapacity(struct timsort *ts, size_t minCapacity,
			    size_t width)
{
	if (ts->tmp_length < minCapacity) {
		// Compute smallest power of 2 > minCapacity
		size_t newSize = minCapacity;
		newSize |= newSize >> 1;
		newSize |= newSize >> 2;
		newSize |= newSize >> 4;
		newSize |= newSize >> 8;
		newSize |= newSize >> 16;
		if (sizeof(newSize) > 4)
			newSize |= newSize >> 32;

		newSize++;
		newSize = MIN(newSize, ts->a_length >> 1);
		if (newSize == 0) {	// (overflow) Not bloody likely!
			newSize = minCapacity;
		}

		free(ts->tmp);
		ts->tmp_length = newSize;
		ts->tmp = malloc(ts->tmp_length * width);
	}

	return ts->tmp;
}

#define WIDTH 4
    #include "Timsort.h"
#undef WIDTH

#define WIDTH 8
    #include "Timsort.h"
#undef WIDTH

#define WIDTH 16
    #include "Timsort.h"
#undef WIDTH

#define WIDTH width
    #include "Timsort.h"
#undef WIDTH

bool jtk_Timsort_sort(void* array, int32_t size, size_t width,
    jtk_ComparatorFunction_t compare) {
	switch (width) {
	case 4:
		return timsort_4(array, size, width, CMPARGS(compare, carg));
	case 8:
		return timsort_8(array, size, width, CMPARGS(compare, carg));
	case 16:
		return timsort_16(array, size, width, CMPARGS(compare, carg));
	default:
		return timsort_width(array, size, width, CMPARGS(compare, carg));
	}
}