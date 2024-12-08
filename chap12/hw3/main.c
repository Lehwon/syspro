#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define READ 0	
#define WRITE 1

int main(int argc, char* argv[]) 
{
    char str[1024];
    char *command1, *command2;
    char *args1[100], *args2[100];
    int fd[2];

    printf("[shell] ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    if (strchr(str, '|') != NULL) {
        command1 = strtok(str, "|");
        command2 = strtok(NULL, "|");

        char *token = strtok(command1, " ");
        int i = 0;
        while (token != NULL) {
            args1[i++] = token;
            token = strtok(NULL, " ");
        }
        args1[i] = NULL;

        token = strtok(command2, " ");
        i = 0;
        while (token != NULL) {
            args2[i++] = token;
            token = strtok(NULL, " ");
        }
        args2[i] = NULL;

        pipe(fd);

        if (fork() == 0) {
            close(fd[READ]);
            dup2(fd[WRITE], STDOUT_FILENO);
            close(fd[WRITE]);
            execvp(args1[0], args1);
            perror("execvp");
            exit(1);
        } else {
            close(fd[WRITE]);
            dup2(fd[READ], STDIN_FILENO);
            close(fd[READ]);
            execvp(args2[0], args2);
            perror("execvp");
            exit(1);
        }
    } else {
        execvp(argv[1], &argv[1]);
        perror("execvp");
    }

    return 0;
}

