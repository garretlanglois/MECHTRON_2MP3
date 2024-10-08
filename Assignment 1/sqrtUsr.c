#include <stdio.h>

double sqrtUsr(double number, int n) {

    /* Declares two variables the first indicates to the code if it is the first iteration of the loop
    the second stores the initial value that is to be square rooted which is needed for Newton's Method*/
    static int f_run = 1;
    static double original_value;

    //Sets up the initial conditions
    if(f_run) {
        f_run = 0;
        original_value = number;
        n = (1 << (32 - __builtin_clz(n - 1)))*2; //Stole this bit manipulation from online and added the *2
        //https://stackoverflow.com/questions/466204/rounding-up-to-next-power-of-2
        //It rounds it up to the nearest power of two because the error is bound by 1 - 1/2^n
        //The *2 is to bring it up another power of 2 as the first error term gives no decimal places
    }
    
    //Checks to see if precision has been reached
    //The precision for this method works as 2^n where n is number of iters
    if (n == 0) {
        return number;
    }

    number = 0.5*(number+original_value/number);
    return sqrtUsr(number, n/2);
}

int main() {

    //Define the values we want to find
    //The number we want the root of
    double root_number = 100;

    //The number of digits in accuracy we want
    int num = 8;

    //Becuase the accuracy doubles everytime the precision will be rounded up to the nearest power of 2
    double result = sqrtUsr(root_number, num);

    //Print out the output of the recursive function to the terminal
    printf("The rooted result is %0.*f", num, result);

}

//Precision follows: https://math.stackexchange.com/questions/179225/newtons-method-determine-accuracy-in-calculation