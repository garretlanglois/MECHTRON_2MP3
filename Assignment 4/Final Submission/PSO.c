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

        //Keep track of the global best position from the initialized particles
        if (currentPosition < globalBestPosition.currentValue) {
            globalBestPosition.currentValue = currentPosition;
            //We want to copy the decision variables of the particle to the global best position, this way we can use it for the velocity value
            memcpy(globalBestPosition.decisionVariables, particleArray[i]->decisionVariables, NUM_VARIABLES * sizeof(double));
        }
    }

    //Keep track of the while loop iterations
    int iterationCount = 0;

    //This is the number of convergence iterations
    while (iterationCount < MAX_ITERATIONS) {

        srand48(time(NULL));

        for (int i = 0; i < NUM_PARTICLES; i++) {
            
            // Update velocity and position of the particles for each iteration
            //We need to loop through the variables for position and velocity of each partilce
            for (int j = 0; j < NUM_VARIABLES; j++) {

                //Generate two random number which will add some randomness to the velocity calculation
                double r1 = random_double(0, 1);
                double r2 = random_double(0, 1);

                // This is the velocity calculation formula which is done for each dimension
                //It is the one from the assignment document              
                particleArray[i]->velocityVariables[j] = INERTIAL_WEIGHT* particleArray[i]->velocityVariables[j] +
                    COGNITIVE_COEFFICIENT * r1 * (particleArray[i]->personalBest[j] - particleArray[i]->decisionVariables[j]) +
                    SOCIAL_COEFFICIENT * r2 * (globalBestPosition.decisionVariables[j] - particleArray[i]->decisionVariables[j]);

                // Update position
                particleArray[i]->decisionVariables[j] += particleArray[i]->velocityVariables[j];

                // Clamp position within bounds
                particleArray[i]->decisionVariables[j] = fmax(bounds->lowerBound, fmin(bounds->upperBound, particleArray[i]->decisionVariables[j]));
                
                //Check to see if the position is within bounds, this will probably never happen due to the clamp but just in case
                if (particleArray[i]->decisionVariables[j] < bounds->lowerBound || particleArray[i]->decisionVariables[j] > bounds->upperBound) {
                    printf("Error: Particle %d, Dimension %d is out of bounds\n", i, j);
                    exit(EXIT_FAILURE);
                }
            }

            //Calculate the fitness of the current particle
            double position = objective_function(NUM_VARIABLES, particleArray[i]->decisionVariables);

            //Update current position of the particle 
            particleArray[i]->currentPosition = position;

            // Update personal best if current position is better
            if (position < particleArray[i]->personalBestFitness) {

                //Copy the decision variables to the personal best
                memcpy(particleArray[i]->personalBest, particleArray[i]->decisionVariables, NUM_VARIABLES * sizeof(double));

                //Set the personal best fitness to the current position
                particleArray[i]->personalBestFitness = position;

                //Reset the stagnant iterations
                particleArray[i]->stagnantIterations = 0;
            }

            //If the current position is greater than or equal to the current best then we increment the stagnant iterations
            else {
                particleArray[i]->stagnantIterations += 1;
            }

            // Update global best if current position is better
            if (position < globalBestPosition.currentValue) {

                //Set the global best position to the current position
                globalBestPosition.currentValue = position;

                //Copy the decision variables to the global best position
                memcpy(globalBestPosition.decisionVariables, particleArray[i]->decisionVariables, NUM_VARIABLES * sizeof(double));
            }

            //This is the main difference between the pseudo code in the assignment document and the actual code
            //If the maximum number of stagnant iterations is reached, then we move the particle in a random direction by a small amount

            if (particleArray[i]->stagnantIterations > STAGNANT_ITERATIONS) {

                //Loop through all of the dimensions of the particle
                for (int j = 0; j < NUM_VARIABLES; j++) {

                    //Move the particle in a random direction by a small amount
                    particleArray[i]->decisionVariables[j] += random_double(-0.8, 0.8);

                    //We need to clamp the position within bounds
                    particleArray[i]->decisionVariables[j] = fmax(bounds->lowerBound, fmin(bounds->upperBound, particleArray[i]->decisionVariables[j]));
                
                    //reset the velocity
                    particleArray[i]->velocityVariables[j] = random_double(-1, 1);
                }
                particleArray[i]->stagnantIterations = 0;
            }
        }

        // Print fitness every 100 iterations
        //I have commented this out but you can turn it back on if you want to see the fitness every 100 iterations
        /*
        if (iterationCount % 100 == 0) {
            printf("Iteration %d: Best Fitness = %.30f\n", iterationCount, globalBestPosition.currentValue);

            //print the first two particles current fitness positions for debugging

            printf("Particle 0: %.30f\n", particleArray[0]->currentPosition);
            printf("Particle 1: %.30f\n", particleArray[1]->currentPosition);
        }
        */

        // Optional stopping condition, this can be turned on and off and only acts as a stopping condition but fucntions that converge to 0
        if ((globalBestPosition.currentValue < 1e-4 && globalBestPosition.currentValue > 0)) {
            break; 
        }

        // Increment iteration count
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

    //Return the global best position

    return globalBestPosition.currentValue;
}

/*
int main(void) {

    //Create a seed for the random number generation
    srand48(time(NULL));

    return 0;
}
*/