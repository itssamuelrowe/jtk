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

// Thursday, June 28, 2018

#include <jtk/collection/array/Array.h>
#include <jtk/collection/array/ArrayIterator.h>
#include <jtk/collection/array/Arrays.h>
#include <jtk/core/Integer.h>
#include <jtk/core/Float.h>
#include <jtk/core/Double.h>

/*******************************************************************************
 * Array                                                                       *
 *******************************************************************************/

/* Constructor */

jtk_Array_t* jtk_Array_new(int32_t size) {
    jtk_Assert_assertTrue(size >= 0, "The specified array size is invalid.");

    jtk_Array_t* array = jtk_Memory_allocate(jtk_Array_t, 1);
    if (size != 0) {
        array->m_values = jtk_Memory_allocate(void*, size);
        array->m_size = size;

        /* By default, newly allocated arrays contain garbage values.
         * The library initializes all the elements to null by default.
         */
        jtk_Arrays_fill_v(array->m_values, size, NULL);
    }
    else {
        array->m_values = NULL;
        array->m_size = 0;
    }
    return array;
}

jtk_Array_t* jtk_Array_newFromRawArray(void** other, int32_t size) {
    jtk_Assert_assertObject(other, "The specified source array is null.");
    jtk_Assert_assertTrue(size >= 0, "The specified array size is invalid.");

    jtk_Array_t* array = jtk_Array_new(size);
    jtk_Arrays_copy_v(other, size, array->m_values, array->m_size);

    return array;
}

jtk_Array_t* jtk_Array_newWithDefaultValue(int32_t size, void* defaultValue) {
    jtk_Assert_assertTrue(size >= 0, "The specified array size is invalid.");

    jtk_Array_t* array = jtk_Memory_allocate(jtk_Array_t, 1);
    if (size > 0) {
        array->m_values = jtk_Memory_allocate(void*, size);
        array->m_size = size;
        jtk_Arrays_fill_v(array->m_values, size, defaultValue);
    }
    else {
        array->m_values = NULL;
        array->m_size = 0;
    }
    return array;
}

/* Destructor */

void jtk_Array_delete(jtk_Array_t* array) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    if (array->m_values != NULL) {
        jtk_Memory_deallocate(array->m_values);
    }
}

/* Copy */

int32_t jtk_Array_copy(jtk_Array_t* source, jtk_Array_t* destination) {
    jtk_Assert_assertObject(destination, "The specified source array is null.");
    jtk_Assert_assertObject(destination, "The specified array is null.");

    return jtk_Arrays_copy_v(source->m_values, source->m_size, destination->m_values,
        destination->m_size);
}

/* Copy Extended */

int32_t jtk_Array_copyEx(jtk_Array_t* source, int32_t sourceIndex,
    jtk_Array_t* destination, int32_t destinationIndex, int32_t size) {
    jtk_Assert_assertObject(destination, "The specified source array is null.");
    jtk_Assert_assertObject(destination, "The specified destination array is null.");

    // TODO: Assert index :)

    return jtk_Arrays_copyEx_v(source->m_values, source->m_size, sourceIndex,
        destination->m_values, destination->m_size, destinationIndex, size);
}

/* Copy Of */

jtk_Array_t* jtk_Array_copyOf(jtk_Array_t* source, int32_t newSize, void* defaultValue) {
    jtk_Assert_assertObject(source, "The specified source array is null.");
    jtk_Assert_assertTrue(newSize > 0, "The specified new array size is invalid.");

    jtk_Array_t* result = jtk_Array_new(newSize);
    int32_t size0 = jtk_Integer_min(source->m_size, newSize);
    jtk_Arrays_copyEx_v(source->m_values, source->m_size, 0, result->m_values,
        newSize, 0, size0);
    if (newSize > size0) {
        jtk_Arrays_fillEx_v(result->m_values, newSize, size0, newSize, defaultValue);
    }
    return result;
}

/* Copy Of Range */

jtk_Array_t* jtk_Array_copyOfRange(jtk_Array_t* source, int32_t startIndex,
    int32_t stopIndex, void* defaultValue) {
    jtk_Assert_assertObject(source, "The specified source array is null.");
    /* The start index should be lesser than stop index. This prevents zero
     * sized arrays in results.
     */
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex < stopIndex), "The specified range is invalid.");

    int32_t newSize = stopIndex - startIndex;
    jtk_Array_t* result = jtk_Array_new(newSize);
    int32_t size0 = jtk_Integer_min(source->m_size - startIndex, newSize);
    jtk_Arrays_copyEx_v(source->m_values, source->m_size, startIndex,
        result->m_values, newSize, 0, size0);
    if (newSize > size0) {
        jtk_Arrays_fillEx_v(result->m_values, newSize, size0, newSize, defaultValue);
    }
    return result;
}

/* Clone */

jtk_Array_t* jtk_Array_clone(jtk_Array_t* other) {
    jtk_Assert_assertObject(other, "The specified array is null.");

    jtk_Array_t* array = jtk_Memory_allocate(jtk_Array_t, 1);
    if (other->m_values != NULL) {
        array->m_values = jtk_Memory_allocate(void*, other->m_size);
        array->m_size = other->m_size;
        jtk_Arrays_copy_v(array->m_values, array->m_size, other->m_values, other->m_size);
    }
    else {
        array->m_values = NULL;
        array->m_size = 0;
    }
    return array;
}

/* Empty */

bool jtk_Array_isEmpty(jtk_Array_t* array) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    return array->m_size == 0;
}

/* Equals */

bool jtk_Array_equals(jtk_Array_t* array1, jtk_Array_t* array2) {
    if (array1 == array2) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }
    if (array1->m_size != array2->m_size) {
        return false;
    }

    bool result = true;
    if (array1->m_adapter != NULL) {
        for (int32_t i = 0; i < array1->m_size; i++) {
            if (!array1->m_adapter->equals(array1->m_values[i], array2->m_values[i])) {
                result = false;
                break;
            }
        }
    }
    else {
        for (int32_t i = 0; i < array1->m_size; i++) {
            if ((array1->m_values[i] != array2->m_values[i])) {
                result = false;
                break;
            }
        }
    }
    return result;
}

/* Equals Extended */

bool jtk_Array_equalsEx(jtk_Array_t* array1, int32_t index1, jtk_Array_t* array2,
    int32_t index2, int32_t size) {
    jtk_Assert_assertTrue(index1 >= 0, "The specified first index is invalid.");
    jtk_Assert_assertTrue(index1 + size <= array1->m_size, "With respect to the first array, the specified range size results in an invalid range.");
    jtk_Assert_assertTrue(index2 >= 0, "The specified second index is invalid.");
    jtk_Assert_assertTrue(index2 + size <= array2->m_size, "With respect to the second array, the specified range size results in an invalid range.");

    if ((array1 == array2) && (index1 == index2)) {
        return true;
    }
    if ((array1 == NULL) || (array2 == NULL)) {
        return false;
    }

    bool result = true;
    int32_t i;
    if (array1->m_adapter != NULL) {
        for (i = 0; i < size; i++) {
            if (!array1->m_adapter->equals(array1->m_values[index1 + i], array2->m_values[index2 + i])) {
                result = false;
                break;
            }
        }
    }
    else {
        for (i = 0; i < size; i++) {
            if (array1->m_values[index1 + i] != array2->m_values[index2 + i]) {
                result = false;
                break;
            }
        }
    }
    return result;
}

/* Fill */

void jtk_Array_fill(jtk_Array_t* array, void* value) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    jtk_Arrays_fill_v(array->m_values, array->m_size, value);
}

/* Fill Extended */

void jtk_Array_fillEx(jtk_Array_t* array, int32_t startIndex, int32_t stopIndex,
    void* value) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    jtk_Arrays_fillEx_v(array->m_values, array->m_size, startIndex, stopIndex, value);
}

/* Iterator */

jtk_Iterator_t* jtk_Array_getIterator(jtk_Array_t* array) {
    jtk_ArrayIterator_t* iterator = jtk_ArrayIterator_new(array->m_values, array->m_size);
    return jtk_ArrayIterator_getIterator(iterator);
}

/* Migrate */

jtk_Array_t* jtk_Array_migrate(jtk_Array_t* array, jtk_Array_MigrateFunction_t migrate) {
    jtk_Array_t* result = jtk_Array_new(array->m_size);
    int32_t i;
    for (i = 0; i < array->m_size; i++) {
        void* oldValue = array->m_values[i];
        void* newValue = migrate(oldValue);
        result->m_values[i] = newValue;
    }
    return result;
}

jtk_Array_t* jtk_Array_migrate_v(void** array, int32_t size, jtk_Array_MigrateFunction_t migrate) {
    jtk_Array_t* result = jtk_Array_new(size);
    int32_t i;
    for (i = 0; i < size; i++) {
        void* oldValue = array[i];
        void* newValue = migrate(oldValue);
        result->m_values[i] = newValue;
    }
    return result;
}

/* Raw Array */

void** getRawArray(jtk_Array_t* array) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    return array->m_values;
}

void** jtk_Array_toRawArray(jtk_Array_t* array) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    return jtk_Arrays_clone_v(array->m_values, array->m_size);
}

/* Recycle */

/*

void jtk_ArrayTest_testRecycle() {
    jtk_Array_recycle(arrayWithElements, otherWithElements);
    jtk_Array_recycle(arrayWithElements, otherWithoutElements);
    jtk_Array_recycle(arrayWithoutElements, otherWithElements);
    jtk_Array_recycle(arrayWithoutElements, otherWithoutElements);
}

*/

// TODO: Test this function :")
void jtk_Array_recycle(jtk_Array_t* array, jtk_Array_t* other) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertObject(other, "The specified source array is null.");

    if (array != other) {
        if ((array->m_size != other->m_size) && (array->m_values != NULL)) {
            jtk_Memory_deallocate(array->m_values);
        }
        if (other->m_size > 0) {
            if (array->m_size != other->m_size) {
                array->m_values = jtk_Memory_allocate(void*, other->m_size);
                array->m_size = other->m_size;
            }
            jtk_Arrays_copy_v(array->m_values, array->m_size, other->m_values, other->m_size);
        }
        else {
            array->m_values = NULL;
            array->m_size = 0;
        }
    }
}

/* Reverse */

void jtk_Array_reverse(jtk_Array_t* array) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    jtk_Arrays_reverse_v(array->m_values, array->m_size);
}

/* Reverse Extended */

void jtk_Array_reverseEx(jtk_Array_t* array, int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    jtk_Arrays_reverseEx_v(array->m_values, array->m_size, startIndex, stopIndex);
}

/* Rotate */

void jtk_Array_rotate(jtk_Array_t* array, int32_t distance) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    jtk_Arrays_rotate_v(array->m_values, array->m_size, distance);
}

/* Size */

int32_t jtk_Array_getSize(jtk_Array_t* array) {
    jtk_Assert_assertObject(array, "The specified array is null.");

    return array->m_size;
}

/* Swap */

void jtk_Array_swap(jtk_Array_t* array, int32_t index1, int32_t index2) {
    jtk_Assert_assertObject(array, "The specified object is null.");
    jtk_Arrays_checkIndex(array->m_size, index1);
    jtk_Arrays_checkIndex(array->m_size, index2);

    void* temporary = array->m_values[index1];
    array->m_values[index1] = array->m_values[index2];
    array->m_values[index2] = temporary;
}

/* Value */

void* jtk_Array_getValue(jtk_Array_t* array, int32_t index) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue((index >= 0) && (index < array->m_size), "The specified index is invalid.");

    return array->m_values[index];
}

void jtk_Array_setValue(jtk_Array_t* array, int32_t index, void* value) {
    jtk_Assert_assertObject(array, "The specified array is null.");
    jtk_Assert_assertTrue((index >= 0) && (index < array->m_size), "The specified index is invalid.");

    array->m_values[index] = value;
}