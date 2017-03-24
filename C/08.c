#include <stdio.h>
#include <stdlib.h>
#include "common.h"

size_t adjProduct(char*, const int);
void updateSubjects(int*, char*, const int);

void updateSubjects(int* arr, char* c, int arr_size) {
	int i;

	for (i = 1; i < arr_size; i++) {
		arr[i - 1] = arr[i];		
	}

	arr[arr_size - 1] = ((int) *c) - 48;
}

size_t adjProduct(char* f_path, int m_range) {
	FILE* file = fopen(f_path, "r");
	size_t c_prd, h_prd = 0;
	char c;

	if (file == NULL) {
		exit(-1);
	}

	int* subjects = malloc(sizeof(int) * m_range);
	int i;

	for (i = 0; i < m_range; i++)
		subjects[i] = ((int) getNextChar(file)) - 48;

	do {
		c_prd = 1;

		for (i = 0; i < m_range; i++)
			c_prd *= subjects[i];

		if (c_prd > h_prd)
			h_prd = c_prd;

		c = getNextChar(file);
		updateSubjects(subjects, &c, m_range);
	} while (c != EOF);

	free(subjects);
	return h_prd;
}

int main() {

	printf("%zu\n", adjProduct("./files/1000digits.txt", 13));
	return 0;
}