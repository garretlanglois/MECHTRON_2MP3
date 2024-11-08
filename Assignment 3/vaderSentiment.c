#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printTokenList(char** list, int tokenCount) {

    printf("[");

    for (int i = 0; i < tokenCount; i++) {
        printf("%s, ",list[i]);
    }
    printf("]");
}

//Custom tokenization function that will require reallocation of memory
char** tokenization(char * sentence, int size) {

    int tokenSize = 10;
    int tokenCount = 0;

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
                exit(1);
            }

            strncpy(token, &sentence[index-tokenLength], tokenLength);

            token[tokenLength] = '\0';

            printf("token:%s\n\n", token);


            //We need to reallocate the tokens array if we run into a size error:

            if (tokenCount == tokenSize) {
                tokenSize *= 2;
                tokens = (char **)realloc(tokens, tokenSize * sizeof(char*));
                if (tokens == NULL) {
                    printf("Error in reallocating token array memory");
                    exit(1);
                }
            }

            tokens[tokenCount] = token;
            tokenLength = 0; 

            tokenCount++;
        }
        else {
            tokenLength++;
        }
        index++;

    }

    printf("Total token length count: %d", totalTokenLengthCount);

    //Grab the last token if the last character is not our delimeter
    if (totalTokenLengthCount < size - 1) {

        char* token = (char *)malloc((tokenLength+1-3)*sizeof(char));

        strncpy(token, &sentence[index-tokenLength], tokenLength-3);

        tokens[tokenCount] = token;

        tokenCount++;

    }

    printTokenList(tokens, tokenCount);

    return tokens;

}

int main(void) {
    
    char sentence[18] = {"This is a sentence"};

    tokenization(sentence, 18);

}