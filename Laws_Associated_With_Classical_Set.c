//Q6. Write a program in C to implement and verify various Laws associated with Classical sets.
// Created by tavneet on 4/6/25.
#include <stdio.h>
#include <stdbool.h>

#define MAX_SET_SIZE 100
#define UNIVERSE_SIZE 10

// Function to display a set
void displaySet(bool set[], int size) {
    printf("{ ");
    bool isEmpty = true;

    for (int i = 0; i < size; i++) {
        if (set[i]) {
            printf("%d ", i);
            isEmpty = false;
        }
    }

    if (isEmpty) {
        printf("∅");
    }

    printf("}");
}

// Function to perform union of two sets
void setUnion(bool A[], bool B[], bool result[], int size) {
    for (int i = 0; i < size; i++) {
        result[i] = A[i] || B[i];
    }
}

// Function to perform intersection of two sets
void setIntersection(bool A[], bool B[], bool result[], int size) {
    for (int i = 0; i < size; i++) {
        result[i] = A[i] && B[i];
    }
}

// Function to perform complement of a set
void setComplement(bool A[], bool result[], int size) {
    for (int i = 0; i < size; i++) {
        result[i] = !A[i];
    }
}

// Function to perform set difference A - B
void setDifference(bool A[], bool B[], bool result[], int size) {
    for (int i = 0; i < size; i++) {
        result[i] = A[i] && !B[i];
    }
}

// Function to check if two sets are equal
bool areEqual(bool A[], bool B[], int size) {
    for (int i = 0; i < size; i++) {
        if (A[i] != B[i]) {
            return false;
        }
    }
    return true;
}

// Function to check if a set is a subset of another
bool isSubset(bool A[], bool B[], int size) {
    for (int i = 0; i < size; i++) {
        if (A[i] && !B[i]) {
            return false;
        }
    }
    return true;
}

// Function to create empty set
void emptySet(bool set[], int size) {
    for (int i = 0; i < size; i++) {
        set[i] = false;
    }
}

// Function to create universal set
void universalSet(bool set[], int size) {
    for (int i = 0; i < size; i++) {
        set[i] = true;
    }
}

// Function to test idempotent laws
void testIdempotentLaws(bool A[], int size) {
    bool result[MAX_SET_SIZE];

    printf("\n\n=== IDEMPOTENT LAWS ===\n");

    // A ∪ A = A
    printf("\n1. A ∪ A = A\n");
    printf("   A = "); displaySet(A, size); printf("\n");

    setUnion(A, A, result, size);
    printf("   A ∪ A = "); displaySet(result, size); printf("\n");
    printf("   A = "); displaySet(A, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result, A, size) ? "PASSED" : "FAILED");

    // A ∩ A = A
    printf("\n2. A ∩ A = A\n");
    printf("   A = "); displaySet(A, size); printf("\n");

    setIntersection(A, A, result, size);
    printf("   A ∩ A = "); displaySet(result, size); printf("\n");
    printf("   A = "); displaySet(A, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result, A, size) ? "PASSED" : "FAILED");
}

// Function to test commutative laws
void testCommutativeLaws(bool A[], bool B[], int size) {
    bool result1[MAX_SET_SIZE];
    bool result2[MAX_SET_SIZE];

    printf("\n\n=== COMMUTATIVE LAWS ===\n");

    // A ∪ B = B ∪ A
    printf("\n1. A ∪ B = B ∪ A\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   B = "); displaySet(B, size); printf("\n");

    setUnion(A, B, result1, size);
    printf("   A ∪ B = "); displaySet(result1, size); printf("\n");

    setUnion(B, A, result2, size);
    printf("   B ∪ A = "); displaySet(result2, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result1, result2, size) ? "PASSED" : "FAILED");

    // A ∩ B = B ∩ A
    printf("\n2. A ∩ B = B ∩ A\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   B = "); displaySet(B, size); printf("\n");

    setIntersection(A, B, result1, size);
    printf("   A ∩ B = "); displaySet(result1, size); printf("\n");

    setIntersection(B, A, result2, size);
    printf("   B ∩ A = "); displaySet(result2, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result1, result2, size) ? "PASSED" : "FAILED");
}

// Function to test associative laws
void testAssociativeLaws(bool A[], bool B[], bool C[], int size) {
    bool temp1[MAX_SET_SIZE];
    bool temp2[MAX_SET_SIZE];
    bool result1[MAX_SET_SIZE];
    bool result2[MAX_SET_SIZE];

    printf("\n\n=== ASSOCIATIVE LAWS ===\n");

    // (A ∪ B) ∪ C = A ∪ (B ∪ C)
    printf("\n1. (A ∪ B) ∪ C = A ∪ (B ∪ C)\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   B = "); displaySet(B, size); printf("\n");
    printf("   C = "); displaySet(C, size); printf("\n");

    setUnion(A, B, temp1, size);
    printf("   (A ∪ B) = "); displaySet(temp1, size); printf("\n");

    setUnion(temp1, C, result1, size);
    printf("   (A ∪ B) ∪ C = "); displaySet(result1, size); printf("\n");

    setUnion(B, C, temp2, size);
    printf("   (B ∪ C) = "); displaySet(temp2, size); printf("\n");

    setUnion(A, temp2, result2, size);
    printf("   A ∪ (B ∪ C) = "); displaySet(result2, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result1, result2, size) ? "PASSED" : "FAILED");

    // (A ∩ B) ∩ C = A ∩ (B ∩ C)
    printf("\n2. (A ∩ B) ∩ C = A ∩ (B ∩ C)\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   B = "); displaySet(B, size); printf("\n");
    printf("   C = "); displaySet(C, size); printf("\n");

    setIntersection(A, B, temp1, size);
    printf("   (A ∩ B) = "); displaySet(temp1, size); printf("\n");

    setIntersection(temp1, C, result1, size);
    printf("   (A ∩ B) ∩ C = "); displaySet(result1, size); printf("\n");

    setIntersection(B, C, temp2, size);
    printf("   (B ∩ C) = "); displaySet(temp2, size); printf("\n");

    setIntersection(A, temp2, result2, size);
    printf("   A ∩ (B ∩ C) = "); displaySet(result2, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result1, result2, size) ? "PASSED" : "FAILED");
}

// Function to test distributive laws
void testDistributiveLaws(bool A[], bool B[], bool C[], int size) {
    bool temp1[MAX_SET_SIZE];
    bool temp2[MAX_SET_SIZE];
    bool result1[MAX_SET_SIZE];
    bool result2[MAX_SET_SIZE];

    printf("\n\n=== DISTRIBUTIVE LAWS ===\n");

    // A ∪ (B ∩ C) = (A ∪ B) ∩ (A ∪ C)
    printf("\n1. A ∪ (B ∩ C) = (A ∪ B) ∩ (A ∪ C)\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   B = "); displaySet(B, size); printf("\n");
    printf("   C = "); displaySet(C, size); printf("\n");

    setIntersection(B, C, temp1, size);
    printf("   (B ∩ C) = "); displaySet(temp1, size); printf("\n");

    setUnion(A, temp1, result1, size);
    printf("   A ∪ (B ∩ C) = "); displaySet(result1, size); printf("\n");

    setUnion(A, B, temp1, size);
    printf("   (A ∪ B) = "); displaySet(temp1, size); printf("\n");

    setUnion(A, C, temp2, size);
    printf("   (A ∪ C) = "); displaySet(temp2, size); printf("\n");

    setIntersection(temp1, temp2, result2, size);
    printf("   (A ∪ B) ∩ (A ∪ C) = "); displaySet(result2, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result1, result2, size) ? "PASSED" : "FAILED");

    // A ∩ (B ∪ C) = (A ∩ B) ∪ (A ∩ C)
    printf("\n2. A ∩ (B ∪ C) = (A ∩ B) ∪ (A ∩ C)\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   B = "); displaySet(B, size); printf("\n");
    printf("   C = "); displaySet(C, size); printf("\n");

    setUnion(B, C, temp1, size);
    printf("   (B ∪ C) = "); displaySet(temp1, size); printf("\n");

    setIntersection(A, temp1, result1, size);
    printf("   A ∩ (B ∪ C) = "); displaySet(result1, size); printf("\n");

    setIntersection(A, B, temp1, size);
    printf("   (A ∩ B) = "); displaySet(temp1, size); printf("\n");

    setIntersection(A, C, temp2, size);
    printf("   (A ∩ C) = "); displaySet(temp2, size); printf("\n");

    setUnion(temp1, temp2, result2, size);
    printf("   (A ∩ B) ∪ (A ∩ C) = "); displaySet(result2, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result1, result2, size) ? "PASSED" : "FAILED");
}

// Function to test complement laws
void testComplementLaws(bool A[], int size) {
    bool result[MAX_SET_SIZE];
    bool universal[MAX_SET_SIZE];
    bool empty[MAX_SET_SIZE];
    bool Acomplement[MAX_SET_SIZE];
    bool doubleComplement[MAX_SET_SIZE];

    universalSet(universal, size);
    emptySet(empty, size);
    setComplement(A, Acomplement, size);

    printf("\n\n=== COMPLEMENT LAWS ===\n");

    // A ∪ A' = U (Universal set)
    printf("\n1. A ∪ A' = U\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   A' = "); displaySet(Acomplement, size); printf("\n");

    setUnion(A, Acomplement, result, size);
    printf("   A ∪ A' = "); displaySet(result, size); printf("\n");

    printf("   U = "); displaySet(universal, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result, universal, size) ? "PASSED" : "FAILED");

    // A ∩ A' = ∅ (Empty set)
    printf("\n2. A ∩ A' = ∅\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   A' = "); displaySet(Acomplement, size); printf("\n");

    setIntersection(A, Acomplement, result, size);
    printf("   A ∩ A' = "); displaySet(result, size); printf("\n");

    printf("   ∅ = "); displaySet(empty, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result, empty, size) ? "PASSED" : "FAILED");

    // (A')' = A (Double Complement)
    printf("\n3. (A')' = A\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   A' = "); displaySet(Acomplement, size); printf("\n");

    setComplement(Acomplement, doubleComplement, size);
    printf("   (A')' = "); displaySet(doubleComplement, size); printf("\n");

    printf("   Verification: %s\n", areEqual(doubleComplement, A, size) ? "PASSED" : "FAILED");
}

// Function to test DeMorgan's laws
void testDeMorganLaws(bool A[], bool B[], int size) {
    bool temp1[MAX_SET_SIZE];
    bool result1[MAX_SET_SIZE];
    bool result2[MAX_SET_SIZE];
    bool Acomplement[MAX_SET_SIZE];
    bool Bcomplement[MAX_SET_SIZE];

    setComplement(A, Acomplement, size);
    setComplement(B, Bcomplement, size);

    printf("\n\n=== DEMORGAN'S LAWS ===\n");

    // (A ∪ B)' = A' ∩ B'
    printf("\n1. (A ∪ B)' = A' ∩ B'\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   B = "); displaySet(B, size); printf("\n");

    setUnion(A, B, temp1, size);
    printf("   (A ∪ B) = "); displaySet(temp1, size); printf("\n");

    setComplement(temp1, result1, size);
    printf("   (A ∪ B)' = "); displaySet(result1, size); printf("\n");

    printf("   A' = "); displaySet(Acomplement, size); printf("\n");
    printf("   B' = "); displaySet(Bcomplement, size); printf("\n");

    setIntersection(Acomplement, Bcomplement, result2, size);
    printf("   A' ∩ B' = "); displaySet(result2, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result1, result2, size) ? "PASSED" : "FAILED");

    // (A ∩ B)' = A' ∪ B'
    printf("\n2. (A ∩ B)' = A' ∪ B'\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   B = "); displaySet(B, size); printf("\n");

    setIntersection(A, B, temp1, size);
    printf("   (A ∩ B) = "); displaySet(temp1, size); printf("\n");

    setComplement(temp1, result1, size);
    printf("   (A ∩ B)' = "); displaySet(result1, size); printf("\n");

    printf("   A' = "); displaySet(Acomplement, size); printf("\n");
    printf("   B' = "); displaySet(Bcomplement, size); printf("\n");

    setUnion(Acomplement, Bcomplement, result2, size);
    printf("   A' ∪ B' = "); displaySet(result2, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result1, result2, size) ? "PASSED" : "FAILED");
}

// Function to test identity laws
void testIdentityLaws(bool A[], int size) {
    bool result[MAX_SET_SIZE];
    bool universal[MAX_SET_SIZE];
    bool empty[MAX_SET_SIZE];

    universalSet(universal, size);
    emptySet(empty, size);

    printf("\n\n=== IDENTITY LAWS ===\n");

    // A ∪ ∅ = A
    printf("\n1. A ∪ ∅ = A\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   ∅ = "); displaySet(empty, size); printf("\n");

    setUnion(A, empty, result, size);
    printf("   A ∪ ∅ = "); displaySet(result, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result, A, size) ? "PASSED" : "FAILED");

    // A ∩ U = A
    printf("\n2. A ∩ U = A\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   U = "); displaySet(universal, size); printf("\n");

    setIntersection(A, universal, result, size);
    printf("   A ∩ U = "); displaySet(result, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result, A, size) ? "PASSED" : "FAILED");

    // A ∪ U = U
    printf("\n3. A ∪ U = U\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   U = "); displaySet(universal, size); printf("\n");

    setUnion(A, universal, result, size);
    printf("   A ∪ U = "); displaySet(result, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result, universal, size) ? "PASSED" : "FAILED");

    // A ∩ ∅ = ∅
    printf("\n4. A ∩ ∅ = ∅\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   ∅ = "); displaySet(empty, size); printf("\n");

    setIntersection(A, empty, result, size);
    printf("   A ∩ ∅ = "); displaySet(result, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result, empty, size) ? "PASSED" : "FAILED");
}

// Function to test absorption laws
void testAbsorptionLaws(bool A[], bool B[], int size) {
    bool temp[MAX_SET_SIZE];
    bool result[MAX_SET_SIZE];

    printf("\n\n=== ABSORPTION LAWS ===\n");

    // A ∪ (A ∩ B) = A
    printf("\n1. A ∪ (A ∩ B) = A\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   B = "); displaySet(B, size); printf("\n");

    setIntersection(A, B, temp, size);
    printf("   (A ∩ B) = "); displaySet(temp, size); printf("\n");

    setUnion(A, temp, result, size);
    printf("   A ∪ (A ∩ B) = "); displaySet(result, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result, A, size) ? "PASSED" : "FAILED");

    // A ∩ (A ∪ B) = A
    printf("\n2. A ∩ (A ∪ B) = A\n");
    printf("   A = "); displaySet(A, size); printf("\n");
    printf("   B = "); displaySet(B, size); printf("\n");

    setUnion(A, B, temp, size);
    printf("   (A ∪ B) = "); displaySet(temp, size); printf("\n");

    setIntersection(A, temp, result, size);
    printf("   A ∩ (A ∪ B) = "); displaySet(result, size); printf("\n");

    printf("   Verification: %s\n", areEqual(result, A, size) ? "PASSED" : "FAILED");
}

int main() {
    bool A[UNIVERSE_SIZE] = {false};
    bool B[UNIVERSE_SIZE] = {false};
    bool C[UNIVERSE_SIZE] = {false};
    bool U[UNIVERSE_SIZE] = {false}; // Universal set
    bool E[UNIVERSE_SIZE] = {false}; // Empty set

    // Initialize set A = {1, 3, 5, 7, 9}
    A[1] = true;
    A[3] = true;
    A[5] = true;
    A[7] = true;
    A[9] = true;

    // Initialize set B = {0, 2, 4, 6, 8}
    B[0] = true;
    B[2] = true;
    B[4] = true;
    B[6] = true;
    B[8] = true;

    // Initialize set C = {1, 2, 3, 4, 5}
    C[1] = true;
    C[2] = true;
    C[3] = true;
    C[4] = true;
    C[5] = true;

    // Initialize the universal set
    universalSet(U, UNIVERSE_SIZE);

    // Initialize the empty set
    emptySet(E, UNIVERSE_SIZE);

    printf("===== VERIFICATION OF CLASSICAL SET LAWS =====\n\n");
    printf("Initial Sets:\n");
    printf("Universal Set U = "); displaySet(U, UNIVERSE_SIZE); printf("\n");
    printf("Set A = "); displaySet(A, UNIVERSE_SIZE); printf("\n");
    printf("Set B = "); displaySet(B, UNIVERSE_SIZE); printf("\n");
    printf("Set C = "); displaySet(C, UNIVERSE_SIZE); printf("\n");
    //printf("Empty Set ∅ = "); displaySet(E, UNIVERSE_SIZE); printf("\n");

    // Test all set laws with detailed output
    testIdempotentLaws(A, UNIVERSE_SIZE);
    testCommutativeLaws(A, B, UNIVERSE_SIZE);
    testAssociativeLaws(A, B, C, UNIVERSE_SIZE);
    testDistributiveLaws(A, B, C, UNIVERSE_SIZE);
    testComplementLaws(A, UNIVERSE_SIZE);
    testDeMorganLaws(A, B, UNIVERSE_SIZE);
    testIdentityLaws(A, UNIVERSE_SIZE);
    testAbsorptionLaws(A, B, UNIVERSE_SIZE);

    printf("\n\n===== ALL SET LAWS VERIFIED =====\n");
    return 0;
}
