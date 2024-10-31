#include <stdio.h>

void findEndOfString(char *str) {
    int i = 0;

    // Loop until we find the null terminator
    while (str[i] != '\0') {
        i++;
    }

    // Print the last character before the null terminator
    if (i > 0) {
        printf("The last character is: %c\n", str[i - 1]);
    } else {
        printf("The string is empty.\n");
    }
}

int main(void) {
    char strValue[] = "Hello World";

    findEndOfString(strValue); 

    return 0;
}