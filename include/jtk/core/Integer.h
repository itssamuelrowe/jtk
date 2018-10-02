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

// Monday, February 26, 2018

#ifndef JTK_CORE_INTEGER_H
#define JTK_CORE_INTEGER_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * Integer                                                                     *
 *******************************************************************************/

/**
 * @class Integer
 * @ingroup jtk_core
 * @author Samuel Rowe
 * @since JTK 1.0
 */

/* Capacity */

/**
 * The JTK_INTEGER_MAX_VALUE constant represents the maximum value the `int32_t`
 * type can hold.
 *
 * @memberof Integer
 */
#define JTK_INTEGER_MAX_VALUE 0x7FFFFFFF

/**
 * The JTK_INTEGER_MIN_VALUE constant represents the minimum value the `int32_t`
 * type can hold.
 *
 * @memberof Integer
 */
#define JTK_INTEGER_MIN_VALUE 0x80000000

/**
 * The JTK_INTEGER_UNSIGNED_MAX_VALUE constant represents the maximum value the
 * `uint32_t` type can hold.
 *
 * @memberof Integer
 */
#define JTK_UNSIGNED_INTEGER_MAX_VALUE 0xFFFFFFFFU

/**
 * The JTK_INTEGER_UNSIGNED_MIN_VALUE constant represents the minimum value the
 * `uint32_t` type can hold.
 *
 * @memberof Integer
 */
#define JTK_UNSIGNED_INTEGER_MIN_VALUE 0

/* Size */

/**
 * The JTK_INTEGER_SIZE_IN_BITS constant represents the number of bits used to
 * represent an `int32_t` value.
 *
 * @memberof Integer
 */
#define JTK_INTEGER_SIZE_IN_BITS 32

/**
 * The JTK_INTEGER_SIZE_IN_BYTES constant represents the number of bytes used to
 * represent an `int32_t` value.
 *
 * @memberof Integer
 */
#define SIZE_IN_BYTES 4

/* Radix */

/**
 * @memberof Integer
 */
#define JTK_INTEGER_MIN_RADIX 2

/**
 * @memberof Integer
 */
#define JTK_INTEGER_MAX_RADIX 36

/* Maximum */

/**
 * The max() function returns the largest number in the specified integers.
 * If the specified integers are equal, the first integer argument is returned.
 *
 * @param  value1
 *         This argument specifies the first integer value.
 * @param  value2
 *         This argument specifies the second integer value.
 * @return The largest number in the specified integers.
 * @memberof Integer
 */
int32_t jtk_Integer_max(int32_t value1, int32_t value2);

/* Minimum */

/**
 * The min() function returns the smallest number in the specified
 * integers. If the specified integers are equal, the first integer
 * is returned.
 *
 * @param  value1
 *         This argument specifies the first integer value.
 * @param  value2
 *         This argument specifies the second integer value.
 * @return The smallest number in the specified integers.
 * @memberof Integer
 */
int32_t jtk_Integer_min(int32_t value1, int32_t value2);

/* Numeric Comparison */

/**
 * The compare() function compares the specified integer values,
 * numerically. It returns a negative integer, zero, or a positive integer
 * if the first integer value is less than, equal to, or greater than the
 * second integer value, respectively.
 *
 * @param  value1
 *         This argument specifies the first integer value.
 * @param  value2
 *         This argument specifies the second integer value.
 * @return A negative integer, zero, or a positive integer if the first
 *         integer value is less than, equal to, or greater than the
 *         second integer value, respectively.
 * @memberof Integer
 */
int32_t jtk_Integer_compare(int32_t value1, int32_t value2);

/**
 * The compareUnsigned() function compares the specified unsigned
 * integer values,numerically. It returns a negative integer, zero, or
 * a positive integer if the first unsigned integer value is less than,
 * equal to, or greater than the second unsigned integer value,
 * respectively.
 *
 * @param  value1
 *         This argument specifies the first unsigned integer value.
 * @param  value2
 *         This argument specifies the second unsigned integer value.
 * @return A negative integer, zero, or a positive integer if the first
 *         unsigned integer value is less than, equal to, or greater
 *         than the second unsigned integer value, respectively.
 * @memberof Integer
 */
int32_t jtk_Integer_compareUnsigned(uint32_t value1, uint32_t value2);

/* Parse */

/**
 * The parse() function returns the specified string as a signed integer
 * value in the specified radix.
 *
 * @param  string
 *         This argument specifies the string to parse.
 * @param  radix
 *         This argument specifies the radix.
 * @return The integer representation of the specified string in the
 *         specified radix. THe negative integer `-1` is returned if one
 *         of the following is true:
 *         <ul>
 *         <li>The specified string is empty.</li>
 *         <li>A character of the string is not a digit of the specified
 *             radix, except the first character which may be a minus
 *             sign `'-'` or plus sign `'+'`, provided that
 *             the string contains more than one character.
 *         </ul>
 * @memberof Integer
 */
int32_t jtk_Integer_parse(const uint8_t* text, int32_t radix);

/*
 * The parse() function returns the specified string as a signed integer
 * value in the specified radix.
 *
 * @param  string
 *         This argument specifies the string to parse.
 * @param  radix
 *         This argument specifies the radix.
 * @param  valid
 *         A boolean pointer which is set to `true` if the string
 *         was parsed successfully; `false` otherwise.
 * @param  defaultValue
 *         The value which is returned if the string is invalid.
 * @return The integer representation of the specified string in the
 *         specified radix. The specified default value is returned if one
 *         of the following is true:
 *         <ul>
 *         <li>The specified string is empty.</li>
 *         <li>A character of the string is not a digit of the default
 *             radix 10, except the first character which may be a minus
 *             sign `'-'` or plus sign `'+'`, provided that
 *             the string contains more than one character.
 *         </ul>
 */
// int32_t jtk_Integer_parseEx(const uint8_t* text, int32_t radix, bool* valid, int32_t defaultValue);

#endif /* JTK_CORE_INTEGER_H */
