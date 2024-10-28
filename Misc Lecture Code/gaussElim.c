#include <stdio.h>
#include <stdlib.h>

void printSystem(double **A, double *b, int n);

void gaussianElimination(double **A, double *b, double *x, int n) {

    double factor;

    int i, j, k;

    for (i = 0; i < n - 1; i++) {
        if (A[i][i] == 0) {
            printf("Error division by zero detected");
            exit(1);
        }


        //make zero the coefficient for the same column but different rows
        for (j = i+1; j < n; j++) {

            factor = -A[j][i]/A[i][i];


            //update all the columns in matrix A for the same row
            for (k = i; k < n; k++) {
                A[j][k]+= factor*A[i][k];
            }

            //Update  matrix b as well
            b[j] += factor*b[i];


        }

        printSystem(A, b, n);
    }

    //Backwrd elim

    for (i = n-1; i >= 0; i--) {
        x[i] = b[i];

        for (j = i+1; j < n; j++) {
            x[i] -= A[i][j]*x[j];
        }

        x[i] = x[i]/A[i][i];
    }
}

void printSystem(double **A, double *b, int n) {
    printf("System A|b: \n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.4lf", A[i][j]);
        }
        printf("%8.4lf\n", b[i]);
    } 
}

int main() {
    const int n = 3;

    double inputA[n][n] = {{2, 1, -1},{-3, -1, 2},{-2, 1, 2}};
    double inputB[3] = {1, 4, -2};

    double **A = (double**)malloc(n*sizeof(double*));


    for (int i = 0; i < n; i ++) {

        A[i] = malloc(n*sizeof(double));

    }

    double *b = (double*)malloc(n*sizeof(double));

    double *x = (double*)malloc(n*sizeof(double));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = inputA[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        b[i] = inputB[i];
    }

    printSystem(A, b, n);

    gaussianElimination(A, b, x, n);

    for (int i = 0; i < n; i++) {
        printf("x[%d] = %8.4f\n", i, x[i]);
    }

    free(b);
    free(x);
}