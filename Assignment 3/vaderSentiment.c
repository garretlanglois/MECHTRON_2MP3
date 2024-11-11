#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Values that can be adjusted
#define ARRAY_SIZE 10
#define MAX_STRING_LENGTH 17
#define LEXICON_SIZE 7525
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

WordData* lexicon[LEXICON_SIZE];


void parseLexicon() {
    FILE *file = fopen("vader_lexicon.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    for (int i = 0; i < LEXICON_SIZE; i++) {
        lexicon[i] = malloc(sizeof(WordData));  // Allocate memory for each WordData entry
        if (lexicon[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }

        //To save memory we can dynamically change the size of the word in the struct: 

        //This is the original way I had the code made, but when analyzing memory usage it was less efficient, I don't know why
        /*
        if (fscanf(file, "%s %f %f [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]", buffer, &lexicon[i]->meanSentiment, &lexicon[i]->standardDeviation, 
        &lexicon[i]->intArray[0], &lexicon[i]->intArray[1], &lexicon[i]->intArray[2], &lexicon[i]->intArray[3], &lexicon[i]->intArray[4],
        &lexicon[i]->intArray[5], &lexicon[i]->intArray[6], &lexicon[i]->intArray[7],&lexicon[i]->intArray[8], &lexicon[i]->intArray[9])) {

            int size = strlen(buffer)+1;//For the /0 thing

            lexicon[i]->word = malloc(size*sizeof(char));
            if (lexicon[i]->word == NULL) {
                printf("Memory allocation failed");
                exit(1);
            }

            strcpy(lexicon[i]->word, buffer);

            //printf("%s\n", lexicon[i]->word);


        }
        */

        //This method uses the fixed size for the word.+
        if (fscanf(file, "%s %f %f [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]", lexicon[i]->word, &lexicon[i]->meanSentiment, &lexicon[i]->standardDeviation, 
        &lexicon[i]->intArray[0], &lexicon[i]->intArray[1], &lexicon[i]->intArray[2], &lexicon[i]->intArray[3], &lexicon[i]->intArray[4],
        &lexicon[i]->intArray[5], &lexicon[i]->intArray[6], &lexicon[i]->intArray[7],&lexicon[i]->intArray[8], &lexicon[i]->intArray[9])) {

            printf("lexicon[%d] = %s\n", i, lexicon[i]->word);

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

int main(void) {


    parseLexicon();

    int tokenCount = 0;
    
    char sentence[] = {"This is a sentence?!"};

    char** tokens = tokenization(sentence, 18, &tokenCount);

    int lexiconSize = sizeof(lexicon)/sizeof(WordData *);

    printf("\n\nThe value is %s\n", lexicon[7524]->word);

    printf("\nThe lexicon size is: %d", lexiconSize);

    freeTokens(tokens, tokenCount);

}