= 2024 传递过程原理大作业

刘宽 2022013189 探微-分21

#pagebreak()

== 问题描述

#table(
  columns: (auto, auto, auto, auto),
  align: horizon,
  table.header(
    [],
    [密度 $"kg"\/upright(m)^3$],
    [热容 $upright(J)\/("kg" dot.c upright(K))$],
    [导热系数 $upright(W)\/(upright(m) dot.c upright(K))$],
  ),

  [陶瓷], [$rho_1 = 2600$], [$C_(p 1) = 1150$], [$k_1=3.0$],
  [保温层], [$rho_2 = 600$], [$C_(p 2) = 200$], [$k_2=0.2$],
)

陶瓷与反应物流的对流换热系数为 $h_1 = 500 upright(W)\/(upright(m)^2 dot.c upright(K))$，保温层与环境气流的对流换热系数为 $h_2 = 10 upright(W)\/(upright(m)^2 dot.c upright(K))$。

起始时，反应物流温度为 $T_0 = 1500 upright(K)$，环境气流温度为 $T_infinity = 298 upright(K)$，反应器温度为 $T_"init" = 300 upright(K)$，反应器内径 $R_1 = 0.05 upright(m)$，保温层内径 $R_2 = 0.075 upright(m)$，反应器外径 $R_3 = 0.125 upright(m)$。

记陶瓷温度为 $T_1$，传热因子为 $alpha_1$；保温层温度为 $T_2$，传热因子为 $alpha_2$。

== 问题分析

传热基本方程：

$
  (upright(D) T) / (upright(D) t) = alpha nabla^2 T + dot(q) / (rho C_p)
$

对于陶瓷和保温层的传热过程，其为一维非稳态导热问题，无内热源，边界处均为第三类边界条件（对流换热）。从而，其传热方程简化为：

$
  (partial T) / (partial t) = alpha nabla^2 T
$

陶瓷和保温层均为圆管状，温度分布只与时间 $T$ 和径向变量 $r$ 有关，从而方程进一步简化为：

$
  (partial T) / (partial t) = alpha partial / (partial r) (1 / r (partial (r T)) / (partial r))
$

在传热过程中，涉及到三处边界条件：

- 陶瓷与反应物流
- 陶瓷与保温层
- 保温层与环境气流

简化模型，将所有边界传热视作拟稳态传热，以由内向外为传热方向，即有：

$
  q_1 =& h_1 (T_0 - T_"1w") &= k_1 lr((partial T_1) / (partial r)|)_(r = R_1) \
  q_2 =& k_1 lr((partial T_1) / (partial r)|)_(r = R_2) &= k_2 lr((partial T_2) / (partial r)|)_(r = R_2) \
  q_3 =& h_2 (T_"2w" - T_infinity) &= k_2 lr((partial T_2) / (partial r)|)_(r = R_3)
$

== 解题思路

将圆管视作一段一段同心环管，以半径均分为 $n$ 段，$Delta r = (R_3 - R_1) \/ n$，则有：

$
  alpha((T_(i+1)^m + T_(i-1)^m - 2 T_i^m) / (Delta r^2) + 1 / r_i (T_(i+1)^m-T_(i-1)^m) / (2 Delta r) - T_i^m / r_i^2) = (T_i^(m+1) - T_i^m) / (Delta t)
$

其中 $i = 1, 2, 3, ..., n - 1$，$m = 0, 1, 2, 3, ...$，$r_i = R_1 + i Delta r$。

定解条件为：

$
  T_i^0 &= T_"init", &i = 1, 2, 3, ..., n - 1 \
  h_1 (T_0 - T_0^m) &= k_1 (T_0^m - T_1^m) / (Delta r), &m = 0, 1, 2, 3, ... \
  k_1 (T_(n \/ 3 -1)^m - T_(n \/ 3)^m) / (Delta r) &= k_2 (T_(n \/ 3)^m - T_(n \/ 3 + 1)^m) / (Delta r), &m = 0, 1, 2, 3, ... \
  h_2 (T_n^m - T_infinity) &= k_2 (T_(n-1)^m - T_n^m) / (Delta r), &m = 0, 1, 2, 3, ...
$

即：

$
  T_i^0 &= T_"init", &i = 1, 2, 3, ..., n - 1 \
  T_0^m &= (h_1 T_0 + k_1 T_1^m \/ Delta r) / (h_1 + k_1 \/ Delta r), &m = 0, 1, 2, 3, ... \
  T_(n \/ 3)^m &= (k_1 T_(n \/ 3 - 1)^m + k_2 T_(n \/ 3 + 1)^m) / (k_1 + k_2), &m = 0, 1, 2, 3, ... \
  T_n^m &= (h_2 T_infinity + k_2 T_(n-1)^m \/ Delta r) / (h_2 + k_2 \/ Delta r), &m = 0, 1, 2, 3, ...
$

对于 $T_0^0$ 和 $T_n^0$，使用初始拟稳态假设求解。
