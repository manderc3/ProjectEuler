'''

Project Euler Solutions - Problem 02

By Chris Mander (http://github.com/manderc3)

'''

import time

def fib(n):
	''' 
	General Fibonacci Algorithm, return value for 'n' terms - O(n) time	
	'''
	x = fib_sum = 0
	y = 1

	for i in range(1, n + 1):
		fib_sum = x + y
		x, y = y, fib_sum

	return fib_sum

def evenFib(n):
	''' 
	Returning sum of even terms, sum less than 'n' returned - 0(n) time 
	'''
	x = y = 1
	z = even_sum = 0

	while (z < n):
		if (z % 2 == 0):
			even_sum += z

		x, y = y, z
		z = (x + y)

	return even_sum

def evenFib2(n):
	'''
	Same as evenFib, although all odd terms are skipped - O(n) time
	'''
	x, y = 2, 0
	result = 2
	even_sum = 0

	while (result < n):
		even_sum += result

		result = 4 * x + y # result is always the following even term
		x, y = result, x

	return even_sum

def evenFib3(n):
	'''
	Lessens the number of variables stored in memory - O(n) time
	'''
	fib = [2, 0]
	i = even_sum = 0

	while (fib[i] < n):
		even_sum += fib[i]
		i = (i + 1) % 2 # remain in bounds of list
		fib[i] = 4 * fib[(i + 1) % 2] + fib[i]

	return even_sum

if __name__ == "__main__":
	start = time.clock()
	#print(fib(10))
	#print(evenFib(4000000))
	#print(evenFib2(4000000))
	print(evenFib3(4000000))
	print("Time: " + str(time.clock() - start))

