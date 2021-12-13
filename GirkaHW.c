#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

void Split(char* string, char* delimiters, char** tokens, int* tokensCount) {
        string = strtok(string, delimiters);
        while (string != NULL) {
            tokens[*tokensCount] = string;
            (*tokensCount)++;
            string = strtok(NULL, delimiters);
        }
}

int main()
{
    char* string = (char*) malloc(1000 * sizeof(char));
    char* delimiters = (char*) malloc(100 * sizeof(char));
    char** tokens = (char**) malloc(1000 * sizeof(char));
    int tokensCount = 0, i;
    fgets(string, 1000, stdin);
    fgets(delimiters, 100, stdin);
    Split(string, delimiters, tokens, &tokensCount);
    for (i = 0; i < tokensCount; i++) {
        printf("%s\n", tokens[i]);
    }
    return 0;
}


// TODO: продемонстрируйте в int main(), как воспользоваться ф-ей Split
