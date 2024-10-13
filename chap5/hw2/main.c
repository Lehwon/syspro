#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LINES 10
#define MAX_LENGTH 100

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    char savedText[MAX_LINES][MAX_LENGTH];
    int total_lines = 0;
    char ch;
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

    for (int i = total_lines - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }

    return 0;
}

