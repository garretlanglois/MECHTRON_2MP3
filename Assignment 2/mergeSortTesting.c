#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mergeSort(int arr[], int n) {

    if (n == 1) {
        
    }
    if (n == 2) {
        if (arr[1] < arr[0]) {
            swap(&arr[1], &arr[0]);
        }
    }

    else {
        int leftSize = n/2;

        int rightSize = n - leftSize;

        int *leftArr = (int*)malloc(leftSize*sizeof(int));
        int *rightArr = (int*)malloc(rightSize*sizeof(int));

        if (leftArr == NULL || rightArr == NULL) {
            printf("ERROR \n");
            exit(1);
        }

        memcpy(leftArr, arr, leftSize * sizeof(int));             // Copy left half
        memcpy(rightArr, &arr[leftSize], rightSize * sizeof(int));

        mergeSort(leftArr, leftSize);
        mergeSort(rightArr, rightSize);

        memcpy(arr, leftArr, leftSize*sizeof(int));
        memcpy(&arr[leftSize], rightArr, rightSize*sizeof(int));

        free(leftArr);
        free(rightArr);
    }

}