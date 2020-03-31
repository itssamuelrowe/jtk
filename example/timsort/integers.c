#include <stdio.h>
#include <jtk/core/Integer.h>
#include <jtk/collection/array/Arrays.h>

void printIntegers(int8_t* array, int32_t n) {
	int32_t i;
    for (i = 0; i < n; i++) {
		printf("%d\t", array[i]);
	}
	puts("");
}

int main() {
	int n = 100000;
	int8_t array[n];

	int i;
	for (i = 0; i < n; i++) {
		array[i] = rand() % 255;
	}

	jtk_Arrays_timSortEx_b(array, n, 0, n, false);

    printIntegers(array, n);

	return 0;
}