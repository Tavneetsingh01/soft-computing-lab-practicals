// Q7. Write a program in C to perform various primitive operations on Fuzzy Sets with Dynamic Components
// Created by tavneet on 4/14/25.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a fuzzy set
typedef struct {
    float *membership; // Array to store membership values
    int size;          // Size of the universe
} FuzzySet;

// Function to create a fuzzy set
FuzzySet createFuzzySet(int size) {
    FuzzySet set;
    set.size = size;
    set.membership = (float *)malloc(size * sizeof(float));

    if (set.membership == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    printf("\n[INFO] Created a fuzzy set with universe size %d\n", size);
    return set;
}

// Function to free memory allocated for a fuzzy set
void freeFuzzySet(FuzzySet set) {
    free(set.membership);
    printf("[INFO] Freed memory allocated for fuzzy set\n");
}

// Function to input membership values for a fuzzy set
void inputFuzzySet(FuzzySet set) {
    printf("\n----- MEMBERSHIP VALUE INPUT -----\n");
    printf("Enter membership values (between 0 and 1):\n");
    printf("Note: Membership values represent the degree to which elements belong to the set\n");

    for (int i = 0; i < set.size; i++) {
        printf("Element %d: ", i + 1);
        scanf("%f", &set.membership[i]);

        // Validate input
        if (set.membership[i] < 0 || set.membership[i] > 1) {
            printf("Invalid input! Membership values must be between 0 and 1.\n");
            i--; // Retry this element
        } else {
            printf("[INFO] Element %d has membership value %.2f\n", i + 1, set.membership[i]);
        }
    }
    printf("------------------------------\n");
}

// Function to display a fuzzy set
void displayFuzzySet(FuzzySet set, const char *name) {
    printf("%s = {", name);
    for (int i = 0; i < set.size; i++) {
        printf("%.2f", set.membership[i]);
        if (i < set.size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

// Function to find the union of two fuzzy sets
FuzzySet fuzzyUnion(FuzzySet set1, FuzzySet set2) {
    if (set1.size != set2.size) {
        printf("Error: Sets must have the same size for union operation.\n");
        exit(1);
    }

    FuzzySet result = createFuzzySet(set1.size);

    printf("\n----- UNION OPERATION DETAILS -----\n");
    printf("Union operation takes the MAXIMUM membership value at each position\n");

    for (int i = 0; i < set1.size; i++) {
        // Union = maximum of membership values
        result.membership[i] = (set1.membership[i] > set2.membership[i]) ?
                                set1.membership[i] : set2.membership[i];

        printf("Element %d: max(%.2f, %.2f) = %.2f\n",
               i + 1, set1.membership[i], set2.membership[i], result.membership[i]);
    }

    printf("-------------------------------\n");
    return result;
}

// Function to find the intersection of two fuzzy sets
FuzzySet fuzzyIntersection(FuzzySet set1, FuzzySet set2) {
    if (set1.size != set2.size) {
        printf("Error: Sets must have the same size for intersection operation.\n");
        exit(1);
    }

    FuzzySet result = createFuzzySet(set1.size);

    printf("\n----- INTERSECTION OPERATION DETAILS -----\n");
    printf("Intersection operation takes the MINIMUM membership value at each position\n");

    for (int i = 0; i < set1.size; i++) {
        // Intersection = minimum of membership values
        result.membership[i] = (set1.membership[i] < set2.membership[i]) ?
                                set1.membership[i] : set2.membership[i];

        printf("Element %d: min(%.2f, %.2f) = %.2f\n",
               i + 1, set1.membership[i], set2.membership[i], result.membership[i]);
    }

    printf("-------------------------------\n");
    return result;
}

// Function to find the complement of a fuzzy set
FuzzySet fuzzyComplement(FuzzySet set) {
    FuzzySet result = createFuzzySet(set.size);

    printf("\n----- COMPLEMENT OPERATION DETAILS -----\n");
    printf("Complement operation calculates (1 - membership value) for each element\n");

    for (int i = 0; i < set.size; i++) {
        // Complement = 1 - membership value
        result.membership[i] = 1.0 - set.membership[i];

        printf("Element %d: 1 - %.2f = %.2f\n",
               i + 1, set.membership[i], result.membership[i]);
    }

    printf("-------------------------------\n");
    return result;
}

// Function to calculate the difference of two fuzzy sets (A - B)
FuzzySet fuzzyDifference(FuzzySet set1, FuzzySet set2) {
    if (set1.size != set2.size) {
        printf("Error: Sets must have the same size for difference operation.\n");
        exit(1);
    }

    FuzzySet result = createFuzzySet(set1.size);

    printf("\n----- DIFFERENCE OPERATION DETAILS -----\n");
    printf("Difference operation (A - B) uses the formula: min(A, 1-B) for each element\n");
    printf("Difference operation (B - A) uses the formula: min(B, 1-A) for each element\n");

    for (int i = 0; i < set1.size; i++) {
        float complementB = 1.0 - set2.membership[i];
        // Difference = min(A, complement of B)
        result.membership[i] = (set1.membership[i] < complementB) ?
                                set1.membership[i] : complementB;

        printf("Element %d: min(%.2f, 1-%.2f) = min(%.2f, %.2f) = %.2f\n",
               i + 1, set1.membership[i], set2.membership[i],
               set1.membership[i], complementB, result.membership[i]);
    }

    printf("-------------------------------\n");
    return result;
}

// Function to check if set1 is a subset of set2
int fuzzySubset(FuzzySet set1, FuzzySet set2) {
    if (set1.size != set2.size) {
        return 0; // Not a subset if sizes differ
    }

    printf("\n----- SUBSET CHECK DETAILS -----\n");
    printf("Set A is a subset of Set B if membership value of A ≤ membership value of B for all elements\n");

    int isSubset = 1; // Assume it's a subset until proven otherwise

    for (int i = 0; i < set1.size; i++) {
        // For set1 to be a subset of set2, each membership in set1 must be <= corresponding value in set2
        printf("Element %d: Checking if %.2f ≤ %.2f ",
               i + 1, set1.membership[i], set2.membership[i]);

        if (set1.membership[i] > set2.membership[i]) {
            printf("(FALSE)\n");
            isSubset = 0;
        } else {
            printf("(TRUE)\n");
        }
    }

    printf("\nConclusion: Set A is %sa subset of Set B\n", isSubset ? "" : "NOT ");
    printf("-------------------------------\n");

    return isSubset;
}

// Function to check if two fuzzy sets are equal
int fuzzyEquals(FuzzySet set1, FuzzySet set2) {
    if (set1.size != set2.size) {
        return 0;
    }

    printf("\n----- EQUALITY CHECK DETAILS -----\n");
    printf("Two fuzzy sets are equal if all corresponding membership values are equal\n");

    int isEqual = 1; // Assume they're equal until proven otherwise

    for (int i = 0; i < set1.size; i++) {
        // Sets are equal if all membership values are equal
        printf("Element %d: Checking if %.2f == %.2f ",
               i + 1, set1.membership[i], set2.membership[i]);

        if (fabs(set1.membership[i] - set2.membership[i]) > 0.0001) {
            printf("(FALSE - difference is %.4f)\n", fabs(set1.membership[i] - set2.membership[i]));
            isEqual = 0;
        } else {
            printf("(TRUE)\n");
        }
    }

    printf("\nConclusion: Set A is %sequal to Set B\n", isEqual ? "" : "NOT ");
    printf("-------------------------------\n");

    return isEqual;
}

// Function to calculate the algebraic sum of two fuzzy sets
FuzzySet fuzzyAlgebraicSum(FuzzySet set1, FuzzySet set2) {
    if (set1.size != set2.size) {
        printf("Error: Sets must have the same size for algebraic sum operation.\n");
        exit(1);
    }

    FuzzySet result = createFuzzySet(set1.size);

    printf("\n----- ALGEBRAIC SUM OPERATION DETAILS -----\n");
    printf("Algebraic Sum uses the formula: a + b - (a × b) for each element\n");

    for (int i = 0; i < set1.size; i++) {
        // Algebraic sum = a + b - a*b
        result.membership[i] = set1.membership[i] + set2.membership[i] -
                              (set1.membership[i] * set2.membership[i]);

        printf("Element %d: %.2f + %.2f - (%.2f × %.2f) = %.2f\n",
               i + 1, set1.membership[i], set2.membership[i],
               set1.membership[i], set2.membership[i], result.membership[i]);
    }

    printf("-------------------------------\n");
    return result;
}

// Function to calculate the algebraic product of two fuzzy sets
FuzzySet fuzzyAlgebraicProduct(FuzzySet set1, FuzzySet set2) {
    if (set1.size != set2.size) {
        printf("Error: Sets must have the same size for algebraic product operation.\n");
        exit(1);
    }

    FuzzySet result = createFuzzySet(set1.size);

    printf("\n----- ALGEBRAIC PRODUCT OPERATION DETAILS -----\n");
    printf("Algebraic Product uses the formula: a × b for each element\n");

    for (int i = 0; i < set1.size; i++) {
        // Algebraic product = a * b
        result.membership[i] = set1.membership[i] * set2.membership[i];

        printf("Element %d: %.2f × %.2f = %.2f\n",
               i + 1, set1.membership[i], set2.membership[i], result.membership[i]);
    }

    printf("-------------------------------\n");
    return result;
}

// Function to calculate the cardinality of a fuzzy set
float fuzzyCardinality(FuzzySet set) {
    float sum = 0.0;

    printf("\n----- CARDINALITY CALCULATION DETAILS -----\n");
    printf("Cardinality is the sum of all membership values\n");
    printf("Calculation: ");

    for (int i = 0; i < set.size; i++) {
        sum += set.membership[i];

        printf("%.2f", set.membership[i]);
        if (i < set.size - 1) {
            printf(" + ");
        }
    }

    printf(" = %.2f\n", sum);
    printf("-------------------------------\n");

    return sum;
}

// Function to perform alpha cut on a fuzzy set
FuzzySet fuzzyAlphaCut(FuzzySet set, float alpha) {
    if (alpha < 0 || alpha > 1) {
        printf("Error: Alpha value must be between 0 and 1.\n");
        exit(1);
    }

    FuzzySet result = createFuzzySet(set.size);

    printf("\n----- ALPHA-CUT OPERATION DETAILS (α = %.2f) -----\n", alpha);
    printf("Alpha-cut creates a crisp set where elements with membership ≥ α get 1.0, others get 0.0\n");

    for (int i = 0; i < set.size; i++) {
        // Elements with membership >= alpha get 1, others get 0
        result.membership[i] = (set.membership[i] >= alpha) ? 1.0 : 0.0;

        printf("Element %d: %.2f %s %.2f, so membership = %.1f\n",
               i + 1, set.membership[i],
               (set.membership[i] >= alpha) ? "≥" : "<",
               alpha, result.membership[i]);
    }

    printf("-------------------------------\n");
    return result;
}

int main() {
    int size;

    printf("\n============================================\n");
    printf("   FUZZY SET OPERATIONS DEMONSTRATION   \n");
    printf("============================================\n");

    // Get the size of the universe
    printf("\nEnter the size of the universe: ");
    scanf("%d", &size);

    printf("\n[INFO] Creating fuzzy sets with universe size %d\n", size);

    // Create two fuzzy sets
    FuzzySet setA = createFuzzySet(size);
    FuzzySet setB = createFuzzySet(size);

    // Input membership values
    printf("\nFor Fuzzy Set A:\n");
    inputFuzzySet(setA);

    printf("\nFor Fuzzy Set B:\n");
    inputFuzzySet(setB);

    // Display the fuzzy sets
    printf("\n============================================\n");
    printf("   INPUT FUZZY SETS   \n");
    printf("============================================\n");
    displayFuzzySet(setA, "Set A");
    displayFuzzySet(setB, "Set B");

    // Perform operations
    printf("\n============================================\n");
    printf("   PERFORMING FUZZY SET OPERATIONS   \n");
    printf("============================================\n");

    FuzzySet unionSet = fuzzyUnion(setA, setB);
    FuzzySet intersectionSet = fuzzyIntersection(setA, setB);
    FuzzySet complementSetA = fuzzyComplement(setA);
    FuzzySet differenceSetA_B = fuzzyDifference(setA, setB);
    FuzzySet differenceSetB_A = fuzzyDifference(setB, setA);
    FuzzySet algebraicSumSet = fuzzyAlgebraicSum(setA, setB);
    FuzzySet algebraicProductSet = fuzzyAlgebraicProduct(setA, setB);

    // Display results
    printf("\n============================================\n");
    printf("   OPERATION RESULTS   \n");
    printf("============================================\n");

    displayFuzzySet(unionSet, "Union (A ∪ B)");
    displayFuzzySet(intersectionSet, "Intersection (A ∩ B)");
    displayFuzzySet(complementSetA, "Complement of A (A')");
    displayFuzzySet(differenceSetA_B, "Difference (A - B)");
    displayFuzzySet(differenceSetB_A, "Difference (B - A)");
    displayFuzzySet(algebraicSumSet, "Algebraic Sum");
    displayFuzzySet(algebraicProductSet, "Algebraic Product");

    // Check if setA is a subset of setB
    int isSubset = fuzzySubset(setA, setB);

    // Check if the sets are equal
    int isEqual = fuzzyEquals(setA, setB);

    // Calculate and display cardinality
    printf("\nCardinality of Set A: %.2f\n", fuzzyCardinality(setA));
    printf("Cardinality of Set B: %.2f\n", fuzzyCardinality(setB));

    // Perform alpha-cut
    float alpha;
    printf("\nEnter alpha value for alpha-cut (between 0 and 1): ");
    scanf("%f", &alpha);

    FuzzySet alphaCutSetA = fuzzyAlphaCut(setA, alpha);
    printf("\nAlpha-cut of Set A with alpha = %.2f:\n", alpha);
    displayFuzzySet(alphaCutSetA, "Alpha-cut Set A");

    FuzzySet alphaCutSetB = fuzzyAlphaCut(setB, alpha);
    printf("\nAlpha-cut of Set B with alpha = %.2f:\n", alpha);
    displayFuzzySet(alphaCutSetB, "Alpha-cut Set B");

    // Free allocated memory
    printf("\n============================================\n");
    printf("   CLEANING UP RESOURCES   \n");
    printf("============================================\n");

    freeFuzzySet(setA);
    freeFuzzySet(setB);
    freeFuzzySet(unionSet);
    freeFuzzySet(intersectionSet);
    freeFuzzySet(complementSetA);
    freeFuzzySet(differenceSetA_B);
    freeFuzzySet(differenceSetB_A);
    freeFuzzySet(algebraicSumSet);
    freeFuzzySet(algebraicProductSet);
    freeFuzzySet(alphaCutSetA);

    printf("\nProgram execution completed successfully!\n");

    return 0;
}