/*
 *                              Jez Toolkit (JTK)
 *     Copyright (C) 2018 OneCube Software Solutions. All rights reserved.
 *
 * This file is part of Jez Toolkit Free Edition, version 1.0.
 *
 * See the file "LICENSE" included in the distribution for the terms and conditions,
 * or visit http://www.onecube.in/jtk/free-license.
 *
 * IMPORTANT NOTE: You may NOT copy the content of this file, either partially
 * or fully, into your source code.
 */

// Saturday, June 30, 2018

#include <jtk/core/Double.h>

/*******************************************************************************
 * Double                                                                      *
 *******************************************************************************/

/* Bit Mask */

const int64_t JTK_DOUBLE_EXPONENT_BIT_MASK = 0x7FF0000000000000LL;

const int64_t JTK_DOUBLE_SIGN_BIT_MASK = 0x8000000000000000LL;

const int64_t JTK_DOUBLE_SIGNIFICAND_BIT_MASK = 0x000FFFFFFFFFFFFFLL;

/* Exponent */

const int32_t JTK_DOUBLE_MAX_EXPONENT = 1023;

const int32_t JTK_DOUBLE_MIN_EXPONENT = -1022;

// Exponent Bias

const int32_t JTK_DOUBLE_EXPONENT_BIAS = 1023;

/* Infinity */

const double JTK_DOUBLE_NEGATIVE_INFINITY = -1.0 / 0.0;

const double JTK_DOUBLE_POSITIVE_INFINITY = 1.0 / 0.0;

/* Infinity Bit Pattern */

const int64_t JTK_DOUBLE_NEGATIVE_INFINITY_BIT_PATTERN = 0xFFF0000000000000LL;

const int64_t JTK_DOUBLE_POSITIVE_INFINITY_BIT_PATTERN = 0x7FF0000000000000LL;

/* Not-a-Number (NaN) */

const double JTK_DOUBLE_NAN = 0.0 / 0.0;

/* Not-a-Number (NaN) Bit Pattern */

const int64_t JTK_DOUBLE_NAN_BIT_PATTERN = 0x7FF8000000000000LL;

/* Size */

const int32_t JTK_DOUBLE_SIZE_IN_BITS = 64;

const int32_t JTK_DOUBLE_SIZE_IN_BYTES = 8;

/* Width */

const int32_t JTK_DOUBLE_EXPONENT_WIDTH = 11;

const int32_t JTK_DOUBLE_SIGN_WIDTH = 1;

const int32_t JTK_DOUBLE_SIGNIFICAND_WIDTH = 52;

/* Equality */

bool jtk_Double_equals(double value1, double value2) {
    int64_t pattern0 = jtk_Double_unpack(value1);
    int64_t pattern1 = jtk_Double_unpack(value2);
    return pattern0 == pattern1;
}

/* Exponent */

int32_t jtk_Double_getExponent(double value) {
    int64_t bits = jtk_Double_unpack(value);
    int32_t biased = ((bits & JTK_DOUBLE_EXPONENT_BIT_MASK) >> JTK_DOUBLE_SIGNIFICAND_WIDTH);
    return biased - JTK_DOUBLE_EXPONENT_BIAS;
}

int32_t jtk_Double_getRawExponent(double value) {
    int64_t bits = jtk_Double_unpack(value);
    return (bits & JTK_DOUBLE_EXPONENT_BIT_MASK) >> JTK_DOUBLE_SIGNIFICAND_WIDTH;
}

/* Hash Code */

int32_t jtk_Double_hash(double value) {
    int32_t pattern = jtk_Double_unpack(value);
    return (int32_t)(pattern ^ ((uint64_t)pattern >> 32));
}

/* NaN */

bool jtk_Double_isNaN(double value) {
    return value != value;
}

/* Numeric Comparison */

int32_t jtk_Double_compare(double value1, double value2) {
    if (!jtk_Double_isUnordered(value1, value2)) {
        if (value1 < value2) {
            return -1;
        }
        if (value1 > value2) {
            return 1;
        }
    }
    int64_t pattern0 = jtk_Double_unpack(value1);
    int64_t pattern1 = jtk_Double_unpack(value2);
    return (pattern0 == pattern1)? 0 : ((pattern0 < pattern1)? -1 : 1);
}

/* Pack */

double jtk_Double_pack(int64_t value) {
    union {
        int64_t asInteger;
        double asDecimal;
    } bitPattern;
    bitPattern.asInteger = value;
    return bitPattern.asDecimal;
}

/* Power of Two */

double jtk_Double_powerOfTwo(int32_t n) {
    jtk_Assert_assertFalse((n < JTK_DOUBLE_MIN_EXPONENT) || (n > JTK_DOUBLE_MAX_EXPONENT),
        "The specified power is invalid (limited to -126..127).");
    
    int64_t bits = ((int64_t)(n + JTK_DOUBLE_EXPONENT_BIAS) << JTK_DOUBLE_SIGNIFICAND_WIDTH) &
        JTK_DOUBLE_EXPONENT_BIT_MASK;
    return jtk_Double_pack(bits);
}

/* Raw Unpack */

int64_t jtk_Double_rawUnpack(double value) {
    union {
        int64_t asInteger;
        double asDecimal;
    } bitPattern;
    bitPattern.asDecimal = value;
    return bitPattern.asInteger;
}

/* Unordered */

bool jtk_Double_isUnordered(double value1, double value2) {
    return jtk_Double_isNaN(value1) || jtk_Double_isNaN(value2);
}

/* Unpack */

int64_t jtk_Double_unpack(double value) {
    union {
        int64_t asInteger;
        double asDecimal;
    } bitPattern;
    bitPattern.asDecimal = value;
    int64_t result = bitPattern.asInteger;
    /* Collapse all the bit patterns encoding a NaN to a float "canonical"
     * Nan value.
     */
    if (((result & JTK_DOUBLE_EXPONENT_BIT_MASK) == JTK_DOUBLE_EXPONENT_BIT_MASK) &&
       ((result & JTK_DOUBLE_SIGNIFICAND_BIT_MASK) != 0)) {
        result = JTK_DOUBLE_NAN_BIT_PATTERN;
    }
    return result;
}

/* Verify Masks */

/**
 * Verify bit masks provided by the Double class.
 */
void jtk_Double_verifyMasks() {
    jtk_Assert_assertTrue(
        ((0x8000000000000000LL | 0x7FF0000000000000LL | 0x000FFFFFFFFFFFFFLL) == ~0ULL) &&
        ((0x8000000000000000LL & 0x7FF0000000000000LL) == 0ULL) &&
        ((0x8000000000000000LL & 0x000FFFFFFFFFFFFFLL) == 0ULL) &&
        ((0x7FF0000000000000LL & 0x000FFFFFFFFFFFFFLL) == 0ULL),
        "Verification of bit masks for IEEE 754 \"double format\" failed."
    );
}