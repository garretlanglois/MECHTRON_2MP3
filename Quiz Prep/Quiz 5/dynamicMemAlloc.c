//Dynamic Memory Allocation

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    //2D dynamic memory allocation
    int rows = 3;
    int rowLengths[3] = {3, 5, 2};

    int** raggedArray = malloc(rows*sizeof(int*));

    for(int i = 0; i < rows; i++) {
        raggedArray[i] = malloc(rowLengths[i]*sizeof(int));
    }

    for(int j = 0; j < rows; j++) {
        for(int k = 0; k < rowLengths[j]; k++) {
            printf("%d ", raggedArray[j][k]);
        }
        printf("\n");
    }

    //3D dynamic memory allocation

    



}