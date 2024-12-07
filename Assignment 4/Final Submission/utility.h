#ifndef UTILITY_H
#define UTILITY_H

// Function pointer type for objective functions
typedef double (*ObjectiveFunction)(int, double *);

typedef struct Bound{
    double lowerBound;
    double upperBound;
}Bound;

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


// Function prototypes
double random_double(double min, double max);
double pso(ObjectiveFunction objective_function, int NUM_VARIABLES, Bound *bounds, int NUM_PARTICLES, int MAX_ITERATIONS, double best_position[]);

#endif // UTILITY_H
