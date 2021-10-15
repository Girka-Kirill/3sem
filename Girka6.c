#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pthread.h>

char a[] = "a.fifo";
char b[] = "b.fifo";

void* ZeroRead (void* dummy) {
        int fd1 = open(a, O_WRONLY);
        char buffer[100];

        while (1) {
                fgets(buffer, 100, stdin);
                write(fd1, buffer, 100);
        }
}

void* ZeroWrite (void* dummy) {
        int fd2 = open(b, O_RDONLY);
        char buffer[100];

        while (1) {
                read(fd2, buffer, 100);
                printf("%s", buffer);
        }
}

void* OneRead (void* dummy) {
        int fd1 = open(b, O_WRONLY);
        char buffer[100];

        while (1) {
                fgets(buffer, 100, stdin);
                write(fd1, buffer, 100);
        }
}

void* OneWrite (void* dummy) {
        int fd2 = open(a, O_RDONLY);
        char buffer[100];

        while (1) {
                read(fd2, buffer, 100);
                printf("%s", buffer);
        }
}

void ChattingZeroArg () {
        pthread_t thid1, thid2;
        int result1 = pthread_create(&thid1, (pthread_attr_t *)NULL, ZeroRead, NULL);

        if (result1 != 0) {
                printf ("Thread error\n");
                exit(-1);
        }
        printf("Thread created, thid = %d\n", thid1);
        int result2 = pthread_create(&thid2, (pthread_attr_t *)NULL, ZeroWrite, NULL);
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
        int result1 = pthread_create(&thid1, (pthread_attr_t *)NULL, OneRead, NULL);

        if (result != 0) {
                printf ("Thread error\n");
                exit(-1);
        }
        printf("Thread created, thid = %d\n", thid1);
        int result2 = pthread_create(&thid2, (pthread_attr_t *)NULL, OneWrite, NULL);
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
