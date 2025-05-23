#import "../../template.typ": *

#show: define-config

#set par(first-line-indent: (amount: 2em, all: true))

#set text(font: ((name: "Times New Roman", covers: "latin-in-cjk"), "NSimSun"))

= 高分子材料仪器分析 - 第八周

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题一

用 GPC 测定实际分子量相同的线型分子和树枝状分子，装配有示差、粘度和光散射检测器，则两种分子在三种检测器上的信号有什么不同（峰高、出峰时间）？给出解释

相同分子量的线型分子和树枝状分子相比，线性分子具有更大的流体力学体积，因而具有在 GPC 中的出峰时间比树枝状分子短，在所有检测器上均成立。假设二者初始的浓度是一样的，从而：

- 对于粘度检测器，显然线型分子由于流体力学体积更大，因而特性粘度更大，同时，由于线型分子停留时间更短，洗脱时浓度更大，峰高（特性粘度和浓度的乘积）更高。
- 对于示差折光检测器，如果两种分子的浓度和折光特性相同，由于线型分子停留时间更短，洗脱时浓度更大，则峰高（浓度）更大。
- 对于光散射检测器，光散射强度与浓度与分子量的乘积成正比，二者具有相同的分子量，由于线型分子停留时间更短，洗脱时浓度更大，则峰高（浓度和分子量的乘积）更大。

== 题二

在测 GPC 时，浓度对测量结果会有什么影响？如果溶液中有部分不完全溶解，做出的结果又会出现什么样的偏差？请说明原因。

测量 GPC 时，要求样品溶液为稀溶液，对于高分子溶液，浓度过高时溶液中高分子链会相互重叠，体系粘度增大，对于粘度检测器，其得到的流体力学体积会偏大，导致分子量偏大；对于示差折光检测器，浓度过高时，浓度与折光系数的关系不再呈现线性变化；对于光散射检测器，浓度过高时，不能再忽略外干涉的影响和浓度因素，此时得到的均方回转半径会偏小，导致分子量偏小。

如果溶液中有溶解不完全的部分，GPC 测定到的浓度会更低，即所有的检测器上峰高都更低，计算得到的分子量也会更低，同时未溶解的颗粒可能导致阻塞，若为溶解部分进入柱子，则会引入额外的小峰，引入高分子量分布。

== 题三

说明为什么可以推断出 PPT 倒数第二页聚3-己基噻吩的端基是 Br/H，而不是另外两种情况？

$
  M_"peak" &= 5069.80 \
  M_"re" &= 166.28 \
  M_"cat" &= 1.00 <- "假设" C^+ "为质子"
$

可得 $n = floor(M_"peak" / M_"re") = 30$

末端基团 $G_1 + G_2$ 的质量为：

$
  M_"end" = M_"peak" - M_"cat" - n * M_"re" = 5069.80 - 30 * 166.28 = 5069.80 - 1.00 - 4988.40 = 80.40
$

只可能为 Br/H（$79 + 1 = 80$）。
