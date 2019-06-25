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
