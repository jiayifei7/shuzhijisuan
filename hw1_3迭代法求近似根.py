import math
def f(x):
    return math.exp(x) + 10 * x - 2
x_old=0
d=0.5e-3
while True:
    x_new=(2-math.exp(x_old))/10
    if abs(x_new-x_old)<d:
        break
    x_old=x_new
print(f"{x_new:.5f}, {f(x_new):.9f}")


