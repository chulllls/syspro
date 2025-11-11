#ifndef BOOKDATA_H
#define BOOKDATA_H

#define MAX_BOOKS 100 

typedef struct {
    int id;
    char bookname[50];
    char author[50];
    int year;
    int numofborrow; 
    int borrowable;  
} BookRecord;

#endif
