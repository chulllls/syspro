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

int main() {
    int mode, bookID;
    FILE *fp;
    BookRecord current_book;
    int record_found = 0;
    long record_position = -1;
    
    printf("입력 : ");
    if (scanf("%d %d", &mode, &bookID) != 2) {
        return 1;
    }

    fp = fopen("db.dat", "r+b");
    if (fp == NULL) {
        return 1;
    }

    while (fread(&current_book, sizeof(BookRecord), 1, fp) == 1) {
        if (current_book.id == bookID) {
            record_found = 1;
            record_position = ftell(fp) - sizeof(BookRecord); 
            break; 
        }
    }
    
    if (!record_found) {
        printf("\n--bookupdate--\n");
        fclose(fp);
        return 1;
    }
    
    printf("\n--bookupdate--\n");
    
    if (mode == 0) {
        if (current_book.borrowable == 0) {
            printf("0 bookID: borrow book, 1 bookID: return book ) 0 %d\n", bookID);
            printf("You cannot borrow bellow book since it has been booked.\n");
            printf("id bookname author year numofborrow borrow\n");
            printf("%d %s %s %d %d %s\n", 
                   current_book.id, 
                   current_book.bookname, 
                   current_book.author, 
                   current_book.year, 
                   current_book.numofborrow, 
                   current_book.borrowable ? "True" : "False");
        } 
        else {
            current_book.borrowable = 0; 
            current_book.numofborrow += 1; 

            fseek(fp, record_position, SEEK_SET);
            fwrite(&current_book, sizeof(BookRecord), 1, fp);
            
            printf("0 bookID: borrow book, 1 bookID: return book ) 0 %d\n", bookID);
            print_record_header_and_content(&current_book, 0);
        }
    } 
    else if (mode == 1) {
        current_book.borrowable = 1; 

        fseek(fp, record_position, SEEK_SET);
        fwrite(&current_book, sizeof(BookRecord), 1, fp);

        printf("0 bookID: borrow book, 1 bookID: return book ) 1 %d\n", bookID);
        print_record_header_and_content(&current_book, 1);
    }
    
    if (fp != NULL) fclose(fp);
    return 0;
}
