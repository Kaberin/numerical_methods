/**
 * @file parametric.cpp
 * @author Vyacheslav (you@domain.com)
 * @brief Параметрическая интерполяция
 * @version 0.1
 * @date 30-03-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>
#include <fstream>
#include <limits>

#include "../helpers/print_helper.h"
using namespace std;

double function(double x)
{
    return x * exp(x);
}
std::ofstream &operator<<(std::ofstream &ofs, const std::vector<double> &v)
{
    for (auto &x : v)
    {
        ofs << x << " ";
    }
    ofs << '\n';
    return ofs;
}

int factorial(int n)
{
    int result = 1;
    for (int i = 2; i <= n; i++)
    {
        result *= i;
    }

    return result;
}

double Interpolation(vector<double> x, vector<double> u, double a)
{
    int N = x.size() - 1;
    vector<vector<double>> U(N + 1, vector<double>(N + 1, 0));
    for (int n = 0; n <= N; n++)
    {
        U[n][0] = u[n];
    }

    for (int k = 1; k <= N; k++)
    {
        for (int n = 0; n <= N - k; n++)
        {
            U[n][k] = k * (U[n][k - 1] - U[n + 1][k - 1]) / (x[n] - x[n + k]);
        }
    }

    double result = 0;
    for (int n = 0; n <= N; n++)
    {
        double product = 1;
        for (int k = 0; k <= n - 1; k++)
        {
            product *= (a - x[k]);
        }
        result += U[0][n] * product / factorial(n);
    }

    return result;
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::vector<double> x{2, 4, 2, 4};
    std::vector<double> u{2, 4, 4, 2};
    std::vector<double> t{2, 4, 3, 1};
    int N = 100;
    double start = 0;
    double end = 5;
    std::vector<double> t_interp(N, 0);
    std::vector<double> u_interp(N, 0);
    std::vector<double> x_interp(N, 0);

    for (int i = 0; i < N; i++)
    {
        double step = fabs(end - start) / N;
        t_interp[i] = start + i * step;
    }

    for (int i = 0; i < N; i++)
    {
        u_interp[i] = Interpolation(t, u, t_interp[i]);
        x_interp[i] = Interpolation(t, x, t_interp[i]);
    }

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
    out << x_interp;
    out << "f(x_interpolated): ";
    out << u_interp;

    // double point = 2;
    // double res = Interpolation(x_values, func_values, point);
    // std::cout << "Интерполированное значение функции в точке " << point << " равно " << res << '\n';
    // std::cout << "Настощее значение функции в точке " << point << " равно " << function(point) << '\n';

    return 0;
}