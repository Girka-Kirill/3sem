#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	pid_t pid;
	char *name[] = {"./Girka3_41",NULL};
	pid = fork();
	if (pid == 0) {
		execv(name[0], name);
	}
}
