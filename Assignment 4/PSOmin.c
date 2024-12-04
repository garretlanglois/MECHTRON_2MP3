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
    double currentPosition;
    double personalBestFitness;
} Particle;

// New random function because the old one wouldn't work for me
// double random_double(double min, double max) {
//     double random_fraction = drand48();
//     return min + (max - min) * random_fraction;
// }
// New random function using rand() and srand()
double random_double(double min, double max) {
    double random_fraction = (double)rand() / RAND_MAX;
    double return_value = min + (max - min) * random_fraction;
    //printf("%f, %f, %f\n", return_value,min, max);
    return return_value;
}

double pso(ObjectiveFunction objective_function, int NUM_VARIABLES, Bound *bounds, int NUM_PARTICLES, int MAX_ITERATIONS, double *best_position) {


    // Allocate memory for particles
    Particle *particleArray = (Particle *)malloc(NUM_PARTICLES * sizeof(Particle));
    double *velocityArray = (double *)malloc(NUM_PARTICLES * NUM_VARIABLES * sizeof(double));

    if (!particleArray || !velocityArray) {
        printf("Error allocating memory...");
        exit(EXIT_FAILURE);
    }

    Particle *globalBestParticle = NULL;
    double globalBestValue = INFINITY;

    // Initialize particles
    for (int i = 0; i < NUM_PARTICLES; i++) {

        particleArray[i].decisionVariables = (double *)malloc(NUM_VARIABLES * sizeof(double));
        particleArray[i].personalBest = (double *)malloc(NUM_VARIABLES * sizeof(double));

        if (!particleArray[i].decisionVariables || !particleArray[i].personalBest) {
            printf("Error allocating memory for particle dimensions...");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < NUM_VARIABLES; j++) {
            double rand_num = random_double(bounds->lowerBound, bounds->upperBound);
            particleArray[i].decisionVariables[j] = rand_num;
            particleArray[i].personalBest[j] = rand_num;
            velocityArray[i * NUM_VARIABLES + j] = random_double(-fabs(bounds->upperBound - bounds->lowerBound), fabs(bounds->upperBound - bounds->lowerBound));
        }

        double currentPosition = objective_function(NUM_VARIABLES, particleArray[i].decisionVariables);
        particleArray[i].currentPosition = currentPosition;
        particleArray[i].personalBestFitness = currentPosition;

        if (currentPosition < globalBestValue) {
            globalBestValue = currentPosition;
            globalBestParticle = &particleArray[i];
        }
    }

    int iterationCount = 0;

    // Main optimization loop
    while (iterationCount < MAX_ITERATIONS) {
        for (int i = 0; i < NUM_PARTICLES; i++) {
            // Update velocity and position
            for (int j = 0; j < NUM_VARIABLES; j++) {
                double r1 = random_double(0, 1);
                double r2 = random_double(0, 1);

                velocityArray[i * NUM_VARIABLES + j] = INERTIAL_WEIGHT * velocityArray[i * NUM_VARIABLES + j] +
                    COGNITIVE_COEFFICIENT * r1 * (particleArray[i].personalBest[j] - particleArray[i].decisionVariables[j]) +
                    SOCIAL_COEFFICIENT * r2 * (globalBestParticle->decisionVariables[j] - particleArray[i].decisionVariables[j]);

                // Update position
                particleArray[i].decisionVariables[j] += velocityArray[i * NUM_VARIABLES + j];

                // Clamp position within bounds
                particleArray[i].decisionVariables[j] = fmax(bounds->lowerBound, fmin(bounds->upperBound, particleArray[i].decisionVariables[j]));
            }

            double position = objective_function(NUM_VARIABLES, particleArray[i].decisionVariables);
            particleArray[i].currentPosition = position;

            // Update personal best if current position is better
            if (position < particleArray[i].personalBestFitness) {
                memcpy(particleArray[i].personalBest, particleArray[i].decisionVariables, NUM_VARIABLES * sizeof(double));
                particleArray[i].personalBestFitness = position;
            }

            // Update global best if current position is better
            if (position < globalBestValue) {
                globalBestValue = position;
                globalBestParticle = &particleArray[i];
            }
        }

        // Print the optimal fitness every 50 iterations
        if (iterationCount % 50 == 0) {
            printf("Iteration %d: Optimal fitness = %f\n", iterationCount, globalBestValue);
        }

        // Optional stopping condition
        if (globalBestValue < 1e-8) {
            break;
        }

        iterationCount++;
    }

    // Copy global best position to output parameter
    memcpy(best_position, globalBestParticle->personalBest, NUM_VARIABLES * sizeof(double));

    // Free allocated memory
    for (int i = 0; i < NUM_PARTICLES; i++) {
        free(particleArray[i].decisionVariables);
        free(particleArray[i].personalBest);
    }
    free(particleArray);
    free(velocityArray);

    return globalBestValue;
}

/*
int main(void) {
    // Create a seed for the random number generation
    srand48(time(NULL));

    // Example usage here

    return 0;
}
*/
