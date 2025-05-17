import cmath

def f(x):
    return x**4 + 2*x**3 - x - 1

def df(x):
    return 4*x**3 + 6*x**2 - 1

def newton_method(initial_guess, tolerance=1e-5, max_iterations=1000):
    x = initial_guess
    for i in range(max_iterations):
        fx = f(x)
        dfx = df(x)
        if dfx == 0:
            return None
        x_new = x - fx / dfx
        if abs(x_new - x) < tolerance:
            return x_new
        x = x_new
    return None

real_part, imag_part = map(float, input().split())
initial_guess = complex(real_part, imag_part)

root = newton_method(initial_guess)

if root is not None:
    print(f"{root.real:.8f} {root.imag:.8f}i")
else:
    print("error")
