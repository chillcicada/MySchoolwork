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
  V' &= V + (q - 1) F = (1 + R) D + (q - 1) F
$

若保持$F、x_F、q、V'$不变，增大回流比$R$后，由$V' = V + (q - 1) F = (1 + R) D + (q - 1) F$得$V$不变，$D$减小，其中：

$
  V' = D + R D + q F - F = D + L' - F
$

由于$V'$和$F$不变，$D$减小，因而$L'$增大，进一步由$L' = L + q F$ 得$L$也增大。

$
  cases(
    F x_F = W x_W + D x_D,
    F = W + D,
  )
$

考虑到平衡线不发生变化，即认为$alpha$不变，则$x_D$减小，$x_W$增大。

== 题 2

常压下用一连续精馏塔分离苯-甲苯双组分混合液。泡点进料，进料中含苯30 %，塔顶馏出液含苯95 %，塔苯残液含甲苯90 %。塔顶冷凝器用分凝器，回流比3.21。苯和甲苯的平均相对挥发度为2.47。每个塔板的气相默夫里效率为60 %，试计算需要的理论板数和适合的进料位置。

由题意得：

$
  R &= 3.21 \
  alpha &= 2.47 \
  x_D &= 0.95 \
  x_F &= 0.3 \
  x_W &= 0.1 \
  E_"mv" &= 0.6
$
