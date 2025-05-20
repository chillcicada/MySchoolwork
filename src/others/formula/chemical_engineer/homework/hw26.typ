#import "../../template.typ": *

#show: define-config

#set par(first-line-indent: (amount: 2em, all: true))
#set math.equation(numbering: "(1)")

= 化学工程基础 - 第二十六次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

设计一个连续精馏塔，在常压下分离苯-甲苯双组分混合液。采用饱和蒸汽从最下一块塔板底部进料，进料中含苯30%（摩尔分数，以下同），塔顶馏出液含苯95%。塔顶冷凝器用全凝器，饱和溶液回流，回流比3.21。已知苯和甲苯的平均相对挥发度为2.47。精馏塔内需要多少块理论板？

由题意得：

$
  x_F &= 0.3 \
  x_D &= 0.95 \
  alpha &= 2.47 \
  R &= 3.21
$

平衡关系式为：

$
  y_n = (alpha x_n) / (1 + (alpha - 1) x_n)
$

精馏段操作线方程为：

$
  y_n = R / (R + 1) x_(n + 1) + 1 / (R + 1) x_D
$

从而：

$
  x_(n + 1) = ((R + 1) y_n - x_D) / R
$

进料时为饱和蒸汽，因而 $q = 1$ 爬塔起点即 $x = x_F$，从下往上计算，编写如下脚本辅助：

```py
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
```

运行输入如下结果：

```log
[Round1] x: 0.378, y: 0.514
[Round2] x: 0.492, y: 0.601
[Round3] x: 0.629, y: 0.705
[Round4] x: 0.763, y: 0.807
[Round5] x: 0.869, y: 0.888
[Round6] x: 0.940, y: 0.942
[Round7] x: 0.983, y: 0.975
[Result] x: 0.983, y: 0.975, round: 7
```

塔顶采用全冷凝器，因而无需额外减去一轮，即精馏塔内需要7块理论塔板。

== 题 2

用一常压连续精馏塔分离含苯0.4的苯-甲苯溶液。料液流量为15000 kg/h，进料温度为25 ℃，回流比为3.5，得馏出液与釜液组成分别为0.97和0.02。已知再沸器加热蒸汽压为137 kPa（表压）。塔顶回流液为饱和液体，塔的热损失可以不计。试求：（1）再沸器的加热蒸汽消耗量；（2）冷凝器的热负荷及冷却水用量。

已知：苯和甲苯的定压比热容按137.9 $"J/mol·K"$，汽化热按34.92 J/mol，含苯0.4的苯-甲苯溶液在常压下的泡点温度约为94 ℃。

（1）苯的相对分子质量为78，甲苯的相对分子质量为92，题目提供的汽化热疑似有点太小了，这里正确的单位应该是 "kJ/mol"。由题意得：

$
  x_F &= (0.4 slash 78) / (0.4 slash 78 + 0.6 slash 92) = 0.440 \
  x_D &= (0.97 slash 78) / (0.97 slash 78 + 0.03 slash 92) = 0.974 \
  x_W &= (0.02 slash 78) / (0.02 slash 78 + 0.98 slash 92) = 0.0235 \
  overline(M_r) &= 86.4 \
  F &= 15000 "kg/h" = 173.61 "kmol/h" \
  R &= 3.5 \
  gamma &= 34.92 "kJ/mol" \
  Delta p &= 137 kPa \
  p &= p_0 + Delta p = 238 kPa
$

从而：

$
  cases(
    F = W + D,
    F x_F = W x_W + D x_D,
  ) &=> cases(
    W = 97.536 "kmol/h",
    D = 76.074 "kmol/h",
  ) \
  L &= R D = 266.26 "kmol/h" \
  V &= L + D = 342.33 "kmol/h"
$

进料温度为25 ℃，泡点温度为94 ℃，可得：

$
  q = (137.9 times (94 - 25) + 34.92 times 10^3) / (34.92 times 10^3) = 1.272
$

提馏段流量为：

$
  L' &= L + q F = 266.26 + 1.272 times 173.61 "kmol/h" = 487.091 "kmol/h" \
  V' &= V + (q - 1) F = 342.33 + (1.272 - 1) times 173.61 "kmol/h" = 389.555 "kmol/h"
$

热损失 $Q_L$ 不计，再沸器热负荷：

$
  Q_B = V' gamma = 389.555 times 34.92 times 10^3 "kJ/h" = 1.360 times 10^7 "kJ/h"
$

238kPa 下蒸汽潜热取 $2185 "kJ/kg"$，蒸汽消耗量为：

$
  W_h = Q_B / gamma_h = (1.360 times 10^7) / 2185 "kg/h" = 6224 "kg/h"
$

（2）冷凝器热负荷：

$
  Q_C = V gamma = 342.33 times 34.92 times 10^3 "kJ/h" = 1.195 times 10^7 "kJ/h"
$

水的比热容取 $C_(p, c) = 4.18 "kJ/kg·K"$，假设冷却水的温升为 $Delta t = 10 degC$，冷却水用量为：

$
  W_C = Q_C / (C_(p, c) Delta t) = (1.195 times 10^7) / (4.18 times 10) "kg/h" = 2.86 times 10^6 "kg/h"
$
