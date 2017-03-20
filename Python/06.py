'''

Project Euler Solutions - Problem 06

By Chris Mander (http://github.com/manderc3)

'''

import time

def differenceInSquareSums(n):
	sum_of_squares, sum_of_nums = 0, 0
	
	for i in range(1, n + 1):
		sum_of_squares += i ** 2
		sum_of_nums += i

	return sum_of_nums ** 2 - sum_of_squares

print(differenceInSquareSums(100))