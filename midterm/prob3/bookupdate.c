#include <stdio.h>
#include <stdlib.h>
#include "bookdata.h"

void print_record_header_and_content(const BookRecord *rec, int success_mode) {
    if (success_mode == 0) {
        printf("You've got bellow book..\n");
    } else {
        printf("You've returned bellow book..\n");
    }

    printf("id bookname author year numofborrow borrow\n");
    printf("%d %s %s %d %d %s\n", 
           rec->id, 
           rec->bookname, 
           rec->author, 
           rec->year, 
           rec->numofborrow, 
           rec->borrowable ? "True" : "False");
}
