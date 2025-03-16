#import "../../template.typ": *

#show: defineConfig

= 化学工程基础 - 第八次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

临界流化速度满足：

$
  150 (1- epsilon_"mf")^2 / (epsilon_"mf"^3 (phi d_"ev")^2) mu u_"mf" + 1.75 (1 - epsilon_"mf") / epsilon_"mf"^3 (rho u_"mf"^2) / (phi d_"ev") = (1 - epsilon_"mf") (rho_"s" - rho) g
  quad
  (*)
$

由公式 $(*)$ 可知，临界流化速度主要由颗粒和流体的性质决定，而与床层的几何尺寸无关。

因而，对三个颗粒床，其临界流化速度均为 $u_"mf" = 0.3 "m/s"$，即 $u_1 = u_2 = u_3 = 0.3 "m/s"$。

对于三者的压降，根据压降公式 $Delta p_"f" = h_"mf" (1 - epsilon_"mf") (rho_"s" - rho) g$ 知在颗粒和流体等条件不变的情况下，$Delta p_"f" prop h_"mf"$。

由题意得，$p_2 = p_1 = 10 kPa, p_3 = 0.5 p_1 = 5 kPa$。

== 题 2

#figure(image("hw8/q2.png", width: 65%), caption: "题 2 题图")

阀门 $K_A$ 关小后，A 管路的流动阻力增大，流速减小，流量减小。假设 O 总管的流量不变，此时总管流速不变，B 管流量增大，流速增大，则 B 管流动阻力也增大，显然，此时总支管的流动阻力增大，整体流动阻力增大，O 总管流量减小，与假设不符；假设 O 总管的流量增大，此时总管流速增大，B 管流量增大，流速增大，则 B 管流动阻力也增大，显然，此时总支管的流动阻力增大，整体流动阻力增大，O 总管流量减小，与假设不符；因而，O 总管流量只能减小，此时 O 总管流速减小，因而 O 总管的流动阻力减小，O 点处压力增大，则 B 管路流量增大。

== 题 3

由题意，整理数据得：

$
  phi.alt 108 mm times 4 mm => D = 108 -2 times 4 mm = 100 mm = 0.1 "m" \
  Q_m = 38.4 "t/h" = 38.4 times 10^3 / 3600 "kg/s" = 10.67 "kg/s"
$

对于第一种输送方式：

$
  Q_1 = Q_m / rho_(15degC) = 10.67 / 950 unit("m^3/s") = 0.0112 unit("m^3/s") \
  u_m = 4 Q_1 / (pi D^2) = 4 times 0.0112 / (pi times 0.1^2) = 1.430 "m/s" \
$

雷诺数为：

$
  "Re" = (rho_(15degC) u_m D) / mu_(15degC) = (950 times 1.430 times 0.1) / 3.43 = 39.6 < 2000
$

此时油为钢管内层流，其摩阻系数为：

$
  lambda = 64 / "Re" = 64 / 39.6 = 1.62
$

其需要的扬程为：

$
  H
  &= sum h_f / g + Delta z + u_m^2 / (2 g) \
  &= lambda L / D u_m^2 / (2 g) + Delta z + u_m^2 / (2 g) \
  &= 1.62 times 4300 / 0.1 times 1.430^2 / (2 times 9.81) + 20 + 1.430^2 / (2 times 9.81) "m" \
  &= 7.29 times 10^3 "m"
$

泵和电机的总功率为：

$
  N = (Q_1 rho_(15degC) g H) / eta = (0.0112 times 950 times 7.29 times 10^3 times 9.81) / (50%) kW = 1522 kW
$

每小时消耗的费用为：

$
  C_1 = 1522 times 0.5 "元/h" = 761 "元/h"
$

对于第二种输送方式：

$
  Q_2 = Q_m / rho_(50degC) = 10.67 / 890 unit("m^3/s") = 0.0120 unit("m^3/s") \
  u_m = 4 Q_2 / (pi D^2) = 4 times 0.0120 / (pi times 0.1^2) = 1.526 "m/s" \
$

雷诺数为：

$
  "Re" = (rho_(50degC) u_m D) / mu_(50degC) = (890 times 1.526 times 0.1) / 0.187 = 726.5 < 2000
$

此时油为钢管内层流，其摩阻系数为：

$
  lambda = 64 / "Re" = 64 / 726.5 = 0.0881
$

其需要的扬程为：

$
  H
  &= sum h_f / g + Delta z + u_m^2 / (2 g) \
  &= lambda L / D u_m^2 / (2 g) + Delta z + u_m^2 / (2 g) \
  &= 0.0881 times 4300 / 0.1 times 1.526^2 / (2 times 9.81) + 20 + 1.526^2 / (2 times 9.81) "m" \
  &= 469.7 "m"
$

泵和电机的总功率为：

$
  N = (Q_2 rho_(50degC) g H) / eta = (0.0120 times 890 times 469.7 times 9.81) / (50%) kW = 98.4 kW
$

每小时消耗的费用为：

$
  C_2 = 98.4 times 0.5 "元/h" = 49.2 "元/h"
$

显然，$C_2 << C_1$，如果不考虑加热的费用，第二种输送方式更为经济。
