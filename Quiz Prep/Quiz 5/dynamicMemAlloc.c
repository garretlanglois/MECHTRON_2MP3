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

    //matrix properties
    int layers = 3;
    int rows_per_layer[] = {2, 3, 2}; // Number of rows in each layer
    int cols_per_row[3][3] = {
        {4, 5},      // Layer 0 has 2 rows with 4 and 5 columns
        {3, 2, 6},   // Layer 1 has 3 rows with 3, 2, and 6 columns
        {5, 3}       // Layer 2 has 2 rows with 5 and 3 columns
    };


    int ***raggedThree = malloc(layers*sizeof(int**));

    if (raggedThree == NULL) {
        printf("MEMORY ALLOCATION FAILURE");
    }

    for (int i = 0; i < layers; i++) {
        raggedThree[i] = malloc(rows_per_layer[i]*sizeof(int*));
        for (int j = 0; j < rows_per_layer[i]; j ++) {
            raggedThree[i][j] = malloc(cols_per_row[i][j]*sizeof(int));
        }
    }


    //GPT generated print array function
    for (int i = 0; i < layers; i++) {
        printf("Layer %d:\n", i);
        for (int j = 0; j < rows_per_layer[i]; j++) {
            for (int k = 0; k < cols_per_row[i][j]; k++) {
                raggedThree[i][j][k] = i * 100 + j * 10 + k; // Example initialization
                printf("ragged_array[%d][%d][%d] = %d\n", i, j, k, raggedThree[i][j][k]);
            }
        }
        printf("\n");
    }

    



}