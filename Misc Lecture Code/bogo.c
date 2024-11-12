#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Function to check if the array is sorted
bool isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// Function to shuffle the array randomly
void shuffle(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int random_index = rand() % n;
        int temp = arr[i];
        arr[i] = arr[random_index];
        arr[random_index] = temp;
    }
}

// Function to perform Bogo Sort
void bogoSort(int arr[], int n) {
    int attempts = 0; // Track number of shuffles
    while (!isSorted(arr, n)) {
        shuffle(arr, n);
        attempts++;
    }
    printf("Array sorted after %d shuffles\n", attempts);
}

int main() {
    srand(time(NULL));  // Seed for random number generation

    int arr[12];
    int n = sizeof(arr) / sizeof(arr[0]);

    // Initialize the array with random numbers
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;  // Random values between 0 and 999
    }

    printf("Attempting to sort a 11-element array using Bogo Sort...\n");

    // Warning: This could run indefinitely!
    bogoSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
