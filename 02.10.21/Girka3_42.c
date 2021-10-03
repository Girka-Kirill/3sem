#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// TODO: это идейно похоже на то, что требовалось по заданию. перечитайте ещё раз, что требовалось
int main() {
	pid_t pid;
	char *name[] = {"./Girka3_41",NULL};
	pid = fork();
	if (pid == 0) {
		execv(name[0], name);
	}
}
