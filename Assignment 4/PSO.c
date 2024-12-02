// CODE: include library(s)
#include "utility.h"
#include "OF_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define INERTIAL_WEIGHT 0.7
#define COGNITIVE_COEFFICIENT 1.5
#define SOCIAL_COEFFICIENT 1.5


typedef struct Particle {
    double *decisionVariables;
    double *personalBest;
    double *velocityVariables;
    double currentPosition;
    double personalBestFitness;
} Particle;

//This could've been a particle but to save memory, better to have its own type
typedef struct BestPosition {
    double *decisionVariables;
    double currentValue;
} BestPosition;

// New random function because the old one wouldn't work for me
double random_double(double min, double max) {
    double random_fraction = drand48();
    return min+ (max-min)*random_fraction;

}


// CODE: implement other functions here if necessary

double pso(ObjectiveFunction objective_function, int NUM_VARIABLES, Bound *bounds, int NUM_PARTICLES, int MAX_ITERATIONS, double *best_position) {

    Particle* particleArray[NUM_PARTICLES];

    for (int i = 0; i < NUM_PARTICLES; i++) {
        particleArray[i] = (Particle *)malloc(sizeof(Particle));
        if (particleArray[i] == NULL) {
            printf("Error allocating memory for Particles...");
            exit(EXIT_FAILURE);
        }
    }

    BestPosition globalBestPosition;

    // Initialize global best position
    globalBestPosition.decisionVariables = (double *)malloc(NUM_VARIABLES * sizeof(double));
    if (globalBestPosition.decisionVariables == NULL) {
        printf("Error allocating memory for global best position...");
        exit(EXIT_FAILURE);
    }

    globalBestPosition.currentValue = INFINITY;

    //Initialize all of the dimensions for the particle
    for(int i = 0; i < NUM_PARTICLES; i++) {

        //Malloc everything
        particleArray[i]->decisionVariables = (double *)malloc(NUM_VARIABLES*sizeof(double));
        particleArray[i]->personalBest = (double *)malloc(NUM_VARIABLES*sizeof(double));
        particleArray[i]->velocityVariables = (double *)malloc(NUM_VARIABLES*sizeof(double));

        for(int j=0; j < NUM_VARIABLES; j++) {
            double random_num = random_double(bounds->lowerBound, bounds->upperBound);
            particleArray[i]->decisionVariables[j] = random_num;
            particleArray[i]->personalBest[j] = random_num;

            //Got this line from ChatGPT
            particleArray[i]->velocityVariables[j] = random_double(-fabs(bounds->upperBound - bounds->lowerBound), fabs(bounds->upperBound - bounds->lowerBound));
        }

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

        for (int i = 0; i < NUM_PARTICLES; i++) {
            // Update velocity and position
            for (int j = 0; j < NUM_VARIABLES; j++) {
                double r1 = random_double(0, 1);
                double r2 = random_double(0, 1);

                particleArray[i]->velocityVariables[j] = INERTIAL_WEIGHT * particleArray[i]->velocityVariables[j] +
                    COGNITIVE_COEFFICIENT * r1 * (particleArray[i]->personalBest[j] - particleArray[i]->decisionVariables[j]) +
                    SOCIAL_COEFFICIENT * r2 * (globalBestPosition.decisionVariables[j] - particleArray[i]->decisionVariables[j]);

                // Update position
                particleArray[i]->decisionVariables[j] += particleArray[i]->velocityVariables[j];

                // Clamp position within bounds
                particleArray[i]->decisionVariables[j] = fmax(bounds->lowerBound, fmin(bounds->upperBound, particleArray[i]->decisionVariables[j]));
            }

            double position = objective_function(NUM_VARIABLES, particleArray[i]->decisionVariables);

            particleArray[i]->currentPosition = position;

            // Update personal best if current position is better
            if (position < particleArray[i]->personalBestFitness) {
                memcpy(particleArray[i]->personalBest, particleArray[i]->decisionVariables, NUM_VARIABLES * sizeof(double));
                particleArray[i]->personalBestFitness = position;
            }

            // Update global best if current position is better
            if (position < globalBestPosition.currentValue) {
                globalBestPosition.currentValue = position;
                memcpy(globalBestPosition.decisionVariables, particleArray[i]->decisionVariables, NUM_VARIABLES * sizeof(double));
            }
        }

        // Optional stopping condition
        if (globalBestPosition.currentValue < 1e-8) {
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