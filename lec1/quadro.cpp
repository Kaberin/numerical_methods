#include <iostream>
#include <stdio.h>
#include <cmath>
/*
D = b^2-4ac
*/

int main()
{

    double a, b, c;

    std::cout << "Enter coefficients a b c: ";

    std::cin >> a >> b >> c;

    double D = pow(b, 2) - 4 * a * c;

    if (D == 0)
    {
        std::cout << "Root is " << -b / (2 * a);
    }
    else if (D > 0)
    {
        std::cout << "Root 1 is " << (-b + sqrt(D)) / (2 * a) << '\n';
        std::cout << "Root 2 is " << (-b - sqrt(D)) / (2 * a) << '\n';
    }
    else
    {
        std::cout << "Roots are complex!\n";
    }

    return 0;
}