#include <stdio.h>
#include <stdlib.h>
#include <math.h>

size_t getNextTriNum();
int factorCount(size_t n);
size_t largestTriNum(int n);

size_t getNextTriNum() {
	static int tri_num = 0, tri_sum = 0;

	tri_sum = tri_sum + (++tri_num);	

	return tri_sum;
}

int factorCount(size_t n) {
	int count = 1, i = 2;

	if (n == 1) {
		return 1;
	}
	
	while (i < sqrt(n)) {
		if (n % i == 0) {
			++count;
		}
		++i;
	}
	return count * 2;
}

size_t largestTriNum(int n) {
	size_t tri_num;

	while(1) {
		tri_num = getNextTriNum();
		while (tri_num % 6 != 0 || tri_num % 10 != 0) // Multiples of 6 & 10 consistently yield the largest dividend counts.
			tri_num = getNextTriNum();	

		if (factorCount(tri_num) >= n + 1)
			return tri_num;
	}
		
	return tri_num;
}

int main(int argc, char *argv[]) {

	printf("%zu\n", largestTriNum(103));
	
	return 0;
}