#include <iostream>
#include <functional>
#include <cmath>
double f(double x)
{
    return sin(x);
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

int main()
{
    const double pi = 3.1415926;
    double res = minimize_gr(0, 2 * pi, f);

    std::cout << "Function min at " << res << '\n';
    return 0;
}