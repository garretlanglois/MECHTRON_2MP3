#include "utility.h"

int main(void) {
    bool excessPrinting = false;

    parseLexicon(excessPrinting);

    const char* sentences[] = {
        "VADER is smart, handsome, and funny.",
        "VADER is smart, handsome, and funny!",
        "VADER is very smart, handsome, and funny.",
        "VADER is VERY SMART, handsome, and FUNNY.",
        "VADER is VERY SMART, handsome, and FUNNY!!!",
        "VADER is VERY SMART, uber handsome, and FRIGGIN FUNNY!!!",
        "VADER is not smart, handsome, nor funny.",
        "At least it isn’t a horrible book.",
        "The plot was good, but the characters are uncompelling and the dialog is not great.",
        "Make sure you :) or :D today!",
        "Not bad at all"
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
    return 0;
}
