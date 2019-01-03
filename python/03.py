'''

Project Euler Solutions - Problem 03

By Chris Mander (http://github.com/manderc3)

'''

import time
from math import sqrt
from common import isPrime

def largestPrimeFactor(n):
	factor, divisor = n, 2

	print(n / 2)

	while not isPrime(factor / divisor):
		factor / 2
		n += 1

	return factor

if __name__ == "__main__":
	start = time.clock()
	print(largestPrimeFactor(600851475143	))
	print("Time: " + str(time.clock() - start))

