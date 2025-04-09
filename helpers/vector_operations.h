#pragma once
#include <vector>

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
std::vector<double> operator*(std::vector<double> v, const std::vector<double> &v1)
{
    for (int i = 0; i < v.size(); i++)
    {
        v[i] *= v1[i];
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