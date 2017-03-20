'''

Project Euler Solutions - Problem 01

By Chris Mander (http://github.com/manderc3)

'''

import time

def sumOfMultiplesBF(n):
	''' Brute Force Approach - O(n) time '''
	total_sum = 0

	for i in range(n):
		if (i % 3 == 0 or i % 5 == 0):
			total_sum += i

	return total_sum

def sumOfMultiplesAP(n, p):
	''' Arithmetic Progression Approach - 0(1) time '''
	return n * (p // n) * ((p // n) + 1) // 2

if __name__ == "__main__":
	start = time.clock()
	#print(sumOfMultiplesBF(1000))
	#print(sumOfMultiplesAP(3, 999) + sumOfMultiplesAP(5, 999) - sumOfMultiplesAP(15, 999))
	print("Time: " + str(time.clock() - start))