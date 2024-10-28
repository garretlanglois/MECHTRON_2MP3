#include <stdio.h>


//Forward declatation of factorial function
int factorial(int n);

int main(void) {

    int num = 5;

    int value = factorial(num);

    printf("The value of the factorial of %d, is %d", num, value);

}


//Function for calculating the factorial
int factorial(int n) {

    if (n == 0 || n == 1) {
        return n;
    }

    int calculation = n*factorial(n-1);

    return calculation;

}