"""

Project Euler Solutions - Problem 04

By Chris Mander (http://github.com/manderc3)

"""

import time

def checkPalindrome(product):
	str_product = str(product)

	for i in range(len(str_product)):
		if (str_product[i] == str_product[len(str_product) - 1 - i]):
			continue
		else:
			return False
	
	return True

def largestPalindrome(n):
	"""
	Optimised version that avoids duplicate operations. Runs half of the number of operations
	that a brute force approach does.
	"""

	largest_product = 0
	lower_limit = 10 ** (n - 1)
	upper_limit = 10 ** n

	initial_value_masks = ((0, 0), # For loop #1 (All operations using only odd operands)
						   (1, 1), # For loop #2 (All operations using only even operands)
						   (1, 0)) # For loop #3 (All operations using odd and even operands)

	for i in range(3):
		""" Set initial values using (10 ^ n - 1 + appropriate mask). """
		x = lower_limit + initial_value_masks[i][0]
		y = lower_limit + initial_value_masks[i][1]

		while (x < upper_limit):
			while (y < upper_limit):				
				product = x * y
				if (checkPalindrome(product) and product > largest_product):
					largest_product = product
				y += 2

			x += 2

			if (i > 2):
				y = int('1' + '0' * (n - 1)) # Set y to initial factor (10 ^ n - 1)
			else:
				y = x # Previous factor stored in x ignored for remaining operations

	return largest_product

if __name__ == "__main__":
	start = time.clock()
	print(largestPalindrome(3))
	print("Time: " + str(time.clock() - start))
