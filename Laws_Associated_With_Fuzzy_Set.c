// Q8. Write a program in C to verify various Laws associated with Fuzzy Sets.
// Created by tavneet on 4/19/25.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Define the maximum size of the universe
#define MAX_UNIVERSE_SIZE 100

/**
 * Function to get a valid float value within range [0,1] from user
 * @param prompt The message to display to the user
 * @return A float value between 0 and 1 inclusive
 */
float getValidFuzzyValue(const char* prompt) {
    float value;
    int valid = 0;

    while (!valid) {
        printf("%s (between 0 and 1): ", prompt);
        if (scanf("%f", &value) != 1) {
            // Clear input buffer if invalid input
            while (getchar() != '\n');
            printf("Error: Please enter a valid number.\n");
            continue;
        }

        // Check if value is in valid range for fuzzy membership
        if (value < 0.0 || value > 1.0) {
            printf("Error: Value must be between 0 and 1.\n");
            continue;
        }

        valid = 1;
    }

    return value;
}

/**
 * Function to input a fuzzy set from the user
 * @param name The name of the fuzzy set
 * @param set Array to store the fuzzy set
 * @param size The size of the universe
 */
void inputFuzzySet(const char* name, float* set, int size) {
    printf("\nEnter membership values for fuzzy set %s:\n", name);
    printf("----------------------------------------\n");
    printf("In fuzzy set theory, each element has a membership value between 0 and 1,\n");
    printf("where 0 means no membership and 1 means full membership.\n\n");

    for (int i = 0; i < size; i++) {
        char prompt[100];
        sprintf(prompt, "Element %d in set %s", i+1, name);
        set[i] = getValidFuzzyValue(prompt);
    }
}

/**
 * Function to input a fuzzy relation matrix from the user
 * @param name The name of the relation
 * @param relation Array to store the relation matrix (flattened)
 * @param size The size of the universe
 */
void inputFuzzyRelation(const char* name, float* relation, int size) {
    printf("\nEnter values for fuzzy relation %s (%dx%d matrix):\n", name, size, size);
    printf("--------------------------------------------------\n");
    printf("A fuzzy relation is a matrix where each cell R(i,j) represents the\n");
    printf("strength of relationship between elements i and j (value between 0 and 1).\n\n");

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char prompt[100];
            sprintf(prompt, "R(%d,%d) in relation %s", i+1, j+1, name);
            relation[i*size + j] = getValidFuzzyValue(prompt);
        }
    }
}

/**
 * Function to print a fuzzy set
 * @param name The name of the fuzzy set
 * @param set Array containing the fuzzy set
 * @param size The size of the universe
 */
void printFuzzySet(const char* name, float* set, int size) {
    printf("%s = {", name);
    for (int i = 0; i < size; i++) {
        printf("%.2f", set[i]);
        if (i < size - 1) printf(", ");
    }
    printf("}\n");
}

/**
 * Function to print a fuzzy relation as a matrix
 * @param name The name of the relation
 * @param relation Array containing the relation (flattened matrix)
 * @param size The size of the universe
 */
void printFuzzyRelation(const char* name, float* relation, int size) {
    printf("\nRelation %s (%dx%d matrix):\n", name, size, size);
    printf("-------------------------\n");

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.2f ", relation[i*size + j]);
        }
        printf("\n");
    }
}

/**
 * Function to verify idempotent laws for fuzzy sets
 * Idempotent Laws:
 * 1. A ∪ A = A (Union with itself equals itself)
 * 2. A ∩ A = A (Intersection with itself equals itself)
 * @param A The fuzzy set
 * @param size The size of the universe
 */
void verifyIdempotentLaws(float* A, int size) {
    printf("\n=== IDEMPOTENT LAWS ===\n");
    printf("These laws verify that a set combined with itself remains unchanged.\n");
    printf("1. A ∪ A = A (Union with itself equals itself)\n");
    printf("2. A ∩ A = A (Intersection with itself equals itself)\n\n");

    // Create arrays for results
    float* unionResult = (float*)malloc(size * sizeof(float));
    float* intersectionResult = (float*)malloc(size * sizeof(float));

    printf("Step-by-step calculations:\n");
    printf("-------------------------\n");

    // Compute A ∪ A (using max operator for union)
    printf("For A ∪ A (Union):\n");
    for (int i = 0; i < size; i++) {
        unionResult[i] = fmax(A[i], A[i]);
        printf("  Element %d: max(%.2f, %.2f) = %.2f\n", i+1, A[i], A[i], unionResult[i]);
    }

    printf("\nFor A ∩ A (Intersection):\n");
    // Compute A ∩ A (using min operator for intersection)
    for (int i = 0; i < size; i++) {
        intersectionResult[i] = fmin(A[i], A[i]);
        printf("  Element %d: min(%.2f, %.2f) = %.2f\n", i+1, A[i], A[i], intersectionResult[i]);
    }

    printf("\nResults summary:\n");
    printFuzzySet("A", A, size);
    printFuzzySet("A ∪ A", unionResult, size);
    printFuzzySet("A ∩ A", intersectionResult, size);

    // Verify laws
    int unionValid = 1, intersectionValid = 1;
    printf("\nVerification checks:\n");
    for (int i = 0; i < size; i++) {
        printf("  Element %d: A=%.2f, A∪A=%.2f, A∩A=%.2f\n",
               i+1, A[i], unionResult[i], intersectionResult[i]);

        if (fabs(unionResult[i] - A[i]) > 0.001) {
            unionValid = 0;
            printf("    * Union law failed: %.2f != %.2f\n", unionResult[i], A[i]);
        }

        if (fabs(intersectionResult[i] - A[i]) > 0.001) {
            intersectionValid = 0;
            printf("    * Intersection law failed: %.2f != %.2f\n", intersectionResult[i], A[i]);
        }
    }

    printf("\nVerification Results:\n");
    printf("A ∪ A = A: %s\n", unionValid ? "VERIFIED" : "FAILED");
    printf("A ∩ A = A: %s\n", intersectionValid ? "VERIFIED" : "FAILED");

    // Explanation
    printf("\nExplanation:\n");
    printf("In fuzzy set theory, the union operation uses the maximum of membership values,\n");
    printf("while intersection uses the minimum. When a set is united or intersected with itself,\n");
    printf("the result should be identical to the original set.\n");
    printf("\nThis is because:\n");
    printf("- For any element, max(x, x) = x\n");
    printf("- For any element, min(x, x) = x\n");
    printf("Therefore, both idempotent laws should always be verified for any fuzzy set.\n");

    free(unionResult);
    free(intersectionResult);
}

/**
 * Function to verify commutative laws for fuzzy sets
 * Commutative Laws:
 * 1. A ∪ B = B ∪ A (Order doesn't matter in union)
 * 2. A ∩ B = B ∩ A (Order doesn't matter in intersection)
 * @param A First fuzzy set
 * @param B Second fuzzy set
 * @param size The size of the universe
 */
void verifyCommutativeLaws(float* A, float* B, int size) {
    printf("\n=== COMMUTATIVE LAWS ===\n");
    printf("These laws verify that the order of operands doesn't matter in unions and intersections.\n");
    printf("1. A ∪ B = B ∪ A (Order doesn't matter in union)\n");
    printf("2. A ∩ B = B ∩ A (Order doesn't matter in intersection)\n\n");

    // Create arrays for results
    float* unionAB = (float*)malloc(size * sizeof(float));
    float* unionBA = (float*)malloc(size * sizeof(float));
    float* intersectionAB = (float*)malloc(size * sizeof(float));
    float* intersectionBA = (float*)malloc(size * sizeof(float));

    printf("Step-by-step calculations:\n");
    printf("-------------------------\n");

    // Compute A ∪ B
    printf("For A ∪ B (Union of A and B):\n");
    for (int i = 0; i < size; i++) {
        unionAB[i] = fmax(A[i], B[i]);
        printf("  Element %d: max(%.2f, %.2f) = %.2f\n", i+1, A[i], B[i], unionAB[i]);
    }

    // Compute B ∪ A
    printf("\nFor B ∪ A (Union of B and A):\n");
    for (int i = 0; i < size; i++) {
        unionBA[i] = fmax(B[i], A[i]);
        printf("  Element %d: max(%.2f, %.2f) = %.2f\n", i+1, B[i], A[i], unionBA[i]);
    }

    // Compute A ∩ B
    printf("\nFor A ∩ B (Intersection of A and B):\n");
    for (int i = 0; i < size; i++) {
        intersectionAB[i] = fmin(A[i], B[i]);
        printf("  Element %d: min(%.2f, %.2f) = %.2f\n", i+1, A[i], B[i], intersectionAB[i]);
    }

    // Compute B ∩ A
    printf("\nFor B ∩ A (Intersection of B and A):\n");
    for (int i = 0; i < size; i++) {
        intersectionBA[i] = fmin(B[i], A[i]);
        printf("  Element %d: min(%.2f, %.2f) = %.2f\n", i+1, B[i], A[i], intersectionBA[i]);
    }

    printf("\nResults summary:\n");
    printFuzzySet("A", A, size);
    printFuzzySet("B", B, size);
    printFuzzySet("A ∪ B", unionAB, size);
    printFuzzySet("B ∪ A", unionBA, size);
    printFuzzySet("A ∩ B", intersectionAB, size);
    printFuzzySet("B ∩ A", intersectionBA, size);

    // Verify laws
    int unionValid = 1, intersectionValid = 1;
    printf("\nVerification checks:\n");
    for (int i = 0; i < size; i++) {
        printf("  Element %d: A∪B=%.2f, B∪A=%.2f | A∩B=%.2f, B∩A=%.2f\n",
               i+1, unionAB[i], unionBA[i], intersectionAB[i], intersectionBA[i]);

        if (fabs(unionAB[i] - unionBA[i]) > 0.001) {
            unionValid = 0;
            printf("    * Union commutativity failed: %.2f != %.2f\n", unionAB[i], unionBA[i]);
        }

        if (fabs(intersectionAB[i] - intersectionBA[i]) > 0.001) {
            intersectionValid = 0;
            printf("    * Intersection commutativity failed: %.2f != %.2f\n",
                   intersectionAB[i], intersectionBA[i]);
        }
    }

    printf("\nVerification Results:\n");
    printf("A ∪ B = B ∪ A: %s\n", unionValid ? "VERIFIED" : "FAILED");
    printf("A ∩ B = B ∩ A: %s\n", intersectionValid ? "VERIFIED" : "FAILED");

    // Explanation
    printf("\nExplanation:\n");
    printf("The commutative property states that changing the order of operands doesn't change\n");
    printf("the result. For fuzzy sets, this means that:\n");
    printf("- A ∪ B equals B ∪ A because max(a,b) = max(b,a) for any values a and b\n");
    printf("- A ∩ B equals B ∩ A because min(a,b) = min(b,a) for any values a and b\n");
    printf("This property always holds true for max and min operations in fuzzy set theory.\n");

    free(unionAB);
    free(unionBA);
    free(intersectionAB);
    free(intersectionBA);
}

/**
 * Function to verify associative laws for fuzzy sets
 * Associative Laws:
 * 1. (A ∪ B) ∪ C = A ∪ (B ∪ C) (Grouping doesn't matter in union)
 * 2. (A ∩ B) ∩ C = A ∩ (B ∩ C) (Grouping doesn't matter in intersection)
 * @param A First fuzzy set
 * @param B Second fuzzy set
 * @param C Third fuzzy set
 * @param size The size of the universe
 */
void verifyAssociativeLaws(float* A, float* B, float* C, int size) {
    printf("\n=== ASSOCIATIVE LAWS ===\n");
    printf("These laws verify that the grouping of operands doesn't matter in operations.\n");
    printf("1. (A ∪ B) ∪ C = A ∪ (B ∪ C) (Grouping doesn't matter in union)\n");
    printf("2. (A ∩ B) ∩ C = A ∩ (B ∩ C) (Grouping doesn't matter in intersection)\n\n");

    // Create arrays for results
    float* unionAB = (float*)malloc(size * sizeof(float));
    float* unionABC1 = (float*)malloc(size * sizeof(float));
    float* unionBC = (float*)malloc(size * sizeof(float));
    float* unionABC2 = (float*)malloc(size * sizeof(float));

    float* intersectionAB = (float*)malloc(size * sizeof(float));
    float* intersectionABC1 = (float*)malloc(size * sizeof(float));
    float* intersectionBC = (float*)malloc(size * sizeof(float));
    float* intersectionABC2 = (float*)malloc(size * sizeof(float));

    printf("Step-by-step calculations:\n");
    printf("-------------------------\n");

    // Compute (A ∪ B) ∪ C
    printf("For (A ∪ B) ∪ C:\n");
    printf("  Step 1: Calculate A ∪ B\n");
    for (int i = 0; i < size; i++) {
        unionAB[i] = fmax(A[i], B[i]);
        printf("    Element %d: max(%.2f, %.2f) = %.2f\n", i+1, A[i], B[i], unionAB[i]);
    }

    printf("  Step 2: Calculate (A ∪ B) ∪ C\n");
    for (int i = 0; i < size; i++) {
        unionABC1[i] = fmax(unionAB[i], C[i]);
        printf("    Element %d: max(%.2f, %.2f) = %.2f\n", i+1, unionAB[i], C[i], unionABC1[i]);
    }

    // Compute A ∪ (B ∪ C)
    printf("\nFor A ∪ (B ∪ C):\n");
    printf("  Step 1: Calculate B ∪ C\n");
    for (int i = 0; i < size; i++) {
        unionBC[i] = fmax(B[i], C[i]);
        printf("    Element %d: max(%.2f, %.2f) = %.2f\n", i+1, B[i], C[i], unionBC[i]);
    }

    printf("  Step 2: Calculate A ∪ (B ∪ C)\n");
    for (int i = 0; i < size; i++) {
        unionABC2[i] = fmax(A[i], unionBC[i]);
        printf("    Element %d: max(%.2f, %.2f) = %.2f\n", i+1, A[i], unionBC[i], unionABC2[i]);
    }

    // Compute (A ∩ B) ∩ C
    printf("\nFor (A ∩ B) ∩ C:\n");
    printf("  Step 1: Calculate A ∩ B\n");
    for (int i = 0; i < size; i++) {
        intersectionAB[i] = fmin(A[i], B[i]);
        printf("    Element %d: min(%.2f, %.2f) = %.2f\n", i+1, A[i], B[i], intersectionAB[i]);
    }

    printf("  Step 2: Calculate (A ∩ B) ∩ C\n");
    for (int i = 0; i < size; i++) {
        intersectionABC1[i] = fmin(intersectionAB[i], C[i]);
        printf("    Element %d: min(%.2f, %.2f) = %.2f\n",
               i+1, intersectionAB[i], C[i], intersectionABC1[i]);
    }

    // Compute A ∩ (B ∩ C)
    printf("\nFor A ∩ (B ∩ C):\n");
    printf("  Step 1: Calculate B ∩ C\n");
    for (int i = 0; i < size; i++) {
        intersectionBC[i] = fmin(B[i], C[i]);
        printf("    Element %d: min(%.2f, %.2f) = %.2f\n", i+1, B[i], C[i], intersectionBC[i]);
    }

    printf("  Step 2: Calculate A ∩ (B ∩ C)\n");
    for (int i = 0; i < size; i++) {
        intersectionABC2[i] = fmin(A[i], intersectionBC[i]);
        printf("    Element %d: min(%.2f, %.2f) = %.2f\n",
               i+1, A[i], intersectionBC[i], intersectionABC2[i]);
    }

    printf("\nResults summary:\n");
    printFuzzySet("A", A, size);
    printFuzzySet("B", B, size);
    printFuzzySet("C", C, size);
    printFuzzySet("(A ∪ B) ∪ C", unionABC1, size);
    printFuzzySet("A ∪ (B ∪ C)", unionABC2, size);
    printFuzzySet("(A ∩ B) ∩ C", intersectionABC1, size);
    printFuzzySet("A ∩ (B ∩ C)", intersectionABC2, size);

    // Verify laws
    int unionValid = 1, intersectionValid = 1;
    printf("\nVerification checks:\n");
    for (int i = 0; i < size; i++) {
        printf("  Element %d: (A∪B)∪C=%.2f, A∪(B∪C)=%.2f | (A∩B)∩C=%.2f, A∩(B∩C)=%.2f\n",
               i+1, unionABC1[i], unionABC2[i], intersectionABC1[i], intersectionABC2[i]);

        if (fabs(unionABC1[i] - unionABC2[i]) > 0.001) {
            unionValid = 0;
            printf("    * Union associativity failed: %.2f != %.2f\n", unionABC1[i], unionABC2[i]);
        }

        if (fabs(intersectionABC1[i] - intersectionABC2[i]) > 0.001) {
            intersectionValid = 0;
            printf("    * Intersection associativity failed: %.2f != %.2f\n",
                   intersectionABC1[i], intersectionABC2[i]);
        }
    }

    printf("\nVerification Results:\n");
    printf("(A ∪ B) ∪ C = A ∪ (B ∪ C): %s\n", unionValid ? "VERIFIED" : "FAILED");
    printf("(A ∩ B) ∩ C = A ∩ (B ∩ C): %s\n", intersectionValid ? "VERIFIED" : "FAILED");

    // Explanation
    printf("\nExplanation:\n");
    printf("The associative property states that the grouping of operands doesn't affect the result.\n");
    printf("This is mathematically true because:\n");
    printf("- For union: max(max(a,b),c) = max(a,max(b,c)) for any values a, b, and c\n");
    printf("- For intersection: min(min(a,b),c) = min(a,min(b,c)) for any values a, b, and c\n");
    printf("This property allows us to write A ∪ B ∪ C or A ∩ B ∩ C without ambiguity about grouping.\n");

    free(unionAB);
    free(unionABC1);
    free(unionBC);
    free(unionABC2);
    free(intersectionAB);
    free(intersectionABC1);
    free(intersectionBC);
    free(intersectionABC2);
}

/**
 * Function to verify distributive laws for fuzzy sets
 * Distributive Laws:
 * 1. A ∩ (B ∪ C) = (A ∩ B) ∪ (A ∩ C)
 * 2. A ∪ (B ∩ C) = (A ∪ B) ∩ (A ∪ C)
 * @param A First fuzzy set
 * @param B Second fuzzy set
 * @param C Third fuzzy set
 * @param size The size of the universe
 */
void verifyDistributiveLaws(float* A, float* B, float* C, int size) {
    printf("\n=== DISTRIBUTIVE LAWS ===\n");
    printf("These laws verify how operations distribute over each other.\n");
    printf("1. A ∩ (B ∪ C) = (A ∩ B) ∪ (A ∩ C)\n");
    printf("2. A ∪ (B ∩ C) = (A ∪ B) ∩ (A ∪ C)\n\n");

    // Create arrays for results
    float* unionBC = (float*)malloc(size * sizeof(float));
    float* intersectionABC1 = (float*)malloc(size * sizeof(float));
    float* intersectionAB = (float*)malloc(size * sizeof(float));
    float* intersectionAC = (float*)malloc(size * sizeof(float));
    float* unionABC2 = (float*)malloc(size * sizeof(float));

    float* intersectionBC = (float*)malloc(size * sizeof(float));
    float* unionABC1 = (float*)malloc(size * sizeof(float));
    float* unionAB = (float*)malloc(size * sizeof(float));
    float* unionAC = (float*)malloc(size * sizeof(float));
    float* intersectionABC2 = (float*)malloc(size * sizeof(float));

    printf("Step-by-step calculations:\n");
    printf("-------------------------\n");

    // 1. Compute A ∩ (B ∪ C)
    printf("For A ∩ (B ∪ C):\n");
    printf("  Step 1: Calculate B ∪ C\n");
    for (int i = 0; i < size; i++) {
        unionBC[i] = fmax(B[i], C[i]);
        printf("    Element %d: max(%.2f, %.2f) = %.2f\n", i+1, B[i], C[i], unionBC[i]);
    }

    printf("  Step 2: Calculate A ∩ (B ∪ C)\n");
    for (int i = 0; i < size; i++) {
        intersectionABC1[i] = fmin(A[i], unionBC[i]);
        printf("    Element %d: min(%.2f, %.2f) = %.2f\n",
               i+1, A[i], unionBC[i], intersectionABC1[i]);
    }

    // Compute (A ∩ B) ∪ (A ∩ C)
    printf("\nFor (A ∩ B) ∪ (A ∩ C):\n");
    printf("  Step 1: Calculate A ∩ B\n");
    for (int i = 0; i < size; i++) {
        intersectionAB[i] = fmin(A[i], B[i]);
        printf("    Element %d: min(%.2f, %.2f) = %.2f\n", i+1, A[i], B[i], intersectionAB[i]);
    }

    printf("  Step 2: Calculate A ∩ C\n");
    for (int i = 0; i < size; i++) {
        intersectionAC[i] = fmin(A[i], C[i]);
        printf("    Element %d: min(%.2f, %.2f) = %.2f\n", i+1, A[i], C[i], intersectionAC[i]);
    }

    printf("  Step 3: Calculate (A ∩ B) ∪ (A ∩ C)\n");
    for (int i = 0; i < size; i++) {
        unionABC2[i] = fmax(intersectionAB[i], intersectionAC[i]);
        printf("    Element %d: max(%.2f, %.2f) = %.2f\n",
               i+1, intersectionAB[i], intersectionAC[i], unionABC2[i]);
    }

    // 2. Compute A ∪ (B ∩ C)
    printf("\nFor A ∪ (B ∩ C):\n");
    printf("  Step 1: Calculate B ∩ C\n");
    for (int i = 0; i < size; i++) {
        intersectionBC[i] = fmin(B[i], C[i]);
        printf("    Element %d: min(%.2f, %.2f) = %.2f\n", i+1, B[i], C[i], intersectionBC[i]);
    }

    printf("  Step 2: Calculate A ∪ (B ∩ C)\n");
    for (int i = 0; i < size; i++) {
        unionABC1[i] = fmax(A[i], intersectionBC[i]);
        printf("    Element %d: max(%.2f, %.2f) = %.2f\n",
               i+1, A[i], intersectionBC[i], unionABC1[i]);
    }

    // Compute (A ∪ B) ∩ (A ∪ C)
    printf("\nFor (A ∪ B) ∩ (A ∪ C):\n");
    printf("  Step 1: Calculate A ∪ B\n");
    for (int i = 0; i < size; i++) {
        unionAB[i] = fmax(A[i], B[i]);
        printf("    Element %d: max(%.2f, %.2f) = %.2f\n", i+1, A[i], B[i], unionAB[i]);
    }

    printf("  Step 2: Calculate A ∪ C\n");
    for (int i = 0; i < size; i++) {
        unionAC[i] = fmax(A[i], C[i]);
        printf("    Element %d: max(%.2f, %.2f) = %.2f\n", i+1, A[i], C[i], unionAC[i]);
    }

    printf("  Step 3: Calculate (A ∪ B) ∩ (A ∪ C)\n");
    for (int i = 0; i < size; i++) {
        intersectionABC2[i] = fmin(unionAB[i], unionAC[i]);
        printf("    Element %d: min(%.2f, %.2f) = %.2f\n",
               i+1, unionAB[i], unionAC[i], intersectionABC2[i]);
    }

    printf("\nResults summary:\n");
    printFuzzySet("A", A, size);
    printFuzzySet("B", B, size);
    printFuzzySet("C", C, size);
    printFuzzySet("A ∩ (B ∪ C)", intersectionABC1, size);
    printFuzzySet("(A ∩ B) ∪ (A ∩ C)", unionABC2, size);
    printFuzzySet("A ∪ (B ∩ C)", unionABC1, size);
    printFuzzySet("(A ∪ B) ∩ (A ∪ C)", intersectionABC2, size);

    // Verify laws
    int distributive1Valid = 1, distributive2Valid = 1;
    printf("\nVerification checks:\n");
    for (int i = 0; i < size; i++) {
        printf("  Element %d: A∩(B∪C)=%.2f, (A∩B)∪(A∩C)=%.2f | A∪(B∩C)=%.2f, (A∪B)∩(A∪C)=%.2f\n",
               i+1, intersectionABC1[i], unionABC2[i], unionABC1[i], intersectionABC2[i]);

        if (fabs(intersectionABC1[i] - unionABC2[i]) > 0.001) {
            distributive1Valid = 0;
            printf("    * First distributive law failed: %.2f != %.2f\n",
                   intersectionABC1[i], unionABC2[i]);
        }

        if (fabs(unionABC1[i] - intersectionABC2[i]) > 0.001) {
            distributive2Valid = 0;
            printf("    * Second distributive law failed: %.2f != %.2f\n",
                   unionABC1[i], intersectionABC2[i]);
        }
    }

    printf("\nVerification Results:\n");
    printf("A ∩ (B ∪ C) = (A ∩ B) ∪ (A ∩ C): %s\n",
           distributive1Valid ? "VERIFIED" : "FAILED ");
    printf("A ∪ (B ∩ C) = (A ∪ B) ∩ (A ∪ C): %s\n",
           distributive2Valid ? "VERIFIED" : "FAILED");

    // Explanation
    printf("\nExplanation:\n");
    printf("The distributive laws show how operations distribute over each other:\n");
    printf("1. First law: A ∩ (B ∪ C) = (A ∩ B) ∪ (A ∩ C)\n");
    printf("   This means intersection distributes over union in fuzzy set theory.\n");
    printf("2. Second law: A ∪ (B ∩ C) = (A ∪ B) ∩ (A ∪ C)\n");
    printf("   This means union distributes over intersection in fuzzy set theory.\n");
    printf("Both laws should always hold for fuzzy sets using min and max operators.\n");

    // Free allocated memory
    free(unionBC);
    free(intersectionABC1);
    free(intersectionAB);
    free(intersectionAC);
    free(unionABC2);
    free(intersectionBC);
    free(unionABC1);
    free(unionAB);
    free(unionAC);
    free(intersectionABC2);
}

/**
 * Function to verify De Morgan's laws for fuzzy sets
 * De Morgan's Laws:
 * 1. (A ∪ B)' = A' ∩ B' (Complement of union equals intersection of complements)
 * 2. (A ∩ B)' = A' ∪ B' (Complement of intersection equals union of complements)
 * @param A First fuzzy set
 * @param B Second fuzzy set
 * @param size The size of the universe
 */
void verifyDeMorganLaws(float* A, float* B, int size) {
    printf("\n=== DE MORGAN'S LAWS ===\n");
    printf("These laws relate the complement of combinations of sets to combinations of complements.\n");
    printf("1. (A ∪ B)' = A' ∩ B' (Complement of union equals intersection of complements)\n");
    printf("2. (A ∩ B)' = A' ∪ B' (Complement of intersection equals union of complements)\n\n");

    // Create arrays for results
    float* complementA = (float*)malloc(size * sizeof(float));
    float* complementB = (float*)malloc(size * sizeof(float));
    float* unionAB = (float*)malloc(size * sizeof(float));
    float* complementUnionAB = (float*)malloc(size * sizeof(float));
    float* intersectionComplementAB = (float*)malloc(size * sizeof(float));
    float* intersectionAB = (float*)malloc(size * sizeof(float));
    float* complementIntersectionAB = (float*)malloc(size * sizeof(float));
    float* unionComplementAB = (float*)malloc(size * sizeof(float));

    printf("Step-by-step calculations:\n");
    printf("-------------------------\n");

    // Calculate complements of A and B
    printf("Calculating complements:\n");
    for (int i = 0; i < size; i++) {
        complementA[i] = 1.0 - A[i];
        complementB[i] = 1.0 - B[i];
        printf("  Element %d: A'=1-%.2f=%.2f, B'=1-%.2f=%.2f\n",
               i+1, A[i], complementA[i], B[i], complementB[i]);
    }

    // Verify first De Morgan's law: (A ∪ B)' = A' ∩ B'
    printf("\nFor first De Morgan's law (A ∪ B)' = A' ∩ B':\n");
    printf("  Step 1: Calculate A ∪ B\n");
    for (int i = 0; i < size; i++) {
        unionAB[i] = fmax(A[i], B[i]);
        printf("    Element %d: max(%.2f, %.2f) = %.2f\n", i+1, A[i], B[i], unionAB[i]);
    }

    printf("  Step 2: Calculate (A ∪ B)'\n");
    for (int i = 0; i < size; i++) {
        complementUnionAB[i] = 1.0 - unionAB[i];
        printf("    Element %d: 1 - %.2f = %.2f\n", i+1, unionAB[i], complementUnionAB[i]);
    }

    printf("  Step 3: Calculate A' ∩ B'\n");
    for (int i = 0; i < size; i++) {
        intersectionComplementAB[i] = fmin(complementA[i], complementB[i]);
        printf("    Element %d: min(%.2f, %.2f) = %.2f\n",
               i+1, complementA[i], complementB[i], intersectionComplementAB[i]);
    }

    // Verify second De Morgan's law: (A ∩ B)' = A' ∪ B'
    printf("\nFor second De Morgan's law (A ∩ B)' = A' ∪ B':\n");
    printf("  Step 1: Calculate A ∩ B\n");
    for (int i = 0; i < size; i++) {
        intersectionAB[i] = fmin(A[i], B[i]);
        printf("    Element %d: min(%.2f, %.2f) = %.2f\n", i+1, A[i], B[i], intersectionAB[i]);
    }

    printf("  Step 2: Calculate (A ∩ B)'\n");
    for (int i = 0; i < size; i++) {
        complementIntersectionAB[i] = 1.0 - intersectionAB[i];
        printf("    Element %d: 1 - %.2f = %.2f\n",
               i+1, intersectionAB[i], complementIntersectionAB[i]);
    }

    printf("  Step 3: Calculate A' ∪ B'\n");
    for (int i = 0; i < size; i++) {
        unionComplementAB[i] = fmax(complementA[i], complementB[i]);
        printf("    Element %d: max(%.2f, %.2f) = %.2f\n",
               i+1, complementA[i], complementB[i], unionComplementAB[i]);
    }

    printf("\nResults summary:\n");
    printFuzzySet("A", A, size);
    printFuzzySet("B", B, size);
    printFuzzySet("A'", complementA, size);
    printFuzzySet("B'", complementB, size);
    printFuzzySet("(A ∪ B)'", complementUnionAB, size);
    printFuzzySet("A' ∩ B'", intersectionComplementAB, size);
    printFuzzySet("(A ∩ B)'", complementIntersectionAB, size);
    printFuzzySet("A' ∪ B'", unionComplementAB, size);

    // Verify laws
    int deMorgan1Valid = 1, deMorgan2Valid = 1;
    printf("\nVerification checks:\n");
    for (int i = 0; i < size; i++) {
        printf("  Element %d: (A∪B)'=%.2f, A'∩B'=%.2f | (A∩B)'=%.2f, A'∪B'=%.2f\n",
               i+1, complementUnionAB[i], intersectionComplementAB[i],
               complementIntersectionAB[i], unionComplementAB[i]);

        if (fabs(complementUnionAB[i] - intersectionComplementAB[i]) > 0.001) {
            deMorgan1Valid = 0;
            printf("    * First De Morgan's law failed: %.2f != %.2f\n",
                   complementUnionAB[i], intersectionComplementAB[i]);
        }

        if (fabs(complementIntersectionAB[i] - unionComplementAB[i]) > 0.001) {
            deMorgan2Valid = 0;
            printf("    * Second De Morgan's law failed: %.2f != %.2f\n",
                   complementIntersectionAB[i], unionComplementAB[i]);
        }
    }

    printf("\nVerification Results:\n");
    printf("(A ∪ B)' = A' ∩ B': %s\n", deMorgan1Valid ? "VERIFIED" : "FAILED");
    printf("(A ∩ B)' = A' ∪ B': %s\n", deMorgan2Valid ? "VERIFIED" : "FAILED");

    // Explanation
    printf("\nExplanation:\n");
    printf("De Morgan's laws relate complements of combined sets to combinations of complements:\n");
    printf("1. The complement of a union equals the intersection of complements\n");
    printf("2. The complement of an intersection equals the union of complements\n");
    printf("In fuzzy set theory, these laws translate to:\n");
    printf("1. 1 - max(a,b) = min(1-a, 1-b) for any values a and b in [0,1]\n");
    printf("2. 1 - min(a,b) = max(1-a, 1-b) for any values a and b in [0,1]\n");
    printf("These properties always hold mathematically for fuzzy sets.\n");

    // Free allocated memory
    free(complementA);
    free(complementB);
    free(unionAB);
    free(complementUnionAB);
    free(intersectionComplementAB);
    free(intersectionAB);
    free(complementIntersectionAB);
    free(unionComplementAB);
}

/**
 * Function to verify the law of excluded middle for fuzzy sets
 * Law of Excluded Middle: A ∪ A' = U (universal set)
 * Note: In fuzzy sets, this law may not hold, unlike in classical sets
 * @param A The fuzzy set
 * @param size The size of the universe
 */
void verifyExcludedMiddleLaw(float* A, int size) {
    printf("\n=== LAW OF EXCLUDED MIDDLE ===\n");
    printf("This law states that a set united with its complement equals the universal set.\n");
    printf("Law of Excluded Middle: A ∪ A' = U (universal set)\n");
    printf("Note: In classical sets, this always holds, but may not in fuzzy sets.\n\n");

    // Create arrays for results
    float* complementA = (float*)malloc(size * sizeof(float));
    float* unionWithComplement = (float*)malloc(size * sizeof(float));
    float* universalSet = (float*)malloc(size * sizeof(float));

    // Set universal set (all 1s)
    for (int i = 0; i < size; i++) {
        universalSet[i] = 1.0;
    }

    printf("Step-by-step calculations:\n");
    printf("-------------------------\n");

    // Calculate complement of A
    printf("Calculating complement of A:\n");
    for (int i = 0; i < size; i++) {
        complementA[i] = 1.0 - A[i];
        printf("  Element %d: A'=1-%.2f=%.2f\n", i+1, A[i], complementA[i]);
    }

    // Calculate A ∪ A'
    printf("\nCalculating A ∪ A':\n");
    for (int i = 0; i < size; i++) {
        unionWithComplement[i] = fmax(A[i], complementA[i]);
        printf("  Element %d: max(%.2f, %.2f) = %.2f\n",
               i+1, A[i], complementA[i], unionWithComplement[i]);
    }

    printf("\nResults summary:\n");
    printFuzzySet("A", A, size);
    printFuzzySet("A'", complementA, size);
    printFuzzySet("A ∪ A'", unionWithComplement, size);
    printFuzzySet("Universal Set (U)", universalSet, size);

    // Verify law
    int excludedMiddleValid = 1;
    printf("\nVerification checks:\n");
    for (int i = 0; i < size; i++) {
        printf("  Element %d: A∪A'=%.2f, U=%.2f\n",
               i+1, unionWithComplement[i], universalSet[i]);

        if (fabs(unionWithComplement[i] - universalSet[i]) > 0.001) {
            excludedMiddleValid = 0;
            printf("    * Law of excluded middle failed: %.2f != %.2f\n",
                   unionWithComplement[i], universalSet[i]);
        }
    }

    printf("\nVerification Result:\n");
    printf("A ∪ A' = U: %s\n", excludedMiddleValid ? "VERIFIED" : "FAILED");

    // Explanation
    printf("\nExplanation:\n");
    printf("The law of excluded middle states that a set united with its complement equals\n");
    printf("the universal set. In classical set theory, this always holds true.\n");
    printf("However, in fuzzy set theory, max(a, 1-a) is not necessarily equal to 1.\n");
    printf("The law holds only when the membership value of an element is either 0 or 1,\n");
    printf("but may fail for values in between (e.g., max(0.3, 0.7) = 0.7 ≠ 1).\n");
    printf("This is one of the ways fuzzy set theory differs from classical set theory.\n");

    // Free allocated memory
    free(complementA);
    free(unionWithComplement);
    free(universalSet);
}

/**
 * Function to verify the law of contradiction for fuzzy sets
 * Law of Contradiction: A ∩ A' = ∅ (empty set)
 * Note: In fuzzy sets, this law may not hold, unlike in classical sets
 * @param A The fuzzy set
 * @param size The size of the universe
 */
void verifyContradictionLaw(float* A, int size) {
    printf("\n=== LAW OF CONTRADICTION ===\n");
    printf("This law states that a set intersected with its complement equals the empty set.\n");
    printf("Law of Contradiction: A ∩ A' = ∅ (empty set)\n");
    printf("Note: In classical sets, this always holds, but may not in fuzzy sets.\n\n");

    // Create arrays for results
    float* complementA = (float*)malloc(size * sizeof(float));
    float* intersectionWithComplement = (float*)malloc(size * sizeof(float));
    float* emptySet = (float*)malloc(size * sizeof(float));

    // Set empty set (all 0s)
    for (int i = 0; i < size; i++) {
        emptySet[i] = 0.0;
    }

    printf("Step-by-step calculations:\n");
    printf("-------------------------\n");

    // Calculate complement of A
    printf("Calculating complement of A:\n");
    for (int i = 0; i < size; i++) {
        complementA[i] = 1.0 - A[i];
        printf("  Element %d: A'=1-%.2f=%.2f\n", i+1, A[i], complementA[i]);
    }

    // Calculate A ∩ A'
    printf("\nCalculating A ∩ A':\n");
    for (int i = 0; i < size; i++) {
        intersectionWithComplement[i] = fmin(A[i], complementA[i]);
        printf("  Element %d: min(%.2f, %.2f) = %.2f\n",
               i+1, A[i], complementA[i], intersectionWithComplement[i]);
    }

    printf("\nResults summary:\n");
    printFuzzySet("A", A, size);
    printFuzzySet("A'", complementA, size);
    printFuzzySet("A ∩ A'", intersectionWithComplement, size);
    printFuzzySet("Empty Set (∅)", emptySet, size);

    // Verify law
    int contradictionValid = 1;
    printf("\nVerification checks:\n");
    for (int i = 0; i < size; i++) {
        printf("  Element %d: A∩A'=%.2f, ∅=%.2f\n",
               i+1, intersectionWithComplement[i], emptySet[i]);

        if (fabs(intersectionWithComplement[i] - emptySet[i]) > 0.001) {
            contradictionValid = 0;
            printf("    * Law of contradiction failed: %.2f != %.2f\n",
                   intersectionWithComplement[i], emptySet[i]);
        }
    }

    printf("\nVerification Result:\n");
    printf("A ∩ A' = ∅: %s\n", contradictionValid ? "VERIFIED" : "FAILED");

    // Explanation
    printf("\nExplanation:\n");
    printf("The law of contradiction states that a set intersected with its complement\n");
    printf("equals the empty set. In classical set theory, this always holds true.\n");
    printf("However, in fuzzy set theory, min(a, 1-a) is not necessarily equal to 0.\n");
    printf("The law holds only when the membership value of an element is either 0 or 1,\n");
    printf("but may fail for values in between (e.g., min(0.4, 0.6) = 0.4 ≠ 0).\n");
    printf("This is another fundamental difference between fuzzy and classical set theory.\n");

    // Free allocated memory
    free(complementA);
    free(intersectionWithComplement);
    free(emptySet);
}

/**
 * Function to verify the involution law for fuzzy sets
 * Involution Law: (A')' = A (Double complement equals the original set)
 * @param A The fuzzy set
 * @param size The size of the universe
 */
void verifyInvolutionLaw(float* A, int size) {
    printf("\n=== INVOLUTION LAW ===\n");
    printf("This law states that the double complement of a set equals the original set.\n");
    printf("Involution Law: (A')' = A\n\n");

    // Create arrays for results
    float* complementA = (float*)malloc(size * sizeof(float));
    float* doubleComplementA = (float*)malloc(size * sizeof(float));

    printf("Step-by-step calculations:\n");
    printf("-------------------------\n");

    // Calculate complement of A
    printf("Step 1: Calculate A'\n");
    for (int i = 0; i < size; i++) {
        complementA[i] = 1.0 - A[i];
        printf("  Element %d: A'=1-%.2f=%.2f\n", i+1, A[i], complementA[i]);
    }

    // Calculate (A')'
    printf("\nStep 2: Calculate (A')'\n");
    for (int i = 0; i < size; i++) {
        doubleComplementA[i] = 1.0 - complementA[i];
        printf("  Element %d: (A')'=1-%.2f=%.2f\n", i+1, complementA[i], doubleComplementA[i]);
    }

    printf("\nResults summary:\n");
    printFuzzySet("A", A, size);
    printFuzzySet("A'", complementA, size);
    printFuzzySet("(A')'", doubleComplementA, size);

    // Verify law
    int involutionValid = 1;
    printf("\nVerification checks:\n");
    for (int i = 0; i < size; i++) {
        printf("  Element %d: A=%.2f, (A')'=%.2f\n", i+1, A[i], doubleComplementA[i]);

        if (fabs(A[i] - doubleComplementA[i]) > 0.001) {
            involutionValid = 0;
            printf("    * Involution law failed: %.2f != %.2f\n", A[i], doubleComplementA[i]);
        }
    }

    printf("\nVerification Result:\n");
    printf("(A')' = A: %s\n", involutionValid ? "VERIFIED" : "FAILED");

    // Explanation
    printf("\nExplanation:\n");
    printf("The involution law states that the complement of the complement of a set\n");
    printf("equals the original set. In fuzzy set theory, this means (1-(1-a)) = a.\n");
    printf("This law always holds in fuzzy sets, as the double negation of a value\n");
    printf("mathematically returns the original value.\n");

    // Free allocated memory
    free(complementA);
    free(doubleComplementA);
}

/**
 * Function to verify absorption laws for fuzzy sets
 * Absorption Laws:
 * 1. A ∪ (A ∩ B) = A
 * 2. A ∩ (A ∪ B) = A
 * @param A First fuzzy set
 * @param B Second fuzzy set
 * @param size The size of the universe
 */
void verifyAbsorptionLaws(float* A, float* B, int size) {
    printf("\n=== ABSORPTION LAWS ===\n");
    printf("These laws show how certain combinations of operations result in absorption.\n");
    printf("1. A ∪ (A ∩ B) = A\n");
    printf("2. A ∩ (A ∪ B) = A\n\n");

    // Create arrays for results
    float* intersectionAB = (float*)malloc(size * sizeof(float));
    float* unionWithIntersection = (float*)malloc(size * sizeof(float));
    float* unionAB = (float*)malloc(size * sizeof(float));
    float* intersectionWithUnion = (float*)malloc(size * sizeof(float));

    printf("Step-by-step calculations:\n");
    printf("-------------------------\n");

    // 1. Verify A ∪ (A ∩ B) = A
    printf("For first absorption law A ∪ (A ∩ B) = A:\n");
    printf("  Step 1: Calculate A ∩ B\n");
    for (int i = 0; i < size; i++) {
        intersectionAB[i] = fmin(A[i], B[i]);
        printf("    Element %d: min(%.2f, %.2f) = %.2f\n", i+1, A[i], B[i], intersectionAB[i]);
    }

    printf("  Step 2: Calculate A ∪ (A ∩ B)\n");
    for (int i = 0; i < size; i++) {
        unionWithIntersection[i] = fmax(A[i], intersectionAB[i]);
        printf("    Element %d: max(%.2f, %.2f) = %.2f\n",
               i+1, A[i], intersectionAB[i], unionWithIntersection[i]);
    }

    // 2. Verify A ∩ (A ∪ B) = A
    printf("\nFor second absorption law A ∩ (A ∪ B) = A:\n");
    printf("  Step 1: Calculate A ∪ B\n");
    for (int i = 0; i < size; i++) {
        unionAB[i] = fmax(A[i], B[i]);
        printf("    Element %d: max(%.2f, %.2f) = %.2f\n", i+1, A[i], B[i], unionAB[i]);
    }

    printf("  Step 2: Calculate A ∩ (A ∪ B)\n");
    for (int i = 0; i < size; i++) {
        intersectionWithUnion[i] = fmin(A[i], unionAB[i]);
        printf("    Element %d: min(%.2f, %.2f) = %.2f\n",
               i+1, A[i], unionAB[i], intersectionWithUnion[i]);
    }

    printf("\nResults summary:\n");
    printFuzzySet("A", A, size);
    printFuzzySet("B", B, size);
    printFuzzySet("A ∩ B", intersectionAB, size);
    printFuzzySet("A ∪ (A ∩ B)", unionWithIntersection, size);
    printFuzzySet("A ∪ B", unionAB, size);
    printFuzzySet("A ∩ (A ∪ B)", intersectionWithUnion, size);

    // Verify laws
    int absorption1Valid = 1, absorption2Valid = 1;
    printf("\nVerification checks:\n");
    for (int i = 0; i < size; i++) {
        printf("  Element %d: A=%.2f, A∪(A∩B)=%.2f, A∩(A∪B)=%.2f\n",
               i+1, A[i], unionWithIntersection[i], intersectionWithUnion[i]);

        if (fabs(A[i] - unionWithIntersection[i]) > 0.001) {
            absorption1Valid = 0;
            printf("    * First absorption law failed: %.2f != %.2f\n",
                   A[i], unionWithIntersection[i]);
        }

        if (fabs(A[i] - intersectionWithUnion[i]) > 0.001) {
            absorption2Valid = 0;
            printf("    * Second absorption law failed: %.2f != %.2f\n",
                   A[i], intersectionWithUnion[i]);
        }
    }

    printf("\nVerification Results:\n");
    printf("A ∪ (A ∩ B) = A: %s\n", absorption1Valid ? "VERIFIED" : "FAILED");
    printf("A ∩ (A ∪ B) = A: %s\n", absorption2Valid ? "VERIFIED" : "FAILED");

    // Explanation
    printf("\nExplanation:\n");
    printf("The absorption laws demonstrate how certain combinations of operations result in\n");
    printf("the original set. These laws work because:\n");
    printf("1. For the first law: max(a, min(a,b)) = a for any values a,b in [0,1]\n");
    printf("   This is because min(a,b) ≤ a, so max(a, min(a,b)) = a\n");
    printf("2. For the second law: min(a, max(a,b)) = a for any values a,b in [0,1]\n");
    printf("   This is because max(a,b) ≥ a, so min(a, max(a,b)) = a\n");
    printf("These laws show how combining a set with itself in certain ways 'absorbs'\n");
    printf("the influence of the second set, resulting in the original set.\n");

    // Free allocated memory
    free(intersectionAB);
    free(unionWithIntersection);
    free(unionAB);
    free(intersectionWithUnion);
}

/**
 * Function to verify identity laws for fuzzy sets
 * Identity Laws:
 * 1. A ∪ ∅ = A (Union with empty set gives the original set)
 * 2. A ∩ U = A (Intersection with universal set gives the original set)
 * @param A The fuzzy set
 * @param size The size of the universe
 */
void verifyIdentityLaws(float* A, int size) {
    printf("\n=== IDENTITY LAWS ===\n");
    printf("These laws show how sets interact with special sets (empty set and universal set).\n");
    printf("1. A ∪ ∅ = A (Union with empty set gives the original set)\n");
    printf("2. A ∩ U = A (Intersection with universal set gives the original set)\n\n");

    // Create arrays for results
    float* emptySet = (float*)malloc(size * sizeof(float));
    float* universalSet = (float*)malloc(size * sizeof(float));
    float* unionWithEmpty = (float*)malloc(size * sizeof(float));
    float* intersectionWithUniversal = (float*)malloc(size * sizeof(float));

    // Set empty set (all 0s) and universal set (all 1s)
    for (int i = 0; i < size; i++) {
        emptySet[i] = 0.0;
        universalSet[i] = 1.0;
    }

    printf("Step-by-step calculations:\n");
    printf("-------------------------\n");

    // 1. Verify A ∪ ∅ = A
    printf("For first identity law A ∪ ∅ = A:\n");
    for (int i = 0; i < size; i++) {
        unionWithEmpty[i] = fmax(A[i], emptySet[i]);
        printf("  Element %d: max(%.2f, %.2f) = %.2f\n", i+1, A[i], emptySet[i], unionWithEmpty[i]);
    }

    // 2. Verify A ∩ U = A
    printf("\nFor second identity law A ∩ U = A:\n");
    for (int i = 0; i < size; i++) {
        intersectionWithUniversal[i] = fmin(A[i], universalSet[i]);
        printf("  Element %d: min(%.2f, %.2f) = %.2f\n",
               i+1, A[i], universalSet[i], intersectionWithUniversal[i]);
    }

    printf("\nResults summary:\n");
    printFuzzySet("A", A, size);
    printFuzzySet("Empty Set (∅)", emptySet, size);
    printFuzzySet("Universal Set (U)", universalSet, size);
    printFuzzySet("A ∪ ∅", unionWithEmpty, size);
    printFuzzySet("A ∩ U", intersectionWithUniversal, size);

    // Verify laws
    int identity1Valid = 1, identity2Valid = 1;
    printf("\nVerification checks:\n");
    for (int i = 0; i < size; i++) {
        printf("  Element %d: A=%.2f, A∪∅=%.2f, A∩U=%.2f\n",
               i+1, A[i], unionWithEmpty[i], intersectionWithUniversal[i]);

        if (fabs(A[i] - unionWithEmpty[i]) > 0.001) {
            identity1Valid = 0;
            printf("    * First identity law failed: %.2f != %.2f\n", A[i], unionWithEmpty[i]);
        }

        if (fabs(A[i] - intersectionWithUniversal[i]) > 0.001) {
            identity2Valid = 0;
            printf("    * Second identity law failed: %.2f != %.2f\n",
                   A[i], intersectionWithUniversal[i]);
        }
    }

    printf("\nVerification Results:\n");
    printf("A ∪ ∅ = A: %s\n", identity1Valid ? "VERIFIED" : "FAILED");
    printf("A ∩ U = A: %s\n", identity2Valid ? "VERIFIED" : "FAILED");

    // Explanation
    printf("\nExplanation:\n");
    printf("The identity laws show how fuzzy sets interact with special sets:\n");
    printf("1. Union with empty set (all 0s): max(a,0) = a for any value a in [0,1]\n");
    printf("   The empty set acts as the identity element for the union operation.\n");
    printf("2. Intersection with universal set (all 1s): min(a,1) = a for any value a in [0,1]\n");
    printf("   The universal set acts as the identity element for the intersection operation.\n");
    printf("These laws demonstrate that certain sets don't change the original set under specific operations.\n");

    // Free allocated memory
    free(emptySet);
    free(universalSet);
    free(unionWithEmpty);
    free(intersectionWithUniversal);
}

/**
 * Function to verify domination laws for fuzzy sets
 * Domination Laws:
 * 1. A ∪ U = U (Union with universal set gives universal set)
 * 2. A ∩ ∅ = ∅ (Intersection with empty set gives empty set)
 * @param A The fuzzy set
 * @param size The size of the universe
 */
void verifyDominationLaws(float* A, int size) {
    printf("\n=== DOMINATION LAWS ===\n");
    printf("These laws demonstrate when a set is dominated by special sets in operations.\n");
    printf("1. A ∪ U = U (Union with universal set gives universal set)\n");
    printf("2. A ∩ ∅ = ∅ (Intersection with empty set gives empty set)\n\n");

    // Create arrays for results
    float* emptySet = (float*)malloc(size * sizeof(float));
    float* universalSet = (float*)malloc(size * sizeof(float));
    float* unionWithUniversal = (float*)malloc(size * sizeof(float));
    float* intersectionWithEmpty = (float*)malloc(size * sizeof(float));

    // Set empty set (all 0s) and universal set (all 1s)
    for (int i = 0; i < size; i++) {
        emptySet[i] = 0.0;
        universalSet[i] = 1.0;
    }

    printf("Step-by-step calculations:\n");
    printf("-------------------------\n");

    // 1. Verify A ∪ U = U
    printf("For first domination law A ∪ U = U:\n");
    for (int i = 0; i < size; i++) {
        unionWithUniversal[i] = fmax(A[i], universalSet[i]);
        printf("  Element %d: max(%.2f, %.2f) = %.2f\n",
               i+1, A[i], universalSet[i], unionWithUniversal[i]);
    }

    // 2. Verify A ∩ ∅ = ∅
    printf("\nFor second domination law A ∩ ∅ = ∅:\n");
    for (int i = 0; i < size; i++) {
        intersectionWithEmpty[i] = fmin(A[i], emptySet[i]);
        printf("  Element %d: min(%.2f, %.2f) = %.2f\n",
               i+1, A[i], emptySet[i], intersectionWithEmpty[i]);
    }

    printf("\nResults summary:\n");
    printFuzzySet("A", A, size);
    printFuzzySet("Empty Set (∅)", emptySet, size);
    printFuzzySet("Universal Set (U)", universalSet, size);
    printFuzzySet("A ∪ U", unionWithUniversal, size);
    printFuzzySet("A ∩ ∅", intersectionWithEmpty, size);

    // Verify laws
    int domination1Valid = 1, domination2Valid = 1;
    printf("\nVerification checks:\n");
    for (int i = 0; i < size; i++) {
        printf("  Element %d: A∪U=%.2f, U=%.2f | A∩∅=%.2f, ∅=%.2f\n",
               i+1, unionWithUniversal[i], universalSet[i],
               intersectionWithEmpty[i], emptySet[i]);

        if (fabs(universalSet[i] - unionWithUniversal[i]) > 0.001) {
            domination1Valid = 0;
            printf("    * First domination law failed: %.2f != %.2f\n",
                   unionWithUniversal[i], universalSet[i]);
        }

        if (fabs(emptySet[i] - intersectionWithEmpty[i]) > 0.001) {
            domination2Valid = 0;
            printf("    * Second domination law failed: %.2f != %.2f\n",
                   intersectionWithEmpty[i], emptySet[i]);
        }
    }

    printf("\nVerification Results:\n");
    printf("A ∪ U = U: %s\n", domination1Valid ? "VERIFIED" : "FAILED");
    printf("A ∩ ∅ = ∅: %s\n", domination2Valid ? "VERIFIED" : "FAILED");

    // Explanation
    printf("\nExplanation:\n");
    printf("The domination laws show how certain sets dominate in operations:\n");
    printf("1. Union with universal set (all 1s): max(a,1) = 1 for any value a in [0,1]\n");
    printf("   The universal set dominates in the union operation.\n");
    printf("2. Intersection with empty set (all 0s): min(a,0) = 0 for any value a in [0,1]\n");
    printf("   The empty set dominates in the intersection operation.\n");
    printf("These laws show how certain special sets have dominant properties in set operations.\n");

    // Free allocated memory
    free(emptySet);
    free(universalSet);
    free(unionWithUniversal);
    free(intersectionWithEmpty);
}

/**
 * Main function - menu to select and verify different fuzzy set laws
 */
int main() {
    int size = 0;
    int choice;
    float *A = NULL, *B = NULL, *C = NULL;
    float *R = NULL, *S = NULL; // For relations

    printf("=================================================================\n");
    printf("       FUZZY SET LAWS VERIFICATION PROGRAM (C IMPLEMENTATION)     \n");
    printf("=================================================================\n");
    printf("This program demonstrates and verifies various laws of fuzzy sets\n");
    printf("using numerical examples and step-by-step calculations.\n\n");

    // Get universe size
    while (size <= 0 || size > MAX_UNIVERSE_SIZE) {
        printf("Enter the size of universe (1-%d): ", MAX_UNIVERSE_SIZE);
        if (scanf("%d", &size) != 1 || size <= 0 || size > MAX_UNIVERSE_SIZE) {
            printf("Invalid input. Please enter a positive integer up to %d.\n", MAX_UNIVERSE_SIZE);
            // Clear input buffer
            while (getchar() != '\n');
        }
    }

    // Allocate memory for fuzzy sets
    A = (float*)malloc(size * sizeof(float));
    B = (float*)malloc(size * sizeof(float));
    C = (float*)malloc(size * sizeof(float));

    // Allocate memory for fuzzy relations
    R = (float*)malloc(size * size * sizeof(float));
    S = (float*)malloc(size * size * sizeof(float));

    // Input fuzzy sets
    inputFuzzySet("A", A, size);
    inputFuzzySet("B", B, size);
    inputFuzzySet("C", C, size);

    do {
        // Display menu
        printf("\n=================================================================\n");
        printf("              FUZZY SET LAWS VERIFICATION MENU                    \n");
        printf("=================================================================\n");
        printf("1. Verify Idempotent Laws (A ∪ A = A, A ∩ A = A)\n");
        printf("2. Verify Commutative Laws (A ∪ B = B ∪ A, A ∩ B = B ∩ A)\n");
        printf("3. Verify Associative Laws (A ∪ (B ∪ C) = (A ∪ B) ∪ C, etc.)\n");
        printf("4. Verify Distributive Laws (A ∩ (B ∪ C) = (A ∩ B) ∪ (A ∩ C), etc.)\n");
        printf("5. Verify De Morgan's Laws ((A ∪ B)' = A' ∩ B', etc.)\n");
        printf("6. Verify Law of Excluded Middle (A ∪ A' = U)\n");
        printf("7. Verify Law of Contradiction (A ∩ A' = ∅)\n");
        printf("8. Verify Involution Law ((A')' = A)\n");
        printf("9. Verify Absorption Laws (A ∪ (A ∩ B) = A, etc.)\n");
        printf("10. Verify Identity Laws (A ∪ ∅ = A, A ∩ U = A)\n");
        printf("11. Verify Domination Laws (A ∪ U = U, A ∩ ∅ = ∅)\n");
        printf("12. Verify All Laws\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please try again.\n");
            // Clear input buffer
            while (getchar() != '\n');
            choice = -1;
            continue;
        }

        printf("\n");

        // Process choice
        switch (choice) {
            case 1:
                verifyIdempotentLaws(A, size);
                break;
            case 2:
                verifyCommutativeLaws(A, B, size);
                break;
            case 3:
                verifyAssociativeLaws(A, B, C, size);
                break;
            case 4:
                verifyDistributiveLaws(A, B, C, size);
                break;
            case 5:
                verifyDeMorganLaws(A, B, size);
                break;
            case 6:
                verifyExcludedMiddleLaw(A, size);
                break;
            case 7:
                verifyContradictionLaw(A, size);
                break;
            case 8:
                verifyInvolutionLaw(A, size);
                break;
            case 9:
                verifyAbsorptionLaws(A, B, size);
                break;
            case 10:
                verifyIdentityLaws(A, size);
                break;
            case 11:
                verifyDominationLaws(A, size);
                break;
            case 12:
                printf("\n===== VERIFYING ALL FUZZY SET LAWS =====\n");
                verifyIdempotentLaws(A, size);
                verifyCommutativeLaws(A, B, size);
                verifyAssociativeLaws(A, B, C, size);
                verifyDistributiveLaws(A, B, C, size);
                verifyDeMorganLaws(A, B, size);
                verifyExcludedMiddleLaw(A, size);
                verifyContradictionLaw(A, size);
                verifyInvolutionLaw(A, size);
                verifyAbsorptionLaws(A, B, size);
                verifyIdentityLaws(A, size);
                verifyDominationLaws(A, size);
                break;
            case 0:
                printf("Exiting program. Thank you for using the Fuzzy Set Laws Verifier!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            while (getchar() != '\n'); // Clear any remaining characters
            getchar(); // Wait for Enter
        }

    } while (choice != 0);

    // Free allocated memory
    free(A);
    free(B);
    free(C);
    free(R);
    free(S);

    return 0;
}