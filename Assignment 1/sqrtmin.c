#include <stdio.h>
double sqrtUser(double number, int n) {
    static double f_run = 1.0, original_value = 0;
    if(f_run == 1.0) {
        f_run = 0;
        original_value = number;
    }
    if (n == 0) {
        return number;
    }
    number = 0.5*(number+original_value/number);
    return sqrtUser(number, n/2);
}

int main() {
    double root_number = 7;
    int num = 5;
    double result = sqrtUser(root_number, num);
    printf("The rooted result is %0.*f", num, result);
}