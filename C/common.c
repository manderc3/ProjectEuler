#include "common.h" 

int toThePower(int base, int exponent) {
	int i, result = 1;

	for (i = 0; i < exponent; i++) {
		result *= base;
	}

	return result;
}