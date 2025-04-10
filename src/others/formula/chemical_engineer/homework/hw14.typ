#import "../../template.typ": *

#show: defineConfig

#set par(first-line-indent: (amount: 2em, all: true))
#set math.equation(numbering: "(1)")

= 化学工程基础 - 第十四次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

使用一台列管式换热器将2t/h的工艺水从30℃加热到90℃。加热介质为120℃饱和水蒸汽。列管式换热器基本尺寸包括：换热管规格，#{sym.phi.alt}25mm#{sym.times}2.5mm；管长，1.5m；管程数，2；总管数，128根。试判断该换热器是否合用并说明依据。忽略污垢热阻及管壁导热热阻。工艺水的性质按纯水考虑。

对于一个换热器，如果其理论需要的换热面积小于等于其实际能提供的换热面积，那么就可以认为该换热器是能够满足需求的。

由题意得，水的平均温度为 $t_m = 60 #degC$，查询资料[1][2][3]得在此温度下纯水的相关物性如下：

$
  rho_h &= 983.21 "kg/m"^3 \
  mu_h &= 0.4688 times 10^(-3) "Pa" dot "s" \
  lambda_h &= 0.7310 "W/(m" dot "K)" \
  C_p &= 4.1843 times 10^3 "J/(kg" dot "K)" \
  a_v &= 0.01704
$

相关数据为：

$
  phi.alt 25 mm times 2.5 mm => d_i &= 20 mm = 0.02 "m" \
  d_o &= 25 mm = 0.025 "m" \
  b &= 2.5 mm = 0.0025 "m" \
  N &= 128 \
  L &= 1.5 "m" \
  m_(h, "total") &= 2 "t/h" = 2000 \/ 3600 "kg/s" = 0.5556 "kg/s"
$

对于题目描述的换热器，其示意图如下：

#figure(
  image("hw14/q1.jpg", width: 12cm),
  caption: "换热器示意图",
)

其中管程为双程，即管程一来一回，实际输入的管路只有一半，另一半为输出管路。

现有的传热面积为：

$
  A
  = pi d_o N L
  = pi times 0.025 times 128 times 1.5 "m"^2
  = 15.08 "m"^2
$

对于严格逆流，对数平均温差为：

$
  Delta t_m
  &= ((T_0 - t_i) - (T_0 - t_o)) / ln((T_0 - t_i) \/ (T_0 - t_o)) \
  &= ((120 - 30) - (120 - 90)) / ln((120 - 30) \/ (120 - 90)) #degC \
  &= 54.614 #degC
$

折流换热的矫正系数图如下：

#figure(
  image("hw14/折流.png", width: 15cm),
  caption: "折流换热的矫正系数图",
)

对于题目描述的换热器，其

$
  R &= 0 \
  P &= 0.667
$

参考 $R = 0.2$ 的数据，认为该换热器的矫正系数为 $phi = 1$，即 $Delta t'_m = phi dot Delta t_m = 54.614 #degC$。

对管内流体：

$
  "Re"_h
  &= (rho_h u_h d_i) / mu_h = (4 rho_h Q_h d_i) / (pi d_i^2 mu_h) = (4 m_(h, "total")) / (N \/ 2 dot pi d_i mu_h) \
  &= (4 times 0.5556) / (128 \/ 2 times pi times 0.02 times 0.4688 times 10^(-3)) = 1178.9 < (2000) 2300 \
  "Pr"_h
  &= (C_p mu_h) / lambda_h
  = (4.1843 times 10^3 times 0.4688 times 10^(-3)) / 0.7310
  = 2.683\
  "Gr"_h
  &= (rho_h^2 g a_v Delta t d_i^3) / mu_h^2 \
  &= (983.21^2 times 9.81 times 0.01704 times (90 - 30) times 0.02^3) / (0.4688 times 10^(-3))^2
  = 1.765 times 10^10 > 25000
$

此时 $"Re"_h < 2300$，$"Pr"_h > 0.6$，$"Re"_h dot "Pr"_h dot d_i \/ L = 1178.9 times 2.683 times 0.02 \/ 1.5 = 42.173 > 10$，$"Gr"_h > 25000$，流体在圆管内呈层流流动，需考虑自然对流的影响。

$120 #degC$ 时水的粘度为 $mu_w = 0.232 times 10^(-3) "Pa" dot "s"$。

其对流传热系数为：

$
  alpha_i
  &= 1.86 lambda_h / d_i ("Re"_h dot "Pr"_h dot d_i / L)^(1\/3) (mu_h / mu_w)^0.14 \
  &= 1.86 times 0.7310 / 0.02 times 42.173^(1\/3) ((0.4688 times 10^(-3)) / (0.232 times 10^(-3)))^0.14 "W/(m"^2 dot "K)" \
  &= 261.125 "W/(m"^2 dot "K)"
$

对管外，取水蒸气冷凝换热系数 $alpha_o = 1 times 10^4 "W/(m"^2 dot "K)"$，忽略污垢热阻及管壁导热热阻，总传热系数满足：

$
  1 / K
  = 1 / alpha_o + d_o / d_i 1 / alpha_i
  = 1 / (1 times 10^4) + 0.025 / 0.02 1 / (261.125) "(m"^2 dot "K)/W"
  = 4.887 times 10^(-3) "(m"^2 dot "K)/W"
$

从而总传热系数为 $K = 1 \/ (4.887 times 10^(-3) "W/(m"^2 dot "K)" = 204.625 "W/(m"^2 dot "K)"$

传热速率为：

$
  phi.alt = K A' Delta t_m
$

令

$
  phi.alt = w_h C_p (t_o - t_i)
$

得：

$
  A'
  = (w_h C_p (t_o - t_i)) / (K Delta t_m)
  = (0.5556 times 4.1843 times 10^3 times (90 - 30)) / (204.625 times 54.614)
  = 12.482 "m"^2 < 15.08 "m"^2 = A
$

换热器的实际传热面积 $A = 15.08 "m"^2$ 大于理论需要的换热面积 $A' = 12.482 "m"^2$，因此该换热器是合用的。

== 题 2

在四周墙壁温度为30#{degC}的房间内，有一长6m、直径为100mm的水平管道，管道的外壁温度为150#degC。房间内的气温为25#degC，压力为1atm。若管道外壁表面的发射率#{sym.epsilon}=0.7，试计算该管道的散热损失。

由题意得：

$
  D &= 100 mm = 0.1 "m" \
  L &= 6 "m" \
  T_w &= 150#degC = 423 "K" \
  T &= 25#degC = 298 "K" \
  T_oo &= 30#degC = 303 "K" \
  epsilon &= 0.7
$

由于 $T_w = 150#degC$，因而无法使用管道保温层外对流-辐射联合传热系数，管道的换热损失为：

$
  Q_"total" = Q_c + Q_R
$

其中 $Q_c$ 为自然对流换热量，$Q_R$ 为辐射换热量。

对于 $Q_R$，有：

$
  Q_R
  = epsilon C_0 A ((T_w / 100)^4 - (T_oo / 100)^4)
  = 0.7 times 5.67 times pi times 0.1 times 6 times (4.23^4 - 3.03^4) "W"
  = 1765 "W"
$

对于空气自然对流，查询得25#{degC}时相关数据为：

$
  "Pr" &= 0.7135 \
  mu &= 1.81 times 10^(-5) "Pa" dot "s" \
  rho &= 1.205 "kg/m"^3 \
  lambda &= 0.0267 "W/(m" dot "K)" \
$

膜平均温度为：

$
  T_f = (T_w + T) / 2 = (423 + 298) / 2 = 360.5 "K"
$

从而体膨胀系数为：

$
  beta = 1 / T_f = 1 / 360.5 "K"^(-1) = 2.774 times 10^(-3) "K"^(-1)
$

格拉晓夫数为：

$
  "Gr"
  = (beta g Delta t D^3 rho^2) / mu^2
  = (2.774 times 10^(-3) times 9.81 times (150 - 25) times (0.1)^3 times (1.205)^2) / (1.81 times 10^(-5))^2
  = 1.508 times 10^7
$

则 $"Gr" dot "Pr" = 0.7135 times 1.508 times 10^7 = 1.076 times 10^7$。

#figure(
  image("hw14/自然对流.png", width: 12cm),
  caption: "自然对流换热系数",
)

由图3可得努塞尔数为：

$
  "Nu" = 0.54 times ("Gr" dot "Pr")^0.25 = 0.54 times (1.076 times 10^7)^(0.25) = 30.925
$

对流换热系数为：

$
  alpha_c = ("Nu" dot lambda) / D = (30.925 times 0.0267) / 0.1 "W/(m"^2 dot "K)" = 8.257 "W/(m"^2 dot "K)"
$

对流换热量为：

$
  Q_c
  = alpha_c A (T_w - T_oo)
  = 8.257 times pi times 0.1 times 6 times (423 - 303) "W"
  = 1868 "W"
$

从而，总散射为 $Q_"total" = Q_R + Q_c = 1765 + 1868 "W" = 3633 "W"$

== 题 3

有两块平行放置的大平板，板间距远小于板的长度和宽度，温度分别为400#{degC}和50#{degC}，表面发射率均为0.8，为减少两板间的辐射换热量，现在两板之间放置一块表面发射率均为0.2的遮热板，求辐射换热量将下降多少。

由题意得，将大平板视作极大的两平行面，$T_1 = 673 "K" > T_2 = 323 "K"$，则未加遮热板前的辐射系数为：

$
  C_(1-2)
  = C_0 \/ (1 / epsilon_1 + 1 / epsilon_2 - 1)
  = 5.67 \/ (1 / 0.8 + 1 / 0.8 -1) "W/(m"^2 dot "K"^4")"
  = 3.78 "W/(m"^2 dot "K"^4")"
$

辐射热流为：

$
  q_(1-2)
  = C_(1-2) ((T_1 / 100)^4 - (T_2 / 100)^4)
  = 3.78 times ((673 / 100)^4 - (323 / 100)^4) "W/m"^2
  = 7343 "W/m"^2
$

加遮热板后：

$
  C'_1
  &= C_0 \/ (1 / epsilon_1 + 1 / epsilon - 1)
  &= 5.67 \/ (1 / 0.8 + 1 / 0.2 - 1) "W/(m"^2 dot "K"^4")"
  &= 1.08 "W/(m"^2 dot "K"^4")" \
  C'_2 &= C_0 \/ (1 / epsilon_2 + 1 / epsilon - 1)
  &= 5.67 \/ (1 / 0.8 + 1 / 0.2 - 1) "W/(m"^2 dot "K"^4")"
  &= 1.08 "W/(m"^2 dot "K"^4")"
$

辐射热流满足：

$
  q'_(1-2)
  = C'_1 ((T_1 / 100)^4 - (T / 100)^4)
  = C'_2 ((T / 100)^4 - (T_2 / 100)^4)
$

其中 $T$ 为遮热板的温度，解得 $q'_(1-2) = 0.54 times ((673 \/ 100)^4 - (323 \/ 100)^4) "W/m"^2 = 1049 "W/m"^2$。

即辐射换热量下降了 $Delta q = q_(1-2) - q'_(1-2) = 7343 - 1049 "W/m"^2 = 6294 "W/m"^2$，为原来的 $1049 \/ 7343 = 1 \/ 7$。

#line(length: 100%)

== 参考文献

[1] 水的体积膨胀系数[EB/OL]. [2025-04-06]. https://zhuanlan.zhihu.com/p/243575204.

[2] Water (data page)[M/OL] Wikipedia. (2024-10-23)[2025-04-06]. https://en.wikipedia.org/w/index.php?title=Water_(data_page)&oldid=1252881917.

[3] 水的测量精度和导热系数|首页-腾龙在线客服-15368837779[EB/OL]. [2025-04-06]. http://hotdiskinstruments.com.cn/Case_Detail.aspx?id=27.
