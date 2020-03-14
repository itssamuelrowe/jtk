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
    
    // jtk_Arrays_timSortEx_v(array, size, 0, size, true);
}

/* Tim Sort Extended */

void jtk_Arrays_timSortEx_b(int8_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);
}

void jtk_Arrays_timSortEx_s(int16_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);
}

void jtk_Arrays_timSortEx_i(int32_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue(size >= 0, "The specified array size is invalid.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);
    
}

void jtk_Arrays_timSortEx_l(int64_t* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);
}

void jtk_Arrays_timSortEx_f(float* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);
}

void jtk_Arrays_timSortEx_d(double* array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);
}

void jtk_Arrays_timSortEx_v(void** array, int32_t size, int32_t startIndex,
    int32_t stopIndex, bool ascending, jtk_ComparatorFunction_t comparator) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Arrays_checkRange(size, startIndex, stopIndex);
    jtk_Assert_assertObject(comparator, "The specified comparator is null.");
}
