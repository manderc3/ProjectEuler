#include <stdio.h>
#include <stdlib.h>

int getFileLength(FILE* f) {
	int count = 0;
	char c;

	while ((c = getc(f)) != '\n')
		++count;		
	
	fseek(f, 0, SEEK_SET); // Reset file pointer to beginning
	return count;
}

int getNextNum(FILE* f, char* num_arr) {
	int i = 0;
	char c;

	while ((c = getc(f)) != '\n') {
		if (c == EOF)
			return EOF;
		num_arr[i++] = c;
	}

	return 1;
}

int getLength(char* arr) {
	int i = 0;
	while (arr[++i] != '\0');
	return i;
}

int addLongNums(char* opr1, char* opr2) {
	int sum, i = getLength(opr2), carry = 0;

	while (i >= 0) {
		sum = ((int) opr1[i] - 48) + ((int) opr2[i] - 48) + carry;
		
		if (sum > 9)
			carry = 1;
		else
			carry = 0;

		opr1[i] = (char) sum % 10 + 48;
		i--;
	}

	if (carry > 0) {
		int digit_count = 0, carry_copy = carry;

		while (carry_copy > 0) {
			carry_copy /= 10; 
			++digit_count;
		}

		opr1 = realloc(opr1, sizeof(char) * (getLength(opr1) + digit_count));
	}

	return 1;
}

char* getLongNumSum(char* f_path) {
	FILE* f = fopen(f_path, "r");
	int f_len = getFileLength(f);
	char* opr1 = malloc(sizeof(char) * f_len);
	char* opr2 = malloc(sizeof(char) * f_len);

	getNextNum(f, opr1);
	int j;

	while (getNextNum(f, opr2) != EOF) {
		int i;
		for (i = 0; i < f_len; i++) {
			printf("%c", opr1[i]);
		}
		printf("\n");

		for (i = 0; i < f_len; i++) {
			printf("%c", opr2[i]);
		}
		printf("\n");

		addLongNums(opr1, opr2);

		for (i = 0; i < f_len; i++) {
			printf("%c", opr1[i]);
		}
		printf("\n\n");		
	}

	return opr1;
}

int main(int argc, char* argv[]) {
	int i;

	getLongNumSum("./files/largesum2.txt");

	return 0;
}