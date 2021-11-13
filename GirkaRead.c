#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define TABLE_LIMIT 3;

int main() {
    int i = 0, j, tmpnum, dishsize, tmpnum2, i1, j1, N = TABLE_LIMIT, semid;
    int *timewish;
    int *timeclear;
    FILE* fd1;
    FILE* fd2;
    char** dishes;
    char* tmp;
    char* tmp2;
    char pathname[] = "key.c";
    key_t key;
    char* marknum;
    pid_t pid;
    struct sembuf mybuf1, mybuf2;

    dishes = (char **) malloc(100 * sizeof(char*));
    timewish = (int *) malloc(100 * sizeof(int));
    timeclear = (int *) malloc(100 * sizeof(int));
    tmp = (char*) malloc(100 * sizeof(char));
    tmp2 = (char*) malloc(100 * sizeof(char));
    fd1 = fopen("DishesWish.txt","r");
    while(fscanf(fd1, "%s : %d", tmp, &timewish[i]) != EOF) {
        dishes[i] = (char*) malloc(100 * sizeof(char));
        strcat(dishes[i], tmp);
	i++;
    }
    fclose(fd1);
    dishsize = i;
    printf("%d", dishsize);
    i = 0;
    fd1 = fopen("DishesClean.txt","r");
    while(fscanf(fd1, "%s : %d\n", tmp, &tmpnum) != EOF) {
        for (j = 0; j < dishsize; j++) {
            if (strcmp(dishes[j], tmp) == 0){
                timeclear[j] = tmpnum;
            }
       	}
    }
    fclose(fd1);
    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if((semid = semget(key, 2, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get semid\n");
        exit(-1);
    }
    mybuf1.sem_op = N;
    mybuf1.sem_flg = 0;
    mybuf1.sem_num = 0;
    if(semop(semid, &mybuf1, 1) < 0){
        printf("Can\'t wait for condition\n");
        exit(-1);
    }
    mybuf2.sem_flg = 0;
    pid = fork();
    if (pid == 0) {
        fd1 = fopen("DishesNumber.txt","r");
        while (fscanf(fd1, "%s : %d\n", tmp, &tmpnum) != EOF) {
            for (i = 0; i < dishsize; i++) {
                if (strcmp(dishes[i], tmp) == 0){
		    printf("1 %s %d\n", tmp, tmpnum);
                    for (i1 = 0; i1 < tmpnum; i1++) {
                        sleep(timewish[i]);
                        mybuf1.sem_op = -1;
                        mybuf1.sem_num = 0;
                        if(semop(semid, &mybuf1, 1) < 0){
                            printf("Can\'t wait for condition\n");
                            exit(-1);
            		}
                        mybuf1.sem_op = 1;
                        mybuf1.sem_num = 1;
                        if(semop(semid, &mybuf1, 1) < 0){
                            printf("Can\'t wait for condition\n");
                            exit(-1);
            		}
                    }
                    break;
                }
	    }
            
        }
        fclose(fd1);
    }
    else {
        fd2 = fopen("DishesNumber.txt","r");
        while (fscanf(fd1, "%s : %d\n", tmp2, &tmpnum2) != EOF) {
	    mybuf2.sem_op = -1;
            mybuf2.sem_num = 1;
            if(semop(semid, &mybuf2, 1) < 0){
               printf("Can\'t wait for condition\n");
               exit(-1);
            } 
            mybuf2.sem_op = 1;
            mybuf2.sem_num = 0;
       	    if(semop(semid, &mybuf2, 1) < 0){
                printf("Can\'t wait for condition\n");
                exit(-1);
            }
            for (i = 0; i < dishsize; i++) {
                if (strcmp(dishes[i], tmp2) == 0){
                    for (i1 = 0; i1 < tmpnum2; i1++) {
                        sleep(timeclear[i]);
                    }
                    break;
                }
	    }
            
        }
        fclose(fd2); 
    }
    free(tmp);
    free(tmp2);
    free(timewish);
    free(timeclear);
    free(dishes[0]);
    free(dishes[1]);
    free(dishes);
}
