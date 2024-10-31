#include <stdio.h>

//This file is incomplete

#define MAX_BB 2
#define MAX_NAME 50
#define MAX_BOOKS 10
#define MAX_MEMBERS

struct Book {
    char title[MAX_NAME];
    char author [MAX_NAME];
    int publicationYear;
};


struct LibraryMember {
    char name[MAX_NAME];
    int id; 
    struct Book borrowedBooks[MAX_BB];
    int numBorrowedBooks;
};

void borrowBook(struct LibraryMember *member, struct Book book) {
    if (member->numBorrowedBooks < MAX_BB) {
        member -> borrowedBooks[member->numBorrowedBooks] = book;
        member -> numBorrowedBooks++;
    }
}