// Q4. Design and Simulate the Behaviour of XOR Gate Using Back-Propagation Network in c for Bipolar Inputs and Targets.
// Created by tavneet on 3/27/25.
//
#include <stdio.h>
#include<math.h>
#define NUM_PATTERNS 4
#define NUM_INPUTS 2
#define MAX_ITERATIONS 3000

void main() {
    signed int x[NUM_PATTERNS][NUM_INPUTS], tar[NUM_PATTERNS], y_actual = 0;
    float v[NUM_INPUTS][NUM_INPUTS], vc[NUM_INPUTS][NUM_INPUTS], v_b[NUM_INPUTS];
    float zin[NUM_INPUTS], zout[NUM_INPUTS], yin = 0, yout = 0, w1, w2, w0, alpha =
            0.25, delta_out = 0, delta_internal[NUM_INPUTS] = {0}, delta_in[NUM_INPUTS]={0};
    int i, j, itr = 1, k = 0;

    // Input patterns to be entered by the user
    printf("Enter the input patterns and targets for Bipolar XOR Gate (-1 or 1):\n");
    for (i = 0; i < NUM_PATTERNS; i++) {
        printf("Enter input pattern %d (x1 x2): ", i + 1);
        scanf("%d %d", &x[i][0], &x[i][1]);
        printf("Enter target for pattern %d: ", i + 1);
        scanf("%d", &tar[i]);
    }

    // Input initial weights and biases
    printf("Enter Weights and Bias Between Input and Hidden Layer:\n");
    for (i = 0; i <= 1; i++) {
        for (j = 0; j <= 1; j++) {
            printf("Enter Weight: v[%d][%d]:\n", i + 1, j + 1);
            scanf("%f", &v[i][j]);
            vc[i][j] = 0;
        }

        printf("Enter bias v_b[%d]: ", i + 1);
        scanf("%f", &v_b[i]);
    }

    printf("\nEnter Weights and Bias Between Hidden and Output Layer:\n");
    printf("Enter Weight: w1:\n");
    scanf("%f", &w1);
    printf("Enter Weight: w2:\n");
    scanf("%f", &w2);
    printf("Enter bias: w0:\n");
    scanf("%f", &w0);

    do {
        printf("\n-------------------\n");
        printf("| Iteration: %d |", itr);
        printf("\n---------------------");

        // Print the table header
        printf(
            "\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf(
            "| x\u2081 | x\u2082 | Target | Zin\u2081 | Zin\u2082| Zout\u2081 | Zout\u2082| yin | yout | y_actual | New v\u2081\u2081 | New v\u2082\u2081 | New v_b\u2081 | New v\u2081\u2082 | New v\u2082\u2082 | New v_b\u2082 | New w1 | New w2 | New w0 |\n");
        printf(
            "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

        k = 0;

        for (i = 0; i < 4; i++) {
            zin[0] = 0.0;
            zin[1] = 0.0;
            zout[0] = 0.0;
            zout[1] = 0.0;
            yin = 0.0;
            yout = 0.0;
            y_actual = 0;
            delta_in[0] = 0;
            delta_in[1] = 0;
            delta_internal[0] = 0;
            delta_internal[0] = 0;
            delta_out = 0;

            for (j = 0; j <= 1; j++) {
                zin[j] = (x[i][0] * v[0][j]) + (x[i][1] * v[1][j]) + v_b[j];
                //printf("zin[%d] = %.5f",j+1,zin[j]);

                zout[j] = ((1 - expf(-zin[j])) / (1 + expf(-zin[j])));
            }

            yin = (zout[0] * w1) + (zout[1] * w2) + w0;
            yout = ((1 - expf(-yin)) / (1 + expf(-yin)));

            if (yout >= 0) {
                y_actual = 1;
            } else {
                y_actual = -1;
            }

            if (y_actual != tar[i]) {
                delta_out = (tar[i] - yout) * (0.5 * (1 + yout) * (1 - yout));

                //weight updation between hidden and output layer
                w1 += (alpha * delta_out * zout[0]);
                w2 += (alpha * delta_out * zout[1]);
                w0 += (alpha * delta_out);

                delta_in[0] = delta_out * w1;
                delta_in[1] = delta_out * w2;

                delta_internal[0] = delta_in[0] * (0.5 * (1 + zout[0]) * (1 - zout[0]));
                delta_internal[1] = delta_in[1] * (0.5 * (1 + zout[1]) * (1 - zout[1]));


                //weight updation between input and hidden layer
                v[0][0] += alpha * delta_internal[0] * x[i][0];
                v[0][1] += alpha * delta_internal[1] * x[i][0];
                v_b[0] += alpha * delta_internal[0];

                v[1][0] += alpha * delta_internal[0] * x[i][1];
                v[1][1] += alpha * delta_internal[1] * x[i][1];
                v_b[1] += alpha * delta_internal[1];
            } else if (y_actual == tar[i]) {
                k += 1;
            }
            printf(
                "%d, %d, %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f\n\n",
                x[i][0],
                x[i][1], tar[i], zin[0], zin[1], zout[0], zout[1], yin, yout, y_actual, v[0][0], v[1][0], v_b[0],
                v[0][1],
                v[1][1], v_b[1], w1, w2, w0);
        }
        if (k == 4) {
            break;
        }
        itr = itr + 1;
    } while (itr <= MAX_ITERATIONS);
}
