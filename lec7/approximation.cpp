#include <iostream>
#include <cmath>
#include <vector>
#include "../helpers/print_helper.h"

double FunctionDot(std::vector<double> x, double(*phi)(double, int), int k, std::vector<double> u) {
    double integral = 0;
    int N = x.size();
    for (int n = 1; n < N; n++) {
        integral += (phi(x[n], k) * u[n] + phi(x[n-1], k) * u[n - 1]) / 2 * (x[n] - x[n-1]);
    }
    return integral;
}

double FunctionDot(double (*phi_k)(double, int), int k, double (*phi_m)(double, int), int m){

   
}

double phi(double x, int k) {
    return pow(x, k);
}

int main() {
    std::vector<double> x{1,2,3};
    std::vector<double> u{1,4,9};

    double dot = FunctionDot(x, phi, 1, u);
    std::cout << dot << '\n';
    return 0;
}