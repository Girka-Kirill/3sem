#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

pid_t pid;

void my_handler1 (int nsig) {
	printf("ФРТК\n");
	kill(getpid(), SIGUSR2);
}

void my_handler2 (int nsig) {
	printf("чемпион!\n");
	kill(pid, SIGUSR1);
}


int main (void) {

	(void) signal(SIGUSR1, my_handler1);
	(void) signal(SIGUSR2, my_handler2);
	kill(pid, SIGUSR1);
	pid = fork();
		if (pid == 0) {
			while(1) {}
		}
		else {
			while(1) {} 
		}
	
	return 0; 
}