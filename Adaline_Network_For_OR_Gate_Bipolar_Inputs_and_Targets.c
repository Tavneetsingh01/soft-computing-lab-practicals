// Q2. Design and simulate the behaviour of OR Gate using Adaline Network in C for bipolar inputs and targets.
// Created by tavneet on 2/9/25.

#include <stdio.h>
#define NUM_INPUTS 2
#define NUM_PATTERNS 4
#define MAX_ITERATIONS 100

int main() {
    signed int x[NUM_PATTERNS][NUM_INPUTS], tar[NUM_PATTERNS];
    float w[NUM_INPUTS], wc[NUM_INPUTS], e = 0, es = 0, et = 1.4, yin = 0, alpha = 0.1, b = 0.1, bc = 0.0;
    int i, j, k, q = 1;

    // Input patterns to be entered by the user
    printf("Enter the input patterns and targets for Bipolar OR Gate (-1 or 1):\n");
    for (i = 0; i < NUM_PATTERNS; i++) {
        printf("Enter input pattern %d (x1 x2): ", i + 1);
        scanf("%d %d", &x[i][0], &x[i][1]);
        printf("Enter target for pattern %d: ", i + 1);
        scanf("%d", &tar[i]);
    }

    // Initialize weights and biases
    for (i = 0; i < NUM_INPUTS; i++) {
        w[i] = 0.1;
        wc[i] = 0.0;
    }
    b = 0.1;
    bc = 0.0;

    // Displaying Initial weights and biases
    printf("Initial weights and bias are:\n");
    for (i = 0; i < NUM_INPUTS; i++) {
        printf("Weight w[%d] = %.2f\t",i+1, w[i]);
        printf("Weight Changes wc[%d] = %.2f\t",i+1, wc[i]);
        printf("\n");
    }
    printf("Bias is %.2f\n", b);


    do {
        printf("\n-------------------\n");
        printf("| Iteration: %d |",q);
        printf("\n---------------------");

        // Print the table header
        printf("\n---------------------------------------------------------------------------------------------------------------------------\n");
        printf("| x1 | x2 | Target | Net |  Error: (t-yin) | \u0394w\u2081 | \u0394w\u2082 | \u0394b | New w\u2081 | New w\u2082 | New b | Error^2: (t-yin)^2 |\n");
        printf("-----------------------------------------------------------------------------------------------------------------------------\n");

        es = 0;

        for (i = 0; i < NUM_PATTERNS; i++) {
            yin = 0.0;
            for (j = 0; j < NUM_INPUTS; j++) {
                yin = yin + x[i][j] * w[j];
            }
            yin = yin + b;

            e = (float)tar[i] - yin;
            es = es + e * e;

            // Update weights
            for (k = 0; k < NUM_INPUTS; k++) {
                wc[k] = alpha * e * x[i][k];
                w[k] = w[k] + wc[k];
            }

            // Update bias
            bc = alpha * e;
            b = b + bc;
            // Print the table row for this pattern
            printf("| %d | %d | %d |  %.5f | %.5f | %.5f| %.5f| %.5f | %.5f | %.5f | %.5f | %.5f |\n",
                    x[i][0], x[i][1], tar[i], yin, e, wc[0], wc[1], bc, w[0], w[1], b, e * e);
        }


        printf("-----------------------------------------------------------------------------------------------------------------------\n");
        printf("  Final Weights and bias after Iteration %d: Weights: w[1]=%.5f, w[2]=%.5f, Bias=%.5f   |   Total Error^2 = %.5f\n", q, w[0], w[1], b, es);
        printf("-----------------------------------------------------------------------------------------------------------------------\n");

        if (es <= et) {
            printf("\nConverged! in %d iterations with final error = %.5f\n",q,es);
            printf("Final Weights and bias: w1=%.5f, w2=%.5f, Bias=%.5f\n", w[0], w[1], b);
            break;
        }
        q++;
    } while (q <= MAX_ITERATIONS);

    if (q > MAX_ITERATIONS) {
        printf("\nNot converged within %d iterations.\n", MAX_ITERATIONS);
    }

    return 0;
}