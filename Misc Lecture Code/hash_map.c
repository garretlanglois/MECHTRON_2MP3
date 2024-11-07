#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct {
    int key;
    int value;
} HashEntry;

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void insert(int key, int value, HashEntry **hashTable) {
    int index = hashFunction(key);
    HashEntry *entry = (HashEntry *)malloc(sizeof(HashEntry));
    entry -> key = key;
    entry -> value = value;
    hashTable[index] = entry;
}

void freeHashTable(HashEntry **hashTable) {

    for (int i = 0; i < TABLE_SIZE; i++) {
        if(hashTable[i] != NULL) {
            free(hashTable[i]);
        }
    }

    free(hashTable);

}

int main(void) {

    //Important to recognize that this is a pointer to a pointer
    HashEntry **hashTable = malloc(TABLE_SIZE*sizeof(HashEntry));

    insert(1, 3, hashTable);
    printf("Value at key 1 is %d", hashTable[1]->value);

    freeHashTable(hashTable);
}