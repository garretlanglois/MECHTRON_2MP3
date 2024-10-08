#include <stdio.h>

int main(void) {

    int a = 42; //Grabs 4 bytes -> 32 bits because 8 bits each

    int *pointer;
    pointer = &a;

    printf("The address of a is: %p\n",&a);
    printf("The pointer is: %p\n", pointer);
    printf("The value of a is: %d\n",a);
    printf("The value that the pointer is pointing at: %d\n", *pointer);

    a = 98;

    printf("The address of a is: %p\n",&a);
    printf("The pointer is: %p\n", pointer);
    printf("The value of a is: %d\n",a);
    printf("The value that the pointer is pointing at: %d\n", *pointer);

    *pointer = 500;

    printf("The address of a is: %p\n",&a);
    printf("The pointer is: %p\n", pointer);
    printf("The value of a is: %d\n",a);
    printf("The value that the pointer is pointing at: %d\n", *pointer);


}