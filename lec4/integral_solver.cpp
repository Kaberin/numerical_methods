/**
 * @file integral_solver.cpp
 * @author Vyacheslav
 * @brief Программа находящая интегралы с помощью метода трапеций. Для повышения точности используется итеративный метод ричардсона.
 * Считаются ошибки, эффективные порядки точности. Думал добавить нахождение несобственных интегралов, но решил реализовать в отдельной программе
 * чтобы не захламлять файл + это не входило в изначальную задумку, пришлось бы переписывать кусок, все таки пишу в учебных целях.
 * @version 0.1
 * @date 2025-03-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
#include <windows.h>
#include <string>
// #define DEBUG

#ifdef DEBUG
#include "print_helper.h"
#endif

/**
 * @brief Логарифм
 *
 * @param a Не основания
 * @param b Основние
 * @return double
 */
double log_base(double a, double b)
{
    return log(a) / log(b);
}

/**
 * @brief Класс задающий дискретное количество точек на отрезке. Не массив, вычисляет нужную точку только при обращении.
 *
 */
class Linspace
{
    double st{0};
    double en{0};
    double h{1};
    int n{0};

public:
    Linspace(double start, double end, int N) : st{start}, en{end}, n{N}
    {
        if (st != en && n != 0 && (end > start))
        {
            h = fabs(end - start) / n;
        }
        else
        {
            throw std::runtime_error{"Linspace initialization fail :(\n"};
        }
    }
    /**
     * @brief Реинициализация linspace с нужным отрезком и количеством точек
     *
     * @param start Начало
     * @param end Конец
     * @param N Количество отрезков
     */
    void reinitialize(double start, double end, int N)
    {
        if ((start == st) && (end == en) && (N == n) && N != 0)
        {
            return;
        }
        if (end <= start || N <= 0)
        {
            throw std::runtime_error{"Linspace reinitialization fail :(\n"};
        }
        st = start;
        en = end;
        n = N;
        h = (end - start) / n;
    }

    double operator[](int point)
    {
        if (point < 0 || point > n)
        {
            throw std::out_of_range{"Linspace index out of range"};
        }
        double res = st + h * point;
        if (res <= en)
        {
            return res;
        }
        return en;
    }
    int size() const
    {
        return n;
    }
    double step() const
    {
        return h;
    }
};

/**
 * @brief Решатель интегралов. Использует метод трапеции. Уточение результатов посредством применения формулы Рунге-Ромберга.
 *
 */
class IntegralSolver
{

    std::function<double(double)> f{};
    static constexpr int p = 2;
    static constexpr int q = 2;
    int r{0};
    int s{0};
    std::vector<std::vector<double>> U{};
    std::vector<std::vector<double>> R{};
    std::vector<std::vector<double>> P_eff{};
    Linspace li{0, 1, 10};
    double start{0};
    double end{0};
    int n{1};
    double permissible_error = 0.1;
    double real_error{100};
    void print_arrays()
    {
#ifdef DEBUG
        std::cout << "Таблица приближенных значений интеграла:\n";
        for (auto x : U)
        {
            std::cout << x;
        }
        std::cout << '\n';
        std::cout << "Таблица оценок ошибок:\n";
        for (auto x : R)
        {
            std::cout << x;
        }
        std::cout << '\n';
        std::cout << "Таблица эффективных порядков точности:\n";
        for (auto x : P_eff)
        {
            std::cout << x;
        }
        std::cout << "\n";
#endif
    }

    void log_variable(std::string name, double value)
    {
        std::cout << "VARIABLE " << name << " = " << value << "\n\n";
    }

    double x(double a, double xi, double c, double m)
    {
        // log_variable("a", a);
        // log_variable("xi", xi);
        return a + c * xi / pow(1 - xi, m);
    }

    double dxdxi(double xi, double c, double m)
    {
        return c * ((pow(1 - xi, m) + xi * m * pow(1 - xi, m - 1)) / pow(1 - xi, 2 * m));
    }

    double trapezoid_solver(int N)
    {

        li.reinitialize(start, end, N);

#ifdef DEBUG1
        std::cout << "Linspace\n";
        for (int i = 1; i <= li.size(); i++)
        {
            std::cout << li[i] << '\t';
        }
        std::cout << '\n';
#endif
        double result = 0;
        for (int i = 1; i <= li.size(); i++)
        {
            result += ((f(li[i]) + f(li[i - 1])) / 2) * li.step();
        }
        return result;
    }

public:
    /**
     * @brief Решатель интегралов с уточнением по формуле Рунге-Ромберга
     *
     * @param function Функция с сигнатурой double(double)
     * @param r_ Множитель с которым будет сгущаться сетка
     * @param s_ Порядок точности вычислений
     * @param N Количество интервалов
     * @param permissible_error Допустимая относительная погрешность
     */
    IntegralSolver(std::function<double(double)> function, int r_, int s_, int N = 1, double err = 0.1) : r{r_}, s{s_}, f{function}, U(s), R(s), n{N}, permissible_error{err}, P_eff(s)
    {

        for (int i = 0; i < s; i++)
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
    /**
     * @brief
     *
     * @param a Левая граница интегрирования
     * @param b Правая граница интегрирования
     * @return double Вычисленное значение интеграла
     */

    double error() const
    {
        return real_error;
    }

    double eitken()
    {
        double Un = trapezoid_solver(n);
        double Urn = trapezoid_solver(r * n);
        double Ur2n = trapezoid_solver(r * r * n);

        double result = Ur2n + (Ur2n - Urn) / ((Urn - Un) / (Ur2n - Urn) - 1);
        return result;
    }

    double avgs(double a, int N)
    {
        double integral = 0;
        for (int n = 1; n <= N; n++)
        {
            double xi_n = (n - 0.5) / (double)N;
            // log_variable("xi_n", xi_n);
            double delta = 1 / (double)N;
            // log_variable("delta", delta);
            double h_n = x(a, xi_n, 1, 1);
            // log_variable("h_n", h_n);
            integral += f(h_n) * dxdxi(xi_n, 1, 1) * delta;
        }
        return integral;
    }

    // void richardson()
    // {
    //     for (int i = 0; i < s; i++)
    //     {
    //         U[i][0] = avgs(a);
    //     }
    // }

    double run(double a, double b)
    {
        double result = 0;
        start = a;
        end = b;
        li.reinitialize(start, end, n + 1);
        for (int i = 0; i < s; i++)
        {
            U[i][0] = trapezoid_solver(pow(r, i) * n);
        }
        // i -> s
        // j -> l
        for (int i = 1; i < s; i++)
        {
            for (int j = 0; j < i; j++)
            {
                double denominator = (pow(r, p + j * q) - 1);
                if (denominator == 0)
                {
                    throw std::runtime_error{"Division by zero. run()"};
                }
                R[i][j] = (U[i][j] - U[i - 1][j]) / denominator;
                U[i][j + 1] = U[i][j] + R[i][j];
            }
        }

        for (int i = 2; i < s; i++)
        {
            for (int j = 0; j < i - 1; j++)
            {
                P_eff[i][j] = log(fabs(R[i - 1][j] / R[i][j])) / log(r);
            }
        }

#ifdef DEBUG
        print_arrays();

#endif

        return U[s - 1][s - 1];
    }
};

double f(double x)
{
    return x * x * x * sin(x * x * x);
}

double f1(double x)
{
    return exp(-x);
}

int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    IntegralSolver is(f1, 2, 10, 1, 1);
    double res = is.avgs(4, 64);

    std::cout << "Вычисленное знаение несобственного интеграла: " << res << '\n';

    return 0;
}