#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct collatz_chn {
	unsigned int arr_len; /* Size of array */
	unsigned int len; /* Size of chain. */ 
	unsigned int marker; /* Last element in arr. */ 
	int* arr;
} CollatzChn;

CollatzChn* chnInit(CollatzChn* chn, const int init_val) {
	chn = malloc(sizeof(CollatzChn));
	chn->arr = malloc(sizeof(int));
	if (chn == NULL || chn->arr == NULL) {
		printf("Failed to allocate.\n");
		exit(-1);
	}
	
	chn->len = 1;
	chn->marker = 0;
	chn->arr[chn->marker++] = init_val;

	return chn;
}

void add(CollatzChn* chn, const int val) {
	if (chn->marker == chn->len) {
		int* temp;
		temp = realloc(chn->arr, sizeof(int) * (chn->len *= 2));
		if (temp == NULL) {
			printf("Failed to reallocate.\n");
			exit(-1);
		}
		chn->arr = temp;
	}
	chn->arr[chn->marker++] = val;
}

int main(int argc, char* argv[]) {
	unsigned int m = 1000000;
	unsigned int end = m / 2;
	unsigned int n;
	CollatzChn* longest_chn = NULL;
	CollatzChn* chn = NULL;

	if (m % 2 == 0) --m;

	while (m > end) {
		n = m;

		chn = chnInit(chn, n);
		
		while (n > 1) {
			n = (n % 2 == 0) ? n / 2 : n * 3 + 1;
			add(chn, n);
		}

		if (longest_chn == NULL) {
			longest_chn = malloc(sizeof(CollatzChn));
			longest_chn->arr = malloc(sizeof(int) * chn->marker);

			if (longest_chn == NULL || longest_chn->arr == NULL) {
				printf("Failed to allocate.\n");
				exit(-1);
			}
			memmove(longest_chn, chn, sizeof(CollatzChn));
			memmove(longest_chn->arr, chn->arr, sizeof(int) * chn->len);
		} else if (chn->marker > longest_chn->marker) {
			int* temp = realloc(longest_chn->arr, sizeof(int) * chn->marker);

			if (temp == NULL) {
				printf("Failed to reallocate.\n");
				exit(-1);
			}
			longest_chn->arr = temp;
			memmove(longest_chn, chn, sizeof(CollatzChn));
			memmove(longest_chn->arr, chn->arr, sizeof(int) * chn->len);
		}
		
		free(chn);
		chn = NULL;

		m -= 2;
	}

	int i;
	printf("LONGEST CHAIN: ");
	for (i = 0; i < longest_chn->marker; i++) {
		printf("%d ", longest_chn->arr[i]);
	}
	printf("\n");

	free(longest_chn->arr); free(longest_chn);

	return 0;
}