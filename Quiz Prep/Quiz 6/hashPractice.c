//Hash table with linkedList for collisions!

#include <stdlib.h>
#include <stdio.h>

#define SIZE 20

typedef struct HashEntry { 
    int value;
    int key;
    struct HashEntry* next;
} HashEntry;

HashEntry* hashTable[SIZE];

int hash(int value) {
    return value % 20;
}

//New value

void addValue(int value) {

    int hashedPosition = hash(value);

    HashEntry* tableValue = hashTable[hashedPosition];

    if (tableValue != NULL) {

        HashEntry* tmp = hashTable[hashedPosition]->next;

        HashEntry* previous = NULL;

        while (tmp != NULL) {
            previous = tmp;
            tmp = tmp->next;
        }

        tmp->next = malloc(sizeof(struct HashEntry));

        tmp->next->value = value;
        tmp->next->next = NULL;
    }
    else {
        tableValue->next = NULL;
        tableValue->value = value;
    }

}

int main(void) {

    int value = 63;
    addValue(value);

    int hashedPosition = hash(value);

    printf("The value at the hashed position is %d\n", hashTable[hashedPosition]->value);

}