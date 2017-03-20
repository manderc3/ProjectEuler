'''

Project Euler Solutions - Problem 05

By Chris Mander (http://github.com/manderc3)

'''

import time

def smallestDividendRange(n):
	''' 
	Divisors (n // 2 + 1) to n are evenly divisible by divisors 1 to (n // 2). Therefore only half
	of the total the number of divisors require checking.
	'''
	dividend = n # TODO - try and find a logical starting point

	while (True):
		consistent_div = True		
		divisor = n
		break_point = n // 2

		if (n % 2 != 0): break_point += 1 # For odd values of n

		while (divisor >= n // 2):
			if (dividend % divisor == 0):
				divisor -= 1				
			else:
				consistent_div = False
				break

		if (consistent_div):
			return dividend

		dividend += n

if __name__ == '__main__':

	start = time.clock()
	print(smallestDividendRange(20))
	print("Time: " + str(time.clock() - start))