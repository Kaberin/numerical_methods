/**
 * @file newton_interpolator.cpp
 * @author your name (you@domain.com)
 * @brief Реализация интерполяционного многочлена ньютона
 *
 * @date 2025-03-28
 * @version 0.1 Базовый функционал. Считает интерполяцию. Пишет данные в out.txt. graph.py может построить то что получилось ¯\_(ツ)_/¯
 *
 * @date 2015-03-30
 * @version 0.2 Добавил уточнение путем добавления к расчету дополнительных точек. Вроде работает ¯\_(ツ)_/¯
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <limits>
#include "./newton_interp.h"
#include "../helpers/print_helper.h"
using namespace std;
double Interpolation(vector<double> x, vector<double> u, double a);

double function(double x)
{
    return cos(x);
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

vector<double> x_values = {9, 1, 4, 2, 5, 3, 7, 8};
vector<double> func_values = {2, 4, 4, 3, 1, 3, 4, 2};

void fill_initial()
{
    func_values.resize(x_values.size(), 0);
    for (int i = 0; i < x_values.size(); i++)
    {
        func_values[i] = function(x_values[i]);
    }
}

void fill_vector(double start, double end, int N, std::vector<double> &x, std::vector<double> &u)
{
    double step = fabs(end - start) / (double)N;
    for (int i = 0; i < x.size(); i++)
    {
        x[i] = start + i * step;
        u[i] = function(x[i]);
    }
}

int M = 100;
vector<double> x_inerpolated(M, 0);
vector<double> func_inerpolated(M, 0);

double x_start = 1;
double x_end = 36;
void interpolate_array()
{
    double step = fabs(x_end - x_start) / M;
    for (int i = 0; i < x_inerpolated.size(); i++)
    {
        x_inerpolated[i] = x_start + i * step;
        func_inerpolated[i] = Interpolation(x_values, func_values, x_inerpolated[i]);
    }
    x_inerpolated.push_back(x_end);
    func_inerpolated.push_back(Interpolation(x_values, func_values, x_end));
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

double InterpolationError(std::vector<double> x, vector<double> u, double a, double relative_error)
{

    double error = 100;
    std::vector<double> x_closest{};
    std::vector<double> f_closest{};
    double prev_interpolation = 1;
    int N = x.size();
    for (int j = 0; j < N; j++)
    {
        int closest_index = 0;
        double closest = x[0];
        for (int i = 1; i < N; i++)
        {
            if (fabs(x[i] - a) < fabs(closest - a))
            {
                closest = x[i];
                closest_index = i;
            }
        }
        x_closest.push_back(x[closest_index]);
        f_closest.push_back(u[closest_index]);
        x.erase(x.begin() + closest_index);
        u.erase(u.begin() + closest_index);
        if (j == 0)
        {
            prev_interpolation = Interpolation(x_closest, f_closest, a);
            continue;
        }
        double interpolated_value = Interpolation(x_closest, f_closest, a);
        double rel = fabs((interpolated_value - prev_interpolation) / interpolated_value) * 100;
        std::cout << "Relative error on iteration " << j << " = " << rel << '\n';
        if (rel >= error)
        {
            std::cout << "Relative error started to grow. Was " << error << "% became " << rel << "%\n";
            return prev_interpolation;
        }
        if (rel <= relative_error)
        {
            std::cout << "Demanded precision has been reached "
                      << rel << "%\n";
            return interpolated_value;
        }
        error = rel;
        prev_interpolation = interpolated_value;
    }
    return prev_interpolation;
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

    // std::cout
    //     << "U: ";
    // for (auto x : U)
    // {
    //     std::cout << x;
    // }

    return result;
}
// vector<double> x_values = {9, 1, 4, 2, 5, 3, 7, 8};
// int main()
// {
//     SetConsoleOutputCP(65001);
//     SetConsoleCP(65001);
//     x_start = 1;
//     x_end = 4;
//     int N = 10;
//     x_values.resize(N, 0);
//     func_values.resize(N, 0);
//     fill_vector(x_start, x_end, N, x_values, func_values);
//     std::cout << "X: " << x_values;
//     std::cout << "U(X): " << func_values;
//     std::cout << "Press Enter to continue...\n";
//     std::cin.get();
//     double interpolation_target = 2;
//     double err = 1;
//     double result = InterpolationError(x_values, func_values, interpolation_target, err);
//     double zero = 0;
//     double result_z = InterpolationError(func_values, x_values, zero, err);
//     std::cout << "Zero is at " << result_z << '\n';
//     std::string f = "cos(x)";
//     std::cout << "Function " << f << '\n';
//     std::cout
//         << "Interpolation result " << result << '\n';
//     std::cout << "Real result " << function(interpolation_target) << '\n';
//     // fill_initial();
//     // std::ofstream out{"out.txt"};
//     // if (!out)
//     // {
//     //     return 1;
//     // }
//     // interpolate_array();
//     // out << "x: ";
//     // out << x_values;
//     // out << "f(x): ";
//     // out << func_values;
//     // out << "x_interpolated: ";
//     // out << x_inerpolated;
//     // out << "f(x_interpolated): ";
//     // out << func_inerpolated;

//     // double point = 2;
//     // double res = Interpolation(x_values, func_values, point);
//     // std::cout << "Интерполированное значение функции в точке " << point << " равно " << res << '\n';
//     // std::cout << "Настощее значение функции в точке " << point << " равно " << function(point) << '\n';

//     return 0;
// }