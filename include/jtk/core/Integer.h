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
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
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
#define JTK_INTEGER_SIZE_IN_BYTES 4

/* Radix */

/**
 * @memberof Integer
 */
#define JTK_INTEGER_MIN_RADIX 2

/**
 * @memberof Integer
 */
#define JTK_INTEGER_MAX_RADIX 36

/**
 * @memberof Integer
 */
#define JTK_INTEGER_MAX_BINARY_STRING_SIZE 32

/**
 * @memberof Integer
 */
#define JTK_INTEGER_MAX_OCTAL_STRING_SIZE 32

/**
 * @memberof Integer
 */
#define JTK_INTEGER_MAX_DECIMAL_STRING_SIZE 32

/**
 * @memberof Integer
 */
#define JTK_INTEGER_MAX_HEXADECIMAL_STRING_SIZE 32


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

int32_t jtk_Integer_digit(uint8_t character, int32_t radix);

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

/**
 * The parse() function returns the specified string as a signed integer
 * value in the specified radix.
 *
 * @param  string
 *         This argument specifies the string to parse.
 * @param  size
 *         This argument specifies the size of the input string.
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
int32_t jtk_Integer_parseEx(const uint8_t* text, int32_t size, int32_t radix);

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

/* Reverse */

/**
 * @memberof Integer
 * @since JTK 1.1
 */
int32_t jtk_Integer_reverse(int32_t number);

/* String */

uint8_t* jtk_Integer_toStringEx(int32_t value, int32_t radix);
uint8_t* jtk_Integer_toString(int32_t value);
int32_t jtk_Integer_getString(int32_t value, uint8_t* buffer, int32_t size);
int32_t jtk_Integer_getStringEx(int32_t value, int32_t radix, uint8_t* destination,
    int32_t destinationSize, int32_t destinationIndex);

#endif /* JTK_CORE_INTEGER_H */
