#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// A. Step Function
double step_function(double x) {
    return (x >= 0) ? 1.0 : 0.0;
}

// B. Signum Function
double signum_function(double x) {
    if (x > 0) return 1.0;
    else if (x < 0) return -1.0;
    else return 0.0;
}

// C. Binary Sigmoidal Function
double binary_sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// D. Bipolar Sigmoidal Function
double bipolar_sigmoid(double x) {
    return 2.0 / (1.0 + exp(-x)) - 1.0;
}

// E. ReLU (Rectified Linear Unit) Function
double relu(double x) {
    return (x > 0) ? x : 0.0;
}

// Derivatives of activation functions for backpropagation
double binary_sigmoid_derivative(double x) {
    double sigmoid = binary_sigmoid(x);
    return sigmoid * (1.0 - sigmoid);
}

double bipolar_sigmoid_derivative(double x) {
    double sigmoid = bipolar_sigmoid(x);
    return 0.5 * (1.0 + sigmoid) * (1.0 - sigmoid);
}

double relu_derivative(double x) {
    return (x > 0) ? 1.0 : 0.0;
}

// Function to generate data points for plotting
void generate_graph_data(const char* filename, double min_x, double max_x, int num_points) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    // Write header
    fprintf(file, "X\tStep\tSignum\tBinary_Sigmoid\tBipolar_Sigmoid\tReLU\n");

    // Generate data points
    double step = (max_x - min_x) / (num_points - 1);
    for (int i = 0; i < num_points; i++) {
        double x = min_x + i * step;
        fprintf(file, "%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\n",
               x,
               step_function(x),
               signum_function(x),
               binary_sigmoid(x),
               bipolar_sigmoid(x),
               relu(x));
    }

    fclose(file);
    printf("Graph data has been written to %s\n", filename);
}

// Example usage with sample values and graph generation
int main() {
    // Sample values demonstration
    double test_values[] = {-3.0, -1.0, 0.0, 1.0, 3.0};
    int num_values = sizeof(test_values) / sizeof(test_values[0]);

    printf("Value\tStep\tSignum\tBin_Sigmoid\tBip_Sigmoid\tReLU\n");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < num_values; i++) {
        double x = test_values[i];
        printf("%.1f\t%.1f\t%.1f\t%.6f\t%.6f\t%.1f\n",
               x,
               step_function(x),
               signum_function(x),
               binary_sigmoid(x),
               bipolar_sigmoid(x),
               relu(x));
    }

    // Generate data for graphs
    generate_graph_data("activation_functions.txt", -5.0, 5.0, 200);

    // Instructions for plotting with gnuplot
    printf("\nTo plot using gnuplot:\n");
    printf("1. Install gnuplot if not already installed\n");
    printf("2. Run gnuplot and use the following commands:\n\n");
    printf("   gnuplot> set title 'Neural Network Activation Functions'\n");
    printf("   gnuplot> set xlabel 'Input (x)'\n");
    printf("   gnuplot> set ylabel 'Output'\n");
    printf("   gnuplot> plot 'activation_functions.txt' using 1:2 with lines title 'Step', \\\n");
    printf("                 '' using 1:3 with lines title 'Signum', \\\n");
    printf("                 '' using 1:4 with lines title 'Binary Sigmoid', \\\n");
    printf("                 '' using 1:5 with lines title 'Bipolar Sigmoid', \\\n");
    printf("                 '' using 1:6 with lines title 'ReLU'\n");

    // Alternative instructions for visualization with Python
    printf("\nAlternatively, to plot using Python:\n");
    printf("import matplotlib.pyplot as plt\n");
    printf("import pandas as pd\n\n");
    printf("data = pd.read_csv('activation_functions.txt', sep='\\t')\n");
    printf("plt.figure(figsize=(10, 6))\n");
    printf("plt.plot(data['X'], data['Step'], label='Step')\n");
    printf("plt.plot(data['X'], data['Signum'], label='Signum')\n");
    printf("plt.plot(data['X'], data['Binary_Sigmoid'], label='Binary Sigmoid')\n");
    printf("plt.plot(data['X'], data['Bipolar_Sigmoid'], label='Bipolar Sigmoid')\n");
    printf("plt.plot(data['X'], data['ReLU'], label='ReLU')\n");
    printf("plt.xlabel('Input (x)')\n");
    printf("plt.ylabel('Output')\n");
    printf("plt.title('Neural Network Activation Functions')\n");
    printf("plt.legend()\n");
    printf("plt.grid(True)\n");
    printf("plt.savefig('activation_functions.png')\n");
    printf("plt.show()\n");

    return 0;
}