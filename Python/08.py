"""

Project Euler Solutions - Problem 08

By Chris Mander (http://github.com/manderc3)

"""

import time

def getNextChar(f):
	""" Returns next char in file that isn't a newline. """
	char = f.read(1)
	while char == "\n":
		char = f.read(1)
	return char

def adjProduct(f_path, m_range):
	"""
	Scans a file and returns the highest product from a arbitrary range of ints.
	This function is strictly for files that only contain integers.
	"""
	f = open(f_path, "r")

	h_prd = 0

	subjects = ["" for i in range(m_range)]
	
	for i in range(len(subjects)):
		subjects[i] = getNextChar(f)

	while subjects[len(subjects) - 1]:
		c_prd = 1

		for i in subjects:
			c_prd *= int(i)

		if c_prd > h_prd:
			h_prd = c_prd

		char = getNextChar(f)

		subjects = subjects[1:] + [char]

	f.close()

	return h_prd

if __name__ == "__main__":
	start = time.clock()
	print(adjProduct("files/1000digits.txt", 13))
	print("Time: " + str(time.clock() - start))