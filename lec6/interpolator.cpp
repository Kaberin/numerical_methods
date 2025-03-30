/**
 * @file interpolator.cpp
 * @author your name (you@domain.com)
 * @brief Интерполяция функции с помощью многочлена Лагранжа
 * @version 0.1
 * @date 2025-03-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../lec2/SLE_solver.h"
#include "../helpers/print_helper.h"
#include <windows.h>
#include <cmath>

const int N = 10;
std::vector<double> known_values(N, 0);
std::vector<double> x_values(N, 0);

double interpolated_function(std::vector<double> c, double x)
{
    double value = 0;
    for (int i = 0; i < N; i++)
    {
        value += c[i] * pow(x, i);
    }
    return value;
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    double x = 0.1;
    for (int i = 0; i < known_values.size(); i++)
    {
        x_values[i] = x;
        known_values[i] = exp(x) * sin(x);
        x += 0.5;
    }
    // std::cout << known_values;

    std::vector<std::vector<double>> M(N, std::vector<double>(N, 0));
    for (int i = 0; i < M.size(); i++)
    {
        for (int j = 0; j < M[i].size(); j++)
        {
            M[i][j] = pow(x_values[i], j);
        }
    }

    std::vector<double> coefficiens = SLE_Solver(M, known_values);
    // std::cout << coefficiens;
    double point = 1.11;
    std::cout << "Интерполированное значение функции в точке " << point << " равно " << interpolated_function(coefficiens, point) << '\n';
    std::cout << "Настощее значение функции в точке " << point << " равно " << exp(point) * sin(point) << '\n';

    return 0;
}