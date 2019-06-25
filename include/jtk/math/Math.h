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