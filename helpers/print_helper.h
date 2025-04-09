#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    if (v.size() == 0)
    {
        return os;
    }
    for (auto &x : v)
    {

        os << '\t' << x << "\t";
    }
    os << '\n';
    return os;
}
void log_variable(std::string name, double value);
