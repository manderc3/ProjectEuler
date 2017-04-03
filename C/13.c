#include <stdio.h>
#include <stdlib.h>

int getFileLength(FILE* f) {
	/* Precondition - File contains lines of equal length */
	int count = 0;
	char c;

	while ((c = getc(f)) != '\n')
		++count;		
	
	fseek(f, 0, SEEK_SET); // Reset file pointer to beginning
	return count;
}

int getFileHeight(FILE *f) {
	int count = 1;
	char c;

	while ((c = getc(f)) != EOF) {
		if (c == '\n')
			++count;
	}

	fseek(f, 0, SEEK_SET);
	return count;
}
int getNextNum(FILE* f, char* num_arr) {
	int i = 0;
	char c;

	while ((c = getc(f)) != '\n') {
		if (c == EOF) {
			return;
		}
		num_arr[i++] = c;
	}
}

int getLength(char* arr) {
	int i = 0;
	while (arr[++i] != '\0');
	return i;
}

int addLongNums(char* opr1, char* opr2) {
	int sum, carry = 0;
	int opr1_len = getLength(opr1), opr2_len = getLength(opr2);

	int diff = opr1_len - opr2_len;
	int i = opr1_len - 1;

	while (i >= 0) {
		if (i - diff >= 0)
			sum = (int) opr1[i] - 48 + opr2[i - diff] - 48 + carry;
		else
			sum = (int) opr1[i] - 48 + carry;

		if (sum > 9)
			carry = 1;
		else
			carry = 0;

		opr1[i--] = (char) sum % 10 + 48;
	}

	if (carry) {
		opr1 = realloc(opr1, sizeof(char) * opr1_len + carry);
		int i;
		for (i = opr1_len	 + 1; i >= 0; i--)
			opr1[i] = opr1[i - 1];
		opr1[0] = '1';
	}

	return 1;
}

char* getLongNumSum(char* f_path) {
	FILE* f = fopen(f_path, "r");
	const int F_LEN = getFileLength(f), F_HGT = getFileHeight(f);
	char* opr1 = malloc(sizeof(char) * F_LEN);
	char* opr2 = malloc(sizeof(char) * F_LEN);
	int i = 0;

	getNextNum(f, opr1);

	while (i++ < F_HGT - 1) {
		getNextNum(f, opr2);
		addLongNums(opr1, opr2);
	}

	return opr1;
}

int main(int argc, char* argv[]) {
	int i;
	char* num = getLongNumSum("./files/largesum.txt");

	for (i = 0; i < 10; i++)
		printf("%c", num[i]);
	printf("\n");

	return 0;
}