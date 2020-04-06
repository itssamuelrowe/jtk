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

// Saturday, June 30, 2018

#ifndef JTK_CORE_DOUBLE_H
#define JTK_CORE_DOUBLE_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * Double                                                                      *
 *******************************************************************************/

/**
 * @class Double
 * @ingroup jtk_core
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */

/* Bit Mask */

/**
 * @memberof Double
 */
extern const int64_t JTK_DOUBLE_EXPONENT_BIT_MASK;

/**
 * @memberof Double
 */
extern const int64_t JTK_DOUBLE_SIGN_BIT_MASK;

/**
 * @memberof Double
 */
extern const int64_t JTK_DOUBLE_SIGNIFICAND_BIT_MASK;

/* Exponent */

/**
 * @memberof Double
 */
extern const int32_t JTK_DOUBLE_MAX_EXPONENT;

/**
 * @memberof Double
 */
extern const int32_t JTK_DOUBLE_MIN_EXPONENT;

// Exponent Bias

/**
 * @memberof Double
 */
extern const int32_t JTK_DOUBLE_EXPONENT_BIAS;

/* Infinity */

/**
 * @memberof Double
 */
extern const double JTK_DOUBLE_NEGATIVE_INFINITY;

/**
 * @memberof Double
 */
extern const double JTK_DOUBLE_POSITIVE_INFINITY;

/* Infinity Bit Pattern */

/**
 * @memberof Double
 */
extern const int64_t JTK_DOUBLE_NEGATIVE_INFINITY_BIT_PATTERN;

/**
 * @memberof Double
 */
extern const int64_t JTK_DOUBLE_POSITIVE_INFINITY_BIT_PATTERN;

/* Not-a-Number (NaN) */

/**
 * @memberof Double
 */
extern const double JTK_DOUBLE_NAN;

/* Not-a-Number (NaN) Bit Pattern */

/**
 * @memberof Double
 */
extern const int64_t JTK_DOUBLE_NAN_BIT_PATTERN;

/* Size */

/**
 * @memberof Double
 */
extern const int32_t JTK_DOUBLE_SIZE_IN_BITS;

/**
 * @memberof Double
 */
extern const int32_t JTK_DOUBLE_SIZE_IN_BYTES;

/* Width */

/**
 * @memberof Double
 */
extern const int32_t JTK_DOUBLE_EXPONENT_WIDTH;

/**
 * @memberof Double
 */
extern const int32_t JTK_DOUBLE_SIGN_WIDTH;

/**
 * @memberof Double
 */
extern const int32_t JTK_DOUBLE_SIGNIFICAND_WIDTH;

/* Equality */

/**
 * @memberof Double
 */
bool jtk_Double_equals(double value1, double value2);

/* Exponent */

/**
 * @memberof Double
 */
int32_t jtk_Double_getExponent(double value);

/**
 * @memberof Double
 */
int32_t jtk_Double_getRawExponent(double value);

/* Hash Code */

/**
 * @memberof Double
 */
int32_t jtk_Double_hash(double value);

/* NaN */

/**
 * @memberof Double
 */
bool jtk_Double_isNaN(double value);

/* Numeric Comparison */

/**
 * @memberof Double
 */
int32_t jtk_Double_compare(double value1, double value2);

/* Pack */

/**
 * @memberof Double
 */
double jtk_Double_pack(int64_t value);

/* Power of Two */

/**
 * @memberof Double
 */
double jtk_Double_powerOfTwo(int32_t n);

/* Raw Unpack */

/**
 * @memberof Double
 */
int64_t jtk_Double_rawUnpack(double value);

/* Unordered */

/**
 * @memberof Double
 */
bool jtk_Double_isUnordered(double value1, double value2);

/* Unpack */

/**
 * @memberof Double
 */
int64_t jtk_Double_unpack(double value);

/* Verify Masks */

/**
 * Verify bit masks provided by the Double class.
 *
 * @memberof Double
 */
void jtk_Double_verifyMasks();

#endif /* JTK_CORE_DOUBLE_H */