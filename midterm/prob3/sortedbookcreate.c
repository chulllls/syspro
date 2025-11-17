#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bookdata.h"

#define DB_FILE "db.dat"
extern BookRecord books[100];
extern int book_count;
int load_data(const char* filename, BookRecord list[]);
void save_data(const char* filename, BookRecord list[], int count);
void print_all_books(const BookRecord list[], int count, int show_available);

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
void print_header();
void print_record(const BookRecord *rec);

void print_all_books(const BookRecord list[], int count, int show_available) {
    printf("0: list of all books, 1: list of available books ) %d\n", show_available);
    print_header();

    for (int i = 0; i < count; i++) {
        if (!show_available || list[i].borrowable == 1) {
            print_record(&list[i]);
        }
    }
}

int compare_by_year_descending(const void *a, const void *b) {
    const BookRecord *bookA = (const BookRecord *)a;
    const BookRecord *bookB = (const BookRecord *)b;
    return bookB->year - bookA->year;
}

void save_data(const char* filename, BookRecord list[], int count) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) return;
    fwrite(list, sizeof(BookRecord), count, fp);
    fclose(fp);
}


int main() {
    int count = load_data(DB_FILE, books);
    if (count == 0) return 1;

    qsort(books, count, sizeof(BookRecord), compare_by_year_descending);

    save_data(DB_FILE, books, count);
    printf("Data saved to %s, sorted by year (descending).\n", DB_FILE);

    count = load_data(DB_FILE, books);

    printf("--bookquery--\n");
    print_all_books(books, count, 0);
    print_all_books(books, count, 1);

    return 0;
}
