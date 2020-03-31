#include <stdio.h>
#include <jtk/core/CString.h>
#include <jtk/collection/array/Arrays.h>

void printStrings(const char** strings, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("[%d] %s\n", i, strings[i]);
	}
}

int main() {
	const char* names[100] = {
		"Samuel Rowe",
		"Anushka Madyanam",
		"Joel E. Rego",
		"Keerthana Yadav",
		"Arshad Ahmed",
		"Sreem Chowdhary",
		"Akshay",
		"Monica Mayalagu"
	};
	int32_t n = 8;

	jtk_Arrays_timSort_v((void**)names, n,
		(jtk_ComparatorFunction_t)jtk_CString_comparePtr);

	printStrings(names, n);

	return 0;
}