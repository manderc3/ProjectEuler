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