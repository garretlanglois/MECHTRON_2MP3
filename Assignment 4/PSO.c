// CODE: include library(s)
#include "utility.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// New random function because the old one wouldn't work for me
double random_double(double min, double max) {
    double random_fraction = drand48();
    return min+ (max-min)*random_fraction;

}

// CODE: implement other functions here if necessary

double pso(ObjectiveFunction objective_function, int NUM_VARIABLES, Bound *bounds, int NUM_PARTICLES, int MAX_ITERATIONS, double *best_position) {

    

    return 10.0;
}

int main(void) {

    //Create a seed for the random number generation
    srand48(time(NULL));

    return 0;
}