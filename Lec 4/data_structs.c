#include <stdio.h>

int main() {

	char c = 'P';

	char s[] = "Anne-Marie";

	for (int i = 0; i < 10; i++) {
	
		printf("Data: %c\n", s[i]);

	}
	
	char address = &s;

	printf("%c", address);

}
