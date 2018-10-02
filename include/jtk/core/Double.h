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

#ifndef JTK_CORE_DOUBLE_H
#define JTK_CORE_DOUBLE_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * Double                                                                      *
 *******************************************************************************/

/**
 * @class Double
 * @ingroup jtk_core
 * @author Samuel Rowe
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