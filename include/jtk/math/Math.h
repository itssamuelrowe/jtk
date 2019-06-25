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

#ifndef JTK_CORE_MATH_H
#define JTK_CORE_MATH_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * Math                                                                        *
 *******************************************************************************/

/**
 * @class Math
 * @ingroup jtk_math
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */

/* Palindrome */

/**
 * @memberof Math
 * @since JTK 1.1
 */
bool jtk_Math_isPalindrome_i(int32_t number);

/**
 * @memberof Math
 * @since JTK 1.1
 */
bool jtk_Math_isPalindrome_l(int64_t number);
 
/* Prime */

/**
 * @memberof Math
 * @since JTK 1.1
 */
bool jtk_Math_isPrime_i(int32_t number);

/**
 * @memberof Math
 * @since JTK 1.1
 */
bool jtk_Math_isPrime_l(int64_t number);

/**
 * @memberof Math
 * @since JTK 1.1
 */
bool jtk_Math_isPrimeFast_i(int32_t number);

/**
 * @memberof Math
 * @since JTK 1.1
 */
bool jtk_Math_isPrimeFast_l(int64_t number);

/* Power of Two */

/**
 * @memberof Math
 */
int32_t jtk_Math_findPowerOfTwo(int32_t n);

#endif /* JTK_CORE_MATH_H */