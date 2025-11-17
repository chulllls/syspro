#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bookdata.h"

int main() {
    FILE *fp;
    BookRecord new_book;
    char input_buffer[5];
    int i;
    
    fp = fopen("db.dat", "wb");
    
    if (fp == NULL) {
        return 1;
    }

    for (i = 0; i < 4; i++) {
        
        scanf("%d", &new_book.id);
        scanf("%s", new_book.bookname);
        scanf("%s", new_book.author);
        scanf("%d", &new_book.year);
        scanf("%d", &new_book.numofborrow);
        scanf("%s", input_buffer);

        if (strcmp(input_buffer, "True") == 0) {
            new_book.borrowable = 1;
        } else if (strcmp(input_buffer, "False") == 0) {
            new_book.borrowable = 0;
        } else {
            new_book.borrowable = 0;
        }

        if (fwrite(&new_book, sizeof(BookRecord), 1, fp) != 1) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
