#include <stdio.h>

int main(void) {

    int a = 10, b = 20, *p1, *p2;

    p1 = &a;
    p2 = &b;

    printf("The value of a: %d\n", a);
    printf("The value of b: %d\n", b);
    printf("The address of a: %p\n", &a);
    printf("The address of b: %p\n", &b);

    printf("The value pointer p1 is pointing at: %d\n", *p1);
    printf("The value pointer p2 is pointing at: %d\n", *p2);
    printf("The pointer p1: %p\n", p1);
    printf("The pointer p2: %p\n", p2);

    printf("\n");

    *p1 = *p2;

    printf("The value of a: %d\n", a);
    printf("The value of b: %d\n", b);
    printf("The address of a: %p\n", &a);
    printf("The address of b: %p\n", &b);

    printf("The value pointer p1 is pointing at: %d\n", *p1);
    printf("The value pointer p2 is pointing at: %d\n", *p2);
    printf("The pointer p1: %p\n", p1);
    printf("The pointer p2: %p\n", p2);

    //Pointers are just secondary variables for storing addresses.
}