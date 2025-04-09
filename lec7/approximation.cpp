// Надолго тут застрял, но вроде разобрался

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "../helpers/print_helper.h"
#include "../lec2/SLE_solver.h"
#include "../helpers/vector_operations.h"

double phi(double x, int k)
{
    return pow(x, k);
}

std::vector<double> phi(std::vector<double> x, int k)
{
    for (auto &el : x)
    {
        el = pow(el, k);
    }
    return x;
}
/// @brief Предполагается что x [-1, 1]
/// @param k Порядок phi
/// @param m Порядок phi
/// @return
double Integrate(int k, int m)
{
    if ((m + k) % 2 == 0)
    {
        return 2 / static_cast<double>(m + k + 1);
    }
    return 0;
}

double Integrate(const std::vector<double> &x, const std::vector<double> u)
{
    int N = x.size();
    double integral = 0;
    for (int n = 1; n < N; n++)
    {
        integral += (u[n] + u[n - 1]) * (x[n] - x[n - 1]) / 2;
    }
    return integral;
}

void scale_x(double a, double b, std::vector<double> &x)
{
    double x_0 = (a + b) / 2;
    x = (x - x_0) / ((b - a) / 2);
}
void scale_back(double a, double b, std::vector<double> &x)
{
    double x_0 = (a + b) / 2;
    x = (x * (b - a) / 2) + x_0;
}

double Approximation(std::vector<double> &x, const std::vector<double> &u, int K, double approximation_target)
{
    int N = x.size() - 1;
    std::vector<std::vector<double>> M(K + 1, std::vector<double>(K + 1, 0));
    std::vector<double> D(K + 1, 0);

    for (int m = 0; m < K + 1; m++)
    {
        D[m] = Integrate(x, phi(x, m) * u);
        for (int k = 0; k < K + 1; k++)
        {
            M[k][m] = Integrate(x, phi(x, m) * phi(x, k));
        }
    }

    std::vector<double> Ck = SLE_Solver(M, D);
    // std::cout << "Matrix: \n";
    // for (auto x : M)
    // {
    //     std::cout << x;
    // }
    // std::cout << "Free: \n";
    // std::cout << D;
    // std::cout << "System solution: \n";
    // std::cout << Ck;
    double approximated_value = 0;
    for (int k = 0; k <= K; k++)
    {
        approximated_value += Ck[k] * phi(approximation_target, k);
    }

    return approximated_value;
};

void fill_vector(std::vector<double> &x, double start, double end, int N)
{
    x.resize(N, 0);
    double step = fabs(end - start) / N;
    for (int i = 0; i < x.size(); i++)
    {
        x[i] = start + i * step;
    }
}

int main()
{
    std::vector<double> x{1, 2, 3, 5, 6, 7, 8, 9};
    std::vector<double> u{1, 4, 4, 2, 3, 3, 4, 2};
    double a = vec_min(x);
    double b = vec_max(x);
    scale_x(a, b, x);
    int N = 100;
    std::vector<double> x_approx;
    std::vector<double> u_approx(N + 1, 0);
    fill_vector(x_approx, -1, 1, N + 1);
    int K = 5;
    for (int i = 0; i < N; i++)
    {
        double result = Approximation(x, u, K, x_approx[i]);
        u_approx[i] = result;
    }
    u_approx[N] = Approximation(x, u, K, 1);
    scale_back(a, b, x);
    scale_back(a, b, x_approx);
    std::ofstream out{"out.txt"};
    if (!out)
    {
        return 1;
    }

    out << "x: ";
    out << x;
    out << "f(x): ";
    out << u;
    out << "x_interpolated: ";
    out << x_approx;
    out << "f(x_interpolated): ";
    out << u_approx;

    // double dot = FunctionDot(x, phi, 1, u);
    // std::cout << dot << '\n';
    return 0;
}