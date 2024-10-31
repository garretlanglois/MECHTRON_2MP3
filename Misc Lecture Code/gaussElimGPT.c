#include <stdio.h>
#include <stdlib.h>

#define N 3 // You can change this value to suit the size of your matrix

void printMatrix(float matrix[N][N+1]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            printf("%8.3f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void gaussianElimination(float matrix[N][N+1]) {
    for (int i = 0; i < N; i++) {
        // Find the pivot element
        if (matrix[i][i] == 0.0) {
            printf("Mathematical Error!\n");
            exit(EXIT_FAILURE);
        }

        for (int j = i + 1; j < N; j++) {
            float ratio = matrix[j][i] / matrix[i][i];

            for (int k = 0; k < N + 1; k++) {
                matrix[j][k] -= ratio * matrix[i][k];
            }
        }

        printf("Matrix after step %d:\n", i + 1);
        printMatrix(matrix);
    }
}

void backSubstitution(float matrix[N][N+1], float solution[N]) {
    for (int i = N - 1; i >= 0; i--) {
        solution[i] = matrix[i][N];
        for (int j = i + 1; j < N; j++) {
            solution[i] -= matrix[i][j] * solution[j];
        }
        solution[i] /= matrix[i][i];
    }
}

int main(void) {
    float matrix[N][N+1] = {
        { 2, -1, 1,  8 },
        { -3, -1, 2, -11 },
        { -2, 1, 2, -3 }
    };

    printf("Original matrix:\n");
    printMatrix(matrix);

    gaussianElimination(matrix);

    float solution[N];
    backSubstitution(matrix, solution);

    printf("The solution is:\n");
    for (int i = 0; i < N; i++) {
        printf("x%d = %.3f\n", i+1, solution[i]);
    }

    return 0;
}
