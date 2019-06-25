// Monday, July 23, 2018

#include <jtk/core/Integer.h>
#include <jtk/core/Long.h>
#include <jtk/math/Math.h>

#include <math.h>

/*******************************************************************************
 * Math                                                                        *
 *******************************************************************************/

/* Palindrome */
/*
bool jtk_Math_isPalindrome_i(int32_t number) {
	return jtk_Integer_reverse(number) == number;
}

bool jtk_Math_isPalindrome_l(int64_t number) {
	return jtk_Long_reverse(number) == number;
}

/* Power of Two */

int32_t jtk_Math_findPowerOfTwo(int32_t n) {
	int32_t r = 1;
	while (r < n) {
		r <<= 1;
	}
	return r;
}

/* Prime */

bool jtk_Math_isPrime_i(int32_t number) {
	bool result = false;
	if (number > 0) {
		result = true;
		
		int32_t limit = number / 2;
		int32_t i;
		for (i = 2; i <= limit; i++) {
			if ((number % i) == 0) {
				result = false;
				break;
			}
		}
	}
	return result;
}

bool jtk_Math_isPrime_l(int64_t number) {
	bool result = false;
	if (number > 0) {
		result = true;
		
		int64_t limit = number / 2;
		int64_t i;
		for (i = 2; i <= limit; i++) {
			if ((number % i) == 0) {
				printf("Divisible by %d\n", i);
				result = false;
				break;
			}
		}
	}
	return result;
}
/*
bool jtk_Math_isPrimeFast_i(int32_t number) {
    bool result = true;
    if (((number > 2) && ((number % 2) == 0)) || (number == 1)){
        result = false;
    }
    else {
        int32_t limit = (int32_t)jtk_Math_squareRoot(number);
        int32_t i;
        for (i = 3; i <= limit; i += 2) {
            if((number % i) == 0) {
                result = false;
                break;
            }
        }
    }
    return result;
}

bool jtk_Math_isPrimeFast_l(int64_t number) {
    bool result = true;
    if (((number > 2) && ((number % 2) == 0)) || (number == 1)){
        result = false;
    }
    else {
        int64_t limit = (int64_t)jtk_Math_squareRoot(number);
        int64_t i;
        for (i = 3; i <= limit; i += 2) {
            if ((number % i) == 0) {
                result = false;
                break;
            }
        }
    }
    return result;
}
*/

// Modulus

float jtk_Math_modulo_f(float a, float b) {
    return 0; // fmodf(a, b);
}

double jtk_Math_modulo_d(float a, float b) {
    return 0; // fmod(a, b);
}