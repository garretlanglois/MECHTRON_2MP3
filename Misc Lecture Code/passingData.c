#include <stdlib.h>
#include <stdio.h>


void functionScope(int number, int *pointer) {

    number = 10;
    pointer = &number; 

}


int main(void) {

    int number = 5;

    int value = 100;

    int *pointer = &value;

    printf("The value of number is %d, the address is %p\n", number, &number);
    printf("Pointer is %p, the address is %p\n", pointer, &pointer);

    functionScope(number, pointer);

    printf("The value of number is %d, the address is %p\n", number, &number);
    printf("Pointer is %p, the address is %p\n", pointer, &pointer);
    
    return 0;

}