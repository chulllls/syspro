#include <stdio.h>
#include <stdlib.h>
#include "bookdata.h"

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

int main(int argc, char *argv[]) {
    int mode;
    FILE *fp;
    BookRecord current_book;
    
    if (argc != 2) {
        return 1;
    }
    
    mode = atoi(argv[1]);
    if (mode != 0 && mode != 1) {
        return 1;
    }

    fp = fopen("db.dat", "rb");
    if (fp == NULL) {
        return 1;
    }

    printf("\n--bookquery--\n");
    if (mode == 0) {
        printf("0: list of all books\n");
    } else {
        printf("1: list of available books\n");
    }
    
    print_header();

    while (fread(&current_book, sizeof(BookRecord), 1, fp) == 1) {
        if (mode == 0) {
            print_record(&current_book);
        } else {
            if (current_book.borrowable == 1) {
                print_record(&current_book);
            }
        }
    }
    
    fclose(fp);
    return 0;
}
