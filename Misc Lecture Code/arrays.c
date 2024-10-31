#include <stdio.h>
#include <stdlib.h>

int main() {

	int nums[] = {1,5,2,7,4};
	
	int size = sizeof(nums)/sizeof(nums[0]);

	printf("the size of the array is %d \n",size);

	for (int i = 0; i < 5; i++) {
		printf("nums[%d] = %d\n", i, nums[i]);
	}

}
