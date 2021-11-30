#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pthread.h>

char a[] = "a.fifo";
char b[] = "b.fifo";

void* FunWrite (int* fd) {
        char buffer[100];
        while (1) {
                read(*fd, buffer, 100);
                printf("%s", buffer);
        }
}

void* FunRead (int* fd) {
        char buffer[100];
        while (1) {
                fgets(buffer, 100, stdin);
                write(*fd, buffer, 100);
        }
}


void ChattingZeroArg () {
        pthread_t thid1, thid2;
        int fdwr = open(a, O_WRONGLY);
        int fdrd = open(b, O_RDONLY);
        int result1 = pthread_create(&thid1, (pthread_attr_t *)NULL, FunRead, &fdrd);

        if (result1 != 0) {
                printf ("Thread error\n");
                exit(-1);
        }
        printf("Thread created, thid = %d\n", thid1);
        int result2 = pthread_create(&thid2, (pthread_attr_t *)NULL, FunWrite, &fdwr);
        if (result2 != 0) {
                printf ("Thread error\n");
                exit(-1);
        }
        printf("Thread created, thid = %d\n", thid2);
        pthread_join(thid1, (void **)NULL);
        pthread_join(thid2, (void **)NULL);
}

void ChattingOneArg () {
        pthread_t thid1, thid2;
        int fdwr = open(b, O_WRONGLY);
        int fdrd = open(a, O_RDONLY);
        int result1 = pthread_create(&thid1, (pthread_attr_t *)NULL, FunRead, &fdrd);

        if (result != 0) {
                printf ("Thread error\n");
                exit(-1);
        }
        printf("Thread created, thid = %d\n", thid1);
        int result2 = pthread_create(&thid2, (pthread_attr_t *)NULL, FunWrite, &fdwr);
        if (result2 != 0) {
                printf ("Thread error\n");
                exit(-1);
        }
        printf("Thread created, thid = %d\n", thid2);
        pthread_join(thid1, (void **)NULL);
        pthread_join(thid2, (void **)NULL);
}

int main(int argc, char* argv[]) {
        (void)umask(0);

        if (mknod(a, S_IFIFO | 0666, 0) < 0) {
                printf("Can't create FIFO\n");
        }

        if (mknod(b, S_IFIFO | 0666, 0) < 0) {
                printf("Can't create FIFO\n");
        }

        if (atoi(argv[1]) == 0) {
                ChattingZeroArg();
        } else if (atoi(argv[1]) == 1) {
                ChattingOneArg();
        }

        return 0;
}
