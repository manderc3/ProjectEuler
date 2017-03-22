#include <stdio.h>
#include <stdlib.h>
#include <math.h>

size_t pyTripletProduct(const int);

size_t pyTripletProduct(int n) {
	int a = n / 5, b = a + 1, found = 0;
	double total = 0.0, c;

	while ((int) total <= n * 1.25) {
		while (b++ < n) {
			c = sqrt(pow(a, 2) + pow(b, 2));
			total = a + b + c;
			if ((int) total == n) {
				found = 1;
				break;
			}
		}

		if (found)
			return a * b * c;

		a++;
		b = a + 1;
	}

	return 0;
}

int main() {
	printf("%zu\n", pyTripletProduct(1000));
	return 0;
}