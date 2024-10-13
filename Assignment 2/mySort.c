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