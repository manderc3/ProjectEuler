"""

Project Euler Solutions - Problem 09

By Chris Mander (http://github.com/manderc3)

"""

import time
from math import sqrt

def pyTripletProduct(n):
	"""
	Returns product of abc when a+b+c equals n, returns 0 if a+b+c fails to equate to n.

	Starting at a = n // 5 ensures that a+b+c won't exceed n. And time is saved by skipping
	lower and redunant values.

	There is a margin of n * 0.25, when total exceeds n * 1.25 (n + buffer), we can be certain
	that total will never equal n.  
	"""
	a = n // 5
	b = a + 1
	total = 0
	found = False

	while total <= n * 1.25:
		while b < n:
			c = sqrt(a ** 2 + b ** 2)
			total = a + b + c
			if total == n:
				found = True
				break
			b += 1

		if (found):
			return int(a * b * c)
		a += 1
		b = a + 1
	
	return 0

if __name__ == "__main__":
	start = time.clock()
	print(pyTripletProduct(1000))
	print("Time: " + str(time.clock() - start))


