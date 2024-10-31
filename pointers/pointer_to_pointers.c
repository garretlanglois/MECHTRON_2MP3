//C = A + B
//C = A x B

//Matrix Code Stuff - Unfinished
#include <stdio.h>
#include <stdlib.h>

double **allocate2Darray(int rows, int cols) {
    double **arr = (double*)malloc(rows*sizeof(double*));

    if (arr ==NULL) {
        printf("ERROR");
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        arr[i] = calloc(cols,sizeof(double));
        if (arr[i] == NULL) {
            printf("ERROR");
            for (int j = 0; j < i; i++) {
                free(arr[i]);
            }
            free(arr);
            return NULL;
        }
    }
}

double **MatrixAddition(double **A, double **B, int Arows, int Acols, int Brows, int Bcols) {
    if (Arows != Brows || Acols != Bcols) {

        printf("The matrices do not match in size");
    }

    double **C = (double**)malloc(Arows*sizeof(double*));

    for (int i = 0)
}

void free2Darray(double** arr, int rows) {
    for (int i = 0; i < rows; i++) { 
        free(arr[i]);
    } 

    free(arr);
}

void print2Darray(double **arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%lf ", arr[i][j]);
        }
        printf("\n");
    }
}

int main(void) {

    int Arows = 3, Acols = 2;

    int Brows = 3, Bcols = 2;

    double **A = (double **)malloc(Arows*sizeof(double*));
    double **B = (double **)malloc(Brows*sizeof(double*));

    for (int i = 0; i < Arows; i++) { 
        A[i] = malloc(Acols*sizeof(double));
    } 

    for (int i = 0; i < Brows; i++) { 
        A[i] = malloc(Bcols*sizeof(double));
    } 

    for (int i = 0; i < Arows; i++) {
        for (int j = 0; j < Acols; j++) {
            A[i][j] = i+j;
        }
    }

    for (int i = 0; i < Brows; i++) {
        for (int j = 0; j < Bcols; j++) {
            A[i][j] = i-j;
        }
    }

    print2Darray(A, Arows, Acols);
    print2Darray(B, Brows, Bcols);

    free2Darray(A, Arows);
    free2Darray(B, Brows);
    
}