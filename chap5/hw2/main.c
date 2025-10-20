#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 256

int main(int argc, char *argv[]) {
    char savedText[MAX_LINES][MAX_LINE_LENGTH];
    int line_count = 0;
    int char_idx = 0;
    int fd;
    char buf;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s [file_name].txt\n", argv[0]);
        return 1;
    }

    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        perror("File open error");
        return 1;
    }

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            if (line_count < MAX_LINES) {
                savedText[line_count][char_idx] = '\0';
                line_count++;
                char_idx = 0;
            } else {
                break;
            }
        } else {
            if (char_idx < MAX_LINE_LENGTH - 1) {
                savedText[line_count][char_idx] = buf;
                char_idx++;
            }
        }
    }

    if (char_idx > 0 && line_count < MAX_LINES) {
        savedText[line_count][char_idx] = '\0';
        line_count++;
    }
    
    close(fd);

    for (int i = line_count - 1; i >= 0; i--) {
        if (strlen(savedText[i]) > 0 || (i == line_count - 1 && line_count > 0 && char_idx == 0)) {
             printf("%s\n", savedText[i]);
        }
    }

    return 0;
}
