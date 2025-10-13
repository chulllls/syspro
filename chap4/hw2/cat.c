#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_file(FILE *fp, int show_number) {
    char line[1024];
    int line_num = 1;

    if (show_number) {
        while (fgets(line, sizeof(line), fp) != NULL) {
            printf("%6d  %s", line_num++, line);
        }
    } else {
        while (fgets(line, sizeof(line), fp) != NULL) {
            fputs(line, stdout);
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int show_number = 0;
    int start_index = 1;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-n] file1 [file2 ...]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-n") == 0) {
        show_number = 1;
        start_index = 2;
    }

    for (int i = start_index; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            perror(argv[i]);
            continue;  
        }

        print_file(fp, show_number);
        fclose(fp);
    }

    return 0;
}

