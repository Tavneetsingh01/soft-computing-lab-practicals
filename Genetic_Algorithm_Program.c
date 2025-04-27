// Q12.  Write a program in C to maximize F(X) = X^2 using Genetic Algorithm where 0<X<31.
// Created by tavneet on 4/27/25.
/**
 * Genetic Algorithm to Maximize F(X) = X² where 0 < X < 31
 *
 * This program implements a genetic algorithm to find the maximum value of F(X) = X²
 * in the range 0 < X < 31. While the analytical solution is simply X = 31 (the upper bound),
 * this program demonstrates the core concepts of genetic algorithms as an optimization technique.
 *
 * GENETIC ALGORITHM OVERVIEW:
 * 1. Representation: We use 5-bit binary encoding (chromosomes) to represent integers from 0-31.
 * 2. Population: Multiple potential solutions evolved together.
 * 3. Selection: Based on fitness (higher is better), mimicking natural selection.
 * 4. Crossover: Combining parts of good solutions to create new ones.
 * 5. Mutation: Random changes to maintain diversity and explore the search space.
 * 6. Evolution: Over generations, the population converges toward optimal solutions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

// Parameters for the genetic algorithm
#define POPULATION_SIZE 10     // Number of individuals in the population
#define MAX_GENERATIONS 50     // Maximum number of generations to run
#define MUTATION_RATE 0.1      // Probability of mutation (0.0 to 1.0)
#define CROSSOVER_RATE 0.7     // Probability of crossover (0.0 to 1.0)
#define CHROMOSOME_SIZE 5      // Number of bits to represent X (2^5 = 32, so we can represent 0-31)
#define TOURNAMENT_SIZE 3      // Number of individuals selected for tournament selection

/**
 * Chromosome Encoding:
 * We use a binary representation with 5 bits, allowing values from 0 to 31.
 * For example:
 * [0,0,0,0,0] represents 0
 * [0,0,0,0,1] represents 1
 * [1,1,1,1,1] represents 31
 *
 * The decoded value is calculated as:
 * X = bit[0]*2^4 + bit[1]*2^3 + bit[2]*2^2 + bit[3]*2^1 + bit[4]*2^0
 */

// Structure to represent an individual in the population
typedef struct {
    int chromosome[CHROMOSOME_SIZE];  // Binary representation (bit array)
    int decoded_value;                // The decoded X value
    double fitness;                   // Fitness value F(X) = X²
} Individual;

// Function prototypes
void initialize_population(Individual population[]);
void evaluate_fitness(Individual *individual);
int binary_to_decimal(int binary[]);
void select_parents(Individual population[], Individual *parent1, Individual *parent2);
void crossover(Individual *parent1, Individual *parent2, Individual *offspring1, Individual *offspring2);
void mutate(Individual *individual);
void copy_individual(Individual *source, Individual *destination);
void print_individual(Individual *individual);
Individual find_best_individual(Individual population[]);
void print_population_stats(Individual population[], int generation);

int main() {
    // Seed the random number generator with current time
    // This ensures different random sequences on each run
    srand(time(NULL));

    // Create and initialize the population with random chromosomes
    Individual population[POPULATION_SIZE];
    initialize_population(population);

    printf("=== Genetic Algorithm to Maximize F(X) = X² where 0 < X < 31 ===\n\n");
    printf("ALGORITHM PARAMETERS:\n");
    printf("- Population size: %d individuals\n", POPULATION_SIZE);
    printf("- Chromosome length: %d bits\n", CHROMOSOME_SIZE);
    printf("- Mutation rate: %.1f%%\n", MUTATION_RATE * 100);
    printf("- Crossover rate: %.1f%%\n", CROSSOVER_RATE * 100);
    printf("- Tournament size: %d individuals\n", TOURNAMENT_SIZE);
    printf("- Maximum generations: %d\n\n", MAX_GENERATIONS);

    // Print initial population details
    printf("INITIAL POPULATION (Generation 0):\n");
    for (int i = 0; i < POPULATION_SIZE; i++) {
        printf("Individual %2d: ", i + 1);
        print_individual(&population[i]);
    }

    // Find and print the best individual in the initial population
    Individual best = find_best_individual(population);
    printf("\nBest individual in initial population:\n");
    print_individual(&best);

    // Calculate and display initial population statistics
    print_population_stats(population, 0);

    // Main GA loop - evolve the population over generations
    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        // Create a new population for the next generation
        Individual new_population[POPULATION_SIZE];

        // ELITISM: Copy the best individual directly to the new population
        // This ensures the best solution is never lost due to randomness
        copy_individual(&best, &new_population[0]);

        // Generate rest of the new population through selection, crossover, and mutation
        for (int i = 1; i < POPULATION_SIZE; i += 2) {
            // SELECTION: Choose two parents based on fitness
            Individual parent1, parent2;
            select_parents(population, &parent1, &parent2);

            // Create offspring through crossover and mutation
            Individual offspring1, offspring2;

            // CROSSOVER: Perform with probability CROSSOVER_RATE
            if ((double)rand() / RAND_MAX < CROSSOVER_RATE) {
                crossover(&parent1, &parent2, &offspring1, &offspring2);

                // Display crossover details for educational purposes (only for first few generations)
                if (generation < 3 && i == 1) {
                    printf("\nCROSSOVER EXAMPLE (Generation %d):\n", generation + 1);
                    printf("Parent 1: ");
                    print_individual(&parent1);
                    printf("Parent 2: ");
                    print_individual(&parent2);
                    printf("Offspring 1: ");
                    print_individual(&offspring1);
                    printf("Offspring 2: ");
                    print_individual(&offspring2);
                }
            } else {
                // No crossover - just copy parents to offspring
                copy_individual(&parent1, &offspring1);
                copy_individual(&parent2, &offspring2);
            }

            // MUTATION: Potentially modify genes in offspring
            mutate(&offspring1);
            mutate(&offspring2);

            // Add offspring to new population
            copy_individual(&offspring1, &new_population[i]);

            // Make sure we don't go beyond the population size
            if (i + 1 < POPULATION_SIZE) {
                copy_individual(&offspring2, &new_population[i + 1]);
            }
        }

        // Replace old population with new population
        for (int i = 0; i < POPULATION_SIZE; i++) {
            copy_individual(&new_population[i], &population[i]);
        }

        // Find the best individual in this generation
        best = find_best_individual(population);

        // Print progress every 10 generations or at the end
        if (generation % 10 == 0 || generation == MAX_GENERATIONS - 1) {
            print_population_stats(population, generation + 1);
        }
    }

    // Print final result
    printf("\nFINAL SOLUTION after %d generations:\n", MAX_GENERATIONS);
    printf("Best chromosome: [");
    for (int i = 0; i < CHROMOSOME_SIZE; i++) {
        printf("%d", best.chromosome[i]);
        if (i < CHROMOSOME_SIZE - 1) printf(",");
    }
    printf("]\n");
    printf("Decoded value (X): %d\n", best.decoded_value);
    printf("Fitness value F(X) = X²: %.0f\n", best.fitness);
    printf("\nTheoretical maximum: X = 31, F(X) = 961\n");

    return 0;
}

/**
 * Initialize the population with random chromosomes
 *
 * DETAILED EXPLANATION:
 * 1. We create POPULATION_SIZE individuals, each with a random chromosome
 * 2. For each chromosome, we randomly assign 0 or 1 to each bit position
 * 3. After creating a random chromosome, we evaluate its fitness
 *
 * This random initialization ensures diversity in the initial population,
 * which is important for genetic algorithms to work effectively.
 */
void initialize_population(Individual population[]) {
    printf("\nINITIALIZATION PROCESS:\n");
    printf("- Creating %d individuals with random 5-bit chromosomes\n", POPULATION_SIZE);

    for (int i = 0; i < POPULATION_SIZE; i++) {
        // Randomly initialize chromosome bits
        printf("- Individual %d chromosome generation: ", i + 1);

        for (int j = 0; j < CHROMOSOME_SIZE; j++) {
            // Randomly assign 0 or 1 to each bit position
            population[i].chromosome[j] = rand() % 2;
            printf("%d", population[i].chromosome[j]);
        }

        // Evaluate fitness for this individual
        evaluate_fitness(&population[i]);

        printf(" → Decoded value: %d, Fitness: %.0f\n",
               population[i].decoded_value,
               population[i].fitness);
    }
    printf("\n");
}

/**
 * Calculate fitness for an individual
 *
 * DETAILED EXPLANATION:
 * 1. We first decode the binary chromosome to get the decimal value X
 * 2. Then we calculate the fitness as F(X) = X²
 *
 * The fitness function determines how "good" a solution is.
 * Since we're maximizing X², higher values of X produce higher fitness values.
 */
void evaluate_fitness(Individual *individual) {
    // Decode binary chromosome to decimal value
    individual->decoded_value = binary_to_decimal(individual->chromosome);

    // Calculate fitness: F(X) = X²
    individual->fitness = (double)(individual->decoded_value * individual->decoded_value);
}

/**
 * Convert a binary array to decimal
 *
 * DETAILED EXPLANATION:
 * This function converts a binary (base-2) number to a decimal (base-10) number.
 *
 * For example, binary [1,0,1,1,0] is calculated as:
 * 1*2^4 + 0*2^3 + 1*2^2 + 1*2^1 + 0*2^0 = 16 + 0 + 4 + 2 + 0 = 22
 *
 * We calculate this by iterating through each bit and multiplying it by its
 * corresponding power of 2, determined by its position in the array.
 */
int binary_to_decimal(int binary[]) {
    int decimal = 0;

    for (int i = 0; i < CHROMOSOME_SIZE; i++) {
        // Calculate the place value (power of 2) for this bit position
        // For a 5-bit number, the positions have these values:
        // [0]: 2^4 = 16
        // [1]: 2^3 = 8
        // [2]: 2^2 = 4
        // [3]: 2^1 = 2
        // [4]: 2^0 = 1
        int place_value = 1 << (CHROMOSOME_SIZE - 1 - i);

        // Add this bit's contribution to the decimal value
        decimal += binary[i] * place_value;
    }

    return decimal;
}

/**
 * Tournament selection
 *
 * DETAILED EXPLANATION:
 * 1. We randomly select TOURNAMENT_SIZE individuals from the population
 * 2. We compare their fitness values and choose the one with highest fitness
 * 3. We repeat this process to get another parent
 *
 * Tournament selection mimics natural selection by giving fitter individuals
 * a higher chance of being selected, while still allowing some diversity.
 * The tournament size determines the selection pressure - larger tournaments
 * favor fitter individuals more strongly.
 */
void select_parents(Individual population[], Individual *parent1, Individual *parent2) {
    // Select first parent using tournament selection
    int best_index = rand() % POPULATION_SIZE;

    // Run tournament for first parent
    for (int i = 1; i < TOURNAMENT_SIZE; i++) {
        int candidate_index = rand() % POPULATION_SIZE;

        // Compare fitness and keep track of the best
        if (population[candidate_index].fitness > population[best_index].fitness) {
            best_index = candidate_index;
        }
    }

    // Copy the winner of the tournament as the first parent
    copy_individual(&population[best_index], parent1);

    // Select second parent (ensuring it's different from first if possible)
    int second_best_index;
    do {
        second_best_index = rand() % POPULATION_SIZE;

        // Run tournament for second parent
        for (int i = 1; i < TOURNAMENT_SIZE; i++) {
            int candidate_index = rand() % POPULATION_SIZE;

            if (population[candidate_index].fitness > population[second_best_index].fitness) {
                second_best_index = candidate_index;
            }
        }
    } while (second_best_index == best_index && POPULATION_SIZE > 1); // Avoid identical parents if possible

    // Copy the winner of the second tournament as the second parent
    copy_individual(&population[second_best_index], parent2);
}

/**
 * Single-point crossover
 *
 * DETAILED EXPLANATION:
 * 1. We randomly choose a crossover point between 0 and CHROMOSOME_SIZE-1
 * 2. For the first offspring, we take genes from parent1 up to the crossover point
 *    and from parent2 after the crossover point
 * 3. For the second offspring, we do the opposite
 *
 * Crossover combines genetic material from two parents to create new individuals.
 * This mimics biological reproduction and allows good traits from different parents
 * to be combined, potentially creating better offspring.
 */
void crossover(Individual *parent1, Individual *parent2, Individual *offspring1, Individual *offspring2) {
    // Choose a random crossover point (0 to CHROMOSOME_SIZE-1)
    int crossover_point = rand() % CHROMOSOME_SIZE;

    // Create first offspring: parent1's genes up to crossover_point, then parent2's genes
    for (int i = 0; i < CHROMOSOME_SIZE; i++) {
        if (i < crossover_point) {
            offspring1->chromosome[i] = parent1->chromosome[i]; // Take from parent1
        } else {
            offspring1->chromosome[i] = parent2->chromosome[i]; // Take from parent2
        }
    }

    // Create second offspring: parent2's genes up to crossover_point, then parent1's genes
    for (int i = 0; i < CHROMOSOME_SIZE; i++) {
        if (i < crossover_point) {
            offspring2->chromosome[i] = parent2->chromosome[i]; // Take from parent2
        } else {
            offspring2->chromosome[i] = parent1->chromosome[i]; // Take from parent1
        }
    }

    // Evaluate fitness for the new offspring
    evaluate_fitness(offspring1);
    evaluate_fitness(offspring2);
}

/**
 * Mutation
 *
 * DETAILED EXPLANATION:
 * 1. For each bit in the chromosome, we generate a random number between 0 and 1
 * 2. If this number is less than MUTATION_RATE, we flip the bit (0 becomes 1, 1 becomes 0)
 * 3. After mutation, we re-evaluate the fitness of the individual
 *
 * Mutation introduces small random changes in the genetic material.
 * This helps maintain diversity in the population and allows exploration of the search space.
 * Without mutation, the algorithm might get stuck at local optima.
 */
void mutate(Individual *individual) {
    bool mutated = false;
    printf("  Mutation process: [");

    for (int i = 0; i < CHROMOSOME_SIZE; i++) {
        // For each bit, generate a random probability
        double random_prob = (double)rand() / RAND_MAX;

        // Print the original bit
        printf("%d", individual->chromosome[i]);

        // If the random probability is less than MUTATION_RATE, flip the bit
        if (random_prob < MUTATION_RATE) {
            printf("*"); // Mark mutation with an asterisk
            individual->chromosome[i] = 1 - individual->chromosome[i]; // Flip the bit
            mutated = true;
        } else {
            printf(" "); // Space for no mutation
        }

        if (i < CHROMOSOME_SIZE - 1) printf(",");
    }

    printf("] → ");

    // If mutation occurred, re-evaluate fitness
    if (mutated) {
        int old_decoded = individual->decoded_value;
        double old_fitness = individual->fitness;

        evaluate_fitness(individual);

        printf("Value changed: %d → %d, Fitness: %.0f → %.0f\n",
               old_decoded, individual->decoded_value,
               old_fitness, individual->fitness);
    } else {
        printf("No mutation occurred\n");
    }
}

/**
 * Copy one individual to another
 *
 * DETAILED EXPLANATION:
 * This function creates a deep copy of one individual to another,
 * copying the chromosome bit by bit and all other properties.
 */
void copy_individual(Individual *source, Individual *destination) {
    for (int i = 0; i < CHROMOSOME_SIZE; i++) {
        destination->chromosome[i] = source->chromosome[i];
    }
    destination->decoded_value = source->decoded_value;
    destination->fitness = source->fitness;
}

/**
 * Print details of an individual
 *
 * DETAILED EXPLANATION:
 * This function displays the chromosome as a binary string,
 * its decoded decimal value, and its fitness value.
 */
void print_individual(Individual *individual) {
    // Print chromosome as binary string
    printf("Chromosome: [");
    for (int i = 0; i < CHROMOSOME_SIZE; i++) {
        printf("%d", individual->chromosome[i]);
        if (i < CHROMOSOME_SIZE - 1) {
            printf(",");
        }
    }
    printf("] → X = %2d, F(X) = %.0f\n", individual->decoded_value, individual->fitness);
}

/**
 * Find the individual with the highest fitness in the population
 *
 * DETAILED EXPLANATION:
 * This function iterates through the entire population and keeps track
 * of the individual with the highest fitness value.
 */
Individual find_best_individual(Individual population[]) {
    int best_index = 0;

    for (int i = 1; i < POPULATION_SIZE; i++) {
        if (population[i].fitness > population[best_index].fitness) {
            best_index = i;
        }
    }

    return population[best_index];
}

/**
 * Calculate and print statistics about the population
 *
 * DETAILED EXPLANATION:
 * This function calculates the average fitness, finds the best and worst
 * individuals, and displays these statistics for the current generation.
 */
void print_population_stats(Individual population[], int generation) {
    double total_fitness = 0;
    Individual best = population[0];
    Individual worst = population[0];

    for (int i = 0; i < POPULATION_SIZE; i++) {
        total_fitness += population[i].fitness;

        if (population[i].fitness > best.fitness) {
            copy_individual(&population[i], &best);
        }

        if (population[i].fitness < worst.fitness) {
            copy_individual(&population[i], &worst);
        }
    }

    double avg_fitness = total_fitness / POPULATION_SIZE;

    printf("\nGENERATION %d STATISTICS:\n", generation);
    printf("- Average fitness: %.2f\n", avg_fitness);
    printf("- Best individual: X = %d, F(X) = %.0f\n", best.decoded_value, best.fitness);
    printf("- Worst individual: X = %d, F(X) = %.0f\n", worst.decoded_value, worst.fitness);

    // Display convergence information
    if (best.decoded_value == 31) {
        printf("- OPTIMAL SOLUTION FOUND! X = 31, F(X) = 961\n");
    } else {
        printf("- Distance from optimal: %.2f%%\n", 100.0 * (1.0 - best.fitness / 961.0));
    }
}