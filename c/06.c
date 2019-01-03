#include <stdio.h>
#include <stdlib.h>

int toThePower(int base, int exponent) {
	int i, result = 1;

	for (i = 0; i < exponent; i++) {
		result *= base;
	}

	return result;
}

unsigned int differenceInSquareSums(int n) {
	int sum_of_squares = 0, sum_of_nums = 0, i;

	for (i = 1; i < n + 1; i++) {
		sum_of_squares += toThePower(i, 2);
		sum_of_nums += i;
	} 

	return toThePower(sum_of_nums, 2) - sum_of_squares; 
}

int main() {

	printf("%d\n", differenceInSquareSums(100));
	return 0;
}