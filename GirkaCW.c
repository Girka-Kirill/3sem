#include <stdio.h>
#include <string.h>
#include <malloc.h>

void GenerateString (int n, char* string) {
	char *tmp, A = 'a';
	if (n != 0) {
		GenerateString(n - 1, string);
		tmp = (char*) malloc(((1 << (n + 1)) - 1) * sizeof(char));
		strcat(tmp, string);
		tmp[strlen(tmp)] = A + n;
		strcat(tmp, string);
		strncpy(string, tmp, strlen(tmp));
		free(tmp);
	}
	else {
		string[0] = A;
	}
}

int main() {
	char* string;
	int n;
	scanf("%d", &n);
	string = (char*) malloc(((1 << (n + 1)) - 1) * sizeof(char));
	GenerateString(n, string);
	printf("%s \n", string);
	free(string);
}
