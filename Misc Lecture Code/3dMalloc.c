#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = 3, y = 4, z = 5;

    // Allocate memory for the 3D array
    int ***array = (int ***)malloc(x * sizeof(int **));
    for (int i = 0; i < x; i++) {
        array[i] = (int **)malloc(y * sizeof(int *));
        for (int j = 0; j < y; j++) {
            array[i][j] = (int *)malloc(z * sizeof(int));
        }
    }

    // Initialize array with some values
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                array[i][j][k] = i + j + k; // Example initialization
            }
        }
    }

    // Access and print the array values
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                printf("array[%d][%d][%d] = %d\n", i, j, k, array[i][j][k]);
            }
        }
    }

    // Free the allocated memory
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            free(array[i][j]);
        }
        free(array[i]);
    }
    free(array);

    return 0;
}
