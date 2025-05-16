from numpy import exp, log

ln = log

alpha = 2.47
x_F = 0.3
x_W = 0.15

z = 1 / (alpha - 1) * (ln(x_F / x_W) + alpha * ln((1 - x_W) / (1 - x_F)))

F = 100

W = F / exp(z)
print(f'W = {W:.2f} kmol')
