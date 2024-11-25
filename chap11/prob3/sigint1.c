#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void intHandler();
int main() {
	signal(SIGINT, intHandler);
	while(1)
		pause();
	printf("end\n");
}

void intHandler(int signo) {
	printf("Interrupt signal\n");
	printf("signal number : %d\n", signo);
	exit(0);
}
