#include <stdio.h>
#include <string.h>


struct Person {
    char name[50];
    int age;
};

int main() {

    struct Person p1 = { "John Doe", 30 };
    
    struct Person *ptr = &p1;  

    printf("Name: %s\n", ptr->name);

    return 0;
}
