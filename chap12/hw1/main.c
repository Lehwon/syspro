#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXLINE 100

int main() {
    int n, length, fd[2], pid;
    char message[MAXLINE], line[MAXLINE];

    pipe(fd);

    if ((pid = fork()) == 0) {
        close(fd[0]);
        sprintf(message, "Hello from PID %d\n", getpid());
        length = strlen(message) + 1;
        
        printf("Send: [%d] %s", getpid(), message);
        
        write(fd[1], message, length);
        close(fd[1]);
    } else {
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        
        printf("Recv: [%d] %s", getpid(), line);
        close(fd[0]);
    }

    exit(0);
}

