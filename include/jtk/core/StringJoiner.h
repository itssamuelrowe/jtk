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

// Sunday, May 12, 2019

#ifndef JTK_CORE_STRING_JOINER_H
#define JTK_CORE_STRING_JOINER_H

#include <jtk/Configuration.h>
#include <jtk/core/StringBuilder.h>

/*******************************************************************************
 * StringJoiner                                                                *
 *******************************************************************************/

/**
 * @class StringJoiner
 * @ingroup jtk_core
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_StringJoiner_t {

    /**
     * The string that is used to separate the elements.
     */
    jtk_String_t* m_delimiter;

    /**
     * The string that is used as a substitute when no elements are added.
     */
    jtk_String_t* m_emptyValue;

    /**
     * The string that precedes the content.
     */
    jtk_String_t* m_prefix;

    /**
     * The string that succeeds the content.
     */
    jtk_String_t* m_suffix;

    /**
     * The character sequence constructed from the added elements separated by
     * the delimiter. It does not contain the prefix and suffix.
     */
    jtk_StringBuilder_t* m_value;

    /**
     * The total number of elements joined so far.
     */
    int32_t m_numberOfElements;

};

/**
 * @memberof StringJoiner
 */
typedef struct jtk_StringJoiner_t jtk_StringJoiner_t;

// Constructor

jtk_StringJoiner_t* jtk_StringJoiner_new();

// Destructor

void jtk_StringJoiner_delete(jtk_StringJoiner_t* joiner);

// Delimiter

jtk_String_t* jtk_StringJoiner_getDelimiter(jtk_StringJoiner_t* joiner);

// Empty Value

void jtk_StringJoiner_setEmptyValueSequence(jtk_StringJoiner_t* joiner,
    const uint8_t* emptyValue);

void jtk_StringJoiner_setEmptyValueSequenceEx(jtk_StringJoiner_t* joiner,
    const uint8_t* emptyValue, int32_t size);

void jtk_StringJoiner_setEmptyValue(jtk_StringJoiner_t* joiner,
    jtk_String_t* emptyValue);

jtk_String_t* jtk_StringJoiner_getEmptyValue(jtk_StringJoiner_t* joiner);

// Join

void jtk_StringJoiner_join(jtk_StringJoiner_t* joiner, jtk_String_t* element);

// Join Sequence

void jtk_StringJoiner_joinSequence(jtk_StringJoiner_t* joiner, const uint8_t* element);

void jtk_StringJoiner_joinSequenceEx(jtk_StringJoiner_t* joiner, const uint8_t* element,
    int32_t size);

// Prefix

void jtk_StringJoiner_setPrefix(jtk_StringJoiner_t* joiner, jtk_String_t* prefix);
void jtk_StringJoiner_setPrefixSequence(jtk_StringJoiner_t* joiner, const uint8_t* prefix);
void jtk_StringJoiner_setPrefixSequenceEx(jtk_StringJoiner_t* joiner, const uint8_t* prefix, int32_t prefixSize);
jtk_String_t* jtk_StringJoiner_getPrefix(jtk_StringJoiner_t* joiner);

// Suffix

void jtk_StringJoiner_setSuffix(jtk_StringJoiner_t* joiner, jtk_String_t* prefix);
void jtk_StringJoiner_setSuffixSequence(jtk_StringJoiner_t* joiner, const uint8_t* prefix);
void jtk_StringJoiner_setSuffixSequenceEx(jtk_StringJoiner_t* joiner, const uint8_t* prefix, int32_t prefixSize);
jtk_String_t* jtk_StringJoiner_getSuffix(jtk_StringJoiner_t* joiner);

// Size

int32_t jtk_StringJoiner_getSize(jtk_StringJoiner_t* joiner);

int32_t jtk_StringJoiner_getContentSize(jtk_StringJoiner_t* joiner);

// Number of Elements

int32_t jtk_StringJoiner_getNumberOfElements(jtk_StringJoiner_t* joiner);

// String

jtk_String_t* jtk_StringJoiner_toString(jtk_StringJoiner_t* joiner);

#endif /* JTK_CORE_STRING_JOINER_H */