#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>
#include "../lec6/newton_interp.h"
#include "../helpers/print_helper.h"
double Differentiate(double (*u)(double), double x, double h)
{
    double dif = (u(x) - u(x - h)) / h;
    return dif;
}

double f(double x)
{
    return x * x * x;
}

int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    double x = 0;
    int S = 5;
    double r = 2;
    double h = 0.1;
    int q = 1;
    int p = 1;
    std::vector<std::vector<double>> U(S, std::vector<double>(S, 0));
    std::vector<std::vector<double>> R(S, std::vector<double>(S, 0));
    std::vector<std::vector<double>> P_eff(S, std::vector<double>(S, 0));
    for (int i = 0; i < S; i++)
    {
        U[i].resize(i + 1, 0);
        if (i < 2)
        {
            P_eff[i].resize(0);
        }
        else
        {
            P_eff[i].resize(i - 1, 0);
        }
        R[i].resize(i, 0);
    }

    for (int s = 0; s < S; s++)
    {
        U[s][0] = Differentiate(f, x, h / pow(r, s));
    }

    for (int s = 1; s < S; s++)
    {
        for (int l = 0; l < s; l++)
        {
            R[s][l] = (U[s][l] - U[s - 1][l]) / (pow(r, p + l * q) - 1);
            U[s][l + 1] = U[s][l] + R[s][l];
        }
    }
    for (int s = 2; s < S; s++)
    {
        for (int l = 0; l < s - 1; l++)
        {
            P_eff[s][l] = log(fabs(R[s - 1][l] / R[s][l])) / log(r);
        }
    }

    std::cout << "Таблица приближенных значений производной:\n";
    for (auto x : U)
    {
        std::cout << std::fixed << std::setprecision(5) << x;
    }
    std::cout << '\n';
    std::cout << "Таблица оценок ошибок:\n";
    for (auto x : R)
    {
        std::cout << std::fixed << std::setprecision(5) << x;
    }
    std::cout << '\n';
    std::cout << "Таблица эффективных порядков точности:\n";
    for (auto x : P_eff)
    {
        std::cout << std::fixed << std::setprecision(5) << x;
    }
    std::cout << "\n";

    return 0;
}