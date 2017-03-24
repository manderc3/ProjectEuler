#include <stdio.h>
#include <stdlib.h>

/**
 * Get the length and height of rows and columns in a file (file must have uniform row lengths
 * and column heights.)
 *
 * getHeight depends on getLength's return value as a tradeoff for efficiency.
 **/
int getLength(FILE* f);
int getHeight(FILE* f, const int height);

/**
 * For decoding provided file into multidimensional array. Returns to array on success, NULL otherwise.
 **/
int** decodeFile(FILE* f, const int length, const int height);

/**
 * Functions for getting the highest product from adjacent numbers within 2d arrays.
 * Caller provides a 2d array, a start and end point, and a range of adjacency.
 **/
size_t getHorizontal(int** arr, const int start, const int end, const int range, const int height);
size_t getVertical(int** arr, const int start, const int end, const int range, const int length);
size_t getDiagonal(int** arr, const int range, short direction, const int length, const int height);

/**
 * Interface function that separates the preparation and adjacency checks from the user.
 **/
size_t getLargestAdjProduct(char* fpath, int range);

int getLength(FILE* f) {
	int count = 1; // Length = (no. spaces + 1) 
	char c;

	while ((c = getc(f)) != '\n') {
		if (c == ' ')
			++count; // Spaces separate elements			
	}
	
	fseek(f, 0, SEEK_SET); // Reset file pointer to beginning
	return count;
}

int getHeight(FILE* f, int length) {
	int count = 0;
	char c;

	while ((c = getc(f)) != EOF) {
		++count;
		fseek(f, length * 3 - 1, SEEK_CUR); // Skip to first offset for next line
	}

	fseek(f, 0, SEEK_SET);
	return count;
}

int** decodeFile(FILE* f, int length, int height) {
	char num[2]; // Where each element of f is stored for processing
	int i, j = 0;
	int** arr = malloc(sizeof(*arr) * height);

	if (!arr)
		return NULL;
	
	for (i = 0; i < height; i++) {
		arr[i] = malloc(sizeof(arr[i]) * length);
		if (!arr[i])
			return NULL; // Failed to allocate memory for an offset of arr
	}

	char* num_end;

	for (i = 0; i < height; i++){
		for (j = 0; j < length; j++) {
			fgets(num, 3, f);
			arr[i][j] = (int) strtol(num, &num_end, 10);
			fseek(f, 1, SEEK_CUR); // Skip any encountered spaces in file.
		}
	}

	fseek(f, 0, SEEK_SET);
	return arr;	
}

size_t getHorizontal(int** arr, int start, int end, int range, int height) {
	int i, j, k, prod = 1, h_prod = 0;

	for (i = 0; i < height; i++) {
		for (j = 0; j <= end; j++) {
			for (k = j; k < j + range; k++)
				prod *= arr[i][k];

			if (prod > h_prod)
				h_prod = prod;

			prod = 1;
		}
	}
	return h_prod;
}

size_t getVertical(int** arr, int start, int end, int range, int length) {
	int i, j, k, prod = 1, h_prod = 0;

	for (i = 0; i < length; i++) {
		for (j = 0; j <= end; j++) {
			for (k = j; k < j + range; k++)
				prod *= arr[k][i];

			if (prod > h_prod)
				h_prod = prod;

			prod = 1;			
		}
	}

	return h_prod;
}

size_t getDiagonal(int** arr, int range, short direction, int length, int height) {
	int i, j, k, start, end, prod = 1, h_prod = 0;

	if (direction == -1) {
		start = range - 1;
		end = length;
	}
	else {
		start = 0;
		direction = 1;
		end = length - range + 1;
	}

	for (i = 0; i <= height - range; i++) {
		for (j = start; j < end; j++) {
			for (k = 0; k < range; k++)
				prod *= arr[i + k][j + (k * direction)];

			if (prod > h_prod)
				h_prod = prod;

			prod = 1;
		}
	}

	return h_prod;
}

size_t getLargestAdjProduct(char* fpath, int range) {

	FILE* f = fopen(fpath, "r");
	size_t prod, h_prod = 0;
	int length, height, i;

	if (!f) {
		fprintf(stderr, "Failed to open file.\n");
		exit(-1);
	}		

	length = getLength(f);
	height = getHeight(f, length);

	if (range > length || range > height) {
		fprintf(stderr, "Range is greater than matrix length or height.\n");
		exit(-1);
	}

	int** arr = decodeFile(f, length, height);

	if (!arr) {
		fprintf(stderr, "Failed to allocate memory prior to decoding file.\n");
		exit(-1);
	}

	fclose(f); // File is no longer needed, as contents are now startwstored in array.

	for (i = 0; i < 4; i++) { // NOTE more cases required for odd sized structures
		switch (i) {
			case 0:
				prod = getHorizontal(arr, 0, length - range, range, height);
				break;
			case 1:
				prod = getVertical(arr, 0, length - range, range, length);
				break;
			case 2:
				prod = getDiagonal(arr, range, 1, length, height);
				break;
			case 3:
				prod = getDiagonal(arr, range, -1, length, height);
				break;
		}

		if (prod > h_prod)
			h_prod = prod;
	}

	return h_prod;
}

int main(int argc, char *argv[]) {
	printf("%zu\n", getLargestAdjProduct("./files/20x20digits.txt", 4));

	return 0;
}