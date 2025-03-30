#include <vector>
#include <iostream>
#include <stdio.h>

std::ostream &operator<<(std::ostream &os, const std::vector<double> &v)
{

    for (auto x : v)
    {
        os << x << '\t';
    }
    os << '\n';
    return os;
}
// std::vector<double>
void thomas_gpt(std::vector<std::vector<double>> M)
{
    int N = M.size();

    std::vector<double> a(N, 0);
    std::vector<double> b(N, 0);
    std::vector<double> c(N, 0);
    std::vector<double> d(N, 0);

    // Инициализация коэффициентов
    b[0] = M[0][0];
    c[0] = M[0][1];
    d[0] = M[0][N];

    for (int i = 1; i < N - 1; ++i)
    {
        a[i] = M[i][i - 1];
        b[i] = M[i][i];
        c[i] = M[i][i + 1];
        d[i] = M[i][N];
    }

    a[N - 1] = M[N - 1][N - 2];
    b[N - 1] = M[N - 1][N - 1];
    d[N - 1] = M[N - 1][N];

    std::vector<double> ksi(N, 0);
    std::vector<double> eta(N, 0);

    // Прямой ход
    ksi[0] = c[0] / b[0];
    eta[0] = d[0] / b[0];

    for (int i = 1; i < N; i++)
    {
        double denominator = b[i] - a[i] * ksi[i - 1];

        ksi[i] = c[i] / denominator;
        eta[i] = (d[i] - a[i] * eta[i - 1]) / denominator;
    }

    std::vector<double> x(N, 0);
    x[N - 1] = eta[N - 1];

    // Обратный ход
    for (int i = N - 2; i >= 0; i--)
    {
        x[i] = ksi[i] * x[i + 1] + eta[i]; // Убрали минус
    }

    std::cout << x;
}
void thomas(std::vector<std::vector<double>> M)
{
    int N = M.size();

    std::vector<double> a(N, 0);
    a[0] = 0;
    a[N - 1] = M[N - 1][N - 2];
    std::vector<double> b(N, 0);
    b[0] = M[0][0];
    b[N - 1] = M[N - 1][N - 1];
    std::vector<double> c(N, 0);
    c[0] = M[0][1];
    c[N - 1] = 0;
    std::vector<double> d(N, 0);
    d[0] = M[0][N];
    d[N - 1] = M[N - 1][N];

    for (int i = 1; i < N - 1; ++i)
    {
        a[i] = M[i][i - 1];
        b[i] = M[i][i];
        c[i] = M[i][i + 1];
        d[i] = M[i][N];
    }

    // std::cout << a << b << c << d;

    std::vector<double> ksi(N, 0);
    std::vector<double> eta(N, 0);

    ksi[0] = -c[0] / b[0];
    eta[0] = d[0] / b[0];

    for (int i = 1; i < N; i++)
    {
        double denominator = b[i] - a[i] * ksi[i - 1];

        ksi[i] = c[i] / denominator;
        eta[i] = (d[i] - a[i] * eta[i - 1]) / denominator;
    }

    // std::cout << ksi << eta;

    // ksi[N - 1] = 0;

    std::vector<double> x(N, 0);
    x[N - 1] = eta[N - 1];

    for (int i = N - 2; i >= 0; i--)
    {
        x[i] = ksi[i] * x[i + 1] + eta[i];
    }

    std::cout << x;
}

int main()
{

    std::vector<std::vector<double>> M = {
        {2, 1, 0, 0, 4},
        {2, 7, 1, 0, 3},
        {0, 3, 5, 1, 1},
        {0, 0, 1, 4, 3}};

    thomas(M);
    thomas_gpt(M);

    return 0;
}