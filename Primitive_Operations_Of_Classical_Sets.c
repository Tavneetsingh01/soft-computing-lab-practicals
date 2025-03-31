// Q5. Write a program in C to Implement the various primitive operations of classical sets.
// Created by tavneet on 3/29/25.
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Set representation using an array and size
typedef struct {
    int elements[MAX_SIZE];
    int size;
} Set;

// Function prototypes
void initSet(Set *s);
bool isEmpty(Set *s);
bool isMember(Set *s, int element);
void addElement(Set *s, int element);
void removeElement(Set *s, int element);
int cardinality(Set *s);
void printSet(Set *s);
void unionSet(Set *set1, Set *set2, Set *result);
void intersectionSet(Set *set1, Set *set2, Set *result);
void differenceSet(Set *set1, Set *set2, Set *result);
bool isSubset(Set *set1, Set *set2);
bool isEqual(Set *set1, Set *set2);
void complementSet(Set *universal, Set *s, Set *result);

int main() {
    Set A, B, C, universal;

    // Initialize sets
    initSet(&A);
    initSet(&B);
    initSet(&C);
    initSet(&universal);

    // Create a universal set (for this example: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
    for (int i = 1; i <= 10; i++) {
        addElement(&universal, i);
    }

    // Add elements to set A: {1, 2, 3, 5, 7}
    addElement(&A, 1);
    addElement(&A, 2);
    addElement(&A, 3);
    addElement(&A, 5);
    addElement(&A, 7);

    // Add elements to set B: {2, 4, 6, 8}
    addElement(&B, 2);
    addElement(&B, 4);
    addElement(&B, 6);
    addElement(&B, 8);

    // Print the sets
    printf("Universal set: ");
    printSet(&universal);

    printf("Set A: ");
    printSet(&A);

    printf("Set B: ");
    printSet(&B);

    // Test isEmpty
    printf("\nIs set A empty? %s\n", isEmpty(&A) ? "Yes" : "No");

    // Test isMember
    printf("Is 3 a member of set A? %s\n", isMember(&A, 3) ? "Yes" : "No");
    printf("Is 4 a member of set A? %s\n", isMember(&A, 4) ? "Yes" : "No");

    // Test cardinality
    printf("\nCardinality of a Set:");
    printf("\nCardinality of set A: %d\n", cardinality(&A));
    printf("Cardinality of set B: %d\n", cardinality(&B));

    // Test remove
    printf("\nRemoving 3 from set A\n");
    removeElement(&A, 3);
    printf("Set A after removal: ");
    printSet(&A);

    //Final sets for further operations
    printf("\nFinal Set A: ");
    printSet(&A);
    printf("Final Set B: ");
    printSet(&B);

    // Test union
    unionSet(&A, &B, &C);
    printf("\nUnion of Sets:");
    printf("\nA ∪ B: ");
    printSet(&C);

    // Test intersection
    intersectionSet(&A, &B, &C);
    printf("\nIntersection of Sets:");
    printf("\nA ∩ B: ");
    printSet(&C);

    // Test difference
    differenceSet(&A, &B, &C);
    printf("\nDifference of Sets:");
    printf("\nA - B: ");
    printSet(&C);

    differenceSet(&B, &A, &C);
    printf("B - A: ");
    printSet(&C);

    // Test subset
    printf("\nIs A a subset of universal? %s\n", isSubset(&A, &universal) ? "Yes" : "No");
    printf("Is universal a subset of A? %s\n", isSubset(&universal, &A) ? "Yes" : "No");

    // Test equality
    printf("\nIs A equal to B? %s\n", isEqual(&A, &B) ? "Yes" : "No");

    // Test complement
    complementSet(&universal, &A, &C);
    printf("\nComplement of Set A' : ");
    printSet(&C);
    complementSet(&universal, &B, &C);
    printf("\nComplement of Set B' : ");
    printSet(&C);

    return 0;
}

// Initialize an empty set
void initSet(Set *s) {
    s->size = 0;
}

// Check if a set is empty
bool isEmpty(Set *s) {
    return s->size == 0;
}

// Check if an element is a member of a set
bool isMember(Set *s, int element) {
    for (int i = 0; i < s->size; i++) {
        if (s->elements[i] == element) {
            return true;
        }
    }
    return false;
}

// Add an element to a set if it's not already there
void addElement(Set *s, int element) {
    if (!isMember(s, element) && s->size < MAX_SIZE) {
        s->elements[s->size++] = element;
    }
}

// Remove an element from a set
void removeElement(Set *s, int element) {
    for (int i = 0; i < s->size; i++) {
        if (s->elements[i] == element) {
            // Replace with the last element and reduce size
            s->elements[i] = s->elements[s->size - 1];
            s->size--;
            return;
        }
    }
}

// Return the number of elements in a set
int cardinality(Set *s) {
    return s->size;
}

// Print all elements of a set
void printSet(Set *s) {
    printf("{ ");
    for (int i = 0; i < s->size; i++) {
        printf("%d", s->elements[i]);
        if (i < s->size - 1) {
            printf(", ");
        }
    }
    printf(" }\n");
}

// Union of two sets
void unionSet(Set *set1, Set *set2, Set *result) {
    initSet(result);

    // Add all elements from set1
    for (int i = 0; i < set1->size; i++) {
        addElement(result, set1->elements[i]);
    }

    // Add all elements from set2
    for (int i = 0; i < set2->size; i++) {
        addElement(result, set2->elements[i]);
    }
}

// Intersection of two sets
void intersectionSet(Set *set1, Set *set2, Set *result) {
    initSet(result);

    // Add elements that are in both sets
    for (int i = 0; i < set1->size; i++) {
        if (isMember(set2, set1->elements[i])) {
            addElement(result, set1->elements[i]);
        }
    }
}

// Difference of two sets (set1 - set2)
void differenceSet(Set *set1, Set *set2, Set *result) {
    initSet(result);

    // Add elements from set1 that are not in set2
    for (int i = 0; i < set1->size; i++) {
        if (!isMember(set2, set1->elements[i])) {
            addElement(result, set1->elements[i]);
        }
    }
}

// Check if set1 is a subset of set2
bool isSubset(Set *set1, Set *set2) {
    for (int i = 0; i < set1->size; i++) {
        if (!isMember(set2, set1->elements[i])) {
            return false;
        }
    }
    return true;
}

// Check if two sets are equal
bool isEqual(Set *set1, Set *set2) {
    return isSubset(set1, set2) && isSubset(set2, set1);
}

// Complement of a set (universal - set)
void complementSet(Set *universal, Set *s, Set *result) {
    differenceSet(universal, s, result);
}
