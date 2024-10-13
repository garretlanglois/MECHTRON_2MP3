#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Need to take into account STACK OVERFLOW for large range in python file

//These are the functions for doing tasks
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

void mergeElements(int arr[], int leftPosition, int rightPosition) {

    //It is important to do this instead of n/2 because the position in the original array dynamically
    //changes throughout the recursion
    int middlePosition = leftPosition + (rightPosition-leftPosition)/2;
    
    int leftSize = middlePosition - leftPosition + 1;
    int rightSize = rightPosition - middlePosition;

    //Now we need two different arrays which we will use to temporarly store the data

    int leftArray[leftSize];
    int rightArray[rightSize];


    //Append the values of the array from the left side to the temporary array
    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = arr[leftPosition + i ];
    }

    //Append the values of the array from the right side to the temporary array
    for (int i = 0; i < rightSize; i++) {
        rightArray[i] = arr[1 + middlePosition + i];
    }

    //Had to ask ChatGPT how to get an extra two indexing variables.
    //It ended up being only these two extra lines that I needed.
    //The reason that they are both set to 0 is because i was already used
    int i = 0; //This is the indexing variable for the left array
    int j = 0; //This is the indexing variable for the right array
    int k; //This is the whole array index
    int iterationNum = (rightSize+leftSize)/2 + 1;

    //Now we need to add the values into the original array, which remember is still in the recursive loop
    //so it isnt actually the original array we were sorting
    // Total number of elements in the range to merge is from leftPosition to rightPosition
    for (k = leftPosition; k <= rightPosition; k++) {
        if (i < leftSize && (j >= rightSize || leftArray[i] <= rightArray[j])) {
            arr[k] = leftArray[i];
            i++; // Move index in leftArray
        } else {
            arr[k] = rightArray[j];
            j++; // Move index in rightArray
        }
    }


    //Now we just need to copy over any remaining elements that were not included in the loop.
    //the reason that this happens is because of the bound we set with the division

    //This copy strategy was taken from this article: https://www.geeksforgeeks.org/c-program-for-merge-sort/

    while (i < leftSize) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }

}

//These are the sorting algorithms
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r-l)/2;

        mergeSort(arr, l, m);

        mergeSort(arr, m+1,r);

        mergeElements(arr, l , r);

    }
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

//Define the function for building all subsequent heaps after the initial maximum heap
//In this array index is the index in the array of the parent node that we want to heapify
//I find it helpful to visualize it as a bunch of little lists that we reverse sort and then append
//one by one

//When we recursively heapify we follow the value along until it is at the bottom of its respective branch
//of the heap
void heapify(int arr[], int index, int n) {

    //Because each branch of the tree grows at 2^n where n is the depth we just need two elements for every layer
    int leftIndex = 2*index + 1;
    int rightIndex = 2*index + 2;

    int maxIndex = 0;

    //The first condition ensures the the index is within the bounds
    //The second checks to see if the value is in the wrong place

    //The first condition could have been an if conditional statement surrounding
    //both but I found that that looked messy, so I used &&
    if((leftIndex < n) && (arr[leftIndex] > arr[index])) {
        maxIndex = leftIndex;
    }
    else {
        maxIndex = index;
    }

    //Same this as before but now with the right index
    //We are fine to use maxIndex here because it will have always been defined at this point in the code
    if((rightIndex < n) && (arr[rightIndex] > arr[maxIndex])) {
        maxIndex = rightIndex;
    }

    if (maxIndex != index) {
        swap(&arr[index], &arr[maxIndex]);
        heapify(arr, maxIndex, n);
    }

} 

//Define the function for building the maximum heap, this only ever is called once for any given array
void buildMaxHeap(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--) {
        heapify(arr, i, n);
    }
}

void heapSort(int arr[], int n) {
    //Doing heap sort requires three different functions
    //The heapify function, the build maximum heap function, and the sorting function itself

    buildMaxHeap(arr, n);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, 0, i);    
    }

}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}
//This is the main function for running the code with a test array
int main() {
    int arr[] = {64, -134, -5, 0, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int testArr[n];
    
    // Bubble Sort
    memcpy(testArr, arr, n * sizeof(int));
    printf("Original array: ");
    printArray(testArr, n);
    //bubbleSort(testArr, n);
    heapSort(testArr, n);
    printf("Bubble sorted array: ");
    printArray(testArr, n);
    

    // CODE: do the same test cases for Insertion Sort, Merge Sort, Heap Sort, Counting Sort
    // You will submit main.c, and your project will be marked based on main.c as well
    
    return 0;
}