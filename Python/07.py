'''

Project Euler Solutions - Problem 07

By Chris Mander (http://github.com/manderc3)

'''

import time
from reusable import isPrime

def getPrime(n):

	prime_count, i = 1, 3
	
	while (prime_count < n - 2):
		if (isPrime(i)):
			prime_count += 1		
		i += 2

	return i

print(getPrime(10001))