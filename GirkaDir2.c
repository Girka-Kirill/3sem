#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

void findFile (int depth, char* fileName, char* currentDirectory, int* fileCount, char** fileVector) {
    DIR* direct = opendir(currentDirectory);
    char* nextDirectory;
    struct dirent* dir;
    while (dir = readdir(direct)) {
        if (dir->d_type == 4 && depth != 0) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                nextDirectory = (char *) malloc ((2 + strlen(dir->d_name)) * sizeof(char));
                strcat(nextDirectory, currentDirectory);
                strcat(nextDirectory, "/");
                strcat(nextDirectory, dir->d_name);
                findFile(depth - 1, fileName, nextDirectory, fileCount, fileVector);
                free(nextDirectory);
            }
        }
        if (strcmp(fileName, dir->d_name) == 0) {
            fileVector[*fileCount] = (char *) malloc ((strlen(currentDirectory) + strlen(fileName) + 1) * sizeof(char));
            strcat(fileVector[*fileCount], currentDirectory);
            strcat(fileVector[*fileCount], "/");
            strcat(fileVector[*fileCount], fileName);
            *fileCount += 1;
        }
    }
}

int main(int argc, char* argv[]) {
    int depth = 2, fileCount = 0, i;
    char fileName[] = "a.txt", currentDirectory[] = ".";
    char** fileVector;
    fileVector = (char **) malloc (1000 * sizeof(char *));
    findFile(atoi(argv[3]), argv[2], argv[1], &fileCount, fileVector);
    printf("%d\n", fileCount);
    for (i = 0; i < fileCount; i++) {
        printf("%s\n", fileVector[i]);
        free(fileVector[i]);
    }
    free(fileVector);
}
