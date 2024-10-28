#include <stdio.h>

//Variable scope example

int main(void) {

	int x = 5;

	int y = 0;

	int i;

	int a = 2;

	int b = 5;
	
	int c = 3;

	double test = (float)a*b/c;

	printf("This is the value %f", test);


	for (int i = 1; i < 11; i++) {
		
		y = i*2;

		printf("i =%d\n", i);
		
	}

	printf("The value of i= %d.\n", i);

	printf("the value x= %d.\n",x);
	printf("The value y= %d.\n",y);


}
