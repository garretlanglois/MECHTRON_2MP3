#include <stdio.h>

int main(void) {

	//find the maximum value in the array

	int arr[] = {5, 2, 3, 8, 7, 12, 1, 5};
	
	int size = sizeof(arr)/sizeof(arr[0]);

	int current_max = 0;

	for (int i = 0; i< size; i++) {
	
		if(current_max < arr[i]) {
	
			current_max = arr[i];		

		}

	}	
	
	printf("The maximum value in the array is %d", current_max);

}	
