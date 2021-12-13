#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define TABLE_LIMIT 3;

int main() {
    int i = 0, j, tmpnum, dishsize, N = TABLE_LIMIT;
    int shmid;
    int newm;
    int* array;
    int* timewish;
    FILE* fd1;
    char** dishes;
    char* tmp;
    char pathname[] = "key.c";
    key_t key;

    dishes = (char **) malloc(100 * sizeof(char*));
    timewish = (int *) malloc(100 * sizeof(int));
    tmp = (char*) malloc(100 * sizeof(char));
    fd1 = fopen("DishesWish.txt","r");
    printf("Считывание \n");
    while(fscanf(fd1, "%s : %d", tmp, &timewish[i]) != EOF) {
        dishes[i] = (char*) malloc(100 * sizeof(char));
        strcat(dishes[i], tmp);
        printf("%s %d\n", dishes[i], timewish[i]);
        i++;
    }
    fclose(fd1);
    dishsize = i;
    printf("%d", dishsize);
    i = 0;
    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if((shmid = shmget(key, 2 * sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){
        if(errno != EEXIST){
            printf("Can\'t create shared memory\n");
            exit(-1);
        }
        else {
            if((shmid = shmget(key, 2 * sizeof(int), 0)) < 0){
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
            newm = 0;
        }
    }

    if((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    if (newm) {
        array[0] = 0;
        array[1] = 0;
    }
    printf("Начинаем мыть!\n");
    fd1 = fopen("DishesNumber.txt","r");
    while(fscanf(fd1, "%s : %d", tmp, &tmpnum) != EOF) {
        for (i = 0; i < dishsize; i++) {
            if (strcmp(dishes[i], tmp) == 0){
                for (j = 0; j < tmpnum; j++) {
                    sleep(timewish[i]);
                    while ((array[0] - array[1]) >= N) {
                        sleep(1);
                    }
                    array[0] += 1;
                    printf("%s помыл, %d %d\n", dishes[i], array[0], array[1]);
                }
                break;
            }
        }
    }
    fclose(fd1);
    free(tmp);
    free(timewish);
    free(dishes[0]);
    free(dishes[1]);
    free(dishes);
}
