// Q9. Write a program in C to perform Cartesian product over two given Fuzzy Sets.
// Created by tavneet on 4/27/25.
#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a fuzzy set element
// A fuzzy element has a value and a membership degree between 0 and 1
typedef struct {
    float value;       // The actual value of the element
    float membership;  // Membership degree in the range [0,1]
} FuzzyElement;

// Define a structure to represent a fuzzy set
// A fuzzy set is a collection of fuzzy elements
typedef struct {
    FuzzyElement* elements;  // Array of elements
    int size;                // Number of elements in the set
} FuzzySet;

// Define a structure to represent an element in the Cartesian product
// Each element in the product is an ordered pair from both sets with a membership value
typedef struct {
    float value1;      // Value from the first set
    float value2;      // Value from the second set
    float membership;  // Membership degree in the Cartesian product
} CartesianElement;

// Define a structure to represent the Cartesian product
typedef struct {
    CartesianElement* elements;  // Array of elements
    int size;                    // Number of elements in the product
    int rows;                    // Number of rows (size of set A)
    int cols;                    // Number of columns (size of set B)
} CartesianProduct;

// Function to create a fuzzy set
FuzzySet createFuzzySet(int size) {
    printf("\n[MEMORY ALLOCATION] Allocating memory for a fuzzy set with %d elements\n", size);

    FuzzySet set;
    set.size = size;
    set.elements = (FuzzyElement*)malloc(size * sizeof(FuzzyElement));

    if (set.elements == NULL) {
        printf("[ERROR] Memory allocation failed for fuzzy set\n");
        exit(1);
    }

    printf("[MEMORY ALLOCATION] Successfully allocated memory for the fuzzy set\n");
    return set;
}

// Function to input a fuzzy set from the user
FuzzySet inputFuzzySet(char setName) {
    int size;
    printf("\n=== INPUT FOR FUZZY SET %c ===\n", setName);
    printf("Enter the number of elements in fuzzy set %c: ", setName);
    scanf("%d", &size);

    // Validate input
    while (size <= 0) {
        printf("Number of elements must be positive. Please enter again: ");
        scanf("%d", &size);
    }

    // Create the fuzzy set
    FuzzySet set = createFuzzySet(size);

    // Input each element
    printf("\nEnter the elements of fuzzy set %c:\n", setName);
    for (int i = 0; i < size; i++) {
        printf("Element %d:\n", i + 1);

        printf("  Value: ");
        scanf("%f", &set.elements[i].value);

        printf("  Membership degree (between 0 and 1): ");
        scanf("%f", &set.elements[i].membership);

        // Validate membership degree
        while (set.elements[i].membership < 0 || set.elements[i].membership > 1) {
            printf("  Membership degree must be between 0 and 1. Please enter again: ");
            scanf("%f", &set.elements[i].membership);
        }

        printf("  [STORED] Element (%.2f/%.2f) added to set %c\n",
               set.elements[i].value, set.elements[i].membership, setName);
    }

    return set;
}

// Function to free memory allocated for a fuzzy set
void freeFuzzySet(FuzzySet set) {
    printf("\n[MEMORY CLEANUP] Freeing memory allocated for fuzzy set\n");
    free(set.elements);
}

// Function to compute the Cartesian product of two fuzzy sets
CartesianProduct computeCartesianProduct(FuzzySet A, FuzzySet B) {
    printf("\n=== COMPUTING CARTESIAN PRODUCT ===\n");

    // The size of the Cartesian product is the product of the sizes of the input sets
    int productSize = A.size * B.size;
    printf("[STEP 1] Calculating size of Cartesian product: %d × %d = %d elements\n",
           A.size, B.size, productSize);
    printf("[STEP 1.1] Matrix dimensions will be [%d × %d] (rows × columns)\n", A.size, B.size);

    // Allocate memory for the Cartesian product
    printf("[STEP 2] Allocating memory for Cartesian product with %d elements\n", productSize);
    CartesianProduct product;
    product.size = productSize;
    product.rows = A.size;
    product.cols = B.size;
    product.elements = (CartesianElement*)malloc(productSize * sizeof(CartesianElement));

    if (product.elements == NULL) {
        printf("[ERROR] Memory allocation failed for Cartesian product\n");
        exit(1);
    }

    printf("[MEMORY ALLOCATION] Successfully allocated memory for the Cartesian product\n");

    // Compute each element of the Cartesian product
    printf("[STEP 3] Computing each element of the Cartesian product\n");
    int index = 0;
    for (int i = 0; i < A.size; i++) {
        for (int j = 0; j < B.size; j++) {
            // Get the elements from sets A and B
            FuzzyElement elementA = A.elements[i];
            FuzzyElement elementB = B.elements[j];

            printf("\n  [PAIR %d] Processing pair of elements at matrix position [%d,%d]:\n",
                   index + 1, i, j);
            printf("    - From Set A: (%.2f/%.2f)\n", elementA.value, elementA.membership);
            printf("    - From Set B: (%.2f/%.2f)\n", elementB.value, elementB.membership);

            // Create a new element in the Cartesian product
            CartesianElement productElement;
            productElement.value1 = elementA.value;
            productElement.value2 = elementB.value;

            // The membership degree in the Cartesian product is the minimum
            // of the membership degrees in the original sets
            productElement.membership = elementA.membership < elementB.membership ?
                                        elementA.membership : elementB.membership;

            printf("    - Calculating membership: min(%.2f, %.2f) = %.2f\n",
                   elementA.membership, elementB.membership, productElement.membership);

            // Add the element to the Cartesian product
            product.elements[index++] = productElement;
            printf("    - Result: ((%.2f, %.2f)/%.2f) added to Cartesian product at position [%d,%d]\n",
                   productElement.value1, productElement.value2, productElement.membership, i, j);
        }
    }

    printf("\n[CALCULATION COMPLETE] Cartesian product computed successfully\n");
    return product;
}

// Function to free memory allocated for a Cartesian product
void freeCartesianProduct(CartesianProduct product) {
    printf("\n[MEMORY CLEANUP] Freeing memory allocated for Cartesian product\n");
    free(product.elements);
}

// Function to print a fuzzy set
void printFuzzySet(FuzzySet set, const char* name) {
    printf("\n=== FUZZY SET %s ===\n", name);
    printf("%s = {", name);
    for (int i = 0; i < set.size; i++) {
        printf("(%.2f/%.2f)", set.elements[i].value, set.elements[i].membership);
        if (i < set.size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
    printf("Note: (value/membership_degree)\n");
}

// Function to print a Cartesian product
void printCartesianProduct(CartesianProduct product) {
    printf("\n=== CARTESIAN PRODUCT RESULT ===\n");
    printf("A × B = {\n");
    for (int i = 0; i < product.size; i++) {
        printf("  ((%.2f, %.2f)/%.2f)",
               product.elements[i].value1,
               product.elements[i].value2,
               product.elements[i].membership);
        if (i < product.size - 1) {
            printf(",\n");
        }
    }
    printf("\n}\n");
    printf("Note: ((value_from_A, value_from_B)/membership_degree)\n");

    // Print the matrix dimensions
    printf("\nMatrix Dimensions: [%d × %d] (rows × columns)\n", product.rows, product.cols);
}

// Function to print the Cartesian product as a matrix
void printCartesianProductMatrix(CartesianProduct product) {
    printf("\n=== CARTESIAN PRODUCT AS MATRIX [%d × %d] ===\n", product.rows, product.cols);
    printf("Each cell contains: ((value1, value2)/membership)\n\n");

    // Print column headers
    printf("     ");
    for (int j = 0; j < product.cols; j++) {
        printf("     Column %d     ", j);
    }
    printf("\n");

    // Print matrix rows
    for (int i = 0; i < product.rows; i++) {
        printf("Row %d ", i);
        for (int j = 0; j < product.cols; j++) {
            int index = i * product.cols + j;
            printf("((%.2f, %.2f)/%.2f) ",
                   product.elements[index].value1,
                   product.elements[index].value2,
                   product.elements[index].membership);
        }
        printf("\n");
    }
}

// Function to display the theory of fuzzy Cartesian products
void explainTheory() {
    printf("\n======================================\n");
    printf("THEORY: CARTESIAN PRODUCT OF FUZZY SETS\n");
    printf("======================================\n");
    printf("Given two fuzzy sets A and B:\n");
    printf("- A = {(x/μA(x)) | x ∈ X}\n");
    printf("- B = {(y/μB(y)) | y ∈ Y}\n\n");

    printf("The Cartesian product A × B is defined as:\n");
    printf("A × B = {((x, y)/min(μA(x), μB(y))) | x ∈ X, y ∈ Y}\n\n");

    printf("Where:\n");
    printf("- x is an element from the universe X with membership μA(x) in set A\n");
    printf("- y is an element from the universe Y with membership μB(y) in set B\n");
    printf("- The ordered pair (x, y) is an element of the Cartesian product\n");
    printf("- The membership of (x, y) in A × B is the minimum of μA(x) and μB(y)\n");
    printf("======================================\n\n");

    printf("MATRIX REPRESENTATION:\n");
    printf("The Cartesian product can be visualized as a matrix where:\n");
    printf("- Rows correspond to elements of set A\n");
    printf("- Columns correspond to elements of set B\n");
    printf("- Each cell contains ((value_from_A, value_from_B)/membership_degree)\n");
    printf("- If set A has m elements and set B has n elements, the resulting matrix has dimensions [m × n]\n");
    printf("======================================\n\n");
}

int main() {
    // Display welcome message and theoretical explanation
    printf("==========================================================\n");
    printf("FUZZY SET CARTESIAN PRODUCT CALCULATION WITH MATRIX OUTPUT\n");
    printf("==========================================================\n");
    printf("This program demonstrates the Cartesian product operation\n");
    printf("on two fuzzy sets with detailed step-by-step explanation.\n");

    // Explain the theory
    explainTheory();

    // Input the first fuzzy set A from the user
    FuzzySet A = inputFuzzySet('A');

    // Input the second fuzzy set B from the user
    FuzzySet B = inputFuzzySet('B');

    // Print the fuzzy sets
    printFuzzySet(A, "A");
    printFuzzySet(B, "B");

    // Compute the Cartesian product
    CartesianProduct product = computeCartesianProduct(A, B);

    // Print the Cartesian product as a set
    printCartesianProduct(product);

    // Print the Cartesian product as a matrix
    printCartesianProductMatrix(product);

    // Free allocated memory
    freeFuzzySet(A);
    freeFuzzySet(B);
    freeCartesianProduct(product);

    printf("\n[PROGRAM COMPLETED] All memory has been freed. Exiting.\n");

    return 0;
}