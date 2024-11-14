#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//Values that can be adjusted
#define ARRAY_SIZE 10
#define MAX_STRING_LENGTH 17
#define LEXICON_SIZE 7521

//There is a trade off here, the larger we make the table the less linear probing we will have to do, but the more memory we will use
//I chose to minimize the memory usage by only having 15000 elements in the table
#define TABLE_SIZE 15000

#define boostFactor 0.293
#define negationConstant -0.5

#define positiveCount 11
#define negativeCount 9
#define negationCount 13

char* positiveIntensifiers[positiveCount] = {"absolutely", "completely", "extremely", "really", "so", "totally", "very", "particulary", "exceptionally", 
"incredibly", "remarkably"};

char* negativeIntensifiers[negativeCount] = {"barely", "hardly", "scarcely", "somewhat", "mildly", "slightly", "partially",
"fairly", "pretty much"};

char* negations[negationCount] = {"not", "isn't", "doesn't", "wasn't", "shouldn't", "won't", "cannot", "can't",
"nor", "neither", "without", "lack", "missing"};

typedef struct {
    char word[MAX_STRING_LENGTH];
    float meanSentiment; //Mean sentiment value
    float standardDeviation; //Standard deviation
    int intArray[ARRAY_SIZE]; //Array of sentiment ratings
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

void parseLexicon(bool verbose) {
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

                if (verbose) {
                    printf("Collision detected at index %lu \n", hashed_location);
                    printf("\n Performing linear probing...\n");
                }

                while (lexicon[hashed_location] != NULL) {
                    hashed_location++;
                    hashed_location = hashed_location % TABLE_SIZE;
                }

                if (verbose) {
                    printf("New hashed location: %lu\n", hashed_location);
                }
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

            if (verbose) {
                printf("lexicon[%lu] = %s\n", hashed_location, lexicon[hashed_location]->word);
            }  

        }

        else {
            printf("Parsing failure, exiting program...");
            exit(1);

        }
    }
    fclose(file);
}

void freeTokens(char** tokens, int tokenCount) {
    for (int i = 0; i < tokenCount; i++) {
        free(tokens[i]); 
    }
    free(tokens);
}

void printTokenList(char** list, int tokenCount) {

    printf("[");

    for (int i = 0; i < tokenCount-1; i++) {
        printf("%s, ",list[i]);
    }

    printf("%s", list[tokenCount-1]);
    printf("]");
}

//Custom tokenization function that will require reallocation of memory
char** tokenization(char * sentence, int size, int* tokenCount) {

    int tokenSize = 10;

    int totalTokenLengthCount = 0;

    char** tokens = (char **)malloc(tokenSize*sizeof(char*));

    if (tokens==NULL) {
        printf("Error in tokenization memory allocation");
        exit(1);
    }

    int index = 0;
    int tokenLength = 0;
    char delimeter = ' ';

    while (sentence[index] != '\0') {

        printf("%c\n",sentence[index]);
        
        //Just in case there is a space first && > 0
        if(sentence[index] == delimeter && tokenLength > 0) {

            totalTokenLengthCount += tokenLength;

            char* token = (char *)malloc((tokenLength+1)*sizeof(char));

            if (token == NULL) {
                printf("Memory allocation error when creating individual tokens...");
                freeTokens(tokens, *tokenCount);
                exit(1);
            }

            strncpy(token, &sentence[index-tokenLength], tokenLength);

            token[tokenLength] = '\0';

            printf("token:%s\n\n", token);


            //We need to reallocate the tokens array if we run into a size error:

            if (*tokenCount == tokenSize) {
                tokenSize *= 2;
                tokens = (char **)realloc(tokens, tokenSize * sizeof(char*));
                if (tokens == NULL) {
                    printf("Error in reallocating token array memory");
                    freeTokens(tokens, *tokenCount);
                    exit(1);
                }
            }

            tokens[*tokenCount] = token;
            tokenLength = 0; 

            (*tokenCount)++;
        }
        else {
            tokenLength++;
        }
        index++;

    }

    printf("Total token length count: %d", totalTokenLengthCount);

    //Grab the last token if the last character is not our delimeter
    if (totalTokenLengthCount < size - 1) {

        char* token = (char *)malloc((tokenLength+1)*sizeof(char));
        if (token == NULL) {
            printf("Memory allocation error when creating the last token...");
            freeTokens(tokens, *tokenCount);
            exit(1);
        }

        strncpy(token, &sentence[index-tokenLength], tokenLength);

        tokens[*tokenCount] = token;

        (*tokenCount)++;

    }

    printTokenList(tokens, *tokenCount);

    return tokens;

}

//This function needs to be updated to account for punctuation, caps, negation
double sentimentCalculation(char* testWord, double *intensifierScore ) {

    double wordScore = 0;

    for (int i = 0; i < LEXICON_SIZE; i++) {
        if (lexicon[i]->word == testWord) {

            double sentimentValue = lexicon[i]->meanSentiment;

            wordScore = *intensifierScore*sentimentValue + sentimentValue;

            *intensifierScore = 0;

            for (int j = 0; j < positiveCount; j++) {
                if (lexicon[i]->word == positiveIntensifiers[j]) {
                    *intensifierScore = 0.293;
                }
            }
            if(*intensifierScore == 0) {
                for (int k = 0; k < negativeCount; k++) {
                    if (lexicon[i]->word == negativeIntensifiers[k]) {
                        *intensifierScore = 0.293;
                    }
                }
            }

            return wordScore;
        } 
        else {
            continue;
        }
    }

    //If the word was not found in the lexicon return 0
    return 0;

}

double compoundSentimentScoreCalculation(char** tokens, int sentenceLength) {

    double intensifierScore = 0;

    double totalScore = 0;

    for (int i = 0; i < sentenceLength; i++) {
        totalScore += sentimentCalculation(tokens[i], &intensifierScore);
    }

    double compoundScore = totalScore/sqrt(totalScore*totalScore +15);

    return compoundScore;

}

WordData* findWord(char* word) {

    unsigned long tempWordPosition = hash(word) % TABLE_SIZE;

    if (lexicon[tempWordPosition] != NULL && strcmp(lexicon[tempWordPosition]->word, word) == 0) {
        return lexicon[tempWordPosition];
    }
    else {

        int index = 0;

        char* tempWord = lexicon[tempWordPosition]->word;

        while (lexicon[tempWordPosition] != NULL && strcmp(tempWord, word) != 0) {
            tempWordPosition++;

            //So that it rolls over if its out of bounds
            tempWordPosition = tempWordPosition % TABLE_SIZE;
            if (lexicon[tempWordPosition] != NULL && strcmp(lexicon[tempWordPosition]->word, word) == 0) {
                return lexicon[tempWordPosition];
            }
            else {
                index++;
                if (index > TABLE_SIZE) {
                    break;
                }
            }
            
        }
    }

    return lexicon[tempWordPosition];
}

int main(void) {

    //This can be set to true to show how the code works
    bool excessPrinting = true;

    parseLexicon(excessPrinting);

    int tokenCount = 0;
    
    char sentence[] = {"This is a sentence?!"};

    char** tokens = tokenization(sentence, 18, &tokenCount);

    int lexiconSize = sizeof(lexicon)/sizeof(WordData *);

    printf("\n\nThe value is %s\n", lexicon[7524]->word);

    printf("\nThe hashtable size is: %d", lexiconSize);

    WordData* foundWord = findWord("wise");

    if (foundWord != NULL) {
        printf("\n\nThe word is %s\n", foundWord->word);
    } else {
        printf("\n\nWord not found\n");
    }

    freeTokens(tokens, tokenCount);

}