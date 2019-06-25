// Wednesday, August 29, 2018

#include <jtk/core/Long.h>

/*******************************************************************************
 * Long                                                                        *
 *******************************************************************************/

/* Reverse */
 
int32_t jtk_Long_reverse(int64_t number) {
    bool negative = number < 0;
    int64_t copy = negative? -number : number;
	int64_t reverse = 0;
	while (copy != 0) {
		int32_t digit = copy % 10;
		reverse = (reverse * 10) + digit;
		copy /= 10;
	}
	return negative? -reverse : reverse;
}
