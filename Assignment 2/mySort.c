// CODE: include necessary library(s)
// you have to write all the functions and algorithms from scratch,
// You will submit this file, mySort.c holds the actual implementation of sorting functions


void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

// CODE: implement the algorithms for Insertion Sort, Merge Sort, Heap Sort, Counting Sort

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n - 1; i++) {
        if(arr[i] < arr[i-1]) {
            for (int j = 0; j < n - i; j ++) {

                //Create two new arrays that will store the data of the array up to the position we are splicing
                //And an array that contains everything after the splice that we are making
                int firstSplice[i];
                int secondSplice[n - i];

                memcpy(firstSplice, arr, 3 * sizeof(int)); 
                
                memcpy(secondSplice, &arr[3], 3 * sizeof(int)); 

            }
        }

    }
}