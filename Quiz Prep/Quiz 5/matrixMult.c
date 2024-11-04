//Matrix Multiplication

#include <stdio.h>
#include <stdlib.h>


void matrixMult(int m, int n, int p, int A[m][n], int B[n][p], int **C) {
    for (int i = 0; i < m; i++) { //Iterate through the rows 
        for (int j = 0; j < p; j++) { //Iterate through the columns in the other array (we are creating m x p)
            C[i][j] = 0;
            for (int k = 0; k < n; k++) { //n is the common variable for both
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
}

int main(void) {
    const int m = 2;
    const int n = 3;
    const int p = 2;

    //allocated rows
    int **C = malloc(m*sizeof(int*));

    if (C == NULL) {
        printf("The memory allocation failed");
        free(C);
    }

    for (int i = 0; i < m; i++) {
        C[i] = malloc(p*sizeof(int));
    }

    int A[m][n] = {{1, 5, 3},{2, 6, 3}};

    int B[n][p] = {{1, 5},{9, 2},{7, 1}};

    matrixMult(m, n, p, A, B, C);


    //Print out the matrix
    printf("Resultant matrix C:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }


    //Properly free memory
    for (int i = 0; i < m; i++) {
        free(C[i]);
    }

    free(C);

}