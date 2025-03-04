// Q3. Design and simulate the behaviour XOR Gate using Madaline network in C language for bipolar inputs and targets.
// Created by Tavneet on 2/23/25.
#include <stdio.h>
#include<math.h>
#define NUM_PATTERNS 4
#define NUM_INPUTS 2
#define MAX_ITERATIONS 10

void main() {
    signed int x[NUM_PATTERNS][NUM_INPUTS], tar[NUM_PATTERNS];
    float w[NUM_INPUTS][NUM_INPUTS], wc[NUM_INPUTS][NUM_INPUTS], b[NUM_INPUTS];
    float zin[NUM_INPUTS], zout[NUM_INPUTS], z1 = 0, z2 = 0, yin = 0, yout = 0, b3 = 0.5, v1 = 0.5, v2 = 0.5, alpha =
            0.5, e = 0, es = 0, prev_es = 0;
    int i, j, itr = 1;

    // Input patterns to be entered by the user
    printf("Enter the input patterns and targets for Bipolar XOR Gate (-1 or 1):\n");
    for (i = 0; i < NUM_PATTERNS; i++) {
        printf("Enter input pattern %d (x1 x2): ", i + 1);
        scanf("%d %d", &x[i][0], &x[i][1]);
        printf("Enter target for pattern %d: ", i + 1);
        scanf("%d", &tar[i]);
    }

    // Input initial weights and biases
    printf("Enter Weights:\n");
    for (i = 0; i <= 1; i++) {
        for (j = 0; j <= 1; j++) {
            printf("Enter Weight: w[%d][%d]:\n", i + 1, j + 1);
            scanf("%f", &w[i][j]);
            wc[i][j] = 0;
        }

        printf("Enter bias b[%d]: ", i + 1);
        scanf("%f", &b[i]);
    }
    do {
        printf("\n-------------------\n");
        printf("| Iteration: %d |", itr);
        printf("\n---------------------");

        // Print the table header
        printf(
            "\n---------------------------------------------------------------------------------------------------------------------------\n");
        printf(
            "| x\u2081 | x\u2082 | Target | Zin\u2081 | Zin\u2082| Zout\u2081 | Zout\u2082| yin | yout | New w\u2081\u2081 | New w\u2082\u2081 | New b\u2081 | New w\u2081\u2082 | New w\u2082\u2082 | New b\u2082\n");
        printf(
            "-----------------------------------------------------------------------------------------------------------------------------\n");

        prev_es = es;
        es = 0.0;

        for (i = 0; i < 4; i++) {
            zin[0] = 0.0;
            zin[1] = 0.0;
            zout[0] = 0.0;
            zout[1] = 0.0;
            yin = 0.0;
            yout = 0.0;
            e = 0.0;
            for (j = 0; j <= 1; j++) {
                zin[j] += (x[i][0] * w[0][j]) + (x[i][1] * w[1][j]) + b[j];
                //printf("zin[%d] = %.5f",j+1,zin[j]);
                if (zin[j] >= 0) {
                    zout[j] = 1;
                } else {
                    zout[j] = -1;
                }
            }
            yin += (zout[0] * v1) + (zout[1] * v2) + b3;
            if (yin >= 0) {
                yout = 1;
            } else {
                yout = -1;
            }
            if (yout != tar[i]) {
                if (tar[i] == 1) {
                    // In Madaline Rule I, we're essentially looking at which value
                    // has the smallest absolute value (closest to the decision boundary)
                    float abs_zin1 = fabsf(zin[0]);
                    float abs_zin2 = fabsf(zin[1]);

                    if (abs_zin1 < abs_zin2) {
                        //updating weight and bias associated with zin1
                        w[0][0] += alpha * (tar[i] - zin[0]) * x[i][0];
                        w[1][0] += alpha * (tar[i] - zin[0]) * x[i][1];
                        b[0] += alpha * (tar[i] - zin[0]);
                    } else if (abs_zin2 < abs_zin1) {
                        //updating weight and bias associated with zin2
                        w[0][1] += alpha * (tar[i] - zin[1]) * x[i][0];
                        w[1][1] += alpha * (tar[i] - zin[1]) * x[i][1];
                        b[1] += alpha * (tar[i] - zin[1]);
                    }
                } else if (tar[i] != 1) {
                    if (zin[0] > 0 && zin[1] < 0) {
                        //updating weight and bias associated with zin1
                        w[0][0] += alpha * (tar[i] - zin[0]) * x[i][0];
                        w[1][0] += alpha * (tar[i] - zin[0]) * x[i][1];
                        b[0] += alpha * (tar[i] - zin[0]);
                    } else if (zin[1] > 0 && zin[0] < 0) {
                        //updating weight and bias associated with zin2
                        w[0][1] += alpha * (tar[i] - zin[1]) * x[i][0];
                        w[1][1] += alpha * (tar[i] - zin[1]) * x[i][1];
                        b[1] += alpha * (tar[i] - zin[1]);
                    } else {
                        //updating both weight and bias associated with zin1, zin2
                        w[0][0] += alpha * (tar[i] - zin[0]) * x[i][0];
                        w[1][0] += alpha * (tar[i] - zin[0]) * x[i][1];
                        b[0] += alpha * (tar[i] - zin[0]);

                        //updating weight and bias associated with zin2
                        w[0][1] += alpha * (tar[i] - zin[1]) * x[i][0];
                        w[1][1] += alpha * (tar[i] - zin[1]) * x[i][1];
                        b[1] += alpha * (tar[i] - zin[1]);
                    }
                }
            }
            printf("%d, %d, %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f\n\n", x[i][0],
                   x[i][1], tar[i], zin[0], zin[1], zout[0], zout[1], yin, yout, w[0][0], w[1][0], b[0], w[0][1],
                   w[1][1], b[1]);

            e = (float) tar[i] - yin;
            es += e * e;
        }
        if (itr != 1 && prev_es == es) {
            break;
        }
        itr = itr + 1;
    } while (itr <= MAX_ITERATIONS);
}
