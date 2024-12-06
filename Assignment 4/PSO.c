//Include all the libraries that we need
#include "utility.h"
#include "OF_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

//Define all of the constants that we need
#define INERTIAL_WEIGHT 0.7
#define COGNITIVE_COEFFICIENT 1.5
#define SOCIAL_COEFFICIENT 1.5
#define STAGNANT_ITERATIONS 100


//Define the struct for the particle
//The struct is used to help with readibility of the program and to make designing the logic much easier
typedef struct Particle {
    //Array for the dimensions of the particle
    double *decisionVariables;
    //Array for the personal best position of the particle
    double *personalBest;
    //Array for the velocity of the particle
    double *velocityVariables;
    //The current position of the particle
    double currentPosition;
    //The personal best fitness of the particle
    double personalBestFitness;
    //The number of stagnant iterations
    int stagnantIterations;
} Particle;

//This could've been a particle but to save memory, better to have its own type
typedef struct BestPosition {
    double *decisionVariables;
    double currentValue;
} BestPosition;

// New random function because the old one wouldn't work for me, this uses drand48
double random_double(double min, double max) {

    //Create a random fraction from 0 to 1
    double random_fraction = drand48();

    //Return the random number that is generated within the bounds
    return min+ (max-min)*random_fraction;

}

//This is the main function that will be called by the user to run the PSO algorithm
double pso(ObjectiveFunction objective_function, int NUM_VARIABLES, Bound *bounds, int NUM_PARTICLES, int MAX_ITERATIONS, double *best_position) {

    //Create an array of particles
    Particle* particleArray[NUM_PARTICLES];

    //Malloc the memory for the particles
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particleArray[i] = (Particle *)malloc(sizeof(Particle));

        //Check to see if the memory was allocated properly
        if (particleArray[i] == NULL) {
            printf("Error allocating memory for Particles...");
            exit(EXIT_FAILURE);
        }
    }

    //Create a global best position
    BestPosition globalBestPosition;

    // Initialize global best position
    globalBestPosition.decisionVariables = (double *)malloc(NUM_VARIABLES * sizeof(double));

    //Check to see if the memory was allocated properly
    if (globalBestPosition.decisionVariables == NULL) {
        printf("Error allocating memory for global best position...");
        exit(EXIT_FAILURE);
    }

    //Set the global best position to infinity, this is needed to ensure that the first particle will always be better
    globalBestPosition.currentValue = INFINITY;

    //Initialize all of the dimensions for each particle
    for(int i = 0; i < NUM_PARTICLES; i++) {


        //Malloc everything
        particleArray[i]->decisionVariables = (double *)malloc(NUM_VARIABLES*sizeof(double));
        particleArray[i]->personalBest = (double *)malloc(NUM_VARIABLES*sizeof(double));
        particleArray[i]->velocityVariables = (double *)malloc(NUM_VARIABLES*sizeof(double));

        //Iterate through all of the dimensions and set the values to random numbers
        for(int j=0; j < NUM_VARIABLES; j++) {
            double random_num = random_double(bounds->lowerBound, bounds->upperBound);

            //We want to set the decision variables and the personal best to the same value, that way we can iterate on them
            particleArray[i]->decisionVariables[j] = random_num;
            particleArray[i]->personalBest[j] = random_num;

            //We set the velocity to a random number between -1 and 1
            particleArray[i]->velocityVariables[j] = random_double(-1, 1);
        }


        //Calculate the current position of the particle and set it as both the current position and the personal best fitness
        //We do this because the first iteration will always be the best
        double currentPosition = objective_function(NUM_VARIABLES, particleArray[i]->decisionVariables);
        particleArray[i]->currentPosition = currentPosition;
        particleArray[i]->personalBestFitness = currentPosition;

        if (currentPosition < globalBestPosition.currentValue) {
            globalBestPosition.currentValue = currentPosition;
            memcpy(globalBestPosition.decisionVariables, particleArray[i]->decisionVariables, NUM_VARIABLES * sizeof(double));
        }
    }

    int iterationCount = 0;

    while (iterationCount < MAX_ITERATIONS) {

        srand48(time(NULL));

        for (int i = 0; i < NUM_PARTICLES; i++) {
            // Update velocity and position
            for (int j = 0; j < NUM_VARIABLES; j++) {
                double r1 = random_double(0, 1);
                double r2 = random_double(0, 1);

                particleArray[i]->velocityVariables[j] = INERTIAL_WEIGHT* particleArray[i]->velocityVariables[j] +
                    COGNITIVE_COEFFICIENT * r1 * (particleArray[i]->personalBest[j] - particleArray[i]->decisionVariables[j]) +
                    SOCIAL_COEFFICIENT * r2 * (globalBestPosition.decisionVariables[j] - particleArray[i]->decisionVariables[j]);

                // Update position
                particleArray[i]->decisionVariables[j] += particleArray[i]->velocityVariables[j];

                // Clamp position within bounds
                particleArray[i]->decisionVariables[j] = fmax(bounds->lowerBound, fmin(bounds->upperBound, particleArray[i]->decisionVariables[j]));
                //Check to see if the position is within bounds
                if (particleArray[i]->decisionVariables[j] < bounds->lowerBound || particleArray[i]->decisionVariables[j] > bounds->upperBound) {
                    printf("Error: Particle %d, Dimension %d is out of bounds\n", i, j);
                    exit(EXIT_FAILURE);
                }
            }

            double position = objective_function(NUM_VARIABLES, particleArray[i]->decisionVariables);

            particleArray[i]->currentPosition = position;

            // Update personal best if current position is better
            if (position < particleArray[i]->personalBestFitness) {
                memcpy(particleArray[i]->personalBest, particleArray[i]->decisionVariables, NUM_VARIABLES * sizeof(double));
                particleArray[i]->personalBestFitness = position;
                particleArray[i]->stagnantIterations = 0;
            }
            else {
                particleArray[i]->stagnantIterations += 1;
            }

            // Update global best if current position is better
            if (position < globalBestPosition.currentValue) {
                globalBestPosition.currentValue = position;
                memcpy(globalBestPosition.decisionVariables, particleArray[i]->decisionVariables, NUM_VARIABLES * sizeof(double));
            }

            if (particleArray[i]->stagnantIterations > STAGNANT_ITERATIONS) {
                for (int j = 0; j < NUM_VARIABLES; j++) {
                    particleArray[i]->decisionVariables[j] += random_double(-0.8, 0.8);

                    //ensure it is clamped
                    particleArray[i]->decisionVariables[j] = fmax(bounds->lowerBound, fmin(bounds->upperBound, particleArray[i]->decisionVariables[j]));
                
                    //reset the velocity
                    particleArray[i]->velocityVariables[j] = random_double(-1, 1);
                }
                particleArray[i]->stagnantIterations = 0;
            }
        }

        // Print fitness every 100 iterations
        if (iterationCount % 100 == 0) {
            printf("Iteration %d: Best Fitness = %.30f\n", iterationCount, globalBestPosition.currentValue);

            //print the first two particles current fitness positions for debugging

            printf("Particle 0: %.30f\n", particleArray[0]->currentPosition);
            printf("Particle 1: %.30f\n", particleArray[1]->currentPosition);
        }

        // Optional stopping condition
        if ((globalBestPosition.currentValue < 1e-4 && globalBestPosition.currentValue > 0)) {
            break; 
        }

        iterationCount += 1;
    }

    // Copy global best position to output parameter
    memcpy(best_position, globalBestPosition.decisionVariables, NUM_VARIABLES * sizeof(double));

    // Free allocated memory
    for (int i = 0; i < NUM_PARTICLES; i++) {
        free(particleArray[i]->decisionVariables);
        free(particleArray[i]->personalBest);
        free(particleArray[i]->velocityVariables);
        free(particleArray[i]);
    }
    free(globalBestPosition.decisionVariables);

    return globalBestPosition.currentValue;
}


/*
int main(void) {

    //Create a seed for the random number generation
    srand48(time(NULL));

    return 0;
}
*/