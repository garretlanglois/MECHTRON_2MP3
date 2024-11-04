//Script to perform the Ax = b -> x = b/A operaiton described in class

#include <stdlib.h>
#include <stdio.h>

//Good to remember that this is the correct way to pass in 2d array

void solveForB(int size_A, double two_d_array[][size_A], int size_b, double b[size_b]) {

    //Matrix before row echelon
    for (int i = 0; i < size_A; i++) {
        for (int j = 0; j < size_A; j++) {
            printf("%f ", two_d_array[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for (int i = 0; i < size_A - 1; i++) { //This for the pivot row
        for (int k = i + 1; k < size_A; k++) { //This for every row below the pivot
            double factor = two_d_array[k][i]/two_d_array[i][i]; //Create a factor based on the current iteration at the first number in the next array
            for (int j = i; j < size_A; j++) { 
                two_d_array[k][j] -= two_d_array[i][j]*factor; //Row - pivot_row * factor
            }
            b[k] -= b[i]*factor; // Remove the pivot row * factor from b as well
        }
    }

    for (int i = 0; i < size_A; i++) {
            for (int j = 0; j < size_A; j++) {
                printf("%f ", two_d_array[i][j]);
            }
            printf("| %f", b[i]);
            printf("\n");
    }

    //Now we need to do the backpropogration:

    for (int i = size_A - 1; i >= 0 ; i--) {
        for (int j = i - 1; j >= 0; j--) {
            double factor = two_d_array[j][i]/two_d_array[i][i]; //Remember that pivot always goes on the bottom of the factor
            for (int k = size_A - 1; k >= i; k--) { //k >= i bound is important!
                two_d_array[j][k] -= two_d_array[i][k]*factor;
            }
            b[j] -= b[i] * factor; //Make sure to reduce b as well it is just the current row - pivot*factor
        }
    }

    printf("\n");

    for (int i = 0; i < size_A; i++) {
        for (int j = 0; j < size_A; j++) {
            printf("%f ", two_d_array[i][j]);
        }
        printf("| %f", b[i]);
        printf("\n");
    }

    printf("\n");

    //Now we want to solve for b:

    for (int i = 0; i < size_A; i++) {
        printf("x%d = %f\n", i+1, b[i]/two_d_array[i][i]);
    }

}


int main(void) {

    double array[3][3] = {{1, 2, 3,},{5, 2, 1},{2, 2, 7}};

    double b[3] = {10,3,2};

    int size_b = 3;

    int size_A = 3;

    solveForB(size_A, array, size_b, b);
}