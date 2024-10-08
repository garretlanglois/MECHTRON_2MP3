#include <stdio.h>


double sqrtUser(double number, int n) {

    /*Define all the variables that are independent of the recursion so that the loop can work if only
    the number and the precision are plugged into it*/

    //The variables are the ones resposible for the error bounds calculation
    static double epsilon = 1;
    static double previous = 0;
    static double error_bound = 0;

    //This variable stores the original value that needed to be square rooted
    static double original_value = 0;

    //This if statement will only run on the first iteration of the function
    if (previous == 0) {

        /*We set the original value of the the number we wanted to square root and use it in subsequent iteration
        to calculate the current approximation of the square root of the function*/
        original_value = number;

        //The divisor is the variable taht will go on the bottom of the error bound calculation
        double divisor = 1;
        for (int i = 0; i < n; i++) {
            divisor = divisor*10;
        }

        //The way the error bound is calculated is laid out in the report
        error_bound = 1/divisor;
    }

    /*On every iteration we check to see if the difference between the current value and previous value
    are equal or less then the error bound, this tells us if we have calculated the right number*/
    if (epsilon <= error_bound) {
        return number;
    }


    //This is the babylonian method for calculating the current approximation of the square root
    number = 0.5*(number+original_value/number);

    //This calculates the difference between the two previous runs using the proper double casting
    epsilon = (double)(number-previous)/number;

    //Takes the absolute value of Epsilon
    if(epsilon < 0) {
        epsilon = -epsilon;
    }

    //Sets the previous number to the current iteration as all logic has already been done
    previous = number;

    //Creates the recursion
    return sqrtUser(number, n);

}

int main(void) {

    //Define the values we want to find
    //The number we want the root of
    double root_number = 2;

    //The number of decimal places of accuracy we want
    int num = 20;

    //Checks to see all the possible ways that the input that user provided could cause an issue
    if (root_number < 0) {
        printf("The roots of negative numbers cannot be calculated");
    }

    else if (root_number == 0) {
        printf("Taking the square root of 0 results in a segmentation fault");
    }

    else if (num <= 0) {
        printf("The precision must be a positive integer that is greater than 0");
    }
    
    else {
        //Runs the function, passing in the desired variables
        double result = sqrtUser(root_number, num);

        //Print out the output of the recursive function to the terminal
        printf("The rooted result is %0.*f", num, result);
    }

}