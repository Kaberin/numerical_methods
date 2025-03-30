#include <iostream>
#include <cmath>
// #include <vector>

namespace my {

    struct log {
        double res;
        int n;
    };

    log sqrt(double a) {
        if (a < 0) {
            throw std::runtime_error{ "\n\nSquare root of negative number is not defined\n\n" };
        }
        double x[50] = { 0 };
        x[0] = 10;
        int n = 0;
        double eps = 0.00001;
        while (abs((x[n + 1] - x[n]) / (1 - (x[n + 1] - x[n]) / (x[n] - x[n - 1]))) > eps) {
            x[n + 1] = (1.0 / 2.0) * (x[n] + a / x[n]);
            n++;
            std::cout << abs((x[n + 1] - x[n]) / (1 - (x[n + 1] - x[n]) / (x[n] - x[n - 1]))) << '\n';
            if (n >= 49) {
                throw std::runtime_error{ "\n\nError calculating square root\n\n" };
            }
        }
        return { x[n], n };
    }
}

int main() {
    try {
        double a;
        std::cout << "Enter number: ";
        std::cin >> a;
        // std::cout << "Square root of " << a << " is " << my::sqrt(a).res << ". Number of iterations " << my::sqrt(a).n << '\n';
        my::sqrt(a);
    }
    catch (std::runtime_error e) {
        std::cout << e.what();
    }

    return 0;
}