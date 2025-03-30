

#include <iostream>
#include <vector>
#include <cmath>
#include "../helpers/print_helper.h"

// version_1
double left_rect(double (*f)(double), double a, double b)
{

    int N = 1000;
    double h = fabs((a - b)) / N;

    std::vector<double> x(N, 0);
    for (int i = 0; i < N; i++)
    {
        x[i] = a + h * i;
    }
    x[0] = a;
    x[N - 1] = b;
    // std::cout << x;
    double result = 0;

    for (int i = 1; i <= N; i++)
    {
        result += f(x[i - 1]) * h;
    }

    return result;
}
// version 2
double left_rect_2(double (*f)(double), double a, double b)
{

    int N = 10000;
    double h = fabs((a - b)) / N;
    double x = a;

    double result = 0;

    for (int i = 0; i < N + 1; i++)
    {
        result += f(x) * h;
        x += h;
    }

    return result;
}

double right_rect(double (*f)(double), double a, double b)
{

    int N = 10000;
    double h = fabs((a - b)) / N;
    double x = a;

    double result = 0;

    for (int i = 0; i < N + 1; i++)
    {
        x += h;
        result += f(x) * h;
    }

    return result;
}

double trapezoid(double (*f)(double), double a, double b)
{
    int N = 1000;
    double h = fabs((a - b)) / N;
    double x = a;
    double x1 = a + h;
    double result = 0;

    for (int i = 0; i < N; i++)
    {
        result += ((f(x) + f(x1)) / 2) * h;
        x += h;
        x1 += h;
    }
    return result;
}

double f1(double x)
{
    return x * x * x;
}

int main()
{
    std::cout << left_rect_2(cos, -0.7, 1.9) << '\n';
    std::cout << right_rect(cos, -0.7, 1.9) << '\n';
    std::cout << trapezoid(cos, -0.7, 1.9) << '\n';
    return 0;
}