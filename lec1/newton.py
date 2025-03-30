from sympy import symbols, zeros, diff


a = symbols("a")
f = pow(2.71, a) - 2
eps = 0.001
k1 = 0.1
N_max = 5000
x = zeros(N_max)
x[0] = -4
k = 0

for n in range(N_max):
    x[n + 1] = (x[n] - f.subs(a, x[n]) / diff(f, a).subs(a, x[n])).evalf()

    # psi_0 = f.subs(a, x[n]) ** 2
    # psi_1 = f.subs(a, x[n + 1]) ** 2
    # tau_n = (psi_0 + k1 * psi_1) / (psi_0 + psi_1)
    # x[n + 1] = (x[n] - tau_n * f.subs(a, x[n]) / diff(f, a).subs(a, x[n])).evalf()

    if (
        n >= 1
        and abs((x[n + 1] - x[n]) / (1 - (x[n + 1] - x[n]) / (x[n] - x[n - 1]))) < eps
    ):
        k = n + 1
        break
p = (1 / (1 - (x[k] - x[k - 1]) / (x[k - 1] - x[k - 2]))).evalf()
print(
    "Найден корень x = {0:.2f}. Число итераций {1}, кратность корня {2}".format(
        x[k], k, p
    )
)
