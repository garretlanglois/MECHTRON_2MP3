#include <stdio.h>


void bubbleSort(int arr[], int size) {

    for (int i = 0; i < size - 1; i++) {
        if(arr[i] < arr[i+1]) {
            int swap = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = swap;
        }
    }
    for (int i = 0; i < size -1; i++) {
        if (arr[i] > arr[i+1]) {
            bubbleSort(arr, size);
        }
    }

}


int main(void) {

    int arr[] = {64, -134, -5, 0, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);


    bubbleSort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("Value: %d\n", arr[i]);
    }


}