// Q11. Write a program in C to perform Max-Product Composition of Two Matrices obtained from Cartesian Product.
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

// Define a structure for a fuzzy relation matrix
typedef struct {
    float** matrix;    // 2D array for matrix representation
    float* xValues;    // Values of the X universe
    float* yValues;    // Values of the Y universe
    int rows;          // Number of rows
    int cols;          // Number of columns
} FuzzyRelation;

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
CartesianProduct computeCartesianProductFirst(FuzzySet A, FuzzySet B) {
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
CartesianProduct computeCartesianProductSecond(FuzzySet A, FuzzySet B) {
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
            printf("    - From Set B: (%.2f/%.2f)\n", elementA.value, elementA.membership);
            printf("    - From Set C: (%.2f/%.2f)\n", elementB.value, elementB.membership);

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

// Function to convert CartesianProduct to FuzzyRelation matrix
FuzzyRelation cartesianToRelation(CartesianProduct product, FuzzySet A, FuzzySet B) {
    printf("\n=== CONVERTING CARTESIAN PRODUCT TO FUZZY RELATION MATRIX ===\n");

    FuzzyRelation relation;
    relation.rows = product.rows;
    relation.cols = product.cols;

    // Allocate memory for the matrix
    printf("[STEP 1] Allocating memory for a %d × %d fuzzy relation matrix\n", relation.rows, relation.cols);
    relation.matrix = (float**)malloc(relation.rows * sizeof(float*));
    if (relation.matrix == NULL) {
        printf("[ERROR] Memory allocation failed for relation matrix\n");
        exit(1);
    }

    for (int i = 0; i < relation.rows; i++) {
        relation.matrix[i] = (float*)malloc(relation.cols * sizeof(float));
        if (relation.matrix[i] == NULL) {
            printf("[ERROR] Memory allocation failed for relation matrix row %d\n", i);
            exit(1);
        }
    }

    // Allocate memory for universe values
    relation.xValues = (float*)malloc(relation.rows * sizeof(float));
    relation.yValues = (float*)malloc(relation.cols * sizeof(float));
    if (relation.xValues == NULL || relation.yValues == NULL) {
        printf("[ERROR] Memory allocation failed for universe values\n");
        exit(1);
    }

    // Fill the matrix with membership values
    printf("[STEP 2] Filling the relation matrix with membership values\n");
    for (int i = 0; i < relation.rows; i++) {
        relation.xValues[i] = A.elements[i].value;

        for (int j = 0; j < relation.cols; j++) {
            if (i == 0) {
                relation.yValues[j] = B.elements[j].value;
            }

            int index = i * relation.cols + j;
            relation.matrix[i][j] = product.elements[index].membership;

            printf("  [MATRIX] R[%d,%d] = %.2f (membership between %.2f and %.2f)\n",
                   i, j, relation.matrix[i][j], relation.xValues[i], relation.yValues[j]);
        }
    }

    printf("[CONVERSION COMPLETE] Fuzzy relation matrix created successfully\n");
    return relation;
}

// Function to free memory allocated for a fuzzy relation
void freeRelation(FuzzyRelation relation) {
    printf("\n[MEMORY CLEANUP] Freeing memory allocated for fuzzy relation matrix\n");

    for (int i = 0; i < relation.rows; i++) {
        free(relation.matrix[i]);
    }
    free(relation.matrix);
    free(relation.xValues);
    free(relation.yValues);
}

// Function to compute Max-Product Composition of two fuzzy relations
FuzzyRelation maxProductComposition(FuzzyRelation R, FuzzyRelation S) {
    printf("\n=== COMPUTING MAX-PRODUCT COMPOSITION ===\n");

    // Check if the relations can be composed
    if (R.cols != S.rows) {
        printf("[ERROR] Cannot compute composition: Number of columns in first relation (%d) must equal\n", R.cols);
        printf("        number of rows in second relation (%d)\n", S.rows);
        exit(1);
    }

    // Result will be a matrix with dimensions R.rows × S.cols
    FuzzyRelation T;
    T.rows = R.rows;
    T.cols = S.cols;

    printf("[STEP 1] Resulting composition matrix will have dimensions [%d × %d]\n", T.rows, T.cols);

    // Allocate memory for the result matrix
    printf("[STEP 2] Allocating memory for composition matrix\n");
    T.matrix = (float**)malloc(T.rows * sizeof(float*));
    if (T.matrix == NULL) {
        printf("[ERROR] Memory allocation failed for composition matrix\n");
        exit(1);
    }

    for (int i = 0; i < T.rows; i++) {
        T.matrix[i] = (float*)malloc(T.cols * sizeof(float));
        if (T.matrix[i] == NULL) {
            printf("[ERROR] Memory allocation failed for composition matrix row %d\n", i);
            exit(1);
        }
    }

    // Allocate memory for universe values
    T.xValues = (float*)malloc(T.rows * sizeof(float));
    T.yValues = (float*)malloc(T.cols * sizeof(float));
    if (T.xValues == NULL || T.yValues == NULL) {
        printf("[ERROR] Memory allocation failed for universe values\n");
        exit(1);
    }

    // Copy universe values
    for (int i = 0; i < T.rows; i++) {
        T.xValues[i] = R.xValues[i];
    }
    for (int j = 0; j < T.cols; j++) {
        T.yValues[j] = S.yValues[j];
    }

    // Compute max-product composition
    printf("[STEP 3] Computing each element of the composition matrix\n");
    for (int i = 0; i < T.rows; i++) {
        for (int j = 0; j < T.cols; j++) {
            // Initialize with minimum possible value
            T.matrix[i][j] = 0;

            printf("\n  [ELEMENT] Computing T[%d,%d] (between %.2f and %.2f):\n",
                   i, j, T.xValues[i], T.yValues[j]);

            // For each element in the common dimension
            for (int k = 0; k < R.cols; k++) {
                // Calculate product(R[i,k], S[k,j])
                float product_val = R.matrix[i][k] * S.matrix[k][j];

                printf("    - product(R[%d,%d]=%.2f, S[%d,%d]=%.2f) = %.2f\n",
                       i, k, R.matrix[i][k], k, j, S.matrix[k][j], product_val);

                // Update T[i,j] if this product value is greater
                if (product_val > T.matrix[i][j]) {
                    T.matrix[i][j] = product_val;
                    printf("      New max value found: %.2f\n", T.matrix[i][j]);
                }
            }

            printf("    Final value for T[%d,%d] = %.2f\n", i, j, T.matrix[i][j]);
        }
    }

    printf("\n[CALCULATION COMPLETE] Max-Product composition computed successfully\n");
    return T;
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
void printCartesianProductFirst(CartesianProduct product) {
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

void printCartesianProductSecond(CartesianProduct product) {
    printf("\n=== CARTESIAN PRODUCT RESULT ===\n");
    printf("B × C = {\n");
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
    printf("Note: ((value_from_B, value_from_C)/membership_degree)\n");

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

// Function to print a fuzzy relation matrix
void printRelationMatrix(FuzzyRelation relation, const char* name) {
    printf("\n=== FUZZY RELATION MATRIX %s [%d × %d] ===\n", name, relation.rows, relation.cols);

    // Print column headers (y values)
    printf("      | ");
    for (int j = 0; j < relation.cols; j++) {
        printf("  y=%.2f  ", relation.yValues[j]);
    }
    printf("\n------+-");
    for (int j = 0; j < relation.cols; j++) {
        printf("----------");
    }
    printf("\n");

    // Print rows with x values
    for (int i = 0; i < relation.rows; i++) {
        printf("x=%.2f | ", relation.xValues[i]);
        for (int j = 0; j < relation.cols; j++) {
            printf("   %.2f   ", relation.matrix[i][j]);
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

// Function to explain Max-Product Composition theory
void explainMaxProductComposition() {
    printf("\n======================================\n");
    printf("THEORY: MAX-PRODUCT COMPOSITION OF FUZZY RELATIONS\n");
    printf("======================================\n");
    printf("Given two fuzzy relations R(X,Y) and S(Y,Z):\n");
    printf("- R is a relation from universe X to universe Y\n");
    printf("- S is a relation from universe Y to universe Z\n\n");

    printf("The Max-Product Composition T = R∘S from X to Z is defined as:\n");
    printf("T(x,z) = max{R(x,y) * S(y,z)} for all y in Y\n\n");

    printf("Where:\n");
    printf("- T(x,z) is the membership degree of the pair (x,z) in the resulting relation\n");
    printf("- For each intermediate element y, we find the product of R(x,y) and S(y,z)\n");
    printf("- Then take the maximum of all these products\n");
    printf("======================================\n\n");

    printf("MATRIX COMPUTATION:\n");
    printf("If R is an m×n matrix and S is an n×p matrix:\n");
    printf("1. The resulting composition T will be an m×p matrix\n");
    printf("2. For each element T[i,j]:\n");
    printf("   - Calculate R[i,k] * S[k,j] for each k from 0 to n-1\n");
    printf("   - T[i,j] is the maximum of all these products\n");
    printf("======================================\n\n");

    printf("COMPARISON WITH MAX-MIN COMPOSITION:\n");
    printf("- Max-Min Composition uses min(R[i,k], S[k,j]) as the operation\n");
    printf("- Max-Product Composition uses R[i,k] * S[k,j] as the operation\n");
    printf("- Both take the maximum value at the end\n");
    printf("- Max-Product typically yields lower membership values than Max-Min\n");
    printf("  because product is typically less than or equal to minimum\n");
    printf("======================================\n\n");
}

int main() {
    int choice;

    // Display welcome message and theoretical explanation
    printf("==========================================================\n");
    printf("FUZZY SET OPERATIONS: CARTESIAN PRODUCT & MAX-PRODUCT COMPOSITION\n");
    printf("==========================================================\n");
    printf("This program demonstrates fuzzy set operations with detailed\n");
    printf("step-by-step explanations.\n\n");

    printf("Select operation:\n");
    printf("1. Cartesian Product of two Fuzzy Sets\n");
    printf("2. Max-Product Composition of two Fuzzy Relations\n");
    printf("3. Both operations (create two sets, compute products, then composition)\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    // Validate choice
    while (choice < 1 || choice > 3) {
        printf("Invalid choice. Please enter 1, 2, or 3: ");
        scanf("%d", &choice);
    }

    if (choice == 1 || choice == 3) {
        // Explain the theory of Cartesian product
        explainTheory();

        // Input the first fuzzy set A from the user
        FuzzySet A = inputFuzzySet('A');

        // Input the second fuzzy set B from the user
        FuzzySet B = inputFuzzySet('B');

        // Print the fuzzy sets
        printFuzzySet(A, "A");
        printFuzzySet(B, "B");

        // Compute the Cartesian product
        CartesianProduct product = computeCartesianProductFirst(A, B);

        // Print the Cartesian product as a set
        printCartesianProductFirst(product);

        // Print the Cartesian product as a matrix
        printCartesianProductMatrix(product);

        // Convert Cartesian product to relation matrix
        FuzzyRelation R = cartesianToRelation(product, A, B);

        // Print the relation matrix
        printRelationMatrix(R, "R (A×B)");

        if (choice == 3) {
            // For choice 3, continue with Max-Product Composition

            // Input the third fuzzy set C from the user
            FuzzySet C = inputFuzzySet('C');

            // Compute another Cartesian product B×C
            CartesianProduct product2 = computeCartesianProductSecond(B, C);

            // Print the second Cartesian product
            printCartesianProductSecond(product2);
            printCartesianProductMatrix(product2);

            // Convert to relation matrix
            FuzzyRelation S = cartesianToRelation(product2, B, C);

            // Print the relation matrix
            printRelationMatrix(S, "S (B×C)");

            // Explain Max-Product Composition theory
            explainMaxProductComposition();

            // Compute Max-Product Composition
            FuzzyRelation T_product = maxProductComposition(R, S);

            // Print the result
            printRelationMatrix(T_product, "T = (R∘S) Max-Product Composition");

            // Free allocated memory
            freeFuzzySet(C);
            freeCartesianProduct(product2);
            freeRelation(S);
            freeRelation(T_product);
        }

        // Free allocated memory
        freeFuzzySet(A);
        freeFuzzySet(B);
        freeCartesianProduct(product);
        freeRelation(R);
    }
    else if (choice == 2) {
        // Explain Max-Product Composition theory
        explainMaxProductComposition();

        // For choice 2, let user input relation matrices directly
        printf("\n=== MANUAL INPUT FOR RELATION MATRICES ===\n");

        // Get dimensions for first relation
        int rows1, cols1;
        printf("Enter dimensions for first relation matrix R:\n");
        printf("Number of rows: ");
        scanf("%d", &rows1);
        printf("Number of columns: ");
        scanf("%d", &cols1);

        // Create relation R
        FuzzyRelation R;
        R.rows = rows1;
        R.cols = cols1;

        // Allocate memory
        R.matrix = (float**)malloc(rows1 * sizeof(float*));
        R.xValues = (float*)malloc(rows1 * sizeof(float));
        R.yValues = (float*)malloc(cols1 * sizeof(float));

        for (int i = 0; i < rows1; i++) {
            R.matrix[i] = (float*)malloc(cols1 * sizeof(float));
        }

        // Input relation R
        printf("\nEnter universe X elements (row labels):\n");
        for (int i = 0; i < rows1; i++) {
            printf("X[%d]: ", i);
            scanf("%f", &R.xValues[i]);
        }

        printf("\nEnter universe Y elements (column labels):\n");
        for (int j = 0; j < cols1; j++) {
            printf("Y[%d]: ", j);
            scanf("%f", &R.yValues[j]);
        }

        printf("\nEnter the membership values for relation R:\n");
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < cols1; j++) {
                printf("R[%.2f,%.2f]: ", R.xValues[i], R.yValues[j]);
                scanf("%f", &R.matrix[i][j]);

                // Validate membership degree
                while (R.matrix[i][j] < 0 || R.matrix[i][j] > 1) {
                    printf("Membership degree must be between 0 and 1. Please enter again: ");
                    scanf("%f", &R.matrix[i][j]);
                }
            }
        }

        // Print relation R
        printRelationMatrix(R, "R");

        // Get dimensions for second relation
        int rows2, cols2;
        printf("\nEnter dimensions for second relation matrix S:\n");
        printf("Number of rows: ");
        scanf("%d", &rows2);
        printf("Number of columns: ");
        scanf("%d", &cols2);

        // Check if composition is possible
        if (cols1 != rows2) {
            printf("[ERROR] Cannot compute composition: Number of columns in R (%d) must equal\n", cols1);
            printf("        number of rows in S (%d)\n", rows2);

            // Free allocated memory
            freeRelation(R);
            return 1;
        }

        // Create relation S
        FuzzyRelation S;
        S.rows = rows2;
        S.cols = cols2;

        // Allocate memory
        S.matrix = (float**)malloc(rows2 * sizeof(float*));
        S.xValues = (float*)malloc(rows2 * sizeof(float));
        S.yValues = (float*)malloc(cols2 * sizeof(float));

        for (int i = 0; i < rows2; i++) {
            S.matrix[i] = (float*)malloc(cols2 * sizeof(float));
        }

        // Input relation S
        printf("\nUniverse Y elements (row labels) should match those of relation R:\n");
        for (int i = 0; i < rows2; i++) {
            S.xValues[i] = R.yValues[i];
            printf("Y[%d] = %.2f\n", i, S.xValues[i]);
        }

        printf("\nEnter universe Z elements (column labels):\n");
        for (int j = 0; j < cols2; j++) {
            printf("Z[%d]: ", j);
            scanf("%f", &S.yValues[j]);
        }

        printf("\nEnter the membership values for relation S:\n");
        for (int i = 0; i < rows2; i++) {
            for (int j = 0; j < cols2; j++) {
                printf("S[%.2f,%.2f]: ", S.xValues[i], S.yValues[j]);
                scanf("%f", &S.matrix[i][j]);

                // Validate membership degree
                while (S.matrix[i][j] < 0 || S.matrix[i][j] > 1) {
                    printf("Membership degree must be between 0 and 1. Please enter again: ");
                    scanf("%f", &S.matrix[i][j]);
                }
            }
        }

        // Print relation S
        printRelationMatrix(S, "S");

        // Compute Max-Product Composition
        FuzzyRelation T_product = maxProductComposition(R, S);

        // Print the Max-Product composition result
        printRelationMatrix(T_product, "T = (R∘S) Max-Product Composition");

        // Free allocated memory
        freeRelation(R);
        freeRelation(S);
        freeRelation(T_product);
    }

    printf("\n[PROGRAM COMPLETED] All memory has been freed. Exiting.\n");

    return 0;
}

