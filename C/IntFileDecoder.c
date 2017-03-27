/**
 * Integer File Decoder Module
 *
 * Written by Christopher Mander (http://github.com/manderc3)
 **/

#include <stdio.h>
#include <stdlib.h>
#include "IntFileDecoder.h"

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

struct DecodedFile* dStructInit(char* path) {

	FILE* f = fopen(path, "r");
	if (f == NULL) {
		return NULL;
	}

	struct DecodedFile* d_struct = malloc(sizeof(struct DecodedFile));
	if (d_struct == NULL) {
		return NULL;
	}
	
	d_struct->length = getLength(f);
	d_struct->height = getHeight(f, d_struct->length);
	d_struct->arr = decodeFile(f, d_struct->length, d_struct->height);

	fclose(f);
	return d_struct;
}