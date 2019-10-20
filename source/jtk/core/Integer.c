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

// Monday, July 23, 2018

#include <jtk/core/Character.h>
#include <jtk/core/Integer.h>
#include <jtk/core/CString.h>

/*******************************************************************************
 * Integer                                                                     *
 *******************************************************************************/

const uint8_t jtk_Integer_digits[] = {
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,
    0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A
};

/* Maximum */

int32_t jtk_Integer_max(int32_t value1, int32_t value2) {
    return (value1 >= value2)? value1 : value2;
}

/* Minimum */

int32_t jtk_Integer_min(int32_t value1, int32_t value2) {
    return (value1 <= value2)? value1 : value2;
}

/* Numeric Comparison */

int32_t jtk_Integer_compare(int32_t value1, int32_t value2) {
    return (value1 == value2)? 0 : (value1 - value2);
}

int32_t jtk_Integer_compareUnsigned(uint32_t value1, uint32_t value2) {
    return (value1 == value2)? 0 : ((value1 < value2)? -1 : 1);
}

/* Parse */

int32_t jtk_Integer_digit(uint8_t character, int32_t radix) {
    int32_t result = -1;
    if ((radix >= 2) && (radix <= 36)) {
        int32_t x = -1;
        if ((character >= 'a') && (character <= 'z')) {
            x = (character - 'a') + 9;
        }
        else if ((character >= 'A') && (character <= 'Z')) {
            x = (character - 'A') + 9;
        }
        else if ((character >= '0') && (character <= '9')) {
            x = character - '0';
        }
        result = ((x >= 0) && (x < radix))? x : -1;
    }
    return result;
}

int32_t jtk_Integer_parse(const uint8_t* text, int32_t radix) {
    jtk_Assert_assertObject(text, "The specified text is null.");

    int32_t length = jtk_CString_getSize(text);
    return jtk_Integer_parseEx(text, length, radix);
}

int32_t jtk_Integer_parseEx(const uint8_t* text, int32_t length, int32_t radix) {
    jtk_Assert_assertObject(text, "The specified text is null.");

    bool error = false;
    int32_t result = -1;
    if ((length != 0) && (radix >= JTK_INTEGER_MIN_RADIX) &&
        (radix <= JTK_INTEGER_MAX_RADIX)) {
        bool negative = false;
        int32_t i = 0;
        int32_t limit = -JTK_INTEGER_MAX_VALUE;
        uint8_t first = text[0];
        result = 0;
        if (!((first >= '0') && (first <= '9'))) {
            if (first == '+') {
                negative = false;
            }
            else if (first == '-') {
                negative = true;
                limit = JTK_INTEGER_MIN_VALUE;
            }
            else {
                error = true;
            }

            if (length == 1) {
                error = true;
            }

            i++;
        }

        if (result != -1) {
            int32_t m = limit / radix;
            while (i < length) {
                uint8_t value = text[i++];
                int32_t digit = jtk_Integer_digit(value, radix);
                if ((digit < 0) || (result < m)) {
                    error = true;
                    break;
                }
                result *= radix;
                if (result < (limit + digit)) {
                    error = true;
                    break;
                }
                result -= digit;
            }
            
            if (error) {
                result = -1;
            }
            else {
                result = negative? result : -result;
            }
        }
    }
    return result;
}

/* Reverse */

int32_t jtk_Integer_reverse(int32_t number) {
    bool negative = number < 0;
    int32_t copy = negative? -number : number;
	int32_t reverse = 0;
	while (copy != 0) {
		int32_t digit = copy % 10;
		reverse = (reverse * 10) + digit;
		copy /= 10;
	}
	return negative? -reverse : reverse;
}

/* String */

uint8_t* jtk_Integer_toStringEx(int32_t value, int32_t radix) {
    if ((radix < JTK_CHARACTER_MIN_RADIX) || (radix > JTK_CHARACTER_MAX_RADIX)) {
        radix = JTK_CHARACTER_DEFAULT_RADIX;
    }
    uint8_t buffer[33];
    int32_t index = 32;
    bool negative = value < 0;

    if (negative) {
        value = -value;
    }
    while (value >= radix) {
        buffer[index--] = jtk_Integer_digits[value % radix];
        value /= radix;
    }
    buffer[index] = jtk_Integer_digits[value];
    if (negative) {
        buffer[--index] = '-';
    }

    return jtk_String_newEx(buffer + index, 33 - index);
}

uint8_t* jtk_Integer_toString(int32_t value) {
    return jtk_Integer_toStringEx(value, JTK_CHARACTER_DEFAULT_RADIX);
}

int32_t jtk_Integer_getString(int32_t value, uint8_t* buffer, int32_t size) {
    return jtk_Integer_getStringEx(value, JTK_CHARACTER_DEFAULT_RADIX, buffer,
        size, 0);
}

int32_t jtk_Integer_getStringEx(int32_t value, int32_t radix, uint8_t* destination,
    int32_t destinationSize, int32_t destinationIndex) {
    if ((radix < JTK_CHARACTER_MIN_RADIX) || (radix > JTK_CHARACTER_MAX_RADIX)) {
        radix = JTK_CHARACTER_DEFAULT_RADIX;
    }
    uint8_t buffer[JTK_INTEGER_MAX_BINARY_STRING_SIZE];
    int32_t index = JTK_INTEGER_MAX_BINARY_STRING_SIZE - 1;
    bool negative = value < 0;

    if (negative) {
        value = -value;
    }
    while (value >= radix) {
        buffer[index--] = jtk_Integer_digits[value % radix];
        value /= radix;
    }
    buffer[index] = jtk_Integer_digits[value];
    if (negative) {
        buffer[--index] = '-';
    }

    uint8_t* result = buffer + index;
    int32_t resultSize = JTK_INTEGER_MAX_BINARY_STRING_SIZE - index;
    int32_t copyableSize = jtk_Integer_min(resultSize, destinationSize - destinationIndex);
    jtk_Arrays_copyEx_b(result, resultSize, 0, destination, destinationSize,
        destinationIndex, copyableSize);

    return resultSize;
}