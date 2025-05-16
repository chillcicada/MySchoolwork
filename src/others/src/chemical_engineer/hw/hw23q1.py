from scipy.optimize import fsolve

# p = 101.33
p = 200


def equation(t):
    return (
        0.4 * 10 ** (6.031 - 1206.35 / (t + 220.24))
        + 0.6 * 10 ** (6.078 - 1343.94 / (t + 219.58))
        - p
    )


t = fsolve(equation, 100)[0]
print(f'Temperature: {t:.4f} °C')

p_A0 = 10 ** (6.031 - 1206.35 / (t + 220.24))
p_B0 = 10 ** (6.078 - 1343.94 / (t + 219.58))

print(f'Partial pressure of A: {p_A0:.4f} kPa')
print(f'Partial pressure of B: {p_B0:.4f} kPa')

y_A = p_A0 / p * 0.4
y_B = p_B0 / p * 0.6

alpha = y_A / 0.4 / y_B * 0.6

print(f'Y_A: {y_A:.4f}')
print(f'Y_B: {y_B:.4f}')
print(f'Alpha: {alpha:.4f}')
