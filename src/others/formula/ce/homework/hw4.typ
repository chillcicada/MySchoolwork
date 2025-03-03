#import "@preview/cuti:0.3.0": show-cn-fakebold
#import "@preview/tablem:0.2.0": three-line-table
#import "@preview/unify:0.7.1": unit as u

#show: show-cn-fakebold
#set page(paper: "a4", margin: 1.27cm)
#set text(lang: "zh", region: "cn")

= 化学工程基础 - 第四次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

由题目已知信息可得：

$
  phi.alt = 68"mm" times 4"mm" => r = 68 / 2 - 4 "mm" = 0.03 "m" \
  Q = 20 "m"^3 \/ "h" = 20 / 3600 "m"^3 \/ "s" = 5.556 times 10^(-3) "m"^3 \/ "s" \
  v = Q / (pi r^2) = (5.56 times 10^(-3) ) / (pi times 0.03^2) "m" \/ "s" = 1.966 "m" \/ "s" \
  p_"蒸发室" = 200 "mmHg" = 200 / 760 "atm" = 101.33 times 10^3 times 200 / 760 "Pa" = 26.67 "kPa" \
$

#figure(image("hw4/q1.jpg", width: 40%), caption: "题 1 情景")

由题意得，贮槽内液面维持稳定，因而其速度视为 0，忽略蒸发室进口到蒸发室上部的距离，即把蒸发室内操作压强视作蒸发室进口压强，从贮槽内液面到蒸发室进口（即上图中红色标记的截面），根据质量形式的 Bernoulli 方程，有：

$
  H_e
  &= Delta z + (p_"蒸发室" - p_"贮槽液面") / (rho g) + (v^2 - 0) / (2 g) + h_f / g \
  &= 15 + ((26.67 - 101.33) times 10^3) / (1200 times 9.8) + 1.966^2 / (2 times 9.8) + 120 / 9.8 "m"\
  &= 25.164 "m"
$

有效功率为：

$
  W_e = rho g Q H_e = 1200 times 9.8 times 5.556 times 10^(-3) times 25.164 "W" = 1646 "W"
$

== 题 2

== 题 3

#figure(image("hw4/q3.jpg", width: 40%), caption: "题 3 情景")

相关变量及其量纲信息如下：

#figure(
  three-line-table[
    | 气泡直径D | 小孔直径d | 液体密度ρ | 表面张力σ | 液体粘度μ | 重力加速度g |
    | --------- | --------- | --------- | --------- | --------- | ----------- |
    | m | m | kg/$"m"^3$ | N/m (kg/$"s"^2$) | Pa·s (kg/m/s) | m/$"s"^2$ |
  ],
  caption: "相关变量及其量纲信息",
)

其中有 6 个物理量，根据 $pi$ 定理，其中有 3 个基本因次（M，L，t），因而需要构造 $6-3=3$ 个无量纲组。

设 $D = phi(d, rho, sigma, mu, g)$，采取幂函数的形式表示为：

$
  D = K rho^a sigma^b mu^c g^e d^f
$

式中 K 为无因次常数，代入因次分析的基本方程，得到：

$
  L = (M L^(-3))^a (M t^(-2))^b (M L^(-1) t^(-1))^c (L t^(-2))^e L^f = M^(a+b+c) L^(3a-c+e+f) t^(-2b-c-2d)
$

整理得到：

$
  cases(
    a + b + c = 0,
    -3a - c + e + f = 1,
    -2b - c - 2e = 0
  ) ==> cases(
    b = -a-c,
    e = a+c/2,
    f = 1+2a+c/2
  )
$

从而 $D = K rho^a sigma^(-a-c) mu^c g^(a+c / 2) d^(1+2a+c / 2)$，调整得到：

$
  D / d= K ((rho g d^2) / sigma)^a ((mu g d) / sigma^2)^(c / 2) = phi((rho g d^2) / sigma, (mu g d) / sigma^2)
$

即 $D$ 与 $d$、$rho g d^2 \/ sigma$ 和 $mu g d \/ sigma^2$ 有关，构造无量纲组为：

$
  cases(
    pi_1 = D / d,
    pi_2 = (rho g d^2) / sigma,
    pi_3 = (mu g d) / sigma^2
  )
$

有：

$
  D = d dot phi((rho g d^2) / sigma, (mu g d) / sigma^2)
$

式中 $phi$ 函数由实验确定。

== 题 4
