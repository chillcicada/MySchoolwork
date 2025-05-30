def clac1(x):
    y = 2.47 * x / (1 + 1.47 * x)
    x_next = (y + 0.0773) / 1.773
    return x_next, y


def clac2(x):
    y = 2.47 * x / (1 + 1.47 * x)
    x_next = (y - 0.226) / 0.762
    return x_next, y


if __name__ == '__main__':
    x, y, round = 0.1, 0.1, 0
    while True:
        if y < 0.455:
            x, y = clac1(x)
            round += 1
            print(f'[Round{round}, Stage1] x: {x:.3f}, y: {y:.3f}')
        else:
            x, y = clac2(x)
            round += 1
            print(f'[Round{round}, Stage2] x: {x:.3f}, y: {y:.3f}')
        if x > 0.885:
            break
    print(f'[Result] x: {x:.3f}, y: {y:.3f}, round: {round}')
