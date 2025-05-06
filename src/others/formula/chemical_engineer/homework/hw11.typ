#import "../../template.typ": *

#show: define-config

#set par(first-line-indent: (amount: 2em, all: true))
#set math.equation(numbering: "(1)")

= 化学工程基础 - 第十一次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

由题意可知：

$
  phi.alt 48 mm times 3 mm => D_1 &= 48 - 3 times 2 mm = 42 mm = 0.042 "m" \
  phi.alt 25 mm times 2.5 mm => D_2 &= 25 - 2.5 times 2 mm = 20 mm => 0.02 "m" \
  phi.alt 32 mm times 2.5 mm => D_3 &= 32 - 2.5 times 2 mm = 27 mm => 0.027 "m" \
  D'_2 &= 25 mm = 0.025 "m" \
  D'_3 &= 32 mm = 0.032 "m"
$

更换内管前：

内管特征长度 $d_(i, 1) = D_2 = 0.02 "m"$

环隙特征长度 $d_(i, 2) = 4 pi (D_1^2 / 4 - D'_2^2 / 4) \/ (pi (D_1 + D'_2)) = D_1 - D'_2 = 0.017 "m"$

更换内管后：

内管特征长度 $d'_(i, 1) = D_3 = 0.027 "m"$

环隙特征长度 $d'_(i, 2) = D_1 - D'_3 = 0.01 "m"$

因流量保持不变，$Q = A dot u$ 得：

对内管：

$
  A = 1 / 4 pi D^2 => u'_1 = (d_(i, 1) / d'_(i, 1))^2 u_1 = (0.02 / 0.027)^2 u_1 = 0.549 u_1
$

对环隙：

$
  A = 1 / 4 pi (D_i^2 - D_o^2) => u'_2 = (D_1^2 - D'_2^2) / (D_1^2 - D'_3^2) u_2 = (0.42^2 - 0.25^2) / (0.42^2 - 0.32^2) u_2 = 1.538 u_2
$

假设流动过程满足 Dittus-Boelter 关系式（低粘度流体），即：

$
  alpha = 0.023 lambda / d_i ((u d_i rho) / mu)^0.8 ((c_p mu) / lambda)^n
$

忽略温度变化对物性的影响，从而，$alpha prop u^0.8 dot d_i^(-0.2)$。

对内管有：

$
  alpha'_1
  = (u'_1 / u_1)^0.8 dot (d'_(i, 1) / d_(i, 1))^(-0.2) alpha_1
  = (0.549)^0.8 dot (0.027 / 0.02)^(-0.2) alpha_1
  = 0.583 alpha_1 \
  => alpha'_1 / alpha_1 = 0.583 \
$

对环隙有：

$
  alpha'_2
  = (u'_2 / u_2)^0.8 dot (d'_(i, 2) / d_(i, 2))^(-0.2) alpha_2
  = (1.538)^0.8 dot (0.01 / 0.017)^(-0.2) alpha_2
  = 1.569 alpha_2 \
  => alpha'_2 / alpha_2 = 1.569 \
$

综上，如果流动过程满足 Dittus-Boelter 关系式，内管给热系数变为原来的 58.3%，环隙给热系数变为原来的 1.569 倍。

== 题 2

由题意得：

$
  phi.alt 19 mm times 2 mm => D &= 19 - 2 times 2 mm = 15 mm = 0.015 "m" \
  L &= 2 "m" \
  Q &= 0.5 unit("m^3/h") = 0.5 / 3600 unit("m^3/s") = 1.389 times 10^(-4) unit("m^3/s") \
$

从而流速为：

$
  u
  = 4 Q / ( pi D^2)
  = (4 times 1.389 times 10^(-4)) / (pi times 0.015^2) "m/s" = 0.786 "m/s" \
$

水的平均温度为 20 #degC，查询得 20 #degC 时水的粘度约为 $mu = 0.893 mPa dot "s"$，密度为 $rho = 997 unit("kg/m^3")$，热导率为 $lambda = 0.59 "W/(m·K)"$，比热容为 $c_p = 4.18 "kJ/(kg·K)"$，此时流体流动的雷诺数大致为：

$
  "Re" = (rho u D) / mu = (997 times 0.786 times 0.015) / (0.893 times 10^(-3)) = 13163 > 10^4
$

普朗特数为：

$
  "Pr" = (c_p mu) / lambda = (4.18 times 10^3 times 0.893 times 10^(-3)) / 0.59 = 6.33 < 120
$

即此时流体的流动为激烈湍流，$L \/ d_i = 2 \/ 0.015 = 133 > 50$，满足 Dittus-Boelter 关系式，同时水体被加热，则：

$
  alpha
  &= 0.023 lambda / d_i "Re"^0.8 "Pr"^0.4 \
  &= (0.023 times 0.59 times 13163^0.8 times 6.33^0.4) / 0.015 "W/(m"^2"·K)" \
  &= 3737 "W/(m"^2"·K)"
$

流量下降后，$Q' = 0.3 unit("m^3/h")$

流速变为：

$
  u' = 4 Q' / ( pi D^2) = (4 times 0.3 \/ 3600) / (pi times 0.015^2) "m/s" = 0.472 "m/s" \
$

雷诺数变为：

$
  "Re"' = (rho u' D) / mu = (997 times 0.472 times 0.015) / (0.893 times 10^(-3)) = 7897 < 10^4
$

此时不满足 Dittus-Boelter 方程条件，校正系数为：

$
  phi.alt = 1 - (6 times 10^5) / "Re"'^1.8 = 1 - (6 times 10^5) / 7897^1.8 = 0.942 \
$

使用 Dittus-Boelter 方程得到的换热系数为：

$
  alpha'_i
  &= 0.023 lambda / d_i "Re"^0.8 "Pr"^0.4 \
  &= (0.023 times 0.59 times 7897^0.8 times 6.33^0.4) / 0.015 "W/(m"^2"·K)" \
  &= 2483 "W/(m"^2"·K)"
$

实际换热系数为 $alpha' = phi.alt dot alpha'_i = 2399 "W/(m"^2"·K)" < alpha$。

壁面输送的热流量满足 $phi.alt_T = alpha A (T_w - T)$，流体的吸热量满足 $Q_T = c_p rho Q Delta T$。

相比流量降低前，由于 $Delta T$ 不变，令 $phi.alt_T = Q_T$ 可得：

$
  T_w - T prop Q dot alpha^(-1)
$

流量降低前后有：

$
  (Q' alpha'^(-1)) / (Q alpha^(-1)) = 0.3 / 0.5 dot 3737 / 2399 = 0.935 < 1
$

从而可得管壁与流体的温差下降，管壁温度下降。

综上，流量下降后，对流传热系数变为 2399 $"W/(m"^2"·K)"$，同时再使水温仍由15 ℃升至25 ℃时，管壁温度下降。

== 题 3

由题意可得：

$
  phi.alt 45 mm times 2.5 mm => D &= 45 - 2.5 times 2 mm = 40 mm = 0.04 "m" \
  L &= 5 "m" \
  Q &= 3 unit("m^3/h") = 3 / 3600 unit("m^3/s") = 8.333 times 10^(-4) unit("m^3/s") \
  R &= 0.6 "m"
$

由三根钢管并联，则每根钢管的流量为 1/3，从而流体的流速为：

$
  u
  = (4 Q) / (3 pi D^2)
  = (4 times 8.333 times 10^(-4)) / (3 pi times 0.04^2) = 0.221 "m/s" \
$

苯的平均温度为 $t = 1 / 2 (30+70) degC = 50 degC$，查询资料得，苯在 50 #degC 的物性数据如下：

$
  rho &= 860 unit("kg/m^3") \
  c_p &= 1.80 "kJ/(kg·K)" \
  mu &= 0.45 mPa dot "s" \
  lambda &= 0.14 "W/(m·K)"
$

从而，流体的雷诺数为：

$
  "Re" = (rho u D) / mu = (860 times 0.221 times 0.04) / (0.45 times 10^(-3)) = 16894 > 10^4
$

普朗特数为：

$
  "Pr" = (c_p mu) / lambda = (1.80 times 10^3 times 0.45 times 10^(-3)) / 0.14 = 5.786 < 120
$

即此时流体的流动为激烈湍流，$L \/ d_i = 5 \/ 0.04 = 125 > 50$，流体被冷却，使用 Dittus-Boelter 关系式得到的换热系数为：

$
  alpha_i
  &= 0.023 lambda / d_i "Re"^0.8 "Pr"^0.3 \
  &= (0.023 times 0.14 times 16894^0.8 times 5.786^0.3) / 0.04 "W/(m"^2"·K)" \
  &= 329 "W/(m"^2"·K)"
$

螺旋弯管的修正系数为：

$
  phi.alt = 1 + 1.77 d_i / R = 1 + 1.77 0.04 / 0.6 = 1.118
$

从而实际的传热系数为 $alpha = alpha_i dot phi.alt = 368 "W/(m"^2"·K)"$。
