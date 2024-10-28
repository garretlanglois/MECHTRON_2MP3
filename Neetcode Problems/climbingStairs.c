#include <stdio.h>
#include <stdlib.h>

int climbStairs(int n) {

    int dummyValue = 1;
    int dummyValuePreceding = 0;
    int tempValue = 0;

    for (int i = 0; i < n; i++) {
        tempValue = dummyValue;
        dummyValue += dummyValuePreceding;
        dummyValuePreceding = tempValue;
    }

    return dummyValue;

}

int main() {

    for (int i = 0; i < 10; i++) {
        printf("Value at the %d fibonacci is %d\n", i, climbStairs(i));
    }

}