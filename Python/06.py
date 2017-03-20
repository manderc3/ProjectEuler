"""

Project Euler Solutions - Problem 06

By Chris Mander (http://github.com/manderc3)

"""

import time

def differenceInSquareSums(n):
	"""
	Returns the difference between the sum of squares of integers
	within a sequence and the square of the sum of integer of the
	same sequence.
	"""
	sum_of_squares = sum_of_nums = 0
	
	for i in range(1, n + 1):
		sum_of_squares += i ** 2
		sum_of_nums += i

	return sum_of_nums ** 2 - sum_of_squares

if __name__ == "__main__":
	start = time.clock()
	print(differenceInSquareSums(100))
	print("Time: " + str(time.clock() - start))