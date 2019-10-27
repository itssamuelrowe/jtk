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

// Tuesday, May 21, 2019

#include <jtk/core/Integer.h>
#include <jtk/core/StringBuilder.h>
#include <jtk/core/System.h>
#include <jtk/core/Error.h>

/*******************************************************************************
 * StringBuilder                                                               *
 *******************************************************************************/

// Constructor

jtk_StringBuilder_t* jtk_StringBuilder_new() {
    return jtk_StringBuilder_newWithCapacity(JTK_STRING_BUILDER_DEFAULT_CAPACITY);
}

jtk_StringBuilder_t* jtk_StringBuilder_newWithCapacity(int32_t capacity) {
    jtk_Assert_assertTrue(capacity > 0, "The specified capacity is invalid.");

    jtk_StringBuilder_t* builder = jtk_Memory_allocate(jtk_StringBuilder_t, 1);
    builder->m_value = jtk_Memory_allocate(uint8_t, capacity);
    builder->m_capacity = capacity;
    builder->m_size = 0;

    return builder;
}

jtk_StringBuilder_t* jtk_StringBuilder_newWithSequence(const uint8_t* content) {
    return jtk_StringBuilder_newWithSequenceEx(content, -1);
}

jtk_StringBuilder_t* jtk_StringBuilder_newWithSequenceEx(const uint8_t* content,
    int32_t size) {
    size = (size < 0)? jtk_CString_getSize(content) : size;
    jtk_StringBuilder_t* builder = jtk_StringBuilder_newWithCapacity(size + JTK_STRING_BUILDER_DEFAULT_CAPACITY);

    jtk_Arrays_copy_b(content, size, builder->m_value, builder->m_capacity);
    builder->m_size = size;

    return builder;
}

// Destructor

void jtk_StringBuilder_delete(jtk_StringBuilder_t* builder) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    jtk_Memory_deallocate(builder->m_value);
    jtk_Memory_deallocate(builder);
}

// Append

void jtk_StringBuilder_appendBoolean(jtk_StringBuilder_t* builder, bool value) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    if (value) {
        jtk_StringBuilder_ensureSpace(builder, 4);
        builder->m_value[builder->m_size++] = 't';
        builder->m_value[builder->m_size++] = 'r';
        builder->m_value[builder->m_size++] = 'u';
        builder->m_value[builder->m_size++] = 'e';
    }
    else {
        jtk_StringBuilder_ensureSpace(builder, 5);
        builder->m_value[builder->m_size++] = 'f';
        builder->m_value[builder->m_size++] = 'a';
        builder->m_value[builder->m_size++] = 'l';
        builder->m_value[builder->m_size++] = 's';
        builder->m_value[builder->m_size++] = 'e';
    }
}

/*
void jtk_StringBuilder_appendCodePoint(jtk_StringBuilder_t* builder,
    int32_t codePoint) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    jtk_StringBuilder_ensureSpace(builder, 4);
    int32_t result = jtk_Character_toUtf8Ex(codePoint, builder->m_value, builder->m_capacity,
        builder->m_size);
    builder->m_size += result;
}
*/

// TODO: Right now this function works only for ASCII characters (within 255 codepoints.)
void jtk_StringBuilder_appendCodePoint(jtk_StringBuilder_t* builder,
    int32_t codePoint) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    jtk_StringBuilder_ensureSpace(builder, 1);
    builder->m_value[builder->m_size] = codePoint;
    builder->m_size++;
}

void jtk_StringBuilder_append_c(jtk_StringBuilder_t* builder,
    uint8_t value) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    jtk_StringBuilder_ensureSpace(builder, 1);
    builder->m_value[builder->m_size] = value;
    builder->m_size++;
}

void jtk_StringBuilder_append_i(jtk_StringBuilder_t* builder,
    int32_t value) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    jtk_StringBuilder_ensureSpace(builder, JTK_INTEGER_MAX_DECIMAL_STRING_SIZE);
    int32_t size = jtk_Integer_getStringEx(value, 10, builder->m_value,
        builder->m_capacity, builder->m_size);
    builder->m_size += size;
}

/*
void jtk_StringBuilder_append_l(jtk_StringBuilder_t* builder,
    int64_t value) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    jtk_StringBuilder_ensureSpace(builder, JTK_LONG_MAX_DECIMAL_STRING_SIZE);
    int32_t size = jtk_Long_getStringEx(value, builder->m_value,
        builder->m_capacity, builder->m_size);
    builder->m_size += size;
}
void jtk_StringBuilder_append_f(jtk_StringBuilder_t* builder,
    float value) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    jtk_StringBuilder_ensureSpace(builder, JTK_FLOAT_MAX_DECIMAL_STRING_SIZE);
    int32_t size = jtk_Float_getStringEx(value, builder->m_value,
        builder->m_capacity, builder->m_size);
    builder->m_size += size;
}

void jtk_StringBuilder_append_d(jtk_StringBuilder_t* builder,
    double value) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    jtk_StringBuilder_ensureSpace(builder, JTK_DOUBLE_MAX_DECIMAL_STRING_SIZE);
    int32_t size = jtk_Double_getStringEx(value, builder->m_value,
        builder->m_capacity, builder->m_size);
    builder->m_size += size;
}
*/

void jtk_StringBuilder_append_z(jtk_StringBuilder_t* builder,
    const uint8_t* sequence) {
    jtk_StringBuilder_appendEx_z(builder, sequence, -1);
}

void jtk_StringBuilder_appendEx_z(jtk_StringBuilder_t* builder,
    const uint8_t* sequence, int32_t size) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    if (sequence == NULL) {
        jtk_StringBuilder_appendNull(builder);
    }
    else {
        size = (size < 0)? jtk_CString_getSize(sequence) : size;
        jtk_StringBuilder_ensureSpace(builder, size);
        jtk_Arrays_copyEx_b(sequence, size, 0, builder->m_value,
            builder->m_capacity, builder->m_size, size);
        builder->m_size += size;
    }
}

/*
void jtk_StringBuilder_appendSubsequence(jtk_StringBuilder_t* builder,
    const uint8_t* sequence, int32_t size, int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");
    jtk_Assert_assertTrue(size >= 0, "The specified size is invalid.");


    jtk_StringBuilder_
}
*/

void jtk_StringBuilder_appendString(jtk_StringBuilder_t* builder,
    jtk_String_t* string) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    if (string == NULL) {
        jtk_StringBuilder_appendNull(builder);
    }
    else {
        int32_t size = jtk_String_getSize(string);
        const uint8_t* value = jtk_String_getValue(string);

        jtk_StringBuilder_ensureSpace(builder, size);
        jtk_Arrays_copyEx_b(value, size, 0, builder->m_value,
            builder->m_capacity, builder->m_size, size);
        builder->m_size += size;
    }
}

void jtk_StringBuilder_appendNull(jtk_StringBuilder_t* builder) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    jtk_StringBuilder_appendEx_z(builder, "(null)", 4);
}

// Capacity

bool jtk_StringBuilder_ensureSpace(jtk_StringBuilder_t* builder, int32_t capacity) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    bool result = false;
    if (capacity > 0) {
        int32_t currentCapacity = builder->m_capacity;
        int32_t minimumCapacity = (builder->m_size + capacity);
        int32_t requiredCapacity = minimumCapacity - currentCapacity;
        if (requiredCapacity > 0) {
            int32_t newCapacity = (currentCapacity * 2) + 2;
            if ((newCapacity - minimumCapacity) < 0) {
                newCapacity = minimumCapacity;
            }

            if (newCapacity < 0) {
                if (minimumCapacity < 0) {
                    /* Report an error, the requested capacity is too big. */
                    jtk_System_t* system = jtk_System_getInstance();
                    jtk_System_setErrorEx(system, JTK_ERROR_INTEGER_OVERFLOW,
                        JTK_ERROR_FLAG_SOURCE_LIBRARY | JTK_ERROR_FLAG_LEVEL_LOW);
                }
                else {
                    /* Fall back, the new capacity was recommened by this function. */
                    newCapacity = JTK_INTEGER_MAX_VALUE;
                }
            }

            /* Do not allocate a new buffer if an out-of-memory error was
             * reported.
             */
            if (newCapacity > 0) {
                uint8_t* temporary = builder->m_value;
                builder->m_value = (uint8_t*)jtk_Arrays_copyOfEx_b(builder->m_value,
                    builder->m_capacity, newCapacity, 0, false);
                builder->m_capacity = newCapacity;
                jtk_Memory_deallocate(temporary);
            }
        }
    }
    return result;
}

int32_t jtk_StringBuilder_getCapacity(jtk_StringBuilder_t* builder) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    return builder->m_capacity;
}

// Clear

void jtk_StringBuilder_clear(jtk_StringBuilder_t* builder) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    builder->m_size = 0;
}

// Empty

bool jtk_StringBuilder_isEmpty(jtk_StringBuilder_t* builder) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    return builder->m_size == 0;
}

// Size

int32_t jtk_StringBuilder_getSize(jtk_StringBuilder_t* builder) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    return builder->m_size;
}

// String

jtk_String_t* jtk_StringBuilder_toString(jtk_StringBuilder_t* builder) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    return jtk_String_newEx(builder->m_value, builder->m_size);
}

uint8_t* jtk_StringBuilder_toCString(jtk_StringBuilder_t* builder) {
    jtk_Assert_assertObject(builder, "The specified string builder is null.");

    return jtk_CString_newWithSize(builder->m_value, builder->m_size);
}