#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINE 100
#define MAX_LEN 256

int main(int argc, char *argv[]) {
    int fd;
    char buf;
    char savedText[MAX_LINE][MAX_LEN];
    int i = 0, j = 0;
    ssize_t nread;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [file_name]\n", argv[0]);
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("File open error");
        exit(1);
    }

    printf("File read success\n");

     while ((nread = read(fd, &buf, 1)) > 0) {
        if (buf == '\n') {
            savedText[i][j] = '\0';
            i++;
            j = 0;
        } else {
            savedText[i][j++] = buf;
        }
    }
    savedText[i][0] = '\0';
    close(fd);

    int total = i;
    printf("Total Line : %d\n", total);
    printf("You can choose 1 ~ %d Line\n", total);
    printf("Pls 'Enter' the line to select : ");

    char input[50];
    scanf("%s", input);

    if (strcmp(input, "*") == 0) {
        for (int k = 0; k < total; k++)
            printf("%s\n", savedText[k]);
    }
    else if (strchr(input, '-') != NULL) { 
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        if (start < 1) start = 1;
        if (end > total) end = total;
        for (int k = start - 1; k < end; k++)
            printf("%s\n", savedText[k]);
    }
    else if (strchr(input, ',') != NULL) { 
        char *token = strtok(input, ",");
        while (token != NULL) {
            int line = atoi(token);
            if (line >= 1 && line <= total)
                printf("%s\n", savedText[line - 1]);
            token = strtok(NULL, ",");
        }
    }
    else { 
        int n = atoi(input);
        if (n >= 1 && n <= total)
            printf("%s\n", savedText[n - 1]);
        else
            printf("Invalid line number.\n");
    }

    return 0;
}

