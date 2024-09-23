#include <stdio.h>
#include <strings.h>


int main() {

	char s1[] = "Hello World";
	
	char s2[] = "P";

	char s3[20];
	strcpy(s3,s1);

	printf("s3: %s has a size of %d.\n", s3, (int) strlen(s3));

	strcat(s3, s2);

	printf("s3: %s has a size of %d.\n", s3, (int) strlen(s3));

}

