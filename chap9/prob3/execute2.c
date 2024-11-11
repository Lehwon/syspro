#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	printf("parental process start\n");
	if(fork() == 0) {
		execl("/bin/echo", "echo", "hello", NULL);
		fprintf(stderr, "failed first");
		exit(1);
	}

	if(fork() == 0) {
		execl("/bin/date", "date", NULL);
		fprintf(stderr, "failed second");
		exit(2);
	}

	if(fork() == 0) {
		execl("/bin/ls", "ls", "-l", NULL);
		fprintf(stderr, "failed third");
		exit(3);
	}
	printf("parental process end\n");
}
