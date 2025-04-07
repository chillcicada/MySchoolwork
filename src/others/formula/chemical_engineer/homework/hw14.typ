#import "../../template.typ": *

#show: defineConfig

#set text(font: "SimSun")
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

== 题 3

有两块平行放置的大平板，板间距远小于板的长度和宽度，温度分别为400 #degC 和50 #degC，表面发射率均为0.8，为减少两板间的辐射换热量，现在两板之间放置一块表面发射率均为0.2的遮热板，求辐射换热量将下降多少。

由题意得，将大平板视作极大的两平行面，则辐射系数为：

$
  C_(1-2)
  = C_0 \/ (1 / epsilon_1 + 1 / epsilon_2 - 1)
  = 5.67 \/
$

$
  Q_(1-2)
  =
$

#line(length: 100%)

== 参考文献

[1] 水的体积膨胀系数[EB/OL]. [2025-04-06]. https://zhuanlan.zhihu.com/p/243575204.

[2] Water (data page)[M/OL] Wikipedia. (2024-10-23)[2025-04-06]. https://en.wikipedia.org/w/index.php?title=Water_(data_page)&oldid=1252881917.

[3] 水的测量精度和导热系数|首页-腾龙在线客服-15368837779[EB/OL]. [2025-04-06]. http://hotdiskinstruments.com.cn/Case_Detail.aspx?id=27.
