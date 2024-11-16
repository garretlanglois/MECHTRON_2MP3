#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEXICON_SIZE 7525

//There is a trade off here, the larger we make the table the less linear probing we will have to do, but the more memory we will use
//I chose to minimize the memory usage by only having 15000 elements in the table
#define TABLE_SIZE 15000

typedef struct {
    char word[17];
    float meanSentiment;
    float standardDeviation;
    int intArray[10];
} WordData;

WordData* lexicon[TABLE_SIZE];

unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

void parseLexicon() {
    FILE *file = fopen("vader_lexicon.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    for (int i = 0; i < LEXICON_SIZE; i++) {

        char wordToHash[17];

        float meanSentiment;
        float standardDeviation;

        int intArray[10];

        if (fscanf(file, "%16s %f %f [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]", wordToHash, &meanSentiment, &standardDeviation, 
        &intArray[0], &intArray[1], &intArray[2], &intArray[3], &intArray[4], &intArray[5], &intArray[6], &intArray[7], &intArray[8], &intArray[9])) {

            unsigned long hashed_location = hash(wordToHash) % TABLE_SIZE;

            //This fixes collisions, worst case scenario is O(n) where n is the number of elements in the table 
            if (lexicon[hashed_location] != NULL) {
                printf("Collision detected at index %lu \n", hashed_location);
                printf("\n Performing linear probing...\n");

                while (lexicon[hashed_location] != NULL) {
                    hashed_location++;
                    hashed_location = hashed_location % TABLE_SIZE;
                }

                printf("New hashed location: %lu\n", hashed_location);
            }

            lexicon[hashed_location] = malloc(sizeof(WordData));  // Allocate memory for each WordData entry
            if (lexicon[hashed_location] == NULL) {
                printf("Memory allocation failed\n");
                exit(1);
            }

            strcpy(lexicon[hashed_location]->word, wordToHash);
            lexicon[hashed_location]->meanSentiment = meanSentiment;
            lexicon[hashed_location]->standardDeviation = standardDeviation;

            //This is not O(n)
            for (int j = 0; j < 10; j++) {
                lexicon[hashed_location]->intArray[j] = intArray[j];
            }

            printf("lexicon[%lu] = %s\n", hashed_location, lexicon[hashed_location]->word);

        }

        else {
            printf("Parsing failure, exiting program...");
            exit(1);

        }
    }
}

/*
void parseLexicon() {
    FILE *file = fopen("vader_lexicon.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    for (int i = 0; i < LEXICON_SIZE; i++) {

        char wordToHash[17];

        if (fscanf(file, "%s %*f %*f [%*d, %*d, %*d, %*d, %*d, %*d, %*d, %*d, %*d, %*d]", wordToHash)) {

            unsigned long hashed_location = hash(wordToHash) % TABLE_SIZE;

            if (lexicon[hashed_location] != NULL) {
                printf("Collision detected at index %lu \n", hashed_location);
            }

            lexicon[hashed_location] = malloc(sizeof(WordData));  // Allocate memory for each WordData entry
            if (lexicon[hashed_location] == NULL) {
                printf("Memory allocation failed\n");
                exit(1);
            }

            if (fscanf(file, "%s %f %f [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]", lexicon[hashed_location]->word, &lexicon[hashed_location]->meanSentiment, &lexicon[hashed_location]->standardDeviation, 
            &lexicon[hashed_location]->intArray[0], &lexicon[hashed_location]->intArray[1], &lexicon[hashed_location]->intArray[2], &lexicon[hashed_location]->intArray[3], &lexicon[hashed_location]->intArray[4],
            &lexicon[hashed_location]->intArray[5], &lexicon[hashed_location]->intArray[6], &lexicon[hashed_location]->intArray[7],&lexicon[hashed_location]->intArray[8], &lexicon[hashed_location]->intArray[9])) {

                printf("lexicon[%d] = %s\n", i, lexicon[i]->word);

            }

            else {
                printf("Parsing failure, exiting program...");
                exit(1);
            }
        }


    }

    fclose(file);
}
*/


int main(void) {
    parseLexicon();

    for (int i = 0; i < LEXICON_SIZE; i++) {
        printf("lexicon[%d] = %s\n", i, lexicon[i]->word);
    }

    return 0;
}

