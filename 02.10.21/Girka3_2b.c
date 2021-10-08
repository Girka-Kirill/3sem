#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
        int N = 0, i, PStatus, IdChild;
        scanf("%d", &N);
        for (i = 0; i < N; i++) {
                pid_t pid = fork();

                if (pid == 0) {
                        printf("Процессс с pid %d: Процесс №%d с pid %d создан\n", getppid(),  i + 1, getpid());
                } else {
                        PStatus = 0;
                        IdChild = wait(&PStatus);
                        printf("Процесс с pid %d: удалён\n", IdChild);
                        exit(0);
                }
        }
}
