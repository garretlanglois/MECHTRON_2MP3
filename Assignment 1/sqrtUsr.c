#include <stdio.h>

double sqrtUser(double number, int n) {

    static int f_run = 1;
    static double original_value;

    if(f_run) {
        f_run = 0;
        original_value = number;
        n = (1 << (32 - __builtin_clz(n - 1)))*2; //Stole this bit manipulation from online 
        //https://stackoverflow.com/questions/466204/rounding-up-to-next-power-of-2
        //It rounds n up to the nearest power of 2 ensuring maximum precision, is it ok to be over precise?.
    }

    //Checks to see if precision has been reached
    //The precision for this method works as 2^n where n is number of iters
    if (n == 0) {
        return number;
    }

    number = 0.5*(number+original_value/number);
    return sqrtUser(number, n/2);
}

int main() {

    //Define the values we want to find
    double root_number = 7;
    int num = 5;

    //Becuase the accuracy doubles everytime the precision will be rounded up to the nearest power of 2
    double result = sqrtUser(root_number, num);

    //Print out the output of the recursive function to the terminal
    printf("The rooted result is %0.*f", num, result);

}