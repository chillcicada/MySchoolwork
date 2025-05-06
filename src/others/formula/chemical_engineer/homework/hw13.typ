#import "../../template.typ": *
#import "@preview/tablem:0.2.0": tablem

#show: define-config

#set par(first-line-indent: (amount: 2em, all: true))
#set math.equation(numbering: "(1)")

= 化学工程基础 - 第十三次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

对于一个换热器，如果其理论需要的换热面积小于等于其实际能提供的换热面积，那么就可以认为该换热器是能够满足需求的。

由题意可知，相关数据为：

$
  phi.alt 19 mm times 2 mm => d_i &= 15mm = 0.015 "m" \
  d_o &= 0.019 "m" \
  b &= 0.004 "m" \
  L &= 3 "m" \
  N &= 324 \
  d_t &= 25.4 mm = 0.0254 "m" \
  d_T &= 230 mm = 0.23 "m" \
  D &= 0.6 "m"
$

对于题目描述的换热器，其示意图如下：

#figure(
  image("hw13/q1.jpg", width: 10cm),
  caption: "换热器示意图",
)

其中管程为双程，即管程一来一回，实际输入的管路只有一半，另一半为输出管路。

现有的传热面积为：

$
  A
  = pi d_o N L
  = pi times 0.019 times 324 times 3 "m"^2
  = 58.019 "m"^2
$

流体性质如下：

#figure(
  tablem[
    | 流体 | $c_p, "kJ/(kg" dot "K)"$ | $mu, Pa dot "s"$ | $(mu\/u_w)^0.14$ | $lambda, "W/(m" dot "K)"$ |
    | ---- | -- | -- | ----- | ---- |
    | 反应物 | 1.986 | 0.0029 | 0 | 0.136 |
    | 导热油 | 2.2 | 0.0052 | 0.95 | 0.119 |
  ],
)

对体系有：

$
  "导热油"：150 #degC &-> 110#degC \
  "反应物"：25 #degC &-> 60 #degC
$

对于严格逆流，对数平均温差为：

$
  Delta t_(m, "逆流")
  = ((150 - 60) - (110 - 25)) / ln((150 - 60) \/ (110 - 25))
  = 87.476 #degC
$

代入平均温差的校正因子 $phi = 0.9$ 得：

$
  Delta t_m = phi Delta t_(m, "逆流") = 0.9 times 81.852 = 78.729 #degC
$

对于管内，其质量流速为：

$
  m_(h, "total") &= 38 "kg/s"
$

雷诺数：

$
  "Re"_h
  &= (rho_h u_h d_i) / mu_h = (4 rho_h Q_h d_i) / (pi d_i^2 mu_h) = (4 m_(h, "total")) / (N \/ 2 pi d_i mu_h) \
  &= (4 times 38) / (324 \/ 2 times pi times 0.015 times 0.0029) \
  &= 6866
$

普朗特数为：

$
  "Pr"_h
  = (C_(p, h) mu_h) / lambda_h
  = (1.986 times 10^3 times 0.0029) / 0.136
  = 42.35 < 120
$

有 $2300 < "Re"_h < 10000$，此时为过渡流，管径比 $L\/d_i = 3\/0.015 = 200 > 50$，反应物被加热，Dittus-Boelter 关系式得到的对流传热系数为：

$
  alpha_i
  = 0.023 lambda_h / d_i "Re"_h^0.8 "Pr"_h^0.4
  = 0.023 times 0.136 / 0.015 times 6866^0.8 times 42.35^0.4 "W/(m"^2 dot "K)"
  = 1095.66 "W/(m"^2 dot "K)"
$

由于此时为过渡流，修正因子为：

$
  phi.alt_i
  = 1 - (6 times 10^5) / "Re"^1.8
  = 1 - (6 times 10^5) / 6866^1.8
  = 0.9255
$

即实际的对流传热系数为 $alpha'_i = phi.alt_i alpha_i = 0.9255 times 1095.66 = 1014 "W/(m"^2 dot "K)"$

对于管外，其质量流速为：

$
  m_c = 30 "kg/s"
$

不考虑挡板，其当量直径为：

$
  d_e
  = 4 times (d_t^2 - pi d_o^2\/4) / (pi d_o)
  = 4 times (0.0254^2 - pi times (0.019)^2 \/
  4) / (pi times 0.019) "m"
  = 0.02423 "m"
$

考虑挡板时壳程流体错流流过列管的最大截面，则壳程横流面积为：

$
  A_c
  = D times d_T times (d_t - d_o) / d_t
  = 0.6 times 0.23 times (0.0254 - 0.019) / 0.0254 "m"^2 = 0.0348 "m"^2
$

雷诺数为：

$
  "Re"_c
  = (m_c times d_e) / (A_c mu_c)
  = (30 times 0.02423) / (0.0348 times 0.0052)
  = 4033 < 1 times 10^5
$

普朗特数为：

$
  "Pr"_c
  = (C_(p, c) mu_c) / lambda_c
  = (2.2 times 10^3 times 0.0052) / 0.119
  = 96.134 < 120
$

对流传热系数为：

$
  alpha_o
  &= 0.2 times lambda_c / d_o "Re"_c^0.6 "Pr"_c^(1\/3) times (mu_c / mu_w)^0.14 \
  &= 0.2 times 0.119 / 0.019 times 4033^0.6 times 96.134^(1\/3) times 0.95 "W/(m"^2 dot "K)" \
  &= 794.114 "W/(m"^2 dot "K)"
$

忽略管壁热阻、污垢热阻和热损失，总传热系数满足：

$
  1 / K
  &= 1 / alpha_o + 1 / alpha_i d_o / d_i
  &= 1 / 794.114 + 1 / 1095.66 times 0.019 / 0.015
  &= 2.415 times 10^(-3) "(m"^2 dot "K)/W"
$

即总传热系数 $K = 1 \/ (2.415 times 10^(-3)) "W/(m"^2 dot "K)" = 414 "W/(m"^2 dot "K)"$。

传热速率为：

$
  phi.alt = K A' Delta t_m
$

令

$
  phi.alt = w_h C_(p, h) (t_o - t_i)
$

得：

$
  A'
  &= (w_h C_(p, h) (t_o - t_i)) / (K Delta t_m) \
  &= (38 times 1.986 times 10^3 times (60 - 25)) / (414 times 73.667) "m"^2 \
  &= 81.04 "m"^2 > 58.019 "m"^2 = A
$

即实际需要的换热面积 $A' = 81.04 "m"^2$，大于现有的传热面积 $A = 58.019 "m"^2$，因此该换热器不能满足需求。

== 题 2

=== (1) 总传热系数的计算

由题意可知，相关数据为：

$
  phi.alt 25 mm times 2.5 mm => d_i &= 20mm = 0.02 "m" \
  d_o &= 0.025 "m" \
  b &= 0.0025 "m" \
  L &= 3.0 "m" \
  N &= 40 \
  rho &= 900 "kg/m"^3 \
  mu &= 0.47 times 10^(-3) Pa dot "s" \
  C_p &= 1.80 times 10^3 "J/(kg" dot "K)" \
  lambda &= 0.14 "W/(m" dot "K)" \
  lambda_b &= 45 "W/(m" dot "K)" \
  R_i &= 8.33 times 10^(-4) "(m"^2 dot "K)/W"
$

体系流量为：

$
  w_h = 1.7 times 10^4 "kg/h" = (1.7 times 10^4 / 3600) "kg/s" = 4.722 "kg/s" \
  Q_"total" = w_h / rho = 4.722 / 900 "m"^3"/s" = 5.247 times 10^(-3) "m"^3"/s" \
  Q = Q_"total" / N = (5.247 times 10^(-3)) / 40 "m"^3"/s" = 1.312 times 10^(-4) "m"^3"/s"
$

从而得到流速为：

$
  u
  = 4 Q / (pi d_i^2)
  = 4 times (1.312 times 10^(-4)) / (pi times (0.02)^2) "m/s"
  = 0.4175 "m/s"
$

雷诺数为：

$
  "Re"
  = (rho u d_i) / mu
  = (900 times 0.4175 times 0.02) / (0.47 times 10^(-3))
  = 15991 > 10^4
$

普朗特数为：

$
  "Pr"
  = (C_p mu) / lambda
  = (1.80 times 10^3 times 0.47 times 10^(-3)) / (0.14)
  = 6.043 < 120
$

同时 $L \/ d_i = 3 \/ 0.02 = 150 > 50$，可知此时基本符合 Dittus-Boelter 关系式，管道中苯被加热，因而管内对流传热系数为：

$
  alpha_i
  &= 0.023 lambda / d_i "Re"^0.8 "Pr"^0.4
  &= 0.023 times 0.14 / 0.02 times (15991)^0.8 times (6.043)^0.4 "W/(m"^2 dot "K)"
  &= 762.83 "W/(m"^2 dot "K)"
$

管外侧对流传热系数：

$
  alpha_o = 10^4 "W/(m"^2 dot "K)"
$

忽略管外侧污垢热阻及热损失，对总传热系数有：

$
  1 / K
  &= 1 / alpha_o + (b d_o) / (lambda_b d_m) + 1 / alpha_i d_o / d_i + R_i d_o / d_i \
  &= 1 / alpha_o + d_o / (2 lambda_b) ln(d_o / d_i) + 1 / alpha_i d_o / d_i + R_i d_o / d_i \
  &= 1 / 10^4 + 0.025 / (2 times 45) ln(0.025 / 0.02) + 1 / 762.83 times 0.025 / 0.02 + 8.33 times 10^(-4) times 0.025 / 0.02 "(m"^2 dot "K)/W" \
  &= 2.842 times 10^(-3) "(m"^2 dot "K)/W"
$

即总传热系数 $K = 1 \/ (2.842 times 10^(-3)) "W/(m"^2 dot "K)" = 351.881 "W/(m"^2 dot "K)"$。

=== (2) 实际操作时苯的出口温度

对于单程列管式换热器，其大致结构示意图为：

#figure(
  image("hw13/q2.jpg", width: 5cm),
  caption: "单程列管式换热器示意图（逆流）",
)

以外管径为参照，总的换热面积为：

$
  A_"total"
  = N pi d_o L
  = 40 times pi times 0.025 times 3 "m"^2
  = 9.425 "m"^2
$

设苯的实际出口温度为 $t_o$，对体系有：

$
  苯：30 #degC &-> t_o #degC \
  "水蒸汽冷凝发生相变，温度不变"：120 #degC &-> 120 #degC
$

考察管层流体和壳层流体严格逆流的情况，使用对数平均温差得到：

$
  Delta t_m
  = ((T_0 - t_i) - (T_0 - t_o)) / ln((T_0 - t_i) \/ (T_0 - t_o))
  = (t_o - t_i) / ln((T_0 - t_i) \/ (T_0 - t_o))
$

传热速率为：

$
  phi.alt
  = K A_"total" Delta t_m
  = K A_"total" (t_o - t_i) / ln((T_0 - t_i) \/ (T_0 - t_o))
$

令：

$
  phi.alt = w_h C_p (t_o - t_i)
$

解得：

$
  ln((T_0 - t_i) / (T_0 - t_o))
  = (K A_"total") / (w_c C_p)
  = (351.881 times 9.425) / (4.722 times 1.80 times 10^3)
  = 0.3902 \
  t_o
  = 120 - (120 - 30) e^(-0.3902) #degC
  = 59.077 #degC
$

即实际操作时苯的出口温度为 $59.077 #degC$。
