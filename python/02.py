"""

Project Euler Solutions - Problem 02

By Chris Mander (http://github.com/manderc3)

"""

import time

def evenFib(n):
	"""
	Lessens the number of variables stored in memory - O(n) time
	"""
	fib = [2, 0]
	i = even_sum = 0

	while (fib[i] < n):
		even_sum += fib[i]
		i = (i + 1) % 2 # remain in bounds of list
		fib[i] = 4 * fib[(i + 1) % 2] + fib[i]

	return even_sum

if __name__ == "__main__":
	start = time.clock()
	print(evenFib(4000000))
	print("Time: " + str(time.clock() - start))