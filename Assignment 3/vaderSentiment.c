//Define the header which includes the functions and includes
#include "utility.h"

//Define the hashtable lexicon array
WordData* lexicon[TABLE_SIZE];

//Define the positive intensifiers from the list given in the assignment
char* positiveIntensifiers[positiveCount] = {"absolutely", "completely", "extremely", "really", "so", "totally", "very", "particulary", "exceptionally", 
"incredibly", "remarkably"};

//Define the negative intensifiers from the list given in the assignment
char* negativeIntensifiers[negativeCount] = {"barely", "hardly", "scarcely", "somewhat", "mildly", "slightly", "partially",
"fairly", "pretty much"};

//Define the negations from the list given in the assignment
char* negations[negationCount] = {"not", "isn't", "doesn't", "wasn't", "shouldn't", "won't", "cannot", "can't",
"nor", "neither", "without", "lack", "missing"};

//To make the the time complexity of the hash table O(1) we can use the djb2 hash function
//This is a hash function that I found online that is very fast

//The hash function starts by accepting the word that we want to hash
unsigned long hash(char *str) {

    //This is the seed
    unsigned long hash = 5381;
    int c;

    //This is the bit manipulation for the characters to create a unique hash
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    //This returns the hash from the function call
    //It is a unsigned long because the function returns a large value
    //This will later be remedied by the modulo operator
    return hash;
}

//Now we define a function to parse the lexicon and convert all of the words in wordData
void parseLexicon(bool verbose) {

    //Open the file
    FILE *file = fopen("vader_lexicon.txt", "r");

    //Check to see if the file opening failed
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    //Iterate through the file and parse the data
    for (int i = 0; i < LEXICON_SIZE; i++) {

        //We will start by reading the data and saving the values in the line to temporary values which are defined below
        //Then the word will be hashed to determine the index locaiton in the hash table and it will be saved as a WordData struct
        
        char wordToHash[17];
        float meanSentiment;
        float standardDeviation;
        int intArray[10];

        //This the fscanf function that reads the data from the file
        //There might be a more concise way to accomplish this but this increases readability
        if (fscanf(file, "%16s %f %f [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]", wordToHash, &meanSentiment, &standardDeviation, 
        &intArray[0], &intArray[1], &intArray[2], &intArray[3], &intArray[4], &intArray[5], &intArray[6], &intArray[7], &intArray[8], &intArray[9])) {

            //Hash the word to determine the index location
            unsigned long hashed_location = hash(wordToHash) % TABLE_SIZE;

            //This fixes collisions, worst case scenario is O(n) where n is the number of elements in the table 
            if (lexicon[hashed_location] != NULL) {

                //This allows for all of the print statements to be controlled
                if (verbose) {
                    printf("Collision detected at index %lu \n", hashed_location);
                    printf("\n Performing linear probing...\n");
                }

                //The linear probing is done by incrementing the index by 1 and then taking the modulo of the table size
                while (lexicon[hashed_location] != NULL) {
                    hashed_location++;
                    hashed_location = hashed_location % TABLE_SIZE;
                }

                //We can print out the new hashed location
                if (verbose) {
                    printf("New hashed location: %lu\n", hashed_location);
                }
            }

            //Now, as previously stated, we can place all of the data into the hash table
            //This starts with allocating memory for the WordData struct and then copying the data into the struct
            lexicon[hashed_location] = malloc(sizeof(WordData));

            //Check to see if the memory allocation failed
            if (lexicon[hashed_location] == NULL) {
                printf("Memory allocation failed\n");
                exit(1);
            }

            //Copy the data into the struct
            strcpy(lexicon[hashed_location]->word, wordToHash);
            lexicon[hashed_location]->meanSentiment = meanSentiment;
            lexicon[hashed_location]->standardDeviation = standardDeviation;

            //This does not effect the time complexity as it is constant time with sizing the lexicon
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

//This function frees the tokens that were created in the tokenization function
void freeTokens(char** tokens, int tokenCount) {
    //Iterate through the tokens and free them
    for (int i = 0; i < tokenCount; i++) {
        free(tokens[i]); 
    }
    //Free the tokens array
    free(tokens);
}

//This function prints the token list
void printTokenList(char** list, int tokenCount) {

    printf("[");

    for (int i = 0; i < tokenCount-1; i++) {
        printf("%s,",list[i]);
    }

    printf("%s", list[tokenCount-1]);
    printf("]");
}

//Custom tokenization function that will require reallocation of memory
char** tokenization(char * sentence, int size, int* tokenCount) {

    //Defines some dummy values to be modified
    int tokenSize = 10;
    int totalTokenLengthCount = 0;

    //Allocate memory for the tokens
    char** tokens = (char **)malloc(tokenSize * sizeof(char*));

    //Check to see if the memory allocation failed
    if (tokens == NULL) {
        printf("Error in tokenization memory allocation");
        exit(1);
    }


    int index = 0;
    int tokenLength = 0;
    char delimeter = ' ';

    //Iterate through the sentence and create tokens
    while (sentence[index] != '\0') {

        //We need to check for delimeters and remove different parts of sentences
        if ((sentence[index] == delimeter || sentence[index] == ',') && tokenLength > 0) {

            //Allocate memory for the individual token
            totalTokenLengthCount += tokenLength;
            char* token = (char *)malloc((tokenLength + 1) * sizeof(char));

            //Check to see if the memory allocation failed
            if (token == NULL) {
                printf("Memory allocation error when creating individual tokens...");
                freeTokens(tokens, *tokenCount);
                exit(1);
            }

            //Copy the token into the allocated memory
            strncpy(token, &sentence[index - tokenLength], tokenLength);
            token[tokenLength] = '\0';

            //Remove spaces in token
            while (*token == ' ') {
                memmove(token, token + 1, strlen(token));
            }

            // Reallocate the tokens array if it runs out of space
            if (*tokenCount == tokenSize) {
                // Double the token array size so that there will always be enough space
                tokenSize *= 2;
                tokens = (char **)realloc(tokens, tokenSize * sizeof(char*));
                if (tokens == NULL) {
                    printf("Error in reallocating token array memory");
                    freeTokens(tokens, *tokenCount);
                    exit(1);
                }
            }

            //Add the token to the tokens array
            tokens[*tokenCount] = token;
            tokenLength = 0; 

            //Increment the token count
            (*tokenCount)++;

            //Skip any extra spaces or commas after the token
            while (sentence[index] == ' ' || sentence[index] == ',') {
                index++;
            }
            continue; //Skip the regular index increment to avoid missing characters
        } else if (sentence[index] != ',') {
            tokenLength++;
        }
        index++;
    }

    //Handle the last token
    if (totalTokenLengthCount < size - 1) {

        //Allocate memory for the last token
        char* token = (char *)malloc((tokenLength + 1) * sizeof(char));
        if (token == NULL) {
            printf("Memory allocation error when creating the last token...");
            freeTokens(tokens, *tokenCount);
            exit(1);
        }

        //Copy the last token into the allocated memory
        strncpy(token, &sentence[index - tokenLength], tokenLength);
        token[tokenLength] = '\0';

        //Remove spaces in token
        while (*token == ' ') {
            memmove(token, token + 1, strlen(token));
        }

        tokens[*tokenCount] = token;
        (*tokenCount)++;
    }

    //Print and return the tokens
    printTokenList(tokens, *tokenCount);
    return tokens;
}

//This function converts the word to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {

        //This comes from one of the included headers
        str[i] = tolower(str[i]);
    }
}

//This function finds the word in the lexicon
WordData* findWord(char* word) {

    //Convert the word to lowercase because all of the words in the lexicon are lowercase
    to_lowercase(word);

    //Hash the word to determine the index location
    unsigned long tempWordPosition = hash(word) % TABLE_SIZE;

    //Print the hashed location if you want
    //printf("Hashed location: %lu\n", tempWordPosition);

    //Check the initial hashed location for a match
    if (lexicon[tempWordPosition] != NULL && strcmp(lexicon[tempWordPosition]->word, word) == 0) {
        return lexicon[tempWordPosition];
    }

    //Perform linear probing for a match within a set range if the initial hashed location does not match
    //There is a very low chance that the word will not be found within the first 10 checks
    int index = 0;
    while (index < 10) {

        //Increment position modulo the table size
        tempWordPosition = (tempWordPosition + 1) % TABLE_SIZE;

        //Check for match at the new position
        if (lexicon[tempWordPosition] != NULL && strcmp(lexicon[tempWordPosition]->word, word) == 0) {
            return lexicon[tempWordPosition];
        }

        index++;
    }

    //If word not found after probing, return NULL
    return NULL;
}

//This function calculates the sentiment of the word
double sentimentCalculation(char* testWord, double *intensifierScore ) {


    //Create a dummy word to store the original word, this way when it is lowercased we still have an OG copy to check all caps against
    char dummyWord[100];
    strcpy(dummyWord, testWord);

    //Variable to store the score of the word
    double wordScore = 0;

    //Variable to store the number of exclamation points
    int exclamation_count = 0;

    //We first need to check if the word has any punctuation attached to it
    //If it does we need to remove it
    for (size_t i = 0; i < strlen(testWord); i++) {
        if (testWord[i] == '.' || testWord[i] == ',' || testWord[i] == '?' || testWord[i] == ';' || testWord[i] == ':') {
            testWord[i] = '\0';
        }
        //If it has an exclamation point we need to boost the score
        else if (testWord[i] == '!' && exclamation_count<= 3) {
            wordScore += PUNCTUTATION_BOOST;
            testWord[i] = '\0';
            exclamation_count++;
        }
    }

    //Get the word data from the lexicon, this is O(1)
    WordData* wordData = findWord(testWord);

    //If the word is in the lexicon we can calculate the sentiment
    if (wordData != NULL) {

        //Get the sentiment value from the word data
        double sentimentValue = wordData->meanSentiment;

        //Add the sentiment value to the word score, inclusive of any previous intensifiers
        wordScore += *intensifierScore*sentimentValue + sentimentValue;

        //Check if the word is negated
        int isNegated = 0;
        for (int l = 0; l < negationCount; l++) {
            if (strcmp(wordData->word, negations[l]) == 0) {
                isNegated = 1;
                break;
            }
        }

        //If the word is negated we need to multiply the score by the negation constant, which is defined in the utility header
        if (isNegated) {
            wordScore *= negationConstant;
        }


        //printf("Checking if %s is all caps...\n", testWord);

        //Check if the word is all caps
        int isAllCaps = 1;
        for (size_t m = 0; m < strlen(dummyWord); m++) {

            //This was from ChatGPT
            if (dummyWord[m] < 65 || dummyWord[m] > 90) {
                printf("Not all caps\n");
                isAllCaps = 0;
                break;
            }
        }

        //If the word is all caps we need to boost the score
        if (isAllCaps) {
            wordScore *= 1.5;
        }

        //Reset the intensifier score
        *intensifierScore = 0;

        //Return the word score
        return wordScore;

    }

    //Even if the word is not in the lexicon we can still check if it is an intensifier
   *intensifierScore = 0;

   //Convert the word to lowercase
   to_lowercase(testWord);

    //Check if the word is an intensifier
    for (int j = 0; j < positiveCount; j++) {
        if (strcmp(testWord, positiveIntensifiers[j]) == 0) {
            *intensifierScore = boostFactor;
        }
    }

    //Check if the word is a negative intensifier
    if(*intensifierScore == 0) {
        for (int k = 0; k < negativeCount; k++) {
            if (strcmp(testWord, negativeIntensifiers[k]) == 0) {
                *intensifierScore = boostFactor;
            }
        }
    }

    //Return 0 if the word is not in the lexicon
    return 0;

}

//This function calculates sentiment score for the whole sentence
double compoundSentimentScoreCalculation(char** tokens, int sentenceLength) {

    //Variable to store the intensifier score
    double intensifierScore = 0;

    //Variable to store the total score
    double totalScore = 0;

    //Iterate through the tokens and calculate the individual sentiment scores
    for (int i = 0; i < sentenceLength; i++) {
        double addScore = sentimentCalculation(tokens[i], &intensifierScore);
        totalScore += addScore;
    }

    //Calculate the compound score
    double compoundScore = totalScore/sqrt(totalScore*totalScore +15);

    //Return the compound score
    return compoundScore;

}