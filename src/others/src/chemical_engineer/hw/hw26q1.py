(x_D, x_F, alpha, R) = (0.95, 0.3, 2.47, 3.21)


def clac(x):
    y = alpha * x / (1 + (alpha - 1) * x)
    x_next = ((R + 1) * y - x_D) / R
    return x_next, y


if __name__ == '__main__':
    x, round = x_F, 0
    while True:
        x, y = clac(x)
        round += 1
        print(f'[Round{round}] x: {x:.3f}, y: {y:.3f}')
        if x > x_D:
            break
    print(f'[Result] x: {x:.3f}, y: {y:.3f}, round: {round}')
