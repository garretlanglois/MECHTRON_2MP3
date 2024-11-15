#include "utility.h"

int main(void) {
    bool excessPrinting = false;

    parseLexicon(excessPrinting);

    const char* sentences[] = {
        "VADER is very smart, handsome, and funny.",
    };
    int numSentences = sizeof(sentences) / sizeof(sentences[0]);

    for (int i = 0; i < numSentences; i++) {
        int tokenCount = 0;

        char* sentence = strdup(sentences[i]);  // Create a mutable copy of the sentence
        char** tokens = tokenization(sentence, strlen(sentence), &tokenCount);

        double compoundScore = compoundSentimentScoreCalculation(tokens, tokenCount);

        printf("Sentence: \"%s\"\n", sentences[i]);
        printf("Compound Sentiment Score: %.3f\n\n", compoundScore);

        freeTokens(tokens, tokenCount);
        free(sentence);
    }

    double intensifier = 0.0;

    double value = sentimentCalculation("is", &intensifier);

    printf("Value: %.3f\n", value);

    WordData *word = findWord("is");

    printf("\n\nWord: %s\n", word->word);
    

    return 0;
}
