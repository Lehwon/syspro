#include <stdio.h>
#include <unistd.h>

int main()
{
	int pid;
	printf("[%d] Process start \n", getpid());
	pid = fork();
	printf("[%d] Proess : return value %d \n", getpid(), pid);
}
