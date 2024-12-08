#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#define MAXLINE 100

int main() {
    int fd[2];
    pid_t pid1, pid2;
    char input[MAXLINE];
    char output[MAXLINE];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    printf("parent process start\n");

    if ((pid1 = fork()) == 0) {
        close(fd[0]);
        printf("input string: ");
        fgets(input, MAXLINE, stdin);
        write(fd[1], input, strlen(input) + 1);
        close(fd[1]);
        exit(0);
    }

    wait(NULL);

    if ((pid2 = fork()) == 0) {
        close(fd[1]);
        read(fd[0], output, MAXLINE);
        for (int i = 0; output[i]; i++) {
            output[i] = toupper((char)output[i]);
        }
        printf("%s", output);
        close(fd[0]);
        exit(0);
    }

    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    return 0;
}

