#include <stdbool.h>
#include <stdio.h>

bool isPalindrome(char* s) {

    int size = sizeof(s)/sizeof(s[0]);

    int mid = size/2;

    for (int i = 0; i < mid; i++) {

        if(s[i] == s[size - 1 - i]) {
            
        }

    }

}

int main(void) {

    char s[] = {'a', 'b', 'c'};

    isPalindrome(s);

}