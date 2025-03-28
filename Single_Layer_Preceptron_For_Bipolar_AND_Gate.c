//Q1. Design and simulate the behaviour of AND Gate using Perceptron Network in C for bipolar inputs and targets.
#include <stdio.h>

#define NUM_INPUTS 2
#define NUM_PATTERNS 4

int main() {
    int x[NUM_PATTERNS][NUM_INPUTS], tar[NUM_PATTERNS];
    float w[NUM_INPUTS], wc[NUM_INPUTS], out = 0;
    int i, j, k = 0, h = 1;
    float s = 0, b, bc, alpha = 0;
    float theta;

    printf("Enter the value of theta & alpha: ");
    scanf("%f %f", &theta, &alpha);

    printf("Enter the input patterns and targets:\n");
    for (i = 0; i < NUM_PATTERNS; i++) {
        printf("Enter the value of %d Input row & Target: ", i + 1);
        for (j = 0; j < NUM_INPUTS; j++) {
            scanf("%d", &x[i][j]);
        }
        scanf("%d", &tar[i]);
    }


    // Initialize weights and bias
    for (i = 0; i < NUM_INPUTS; i++) {
        w[i] = 0;
        wc[i] = 0;
    }
    b = 0;
    bc = 0;

    // Display initial weights and bias
    printf("\nInitial weights and bias:\n");
    for (j = 0; j < NUM_INPUTS; j++) {
        printf("Weight w[%d]=%.2f\t", j, w[j]);
    }
    for (j = 0; j < NUM_INPUTS; j++) {
        printf("Weight Changes wc[%d]=%.2f\t", j, w[j]);
    }
    printf("\n\n");
    printf("Bias Changes bc=%.2f\t", bc);
    printf("Bias b=%.2f\n\n", b);

    printf("Net \t Target\t Weight changes\tNew weights\t Bias changes\tNew Bias \n");

    do {
        printf("-----------------------------------------------------------------------------\n");
        printf("ITERATION: %d\n", h);
        printf("----------------------------------------------------------------------------\n");
        k = 0;

        for (i = 0; i < NUM_PATTERNS; i++) {
            s = 0;
            for (j = 0; j < NUM_INPUTS; j++) {
                s += (float)x[i][j] * w[j];
            }
            s += b;
            printf("%.2f\t", s);

            out = (s > theta) ? 1 : ((s < -theta) ? -1 : 0);

            printf("%d\t", tar[i]);

            if (out == tar[i]) {
                for (j = 0; j < NUM_INPUTS; j++) {
                    wc[j] = 0;
                    printf("%.2f\t", wc[j]);
                }
                for (j = 0; j < NUM_INPUTS; j++)
                    printf("%.2f\t", w[j]);
                k++;
                bc = 0;
                printf("%.2f\t\t", bc);
                printf("%.2f\t", b);
            } else {
                for (j = 0; j < NUM_INPUTS; j++) {
                    wc[j] = x[i][j] * tar[i] * alpha;
                    w[j] += wc[j];
                    printf("%.2f\t", wc[j]);
                }
                for (j = 0; j < NUM_INPUTS; j++)
                    printf("%.2f\t", w[j]);
                bc = tar[i] * alpha;
                b += bc;
                printf("%.2f\t\t", bc);
                printf("%.2f\t", b);
            }
            printf("\n");
        }
        h++;
    } while (k < NUM_PATTERNS);

    printf("\nFinal weights\n");
    for (j = 0; j < NUM_INPUTS; j++) {
        printf("w[%d]=%.2f\t", j, w[j]);
    }
    printf("Bias b=%.2f\n", b);

    return 0;
}
