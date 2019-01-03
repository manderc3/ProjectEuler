#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int getIntLength(unsigned int product) {

	int length = 1;

	while (product >= 10) {
		++length;
		product /= 10;		
	}

	return length;
}

int checkPalindrome(unsigned int product) {

	int i, length = getIntLength(product), pivot = length / 2;

	if (length % 2 != 0) ++pivot;
	
	/** Loop will iterate for half of the number of digits in product. **/
	for (i = 1; i <= pivot; i++) {

		if (product / toThePower(10, length - i) % 10 != product / toThePower(10, i - 1) % 10)			
			return 0;
	}

	return 1;
}

int largestPalindrome(int n) {

	int x, y, i;
	unsigned int product, largest_product;

	int initial_value_masks[6] = {0, 0, 1, 1, 1, 0};

	int lower_limit = toThePower(10, n - 1);
	int upper_limit = toThePower(10, n);	

	for (i = 0; i < 6; i += 2) {
		/** Set initial values **/
		x = lower_limit + initial_value_masks[i];
		y = lower_limit + initial_value_masks[i + 1];

		while (x < upper_limit) {
			while (y < upper_limit) {
				product = x * y;

				if (checkPalindrome(product) && product > largest_product)
					largest_product = product;

				y += 2;
			}
			x += 2;

			if (i > 2) 
				y = lower_limit;				
			else 
				y = x;
		}
	}

	return largest_product;
}

int main() {

	printf("%d\n", largestPalindrome(3));
	return 0;
}