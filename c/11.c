#include <stdio.h>
#include <stdlib.h>
#include "IntFileDecoder.h"

/** 
 *Solution depends on a file decoder module that can be found here: http://github.com/manderc3/IntFileDecoder.
 **/

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
	
	int i, j, k, prod 	= 1, h_prod = 0;

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

	size_t prod, h_prod = 0;
	int i;

	struct DecodedFile* d_struct = dStructInit(fpath);
	if (d_struct == NULL) {
		fprintf(stderr, "Failed to initialise decoded file structure.\n");
		exit(-1);
	}

	for (i = 0; i < 4; i++) { // NOTE more cases required for odd sized structures
		switch (i) {
			case 0:
				prod = getHorizontal(d_struct->arr, 0, d_struct->length - range, range, d_struct->height);
				break;
			case 1:
				prod = getVertical(d_struct->arr, 0, d_struct->length - range, range, d_struct->length);
				break;
			case 2:
				prod = getDiagonal(d_struct->arr, range, 1, d_struct->length, d_struct->height);
				break;
			case 3:
				prod = getDiagonal(d_struct->arr, range, -1, d_struct->length, d_struct->height);
				break;
		}

		if (prod > h_prod)
			h_prod = prod;
	}

	free(d_struct);
	return h_prod;
}

int main(int argc, char *argv[]) {
	
	printf("%zu\n", getLargestAdjProduct("./files/20x20digits.txt", 4));

	return 0;
}