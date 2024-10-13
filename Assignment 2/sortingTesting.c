#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

//Need to take into account STACK OVERFLOW for large range in python file

/* First mergeSort attempt
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
*/

void mergeElement (int left, int right, int arr[]) {

}

void merge() {
    
}


void insertionSort(int arr[], int n) {

     //Assume the elements in the array prior to the current element are already sorted
     //Start at the first element of the array and loop through all of the elements after that
    for (int i = 1; i < n; i++) {
    
        int shiftValue = arr[i];

        int j;

        for (j = i - 1; j >= 0; j--) {

            if(arr[j] > shiftValue) {
                arr[j+1] = arr[j];
            }  
            else {
                break;
            }

        }

        //Ran into a segmentation here many times because I tried arr[j] instead of arr[j+1] which would result in the indexing
        //at a negative element
        arr[j + 1] = shiftValue;

    }
}

int main() {
    int arr[] = {64, -134, -5, 0, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int testArr[n];
    
    // Bubble Sort
    memcpy(testArr, arr, n * sizeof(int));
    printf("Original array: ");
    printArray(testArr, n);
    //bubbleSort(testArr, n);
    mergeSort(testArr, n);
    printf("Bubble sorted array: ");
    printArray(testArr, n);
    

    // CODE: do the same test cases for Insertion Sort, Merge Sort, Heap Sort, Counting Sort
    // You will submit main.c, and your project will be marked based on main.c as well
    
    return 0;
}