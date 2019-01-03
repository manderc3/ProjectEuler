"""

Project Euler Solutions - Problem 10

By Chris Mander (http://github.com/manderc3)

"""

from common import isPrime

def sumOfPrimesRange(n):
	"""
	Returns the sum of all primes under a given value.
	"""
	num = 3
	p_sum = 2

	while num < n:
		if isPrime(num):
			p_sum += num
		num += 2
	
	return p_sum