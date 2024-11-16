//The headers are included in this file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

//Define everything that can be modified in the program
#define ARRAY_SIZE 10
#define MAX_STRING_LENGTH 17

//This needs to be edited
#define LEXICON_SIZE 7521
#define TABLE_SIZE 15000
#define PUNCTUTATION_BOOST 0.292
#define boostFactor 0.293
#define negationConstant -0.5
#define positiveCount 11
#define negativeCount 9
#define negationCount 13

//Define the WordData struct
typedef struct {
    char word[MAX_STRING_LENGTH];
    float meanSentiment;
    float standardDeviation;
    int intArray[ARRAY_SIZE];
} WordData;

//Define the "function prototypes"
extern WordData* lexicon[TABLE_SIZE];
void parseLexicon(bool verbose);
void freeTokens(char** tokens, int tokenCount);
void printTokenList(char** list, int tokenCount);
char** tokenization(char* sentence, int size, int* tokenCount);
WordData* findWord(char* word);
double sentimentCalculation(char* testWord, double *intensifierScore, double *negationScore);
double compoundSentimentScoreCalculation(char** tokens, int sentenceLength);
unsigned long hash(char* str);