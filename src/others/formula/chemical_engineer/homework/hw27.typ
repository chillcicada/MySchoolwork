#import "../../template.typ": *

#show: define-config

#set par(first-line-indent: (amount: 2em, all: true))
#set math.equation(numbering: "(1)")

= 化学工程基础 - 第二十七次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

一操作中的精馏塔，若保持$F、x_F、q、V'$不变，增大回流比$R$，试分析$L、V、L'、D、x_D、x_W$的变化趋势。

$
  L &= R D \
  V &= L + D = (1 + R) D \
  L' &= L + q F = R D + q F \
  V' &= V + (q - 1) F = (1 + R) D + (q - 1) F = L' - W
$

若保持$F、x_F、q、V'$不变，增大回流比$R$后，由$V' = V + (q - 1) F = (1 + R) D + (q - 1) F$得$V$不变，$D$减小，其中：

$
  V' = D + R D + q F - F = D + L' - F
$

由于$V'$和$F$不变，$D$减小，因而$L'$增大，进一步由$L' = L + q F$ 得$L$也增大。

考虑到平衡线不发生变化，即认为$alpha$不变，则$R$增大后操作线斜率$R slash (R + 1)$增大，而$x_F$和进料方程不变，因而$x_D$增大，而提馏段操作线斜率为$L' slash V'$，其中$V'$不变而$L'$增大，可知$x_W$增大。

综上，$V$不变，$D$减小，$L、L'、x_D、x_W$增大。

== 题 2

常压下用一连续精馏塔分离苯-甲苯双组分混合液。泡点进料，进料中含苯30 %，塔顶馏出液含苯95 %，塔苯残液含甲苯90 %。塔顶冷凝器用分凝器，回流比3.21。苯和甲苯的平均相对挥发度为2.47。每个塔板的气相默夫里效率为60 %，试计算需要的理论板数和适合的进料位置。

由题意得：

$
  R &= 3.21 \
  alpha &= 2.47 \
  x_D &= 0.95 \
  x_F &= 0.3 \
  x_W &= 0.1 \
  E_"mV" &= 0.6
$

从而平衡线为：

$
  y^* = (alpha x) / (1 + (alpha - 1) x) <=> x = y^* / (alpha - (alpha - 1) y^*)
$

由泡点进料可知 $q = 1$，精馏段操作线为：

$
  y_n = R / (R + 1) x_(n + 1) + 1 / (R + 1) x_D = 0.762 x_(n + 1) + 0.226
$

精馏段操作线与进料线的交点为 $(0.3, 0.455)$。

提馏段操作线为：

$
  y_m = 1.773 x_(m + 1) - 0.0773
$

气相默夫里效率有：

$
  E_"mV" = (y_n - y_(n - 1)) / (y^*_n - y_(n - 1)) = 0.6
$

即：

$
  y_n = 0.6 y^*_n + 0.4 y_(n - 1)
$

由于塔顶使用了分馏器，其为理论板，分馏器上有$y_0 = x_D$，从而从上往下计算有：

$
  x_0 = 0.95 / (2.47 - 1.47 times 0.95) = 0.885
$

剩余部分采用从下往上计算的方式，使最终板达到 $x_0$，编写如下脚本辅助计算：

```py
def clac1(x):
    y_prev = 1.773 * x - 0.0773
    y_star = 2.47 * x / (1 + 1.47 * x)
    y = y_star * 0.6 + y_prev * 0.4
    x_next = (y + 0.0773) / 1.773
    return x_next, y

def clac2(x):
    y_prev = 0.762 * x + 0.226
    y_star = 2.47 * x / (1 + 1.47 * x)
    y = y_star * 0.6 + y_prev * 0.4
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
```

输出如下：

```log
[Round1, Stage1] x: 0.139, y: 0.169
[Round2, Stage1] x: 0.178, y: 0.239
[Round3, Stage1] x: 0.216, y: 0.305
[Round4, Stage1] x: 0.249, y: 0.365
[Round5, Stage1] x: 0.278, y: 0.416
[Round6, Stage1] x: 0.303, y: 0.459
[Round7, Stage2] x: 0.350, y: 0.493
[Round8, Stage2] x: 0.412, y: 0.540
[Round9, Stage2] x: 0.486, y: 0.596
[Round10, Stage2] x: 0.568, y: 0.659
[Round11, Stage2] x: 0.651, y: 0.722
[Round12, Stage2] x: 0.729, y: 0.782
[Round13, Stage2] x: 0.798, y: 0.834
[Round14, Stage2] x: 0.856, y: 0.878
[Round15, Stage2] x: 0.901, y: 0.913
[Result] x: 0.901, y: 0.913, round: 15
```

只考虑理论板数，相关的代码如下：

```py
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
```

相关输出如下：

```log
[Round1, Stage1] x: 0.165, y: 0.215
[Round2, Stage1] x: 0.229, y: 0.328
[Round3, Stage1] x: 0.282, y: 0.423
[Round4, Stage1] x: 0.321, y: 0.492
[Round5, Stage2] x: 0.411, y: 0.539
[Round6, Stage2] x: 0.534, y: 0.633
[Round7, Stage2] x: 0.673, y: 0.739
[Round8, Stage2] x: 0.800, y: 0.836
[Round9, Stage2] x: 0.895, y: 0.908
[Result] x: 0.895, y: 0.908, round: 9
```

从对应的输出结果可以看到，需要的理论板数为9块，实际板数为15块，加料位置在第4块理论板，也即第6块实际板。
