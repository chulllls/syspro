#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *src, *dst;
    int ch;

    if (argc != 3) {
        fprintf(stderr, "How to use:%s FileName\n", argv[0]);
        return 1;
    }

    src = fopen(argv[1], "r");
    if (src == NULL) {
        perror("fopen");
        return 1;
    }

    dst = fopen(argv[2], "a");
    if (dst == NULL) {
        perror("getc");
        fclose(src);
        return 1;
    }

    while ((ch = fgetc(src)) != EOF)
        fputc(ch, dst);

    fclose(src);
    fclose(dst);

    return 0;
}

