#include <stdio.h>
#include <stdlib.h>


int hash(int key, int size) {
    return key % size;
}

int longestConsecutive(int* nums, int numsSize) {
    
    int largestNumber = 0;

    for (int i = 0 ; i < numsSize; i++) {
        if (nums[i] > largestNumber) {
            largestNumber = nums[i];
        }
    }

    int* count = malloc(sizeof(int) * largestNumber);

    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }

    int longestStreak = 0;

    for (int i = 0; i < largestNumber; i++) {
        if (count[i] > 0) {
            int currentNum = i;
            int currentStreak = 1;

            while (count[currentNum + 1] > 0) {
                currentNum++;
                currentStreak++;
            }

            if (currentStreak > longestStreak) {
                longestStreak = currentStreak;
            }
        }
    }

    return longestStreak;

}

int main() {
    // Test case 1: Regular case with mixed numbers
    int nums1[] = {100, 4, 200, 1, 3, 2};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    printf("Test Case 1: %d\n", longestConsecutive(nums1, size1));

    // Test case 2: Array with one element
    int nums2[] = {10};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    printf("Test Case 2: %d\n", longestConsecutive(nums2, size2)); // Expected output: 1

    // Test case 3: Array with no elements
    int nums3[] = {};
    int size3 = 0;
    printf("Test Case 3: %d\n", longestConsecutive(nums3, size3)); // Expected output: 0

    // Test case 4: All elements are the same
    int nums4[] = {7, 7, 7, 7};
    int size4 = sizeof(nums4) / sizeof(nums4[0]);
    printf("Test Case 4: %d\n", longestConsecutive(nums4, size4)); // Expected output: 1

    // Test case 5: Negative and positive numbers
    int nums5[] = {-1, -2, 0, 1, 2};
    int size5 = sizeof(nums5) / sizeof(nums5[0]);
    printf("Test Case 5: %d\n", longestConsecutive(nums5, size5)); // Expected output: 5 (sequence: -2, -1, 0, 1, 2)

    // Test case 6: Large gap between numbers
    int nums6[] = {10, 20, 30, 40};
    int size6 = sizeof(nums6) / sizeof(nums6[0]);
    printf("Test Case 6: %d\n", longestConsecutive(nums6, size6)); // Expected output: 1

    return 0;
}
