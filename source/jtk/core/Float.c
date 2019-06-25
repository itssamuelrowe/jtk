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

// Saturday, June 30, 2018

#include <jtk/core/Float.h>

/*******************************************************************************
 * Float                                                                       *
 *******************************************************************************/

/* Bit Mask */

const int32_t JTK_FLOAT_EXPONENT_BIT_MASK = 0x7F800000;

const int32_t JTK_FLOAT_SIGN_BIT_MASK = 0x80000000;

const int32_t JTK_FLOAT_SIGNIFICAND_BIT_MASK = 0x007FFFFF;

/* Exponent */

const int32_t JTK_FLOAT_MAX_EXPONENT = 127;

const int32_t JTK_FLOAT_MIN_EXPONENT = -126;

/* Exponent Bias */

const int32_t JTK_FLOAT_EXPONENT_BIAS = 127;

/* Infinity */

const float JTK_FLOAT_NEGATIVE_INFINITY = -1.0f / 0.0f;

const float JTK_FLOAT_POSITIVE_INFINITY = 1.0f / 0.0f;

const int32_t JTK_FLOAT_NEGATIVE_INFINITY_BIT_PATTERN = 0xFF800000;

const int32_t JTK_FLOAT_POSITIVE_INFINITY_BIT_PATTERN = 0x7F800000;

/* Not-a-Number (NaN) */

const float JTK_FLOAT_NAN = 0.0f / 0.0f;

const int32_t JTK_FLOAT_NAN_BIT_PATTERN = 0x7FC00000;

/* Size */

const int32_t JTK_FLOAT_SIZE_IN_BITS = 32;

const int32_t JTK_FLOAT_SIZE_IN_BYTES = 4;

/* Width */

const int32_t JTK_FLOAT_EXPONENT_WIDTH = 8;

const int32_t JTK_FLOAT_SIGN_WIDTH = 1;

const int32_t JTK_FLOAT_SIGNIFICAND_WIDTH = 23;

/* Equals */

bool jtk_Float_equals(float value1, float value2) {
    int32_t pattern0 = jtk_Float_unpack(value1);
    int32_t pattern1 = jtk_Float_unpack(value2);
    return pattern0 == pattern1;
}

/* Exponent */

int32_t jtk_Float_getExponent(float value) {
    int32_t bits = jtk_Float_unpack(value);
    int32_t biased = ((bits & JTK_FLOAT_EXPONENT_BIT_MASK) >> JTK_FLOAT_SIGNIFICAND_WIDTH);
    return biased - JTK_FLOAT_EXPONENT_BIAS;
}

int32_t jtk_Float_getRawExponent(float value) {
    int32_t bits = jtk_Float_unpack(value);
    return (bits & JTK_FLOAT_EXPONENT_BIT_MASK) >> JTK_FLOAT_SIGNIFICAND_WIDTH;
}

/* Hash Code */

int32_t jtk_Float_hash(float value) {
    return jtk_Float_unpack(value);
}

/* NaN */

bool jtk_Float_isNaN(float value) {
    return value != value;
}

/* Numeric Comparison */

int32_t jtk_Float_compare(float value1, float value2) {
    if (!jtk_Float_isUnordered(value1, value2)) {
        if (value1 < value2) {
            return -1;
        }
        if (value1 > value2) {
            return 1;
        }
    }
    int32_t pattern0 = jtk_Float_unpack(value1);
    int32_t pattern1 = jtk_Float_unpack(value2);
    return (pattern0 == pattern1)? 0 : ((pattern0 < pattern1)? -1 : 1);
}

/* Pack */

float jtk_Float_pack(int32_t value) {
    /* A float value can be packed with the following algorithm, too. */
    /*
    union {
        int32_t asInteger;
        float asDecimal;
    } bitPattern;
    bitPattern.asInteger = value;
    return bitPattern.asDecimal;
    */
    
    return *((float*)(&value));
}

/* Power Of Two */

float jtk_Float_powerOfTwo(int32_t n) {
    jtk_Assert_assertFalse((n < JTK_FLOAT_MIN_EXPONENT) || (n > JTK_FLOAT_MAX_EXPONENT), "The specified power is invalid (limited to -126..127).");
    int32_t bits = ((n + JTK_FLOAT_EXPONENT_BIAS) << JTK_FLOAT_SIGNIFICAND_WIDTH) & JTK_FLOAT_EXPONENT_BIT_MASK;
    return jtk_Float_pack(bits);
}

/* Raw Unpack */

int32_t jtk_Float_rawUnpack(float value) {
    /* A float value can be unpacked with the following algorithm, too. */
    /*
    union {
        int32_t asInteger;
        int32_t asDecimal;
    } bitPattern;
    bitPattern.asDecimal = value;
    return bitPattern.asInteger;
    */
    
    return *((int32_t*)(&value));
}

/* Unordered */

bool jtk_Float_isUnordered(float value1, float value2) {
    return jtk_Float_isNaN(value1) || jtk_Float_isNaN(value2);
}

/* Unpack */

int32_t jtk_Float_unpack(float value) {
    /* A float value can be unpacked with the following algorithm, too. */
    /*
    union {
        int32_t asInteger;
        float asDecimal;
    } bitPattern;
    bitPattern.asDecimal = value;
    int32_t result = bitPattern.asInteger;
    */
    
    int32_t result = *((int32_t*)(&value));

    /* Collapse all the bit patterns encoding a NaN to a float "canonical"
     * Nan value.
     */
    if (((result & JTK_FLOAT_EXPONENT_BIT_MASK) == JTK_FLOAT_EXPONENT_BIT_MASK) &&
       ((result & JTK_FLOAT_SIGNIFICAND_BIT_MASK) != 0)) {
        result = JTK_FLOAT_NAN_BIT_PATTERN;
    }

    return result;
}

/* Verify Masks */

void jtk_Float_verifyMasks() {
    jtk_Assert_assertTrue(
        ((0x80000000 | 0x7F800000 | 0x007FFFFF) == ~0UL) &&
        ((0x80000000 & 0x7F800000) == 0) &&
        ((0x80000000 & 0x007FFFFF) == 0) &&
        ((0x7F800000 & 0x007FFFFF) == 0),
        "Verification of bit masks for IEEE 754 \"single format\" failed."
    );
}