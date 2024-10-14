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

//This is the function to merge the elements in merge sort, it contains most of the logic
void mergeElements(int arr[], int leftPosition, int rightPosition) {

    //It is important to do this instead of n/2 because the position in the original array dynamically
    //changes throughout the recursion
    int middlePosition = leftPosition + (rightPosition-leftPosition)/2;
    
    int leftSize = middlePosition - leftPosition + 1;
    int rightSize = rightPosition - middlePosition;

    //Now we need two different arrays which we will use to temporarly store the data

    int *leftArray = (int *)malloc(leftSize * sizeof(int));
    int *rightArray = (int *)malloc(rightSize * sizeof(int));


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

    //Free the allocated memory for the left array and right array
    free(leftArray);
    free(rightArray);

}

//These are the sorting algorithms
void mergeSort(int arr[], int l, int r) {

    //This ensures that the size of the elements that are being merged are greater than 0
    if (l < r) {

        //This defines the middle value for the array
        //The reason that single letter variable names are being used is because that is what is used in the header for this function
        int m = l + (r-l)/2;

        //We run the mergeSort recursively for the two different arrays, the left one and the right one
        //Remember they will not run if the dimenions that it is expecting is less than one
        mergeSort(arr, l, m);

        mergeSort(arr, m+1,r);

        //This function contains the main logic for the algorithm, it swaps the elements in the array depending on what order they are in
        mergeElements(arr, l , r);

    }
}

void insertionSort(int arr[], int n) {

     //Assume the elements in the array prior to the current element are already sorted
     //Start at the first element of the array and loop through all of the elements after that
    for (int i = 1; i < n; i++) {
    
        //This will grab the value of the element we want to place in the correct position
        int shiftValue = arr[i];

        //We want to use j later so we define it outside of the loop
        int j;

        //We loop through all of the elements in the list
        for (j = i - 1; j >= 0; j--) {

            //If the current element is greater than the value we are looking at we shift the values that are
            //greater than it in the array one to the right
            if(arr[j] > shiftValue) {
                arr[j+1] = arr[j];
            }  
            //Once we have found a place where the value is not greater than it the correct location is found
            else {
                break;
            }

        }

        //Ran into a segmentation here many times because I tried arr[j] instead of arr[j+1] which would result in the indexing
        //at a negative element
        //This places the shiftValue at the correct position, one position ahead of the last position we checked.
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

void countingSort(int arr[], int n) {

    //Start by constructing a new array of variable length that will keep track of all the occurences of numbers that we see
    //So that we dont run into stack issues we can dynamically resize the array that holds the occurences based on the amount of number we see

    //Originally my implementation did not account for negative numbers so this for loops fixs that by determining the 
    //maximum and minimum values in the array and creating a range

    //Create some original values so that the min and max aren't unassigned cause that would not be good :)
    int min = arr[0];
    int max = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        else if (arr[i] > max) {
            max = arr[i];
        }
    }

    //Now we are going to define a variable which represents the range of the array (difference between the lowest and highest number)

    int range = max - min + 1; //+1 for 0

    //This is another change I made from previous iterations of this code and prevents having to dynamically
    //resize the array occurences, even if it does take another for loop. (We had to make the for loop anyway)
    
    int *occurences = (int *)malloc(range * sizeof(int));

    //Here is the annoying part where we have to initialize the array with all zeroes because C doesn't default to doing that
    for (int i = 0; i < range; i++) {
        occurences[i] = 0;
    }

    //Now we count the total occurences of each number we see using a loop, account for negative numbers using our new range we defined
    for (int i = 0; i  < n; i++) {
        occurences[arr[i] - min]++; //Now we incremement the occurences array at our desired position by one!
    }

    //Now we need to fill the original array based on our occurences array
    //We need to remember to account for the min value that we created earlier
    
    //Using knowledge gained from the merge sort code I remembered that I can place an index outside the loop
    //Here I called it index to make it a little clearer
    int index = 0;

    //Loop through every value in the code
    for (int i = 0; i < range; i++) {

        //We get the "number of each number" using our little occurences array
        int numberOfValues = occurences[i];

        //We now add that many numbers back to our original array! (making sure to account for the minimum value of course...)
        for (int j = 0; j < numberOfValues; j++) {
            arr[index] = i + min;

            //Now we see why we needed this index value because it needs to be independent of both loops.
            //The first loop goes through all the values we need to add and the second one adds that value the correct number of times
            //The index keeps track of where we are in the original list.
            index++;
        }
    }

}