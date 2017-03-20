'''

Project Euler Solutions - Problem 01

By Chris Mander (http://github.com/manderc3)

'''

import time

def sumOfMultiples(n, p):
	""" Arithmetic Progression Approach - 0(1) time """
	return n * (p // n) * ((p // n) + 1) // 2

if __name__ == "__main__":
	start = time.clock()
	print(sumOfMultiples(1000))
	print("Time: " + str(time.clock() - start))