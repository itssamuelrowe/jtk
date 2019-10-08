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

// Wednesday, August 29, 2018

#include <jtk/core/Long.h>
#include <jtk/core/Integer.h>

/*******************************************************************************
 * Long                                                                        *
 *******************************************************************************/

/* Parse */

int64_t jtk_Long_parse(const uint8_t* text, int32_t radix) {
    jtk_Assert_assertObject(text, "The specified text is null.");

    int32_t length = jtk_CString_getSize(text);
    return jtk_Long_parseEx(text, length, radix);
}

int64_t jtk_Long_parseEx(const uint8_t* text, int32_t length, int32_t radix) {
    jtk_Assert_assertObject(text, "The specified text is null.");

    int64_t result = -1;
    if ((length != 0) && (radix >= JTK_INTEGER_MIN_RADIX) &&
        (radix <= JTK_INTEGER_MAX_RADIX)) {
        bool negative = false;
        int32_t i = 0;
        int64_t limit = -JTK_LONG_MAX_VALUE;
        uint8_t first = text[0];
        result = 0;
        if (!((first >= '0') && (first <= '9'))) {
            if (first == '+') {
                negative = false;
            }
            else if (first == '-') {
                negative = true;
                limit = JTK_LONG_MIN_VALUE;
            }
            else {
                result = -1;
            }

            if (length == 1) {
                result = -1;
            }

            i++;
        }

        if (result != -1) {
            int64_t m = limit / radix;
            while (i < length) {
                uint8_t value = text[i++];
                int32_t digit = jtk_Integer_digit(value, radix);
                if ((digit < 0) || (result < m)) {
                    result = -1;
                    break;
                }
                result *= radix;
                if (result < (limit + digit)) {
                    result = -1;
                    break;
                }
                result -= digit;
            }
            if (result != -1) {
                result = negative? result : -result;
            }
        }
    }
    return result;
}

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
