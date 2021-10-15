#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

void ChattingBetweenPrograms (char* a, char* b, char* bufferRd, char* bufferWr, int fdRd, int fdWr) {
        pid_t result = fork();

        if (result < 0) {
                printf("Can't fork children\n");
                exit(-1);
        }

        if (result > 0) {
                fdWr = open(a, O_WRONLY);

                while (1) {
                        fgets(bufferWr, 100, stdin);
                        write(fdWr, bufferWr, 100);
                }
        } else {
                fdRd = open(b, O_RDONLY);

                while (1) {
                        read(fdRd, bufferRd, 100);
                        printf("%s", bufferRd);
                }
        }
}

int main(int argc, char* argv[]) {
        (void)umask(0);

        char a[] = "a.fifo";
        char b[] = "b.fifo";
        pid_t result = fork();
        char bufferWr[100];
        char bufferRd[100];
        int fd1, fd2;

        if (mknod(a, S_IFIFO | 0666, 0) < 0) {
                printf("Can't create FIFO\n");
        }
        if (mknod(b, S_IFIFO | 0666, 0) < 0) {
                printf("Can't create FIFO\n");
        }
        if (result < 0) {
                printf("fork's error\n");
                exit(-1);
        }
        if (atoi(argv[1]) == 0) {
                ChattingBetweenPrograms(a, b, bufferRd, bufferWr, fd1, fd2);
        }
        else if (atoi(argv[1]) == 1) {
                ChattingBetweenPrograms(b, a, bufferRd, bufferWr, fd2, fd1);
        }
        return 0;
}
