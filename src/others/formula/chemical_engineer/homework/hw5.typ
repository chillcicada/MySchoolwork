#import "@preview/tablem:0.2.0": three-line-table
#import "../../template.typ": *

#show: defineConfig

= 化学工程基础 - 第五次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

忽略温度对油的物化性质的影响，假设全过程为 50 ℃ 恒温，根据题意，关联物理量及单位换算如下：

$
  "密度" rho &= 890 "kg/m"^3 \
  "管道长度" L &= 300 km = 3 times 10^5 "m" \
  "油管最大载压" p_max &= 1.57 times 10^7 Pa \
  phi.alt 168 mm times 9 mm => "圆管内半径" r &= 168 / 2 - 9 mm = 0.075 "m" \
  "圆管内径" D &= 2 r = 150 mm = 0.15 "m" \
  "质量流量" Q_m &= 6 times 10^4 kg\/"h" = 60000 / 3600 kg\/"s" = 16.67 kg\/"s" \
  "粘度" mu &= 181 cP = 0.181 Pa dot "s" \
$

体积流量计算：

$
  Q = Q_m / rho = 16.67 / 890 = 0.0187 "m"^3\/"s"
$

平均流速计算：

$
  u = Q / (pi r^2) = 0.0187 / (3.14 times 0.075^2) "m/s" = 1.059 "m/s"
$

雷诺数计算：

$
  "Re" = (rho u D) / mu = (890 times 1.059 times 0.15) / 0.181 = 781 < 2 times 10^3
$

因此，流动属于层流状态，从而，摩擦系数为：

$
  lambda = 64 / "Re" = 64 / 781 = 0.0819
$

总压力降计算：

$
  Delta p = lambda L / D (rho u^2) / 2 = 0.0819 times (3 times 10^5) / 0.15 times (890 times 1.059^2) / 2 Pa = 8.175 times 10^7 Pa
$

假设有 $N$ 个加压站，则每个加压站能提供的最大压力降为 $p_max$，由于压力降可以直接加和，因而满足提供的压力降大于全过程需要的总压力降即可，如下图所示，即：

$
  (N + 1) p_max >= Delta p
$

#figure(image("hw5/q1.jpg", width: 40%), caption: "题 1 情景")

其中 $1$ 表示初始可以提供的压力降，得：

$
  N = (Delta p) / (p_max) - 1 = (8.175 times 10^7) / (1.57 times 10^7) - 1 = 4.2
$

向上取整得到 $N = 5$ 段，即中途需要设置的加压站数量为 $5$ 个。

== 题 2

根据题意，关联物理量及单位换算如下：

$
  "密度" rho &= 980 kg\/m^3 \
  "直管长度" L_1 &= 20 "m" \
  phi.alt 37 mm times 3.5 mm => "钢管内半径" r &= 37 / 2 - 3.5 mm = 15 mm = 0.015 "m" \
  "钢管内径" D = 2 r = 0.03 "m" \
  "粘度" mu &= 1.0 cP = 1.0 times 10^(-3) Pa dot "s" \
  "塔内压强" p &= p_0 + Delta p = 1.2 atm = 1.2 times 101.33 kPa \
  "体积流量" Q &= 5 "m"^3\/"h" = 5 / 3600 "m"^3\/"s" = 1.39 times 10^(-3) "m"^3\/"s" \
  "相对粗糙度" epsilon / D &= (0.2 times 10^-3) / 0.03 = 0.0067
$

平均流速计算：

$
  u = Q / (pi r^2) = (1.39 times 10^(-3)) / (3.14 times 0.015^2) "m/s" = 1.967 "m/s"
$

雷诺数计算：

$
  "Re" = (rho u D) / mu = (980 times 1.967 times 0.03) / (1.0 times 10^(-3)) = 57830 > 4000
$

#figure(image("hw5/lambda.jpg", width: 80%), caption: "摩擦系数查询")

此时流体体系处于完全湍流状态，查询图像得摩擦系数 $lambda = 0.035$

#figure(image("hw5/valve.png", width: 80%), caption: "当量长度查询")

查询数据（如上图所示），相关管件和阀门的当量长度 $L_e$ 为：

#figure(
  three-line-table[
    | 弯头，90 #sym.degree | 回弯管，180 #sym.degree | 球阀（全开） |
    | - | - | - |
    | 35 D | 75 D | 300 D |
  ],
  caption: "相关管件和阀门的当量长度",
)

由当量长度法 $h_f = lambda L_e / D u^2 / 2$，*忽略入口处的流动阻力*，得总流动阻力为：

$
  sum h_f
  &= lambda (L_1 / D + sum L_e / D) u^2 / 2 \
  &= 0.035 times ( 20 / 0.03 + 35 times 2 + 75 + 300) times 1.967^2 / 2 "J/kg" \
  &= 75.270 "J/kg"
$

从水槽面到出口末端面（不含离开出口面，下图中蓝色线段所示），可知初始速度为 0，末端速度为 $u$，*忽略入口处的流动阻力*，由 Bernoulli 方程得：

#figure(image("hw5/q2.jpg", width: 50%), caption: "题 2 情景")

$
  z
  &= (p - p_0) / (rho g) + (sum h_f) / g + (u^2 - 0) / (2 g) \
  &= (0.2 times 101.33 times 10^3) / (980 times 9.8) + 75.270 / 9.8 + 1.967^2 / (2 times 9.8) "m" \
  &= 9.988 "m"
$

即高位槽应放置的高度为 9.988 米。
