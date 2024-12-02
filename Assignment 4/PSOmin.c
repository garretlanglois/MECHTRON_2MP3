#include "utility.h"
#include "OF_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>  //This file is the minimum lines of code required to implement the PSO

#define INERTIAL_WEIGHT 0.7
#define COGNITIVE_COEFFICIENT 1.5
#define SOCIAL_COEFFICIENT 1.5

typedef struct Particle {
    double *decisionVariables, *personalBest, *velocityVariables;
    double currentPosition, personalBestFitness;
} Particle;

typedef struct BestPosition {
    double *decisionVariables, currentValue;
} BestPosition;

double random_double(double min, double max) { return min + (max - min) * drand48(); }

double pso(ObjectiveFunction objective_function, int NUM_VARIABLES, Bound *bounds, int NUM_PARTICLES, int MAX_ITERATIONS, double *best_position) {
    Particle *particles[NUM_PARTICLES];
    BestPosition globalBest = { malloc(NUM_VARIABLES * sizeof(double)), INFINITY };
    if (!globalBest.decisionVariables) exit(EXIT_FAILURE);

    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i] = malloc(sizeof(Particle));
        if (!particles[i]) exit(EXIT_FAILURE);
        particles[i]->decisionVariables = malloc(NUM_VARIABLES * sizeof(double));
        particles[i]->personalBest = malloc(NUM_VARIABLES * sizeof(double));
        particles[i]->velocityVariables = malloc(NUM_VARIABLES * sizeof(double));

        for (int j = 0; j < NUM_VARIABLES; j++) {
            double rand_num = random_double(bounds->lowerBound, bounds->upperBound);
            particles[i]->decisionVariables[j] = particles[i]->personalBest[j] = rand_num;
            particles[i]->velocityVariables[j] = random_double(-fabs(bounds->upperBound - bounds->lowerBound), fabs(bounds->upperBound - bounds->lowerBound));
        }
        double fitness = objective_function(NUM_VARIABLES, particles[i]->decisionVariables);
        particles[i]->currentPosition = particles[i]->personalBestFitness = fitness;

        if (fitness < globalBest.currentValue) {
            globalBest.currentValue = fitness;
            memcpy(globalBest.decisionVariables, particles[i]->decisionVariables, NUM_VARIABLES * sizeof(double));
        }
    }

    for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
        for (int i = 0; i < NUM_PARTICLES; i++) {
            for (int j = 0; j < NUM_VARIABLES; j++) {
                double r1 = random_double(0, 1), r2 = random_double(0, 1);
                particles[i]->velocityVariables[j] = INERTIAL_WEIGHT * particles[i]->velocityVariables[j] +
                    COGNITIVE_COEFFICIENT * r1 * (particles[i]->personalBest[j] - particles[i]->decisionVariables[j]) +
                    SOCIAL_COEFFICIENT * r2 * (globalBest.decisionVariables[j] - particles[i]->decisionVariables[j]);
                particles[i]->decisionVariables[j] += particles[i]->velocityVariables[j];
                particles[i]->decisionVariables[j] = fmax(bounds->lowerBound, fmin(bounds->upperBound, particles[i]->decisionVariables[j]));
            }

            double fitness = objective_function(NUM_VARIABLES, particles[i]->decisionVariables);
            if (fitness < particles[i]->personalBestFitness) {
                memcpy(particles[i]->personalBest, particles[i]->decisionVariables, NUM_VARIABLES * sizeof(double));
                particles[i]->personalBestFitness = fitness;
            }
            if (fitness < globalBest.currentValue) {
                globalBest.currentValue = fitness;
                memcpy(globalBest.decisionVariables, particles[i]->decisionVariables, NUM_VARIABLES * sizeof(double));
            }
        }
        if (globalBest.currentValue < 1e-8) break;
    }

    memcpy(best_position, globalBest.decisionVariables, NUM_VARIABLES * sizeof(double));
    for (int i = 0; i < NUM_PARTICLES; i++) {
        free(particles[i]->decisionVariables);
        free(particles[i]->personalBest);
        free(particles[i]->velocityVariables);
        free(particles[i]);
    }
    free(globalBest.decisionVariables);
    return globalBest.currentValue;
}