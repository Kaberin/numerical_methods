/**
 * @file improper_integral.cpp
 * @author Vyacheslav
 * @brief Программа считающая несобственные интегралы с помощью квазиравномерной сетки методом средних. Уточнение результатов пуем рекурентного применения метода Ричардсона
 * @version 0.1
 * @date 2025-03-26
 *
 * @copyright Copyright (c) 2025
 */

#include <vector>
#include <iostream>
#include <cmath>
#include "../helpers/print_helper.h"
int S = 5; // Количество уплотнений сетки
int r = 2; // Множитель уплотнения сетки
int p = 2; // Теоретический порядок точности
int q = 2;

int a = 0; // Левая граница интегрирования
int N = 1; // Начальное количетсво отрезков

std::vector<std::vector<double>> U(S);     // Значения интеграла
std::vector<std::vector<double>> R(S);     // Ошибки
std::vector<std::vector<double>> P_eff(S); // Эффективный порядок точности

void print_tables()
{

    std::cout << "Таблица приближенных значений интеграла:\n";
    for (auto &x : U)
    {
        if (x.size() == 0)
        {
            continue;
        }
        std::cout << x << '\n';
    }
    std::cout << "Таблица вычисленных ошибок:\n";
    for (auto &x : R)
    {
        if (x.size() == 0)
        {
            continue;
        }
        std::cout << x << '\n';
    }
    std::cout << "Таблица эффективных порядков точности:\n";
    for (auto &x : P_eff)
    {
        if (x.size() == 0)
        {
            continue;
        }
        std::cout << x << '\n';
    }
}

void initialize_vectors()
{
    for (int i = 0; i < S; i++)
    {
        U[i].resize(i + 1);
        if (i < 2)
        {
            P_eff[i].resize(0);
        }
        else
        {
            P_eff[i].resize(i - 1);
        }
        R[i].resize(i);
    }
}

double x(double a, double xi, double c = 1, double m = 1)
{
    return a + c * (xi / pow(1 - xi, m));
}
double dxdxi(double xi, double c = 1, double m = 1)
{
    return c * ((pow(1 - xi, m) + xi * m * pow(1 - xi, m - 1)) / pow(1 - xi, 2 * m));
}

double f(double x)
{
    return exp(-x);
}

/**
 * @brief Интегрирование методом средних

 * @param N Количество отрезков
 * @return double - Численное значение интеграла на сетке из N отрезков
 */
double Integrate(int N)
{
    double integral = 0;
    double delta = 1 / (double)N;
    for (int n = 1; n <= N; ++n)
    {
        double xi_n = (n - 0.5) / (double)N;
        double x_n = x(a, xi_n);
        integral += f(x_n) * dxdxi(xi_n) * delta;
    }
    return integral;
}

double Richardson()
{
    for (int s = 0; s < S; s++)
    {
        U[s][0] = Integrate(pow(r, s) * N);
    }

    for (int s = 1; s < S; s++)
    {
        for (int l = 0; l < s; l++)
        {
            R[s][l] = (U[s][l] - U[s - 1][l]) / (pow(r, p + l * q) - 1);
            U[s][l + 1] = U[s][l] + R[s][l];
            if (s > 1)
            {
                if (R[s][l] == 0)
                {
                    throw std::runtime_error{"Деление на ноль"};
                }
                P_eff[s][l] = log(fabs(R[s - 1][l] / R[s][l])) / log(r);
            }
        }
    }

    print_tables();
    return U[S - 1][S - 1];
}

int main()
{
    initialize_vectors();

    double res = Richardson();
    std::cout << "Результат интегрирования: " << res << '\n';

    return 0;
}