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

// Wednesday, August 29, 2018

#ifndef JTK_CORE_LONG_H
#define JTK_CORE_LONG_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * Long                                                                        *
 *******************************************************************************/

/**
 * @class Long
 * @ingroup jtk_core
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */

/* Capacity */

/**
 * The JTK_LONG_MAX_VALUE constant represents the maximum value the `int32_t`
 * type can hold.
 *
 * @memberof Integer
 */
#define JTK_LONG_MAX_VALUE 0x7FFFFFFFFFFFFFFFLL

/**
 * The JTK_LONG_MIN_VALUE constant represents the minimum value the `int64_t`
 * type can hold.
 *
 * @memberof Integer
 */
#define JTK_LONG_MIN_VALUE 0x8000000000000000LL

/**
 * The JTK_LONG_UNSIGNED_MAX_VALUE constant represents the maximum value the
 * `uint64_t` type can hold.
 *
 * @memberof Integer
 */
#define JTK_UNSIGNED_LONG_MAX_VALUE 0xFFFFFFFFFFFFFFFFULL

/**
 * The JTK_LONG_UNSIGNED_MIN_VALUE constant represents the minimum value the
 * `uint64_t` type can hold.
 *
 * @memberof Integer
 */
#define JTK_UNSIGNED_LONG_MIN_VALUE 0ULL

/* Size */

/**
 * The JTK_LONG_SIZE_IN_BITS constant represents the number of bits used to
 * represent an `int64_t` value.
 *
 * @memberof Integer
 */
#define JTK_LONG_SIZE_IN_BITS 64

/**
 * The JTK_LONG_SIZE_IN_BYTES constant represents the number of bytes used to
 * represent an `int64_t` value.
 *
 * @memberof Integer
 */
#define JTK_LONG_SIZE_IN_BYTES 8

/* Radix */

/**
 * @memberof Integer
 */
#define JTK_LONG_MIN_RADIX 2

/**
 * @memberof Integer
 */
#define JTK_LONG_MAX_RADIX 36

/**
 * @memberof Integer
 */
#define JTK_LONG_MAX_BINARY_STRING_SIZE 64

/**
 * @memberof Integer
 */
#define JTK_LONG_MAX_OCTAL_STRING_SIZE 64

/**
 * @memberof Integer
 */
#define JTK_LONG_MAX_DECIMAL_STRING_SIZE 64

/**
 * @memberof Integer
 */
#define JTK_LONG_MAX_HEXADECIMAL_STRING_SIZE 64

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
int64_t jtk_Long_parse(const uint8_t* text, int32_t radix);

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
int64_t jtk_Long_parseEx(const uint8_t* text, int32_t size, int32_t radix);

/* Reverse */

/**
 * @memberof Long
 */
int64_t jtk_Long_reverse(int64_t number);


#endif /* JTK_CORE_LONG_H */