#include <stdio.h>


int main(void) {

	int arr[] = {1, 3, 5, 7, 8, 12, 15};

	int size = sizeof(arr)/sizeof(arr[0]);

	int target = 9;

	int left = 0;

	int right = size-1;

	int sum = 0;

	while(left<right) {
	
		sum = arr[left]+arr[right];
		if (sum == target) {
		
			printf("arr[%d]+arr[%d] = %d", left, right, target);
			break;

		}
		else if (sum>target) {
			
			right--;
			
		}
		else {
			left++;
		}	

	}


}
