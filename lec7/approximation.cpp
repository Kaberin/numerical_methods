#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "../helpers/print_helper.h"
#include "../lec2/SLE_solver.h"

std::vector<double> operator*(std::vector<double> v, const std::vector<double> &v1)
{
    for (int i = 0; i < v.size(); i++)
    {
        v[i] *= v1[i];
    }
    return v;
}

double phi(double x, int k)
{
    return pow(x, k);
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

double Integrate(const std::vector<double> &x, const std::vector<double> &u, int k)
{
    int N = x.size() - 1; // Количество отрезков
    double integral = 0;
    for (int n = 1; n <= N; n++)
    {
        integral += (phi(x[n], k) * u[n] + phi(x[n - 1], k) * u[n - 1]) * (x[n] - x[n - 1]) / 2;
    }
    return integral;
}

std::vector<double> operator-(std::vector<double> v, double d)
{
    for (auto &x : v)
    {
        x -= d;
    }
    return v;
}
std::vector<double> operator+(std::vector<double> v, double d)
{
    for (auto &x : v)
    {
        x += d;
    }
    return v;
}
std::vector<double> operator*(std::vector<double> v, double d)
{
    for (auto &x : v)
    {
        x *= d;
    }
    return v;
}
std::vector<double> operator/(std::vector<double> v, double d)
{
    for (auto &x : v)
    {
        x /= d;
    }
    return v;
}

double vec_max(const std::vector<double> &x)
{
    double max = (std::numeric_limits<double>::min)();
    for (const auto &el : x)
    {
        if (el > max)
        {
            max = el;
        }
    }
    return max;
}
double vec_min(const std::vector<double> &x)
{
    double min = (std::numeric_limits<double>::max)();
    for (const auto &el : x)
    {
        if (el < min)
        {
            min = el;
        }
    }
    return min;
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
        D[m] = Integrate(x, u, m);
        for (int k = 0; k < K + 1; k++)
        {
            M[k][m] = Integrate(k, m);
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
    std::vector<double> u_approx(N, 0);
    fill_vector(x_approx, -1, 1, N);
    int K = 8;
    for (int i = 0; i < 100; i++)
    {
        double result = Approximation(x, u, K, x_approx[i]);
        u_approx[i] = result;
    }
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