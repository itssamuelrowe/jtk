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

/*******************************************************************************
 * StringJoiner                                                                *
 *******************************************************************************/

// Constructor

jtk_StringJoiner_t* jtk_StringJoiner_new() {
    jtk_StringJoiner_t* joiner = jtk_Memory_allocate(jtk_StringJoiner_t, 1);
    joiner->m_delimiter = NULL;
    joiner->m_emptyValue = NULL;
    joiner->m_prefix = NULL;
    joiner->m_suffix = NULL;
    joiner->m_value = jtk_StringBuilder_new();
    joiner->m_numberOfElements = 0;

    return joiner;
}

// Destructor

void jtk_StringJoiner_delete(jtk_StringJoiner_t* joiner) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    if (joiner->m_delimiter != NULL) {
        jtk_String_delete(joiner->m_delimiter);
    }

    if (joiner->m_emptyValue != NULL) {
        jtk_String_delete(joiner->m_emptyValue;
    }

    if (joiner->m_prefix != NULL) {
        jtk_String_delete(joiner->m_prefix);
    }

    if (joiner->m_suffix != NULL) {
        jtk_String_delete(joiner->m_suffix);
    }

    jtk_StringBuilder_delete(joiner->m_value);
    jtk_Memory_deallocate(joiner);
}

// Delimiter

jtk_String_t* jtk_StringJoiner_getDelimiter(jtk_StringJoiner_t* joiner) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    return joiner->m_delimiter;
}

// Empty Value

void jtk_StringJoiner_setEmptyValueSequence(jtk_StringJoiner_t* joiner,
    const uint8_t* emptyValue) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    if (joiner->m_emptyValue != NULL) {
        jtk_String_delete(joiner->m_emptyValue);
    }

    joiner->m_emptyValue = (emptyValue == NULL)? NULL : jtk_String_new(emptyValue);
}

void jtk_StringJoiner_setEmptyValueSequenceEx(jtk_StringJoiner_t* joiner,
    const uint8_t* emptyValue, int32_t size) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    if (joiner->m_emptyValue != NULL) {
        jtk_String_delete(joiner->m_emptyValue);
    }

    joiner->m_emptyValue = (emptyValue == NULL)? NULL : jtk_String_newEx(emptyValue, size);
}

void jtk_StringJoiner_setEmptyValue(jtk_StringJoiner_t* joiner,
    jtk_String_t* emptyValue) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    if (joiner->m_emptyValue != NULL) {
        jtk_String_delete(joiner->m_emptyValue);
    }

    joiner->m_emptyValue = (emptyValue == NULL)? NULL : jtk_String_clone(emptyValue);
}

jtk_String_t* jtk_StringJoiner_getEmptyValue(jtk_StringJoiner_t* joiner) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    return joiner->m_emptyValue;
}

// Join

void jtk_StringJoiner_join(jtk_StringJoiner_t* joiner, jtk_String_t* element) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    if (joiner->m_numberOfElements > 0) {
        jtk_StringBuilder_appendString(joiner->m_value, joiner->m_delimiter);
    }
    jtk_StringBuilder_appendString(joiner->m_value, element);
    joiner->m_numberOfElements++;
}

// Join Sequence

void jtk_StringJoiner_joinSequence(jtk_StringJoiner_t* joiner,
    const uint8_t* element) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    if (joiner->m_numberOfElements > 0) {
        jtk_StringBuilder_appendString(joiner->m_value, joiner->m_delimiter);
    }
    jtk_StringBuilder_append_z(joiner->m_value, element);
    joiner->m_numberOfElements++;
}

void jtk_StringJoiner_joinSequenceEx(jtk_StringJoiner_t* joiner, const uint8_t* element,
    int32_t size) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    if (joiner->m_numberOfElements > 0) {
        jtk_StringBuilder_appendString(joiner->m_value, joiner->m_delimiter);
    }
    jtk_StringBuilder_appendEx_z(joiner->m_value, element, size);
    joiner->m_numberOfElements++;
}

// Prefix

void jtk_StringJoiner_setPrefix(jtk_StringJoiner_t* joiner, jtk_String_t* prefix) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    if (joiner->m_prefix != NULL) {
        jtk_String_delete(joiner->m_prefix);
    }

    joiner->m_prefix = (prefix == NULL)? NULL : jtk_String_clone(prefix);
}

void jtk_StringJoiner_setPrefixSequence(jtk_StringJoiner_t* joiner,
    const uint8_t* prefix) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    if (joiner->m_prefix != NULL) {
        jtk_String_delete(joiner->m_prefix);
    }

    joiner->m_prefix = (prefix == NULL)? NULL : jtk_String_new(prefix);
}

void jtk_StringJoiner_setPrefixSequenceEx(jtk_StringJoiner_t* joiner,
    const uint8_t* prefix, int32_t prefixSize) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    if (joiner->m_prefix != NULL) {
        jtk_String_delete(joiner->m_prefix);
    }

    joiner->m_prefix = (prefix == NULL)? NULL : jtk_String_newEx(prefix, prefixSize);
}

jtk_String_t* jtk_StringJoiner_getPrefix(jtk_StringJoiner_t* joiner) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    return joiner->m_prefix;
}

// Suffix

void jtk_StringJoiner_setSuffix(jtk_StringJoiner_t* joiner, jtk_String_t* suffix) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    if (joiner->m_suffix != NULL) {
        jtk_String_delete(joiner->m_suffix);
    }

    joiner->m_suffix = (suffix == NULL)? NULL : jtk_String_clone(suffix);
}

void jtk_StringJoiner_setSuffixSequence(jtk_StringJoiner_t* joiner,
    const uint8_t* suffix) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    if (joiner->m_suffix != NULL) {
        jtk_String_delete(joiner->m_suffix);
    }

    joiner->m_suffix = (suffix == NULL)? NULL : jtk_String_new(suffix);
}

void jtk_StringJoiner_setSuffixSequenceEx(jtk_StringJoiner_t* joiner,
    const uint8_t* suffix, int32_t suffixSize) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    if (joiner->m_suffix != NULL) {
        jtk_String_delete(joiner->m_suffix);
    }

    joiner->m_suffix = (suffix == NULL)? NULL : jtk_String_newEx(suffix, suffixSize);
}

jtk_String_t* jtk_StringJoiner_getSuffix(jtk_StringJoiner_t* joiner) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    return joiner->m_suffix;
}

// Size

int32_t jtk_StringJoiner_getSize(jtk_StringJoiner_t* joiner) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    int32_t size = 0;

    if (joiner->m_prefix != NULL) {
        size += jtk_String_getSize(joiner->m_prefix);
    }

    if (joiner->m_numberOfElements == 0) {
        if (joiner->m_emptyValue != NULL) {
            size += jtk_String_getSize(joiner->m_emptyValue);
        }
    }
    else {
        size += jtk_StringBuilder_getSize(joiner->m_value);
    }

    if (joiner->m_suffix != NULL) {
        size += jtk_String_getSize(joiner->m_suffix);
    }
}

int32_t jtk_StringJoiner_getContentSize(jtk_StringJoiner_t* joiner) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    int32_t delimitedSize = jtk_StringBuilder_getSize(joiner->m_value);
    int32_t delimiterSize = jtk_String_getSize(joiner->m_delimiter);
    return delimitedSize - (delimiterSize * (joiner->m_numberOfElements - 1));
}

// Number of Elements

int32_t jtk_StringJoiner_getNumberOfElements(jtk_StringJoiner_t* joiner) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    return joiner->m_numberOfElements;
}

// String

jtk_String_t* jtk_StringJoiner_toString(jtk_StringJoiner_t* joiner) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    return jtk_StringBuilder_toStringWithEdges(joiner->m_value, joiner->m_suffix,
        joiner->m_prefix);
}

// Number of Elements

int32_t jtk_StringJoiner_getNumberOfElements(jtk_StringJoiner_t* joiner) {
    jtk_Assert_assertObject(joiner, "The specified string joiner is null.");

    return joiner->m_numberOfElements;
}