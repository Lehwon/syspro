#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LINES 10
#define MAX_LENGTH 100

void print_lines(char savedText[MAX_LINES][MAX_LENGTH], int total_lines) {
    char input[50];
    printf("You can choose 1 ~ %d Line: ", total_lines);
    fgets(input, sizeof(input), stdin);

    if (strcmp(input, "*\n") == 0) {
        for (int i = 0; i < total_lines; i++)
            printf("%s\n", savedText[i]);
    } else {
        char *token = strtok(input, ", ");
        while (token) {
            if (strchr(token, '-')) {
                int start, end;
                sscanf(token, "%d-%d", &start, &end);
                for (int i = start; i <= end && i <= total_lines; i++)
                    printf("%s\n", savedText[i - 1]);
            } else {
                int line;
                sscanf(token, "%d", &line);
                if (line > 0 && line <= total_lines)
                    printf("%s\n", savedText[line - 1]);
                else
                    printf("Invalid line number: %d\n", line);
            }
            token = strtok(NULL, ", ");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("File read success");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    char savedText[MAX_LINES][MAX_LENGTH];
    int total_lines = 0;
    char ch;
    int line_index = 0;
    int char_index = 0;

    while (total_lines < MAX_LINES && read(fd, &ch, 1) > 0) {
        if (ch == '\n') {
            savedText[total_lines][char_index] = '\0';
            total_lines++;
            char_index = 0;
        } else {
            if (char_index < MAX_LENGTH - 1) {
                savedText[total_lines][char_index++] = ch;
            }
        }
    }

    close(fd);

    if (total_lines > 0) {
        printf("Total lines: %d\n", total_lines);
        print_lines(savedText, total_lines);
    } else {
        printf("The file is empty or has no content.\n");
    }

    return 0;
}
