#import "../../template.typ": *

#show: define-config

= 色谱分析

在色谱法中，将填入玻璃管或不锈钢管内静止不动的一相（固体或液体）称为固定相 ；自上而下运动的一相（一般是气体或液体）称为流动相；装有固定相的管子（玻璃管或不锈钢管）称为色谱柱。

== 塔板理论

由塔板理论，认为色谱峰为高斯曲线，从而在流动项中有：

$
  C = C_0 / (sigma sqrt(2 pi)) exp(- (t - t_R)^2 / (2 sigma^2))
$

其中 $C_0$ 为进样量，$sigma = t_R / sqrt(n)$，$t_R$ 为峰的保留值，$n$ 为塔板数，也即色谱柱效。

峰宽为：

$
  W = 4 sigma = (4 t_R) / sqrt(n)
$

*从而峰宽与保留值成正比，与柱效的平方根成反比，与进样量无关。*

$t = t_R$ 时，峰高为：

$
  C_max = (sqrt(n) C_0) / (sqrt(2 pi) t_R)
$

*即峰高与进样量成正比，与保留值成反比，与柱效的平方根成正比。*

== 速率理论

Van Deemter 方程描述影响板高的动力学因素：

$
  H = A + B / overline(u) + C * overline(u)
$

其中各项系数含义如下：

- A：涡流扩散项
- B：纵向扩散项系数
- C：传质阻力项系数

此外，$H$ 为塔板高度，满足 $H = L / n$，$overline(u)$ 为流速。

- TCD / Thermal Conductivity Detector：热导检测器
- FID / Flame Ionization Detector：氢火焰离子化检测器
- ECD / Electron Capture Detector：电子俘获检测器
- FPD / Flame photometric Detector：火焰光度检测器

压力梯度校正因子 $j$ 的定义为：

$
  j = 3 / 2 ((P_i \/ P_o)^2 - 1) / ((P_i \/ P_o)^3 - 1)
$

其中 $P_i$ 为柱入口压力，$P_o$ 为柱出口压力。

#line(length: 100%)

Kovats 插值法：

$
  I = 100(z + (lg t'_R(x) - lg'_R(z)) / (lg'_R(z + 1) - lg'_R(z)))
$

#line(length: 100%)

数均分子量：

$
  M_n = (sum_(i=1)^N (N_i * M_i) ) / (sum_(i=1)^N N_i)
$

重均分子量：

$
  M_w = (sum_(i=1)^N (N_i * M_i^2) ) / (sum_(i=1)^N N_i * M_i)
$
