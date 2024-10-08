#include <stdio.h>

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};

    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d with address %p\n", i, arr[i], &arr[i]);
    }


} 