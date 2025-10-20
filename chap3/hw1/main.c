#include <stdio.h>
#include <string.h>
#include "copy.h"

#define NUM 5
char lines[NUM][MAXLINE];

int main() {
    int i, j;
    char temp[MAXLINE];

    printf("%d\n", NUM);
    for (i = 0; i < NUM; i++) {
        fgets(lines[i], MAXLINE, stdin);
        lines[i][strcspn(lines[i], "\n")] = '\0';
    }

    for (i = 0; i < NUM - 1; i++) {
        for (j = 0; j < NUM - i - 1; j++) {
            if (strlen(lines[j]) < strlen(lines[j+1])) {
                copy(lines[j], temp);
                copy(lines[j+1], lines[j]);
                copy(temp, lines[j+1]);
            }
        }
    }

    for (i = 0; i < NUM; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}

