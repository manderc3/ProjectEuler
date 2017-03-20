"""

Project Euler Solutions - Problem 07

By Chris Mander (http://github.com/manderc3)

"""

import time
from common import isPrime

def getPrime(n):
	""" Get the nth prime.  """
	prime_count, i = 1, 3

	if n < 1: return 0
	elif n == 1: return 2
	
	while (prime_count < n - 2):
		if (isPrime(i)):
			prime_count += 1		
		i += 2

	return i

if __name__ == "__main__":
	start = time.clock()
	print(getPrime(10001))
	print("Time: " + str(time.clock() - start))