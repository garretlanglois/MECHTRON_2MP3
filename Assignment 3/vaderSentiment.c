#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Custom tokenization function that will require reallocation of memory
char** tokenization(char * sentence, int size) {

        int intialSize = 2;

        char** tokens = (char *)malloc(intialSize*sizeof(char*));

        int index = 0;
        int tokenLength = 0;
        char delimeter = '-';

        while (sentence[index] != '\0') {
            
            //Just in case there is a space first && > 0
            if(sentence[index] == delimeter && tokenLength > 0) {
                strncpy(index-tokenLength);
            }

        }

}

int main(void) {
    
    char sentence[18] = {"This is a sentence"};

    tokenization(sentence, 18);

}