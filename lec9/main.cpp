#include <iostream>
#include <functional>
#include <cmath>

double f(double x)
{
    return (x - 6) * (x - 5) + x * x * x + 4 * x * x * x * x + x - 8;
}
/// @brief Поиск минимума методом золотого сечения. Не работает на симметричном отрезке (потом пофикшу)
/// @param a Левая граница отрезка
/// @param b Правая граница отрезка
/// @param f Функция
/// @return Минимум функции на отрезке
double minimize_gr(double a, double b, std::function<double(double)> f)
{
    double ksi = (3 - sqrt(5)) / 2;

    double length = fabs(b - a);

    double x0 = a + length * ksi;
    double x1 = a + (1 - ksi) * length;
    double f0 = f(x0);
    double f1 = f(x1);
    double h = 0.0001;
    double min = 0;

    while (fabs(x1 - x0) >= h)
    {
        if (f1 < f0)
        {
            min = x1;
            a = x0;
            x0 = x1;
            length = fabs(b - a);
            x1 = a + length * (1 - ksi);
            f0 = f1;
            f1 = f(x1);
        }
        else if (f0 < f1)
        {
            min = x0;
            b = x1;
            x1 = x0;
            length = fabs(b - a);
            x0 = a + ksi * length;
            f1 = f0;
            f0 = f(x0);
        }
    }

    return min;
}

double differ_first(std::function<double(double)> f, double x)
{
    double h = 0.0001;
    return (f(x + h) - f(x)) / h;
}
double differ_second(std::function<double(double)> f, double x)
{
    double h = 0.0001;
    return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
}
/// @brief Минимум методом ньютона. Вроде работает
/// @param f
/// @param eps
/// @return
double newton_min(std::function<double(double)> f, double eps)
{
    double x[50];
    x[0] = 10000;
    int n = 0;
    for (n = 0; n < 49; n++)
    {
        std::cout << differ_first(f, x[n]) / differ_second(f, x[n]) << '\n';
        x[n + 1] = x[n] - differ_first(f, x[n]) / differ_second(f, x[n]);
        if (n > 2)
        {
            double cond = fabs((x[n] - x[n - 1]) / (1 - (x[n] - x[n - 1]) / (x[n - 1] - x[n - 2])));
            if (cond <= eps)
            {
                for (int i = 0; i <= n; i++)
                {
                    std::cout << x[i] << '\t';
                }
                return x[n + 1];
            }
        }
    }
    for (int i = 0; i <= n; i++)
    {
        std::cout << x[i] << '\t';
    }
    std::cout << "Не достигнута требуемая точность. *dies from cringe*";
    return x[n];
}
int main()
{
    const double pi = 3.1415926;
    double res = minimize_gr(-3, 2 * pi, f);
    std::cout << "Function min at " << res << '\n';
    res = newton_min(f, 1e-9);
    std::cout << "Function min at " << res << '\n';
    // std::cout << differ_first(f, 1) << '\n';
    // std::cout << differ_second(f, 1) << '\n';

    return 0;
}