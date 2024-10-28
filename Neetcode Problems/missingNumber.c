#include <stdlib.h>
#include <stdio.h>

int missingNumber(int* nums, int numsSize) {

    int dummySize = numsSize*(numsSize + 1)/2;

    for(int i = 0; i < numsSize; i++) {
        dummySize -= nums[i];
    }

    return dummySize;
}

int main() {
    int nums[9] = {9,6,4,2,3,5,7,0,1};

    int result = missingNumber(nums, 9);

    printf("The result is %d", result);

}