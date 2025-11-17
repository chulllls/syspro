#include <stdio.h>
#include <stdlib.h>
#include "bookdata.h"
BookRecord books[100]; 
int book_count = 0;
void print_header() {
    printf("id bookname author year numofborrow borrowable\n");
}

void print_record(const BookRecord *rec) {
    printf("%d %s %s %d %d %s\n", 
           rec->id, 
           rec->bookname, 
           rec->author, 
           rec->year, 
           rec->numofborrow, 
           rec->borrowable ? "True" : "False");
}
