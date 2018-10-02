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

// Monday, July 23, 2018

#include <jtk/core/Integer.h>
#include <jtk/core/String.h>

/*******************************************************************************
 * Integer                                                                     *
 *******************************************************************************/

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

static int32_t jtk_Integer_digit(uint8_t character, int32_t radix) {
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
    
    int32_t length = jtk_String_getLength(text);
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
                result = -1;
            }

            if (length == 1) {
                result = -1;
            }
            
            i++;
        }
        
        if (result != -1) {
            int32_t m = limit / radix;
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