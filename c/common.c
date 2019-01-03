#include <stdio.h>
#include "common.h" 

int toThePower(int base, int exponent) {
	int i, result = 1;

	for (i = 0; i < exponent; i++) {
		result *= base;
	}

	return result;
}

char getNextChar(FILE* file) {
	/**	To be used on files containing integers only. **/
	char c = getc(file);
	while (c == '\n')
		c = getc(file);	
	return c;
}