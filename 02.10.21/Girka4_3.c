#include <stdio.h>
#include <malloc.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int fd1[2], fd2[2], sum_tmp[2];
	int a[2] = {2, 3};
	int sum;
	pid_t pid;
	pipe(fd1);
	pipe(fd2);
	pid = fork();
	if (pid != 0) {
		close(fd1[0]);
		write(fd1[1], a, 2 * sizeof(int));
		close(fd1[1]);
		close(fd2[0]);
	}
	else {
		read(fd1[0], &sum_tmp, 2 * sizeof(int));
		sum = sum_tmp[0] + sum_tmp[1];
		printf("%d",sum);
		close(fd2[1]);
	}
}
