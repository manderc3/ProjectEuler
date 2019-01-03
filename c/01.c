#include <stdio.h>
#include <stdlib.h>

int sumOfMultiples(int, int);

int sumOfMultiples(int n, int p) {
	return n * (p / n) * ((p / n) + 1) / 2;
}

int main() {
	printf("%d\n", sumOfMultiples(3, 999) + sumOfMultiples(5, 999) - sumOfMultiples(15, 999));
	return 0;
}