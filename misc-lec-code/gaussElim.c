#include <stdio.h>
#include <stdlib.h>

void gaussianElimination(double **A, double *b, double *x, int n) {

}

void printSystem(double **A, double *b, int n) {
    printf("System A|b: \n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.4lf", A[i][j]);
        }
        printf("%8.4lf", b[i]);
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

    free(b);
    free(x);
}