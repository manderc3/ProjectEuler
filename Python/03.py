'''

Project Euler Solutions - Problem 03

By Chris Mander (http://github.com/manderc3)

'''

import time
from math import sqrt

def isPrime(n):
	''' Simple primality test - O(sqrt(n)) time '''
	
	if (n == 2):
		return True

	if (n <= 1 or n % 2 == 0 or n % 3 == 0):
		return False

	for i in range(2, int(sqrt(n)) + 1):
		if (n % i == 0):
			return False
	
	return True

if __name__ == "__main__":
	start = time.clock()
	[print(str(i) + " " + str(isPrime(i))) for i in range(200)]
	print("Time: " + str(time.clock() - start))

