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

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>





int64_t jtk_Math_power(int32_t base, int32_t exponential) {
	int64_t result = 1;
	int32_t i;
	for (i = 1; i <= exponential; i++) {
		result *= base;
	}
	return result;
}

int main() {
	int64_t limit = jtk_Math_power(2, 32) - 1;
	int32_t count = 0;
	int64_t i;
	// for (i = 0; i <= limit; i++) {
		if (jtk_Math_isPrime_l(limit)) {
			count++;
		}
	// }
	printf("Prime numbers = %d\n", count);
	
	return 0;
}