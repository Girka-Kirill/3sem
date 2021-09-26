#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

void Split(char* string, char* delimiters, char*** tokens, int* tokensCount) {
	char* tmp = string;
	char* tmp2;
	int len = strlen(string), i = 0, lenToken;
	while (tmp != NULL) {
		tmp = strpbrk(tmp, delimiters);
		i++;
		if (tmp == NULL) {
			break;
		}
		tmp = tmp + 1;
	}
	*tokensCount = i;
	i = 0;
	*tokens = (char**) realloc(*tokens, *tokensCount * sizeof(char*));
	tmp = string;
	for (i = 0; i < *tokensCount; i++) {
		tmp2 = strpbrk(tmp, delimiters);
		if (tmp2 == NULL) {
			lenToken = strlen(tmp);
			*tokens[i] = (char*) malloc(lenToken * sizeof(char));
			memcpy(*tokens[i], tmp, lenToken);
			break;
		}
		lenToken = strlen(tmp);
		lenToken = strlen(tmp) - strlen(tmp2);
		*tokens[i] = (char*) malloc(lenToken * sizeof(char));
		memcpy(*tokens[i], tmp, lenToken);
		tmp = strpbrk(tmp, delimiters);
		tmp = tmp + 1;
	}
}

// TODO: продемонстрируйте в int main(), как воспользоваться ф-ей Split
