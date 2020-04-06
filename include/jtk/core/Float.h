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

// Monday, February 26, 2018

#ifndef JTK_CORE_DECIMAL_H
#define JTK_CORE_DECIMAL_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * Float                                                                       *
 *******************************************************************************/

/**
 * @class Float
 * @ingroup jtk_core
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */

/* Bit Mask */

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_EXPONENT_BIT_MASK;

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_SIGN_BIT_MASK;

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_SIGNIFICAND_BIT_MASK;

/* Exponent */

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_MAX_EXPONENT;

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_MIN_EXPONENT;

/* Exponent Bias */

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_EXPONENT_BIAS;

/* Infinity */

/**
 * @memberof Float
 */
extern const float JTK_FLOAT_NEGATIVE_INFINITY;

/**
 * @memberof Float
 */
extern const float JTK_FLOAT_POSITIVE_INFINITY;

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_NEGATIVE_INFINITY_BIT_PATTERN;

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_POSITIVE_INFINITY_BIT_PATTERN;

/* Not-a-Number (NaN) */

/**
 * @memberof Float
 */
extern const float JTK_FLOAT_NAN;

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_NAN_BIT_PATTERN;

/* Size */

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_SIZE_IN_BITS;

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_SIZE_IN_BYTES;

/* Width */

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_EXPONENT_WIDTH;

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_SIGN_WIDTH;

/**
 * @memberof Float
 */
extern const int32_t JTK_FLOAT_SIGNIFICAND_WIDTH;

/* Equals */

/**
 * @memberof Float
 */
bool jtk_Float_equals(float value1, float value2);

/* Exponent */

/**
 * @memberof Float
 */
int32_t jtk_Float_getExponent(float value);

/**
 * @memberof Float
 */
int32_t jtk_Float_getRawExponent(float value);

/* Hash Code */

/**
 * @memberof Float
 */
int32_t jtk_Float_hash(float value);

/* NaN */

/**
 * @memberof Float
 */
bool jtk_Float_isNaN(float value);

/* Numeric Comparison */

/**
 * @memberof Float
 */
int32_t jtk_Float_compare(float value1, float value2);

/* Pack */

/**
 * @memberof Float
 */
float jtk_Float_pack(int32_t value);

/* Power Of Two */

/**
 * @memberof Float
 */
float jtk_Float_powerOfTwo(int32_t n);

/* Raw Unpack */

/**
 * @memberof Float
 */
int32_t jtk_Float_rawUnpack(float value);

/* Unordered */

/**
 * @memberof Float
 */
bool jtk_Float_isUnordered(float value1, float value2);

/* Unpack */

/**
 * @memberof Float
 */
int32_t jtk_Float_unpack(float value);

/* Verify Masks */

/**
 * Verify bit masks provided by the Float class.
 *
 * @memberof Float
 */
void jtk_Float_verifyMasks();

#endif /* JTK_CORE_DECIMAL_H */