import matplotlib.pyplot as plt


path = "out.txt"

with open(path, "r") as file:
    lines = file.readlines()


x = []
f_x = []
x_interpolated = []
f_x_interpolated = []


for line in lines:
    parts = line.split(":")
    key = parts[0].strip()
    values = list(map(float, parts[1].split()))

    if key == "x":
        x = values
    elif key == "f(x)":
        f_x = values
    elif key == "x_interpolated":
        x_interpolated = values
    elif key == "f(x_interpolated)":
        f_x_interpolated = values

plt.xlim(0, 10)
plt.ylim(0, 6)
plt.plot(x, f_x, linestyle="none", marker="s", markersize=4, color="b")
plt.plot(x_interpolated, f_x_interpolated)
plt.show()
