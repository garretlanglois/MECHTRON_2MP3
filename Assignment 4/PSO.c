// CODE: include library(s)
#include "utility.h"
#include "OF_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define inertialWeight 0.7
#define cognitiveCoefficient 1.5
#define socialCoefficient 1.5


typedef struct Particle {
    double *decisionVariables;
} Particle;

typedef struct Velocity {
    double *velocityVariables;
} Velocity;

typedef struct BestPosition {
    double bestPosition;
} BestPosition;

// New random function because the old one wouldn't work for me
double random_double(double min, double max) {
    double random_fraction = drand48();
    return min+ (max-min)*random_fraction;

}


// CODE: implement other functions here if necessary

double pso(ObjectiveFunction objective_function, int NUM_VARIABLES, Bound *bounds, int NUM_PARTICLES, int MAX_ITERATIONS, double *best_position) {

    Particle* particleArray[NUM_PARTICLES];

    Velocity* velocityArray[NUM_PARTICLES];

    BestPosition* bestPositionArray[NUM_PARTICLES];

    BestPosition* globalBestPosition[NUM_VARIABLES];

    //Initialize particles with position and velocity

    //Initialize all of the dimensions for the particle
    for(int i = 0; i < NUM_PARTICLES; i++) {
        particleArray[i]->decisionVariables = (double *)malloc(NUM_VARIABLES*sizeof(double));
        velocityArray[i]->velocityVariables = (double *)malloc(NUM_VARIABLES*sizeof(double));

        for(int j=0; j < NUM_VARIABLES; j++) {
            particleArray[i]->decisionVariables[j] = random_double(bounds->lowerBound, bounds->lowerBound);
            velocityArray[i]->velocityVariables[j] = 0.01;
        }

        bestPositionArray[i]->bestPosition = objective_function(5, particleArray[i]->decisionVariables);

    }

    return 10.0;
}

/*
int main(void) {

    //Create a seed for the random number generation
    srand48(time(NULL));

    return 0;
}
*/