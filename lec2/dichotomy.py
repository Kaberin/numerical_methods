"""
@brief Решение уравнений методом деления отрезка пополам
"""

import numpy as np


def f(x):
    return (x - 1) * (x - 2) ** 2 * (x - 3) ** 3


eps = 0.1
N_max = 50
x = np.zeros(N_max)
x[0] = 2.5
x[1] = 3.5

n = 1
while abs(x[n] - x[n - 1]) > eps:
    x[n + 1] = (x[n] + x[n - 1]) / 2
    if (f(x[n + 1]) * f(x[n - 1])) < 0:
        x[n] = x[n - 1]
    elif f(x[n + 1]) == 0:
        n = n + 1
        break
    n = n + 1


print("Найден корень x = {0:.5f}, число итераций - {1}".format(x[n], n - 1))
