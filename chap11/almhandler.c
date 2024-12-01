#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void (*signal(int signum, void (*handler)(int)))(int) {
	struct sigaction sa;
	struct sigaction old_sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(signum, NULL, &old_sa) == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	if (sigaction(signum, &sa, NULL) == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	return old_sa.sa_handler;
}

void alarmHandler(int signo) {
	printf("Wake up\n");
	exit(0);
}

int main() {
	signal(SIGALRM, alarmHandler);
	alarm(5);

	short i = 0;
	while(1) {
		sleep(1);
		i++;
		printf("%d second\n", i);
	}

	printf("end\n");
	return 0;
}

