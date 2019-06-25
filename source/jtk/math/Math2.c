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