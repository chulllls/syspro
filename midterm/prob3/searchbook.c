#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bookdata.h"

#define DB_FILE "db.dat"
#define INPUT_LEN 100
extern BookRecord books[100];
extern int book_count;
int load_data(const char* filename, BookRecord list[]);
void print_header();
void print_record(const BookRecord *rec);

int load_data(const char* filename, BookRecord list[]) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return 0;
    int count = 0;
    while (fread(&list[count], sizeof(BookRecord), 1, fp) == 1 && count < 100) {
        count++;
    }
    fclose(fp);
    return count;
}

int main() {
    char input_bookname[INPUT_LEN];
    bool found = false;

    int count = load_data(DB_FILE, books);
    if (count == 0) return 1;

    printf("input name of book ) ");
    if (scanf("%s", input_bookname) != 1) return 1;

    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].bookname, input_bookname) == 0) {
            if (!found) {
                print_header();
            }
            print_record(&books[i]);
            found = true;
        }
    }

    if (!found) {
        printf("not found book name: '%s'\n", input_bookname);
    }

    return 0;
}
