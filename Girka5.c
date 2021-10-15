#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
        (void)umask(0);

        char a[] = "a.fifo";
        char b[] = "b.fifo";

        if (mknod(a, S_IFIFO | 0666, 0) < 0) {
                printf("Can't create FIFO\n");
        }

        if (mknod(b, S_IFIFO | 0666, 0) < 0) {
                printf("Can't create FIFO\n");
        }

        pid_t result = fork();

        if (result < 0) {
                printf("fork's error\n");
                exit(-1);
        }

        int fdRd, fdWr;
        if (atoi(argv[1]) == 0) {
                fdRd = open("a.fifo", O_RDONLY);
                fdWr = open("b.fifo", O_WRONLY);
        }
        else if (atoi(argv[1]) == 1) {
                fdRd = open("b.fifo", O_RDONLY);
                fdWr = open("a.fifo", O_WRONLY);
        }
        char bufferWr[100];
        char bufferRd[100];

        while (1) {
                        if (result != 0) {
                                fgets(bufferWr, 100, stdin);
                                write(fdWr, bufferWr, 100);
                        } else {
                                read(fdRd, bufferRd, 100);
                                printf("%s", bufferRd);
                        }
        }

        return 0;
}
