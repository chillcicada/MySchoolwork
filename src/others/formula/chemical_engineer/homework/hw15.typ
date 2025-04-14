#import "../../template.typ": *

#show: defineConfig

#set par(first-line-indent: (amount: 2em, all: true))
#set math.equation(numbering: "(1)")

= 化学工程基础 - 第十五次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

某工业空气冷却器采用铝制翅片管（λ=200 W/(mK)），单根管子尺寸为 #{ sym.phi.alt }25mm×2mm，翅片高度 15mm、厚度 0.5mm，翅片间距 5mm，有效长度 3m。已知管内热水温度 80℃，空气侧表面传热系数 #{ sym.alpha }=50 W/(m²K)，环境温度 25℃。对比光管与翅片管的传热量，分析翅片强化传热的原理。

由题目可得：

$
  phi.alt 25mm times 2mm &=> d_i = 0.021 "m", d_o = 0.025 "m" \
  L &= 3 "m"
$

光管：

$
  q
  &= alpha pi d_o L (T_w - T_oo) \
  &= 50 times pi times 0.025 times 3 times (80 - 25) "W" \
  &= 648 "W"
$

翅片管：

相关参数如下：

$
  h &= 15mm = 0.015 "m" \
  delta &= 0.5mm = 5 times 10^(-4) "m" \
  d &= 5mm = 0.005 "m" \
  lambda &= 200 "W/(m" dot "K)"
$

则有：

$
  m &= sqrt((2 alpha) / (lambda delta)) = sqrt((2 times 50) / (200 times 0.0005)) = 31.623 "m"^(-1) \
  eta &= tanh(m h) / (m h) = tanh(31.623 times 0.015) / (31.623 times 0.015) = 93.374%
$

示意图如下：

#figure(
  image("hw15/q1.png", width: 8cm),
  caption: "翅片管的示意图",
)

翅片数量约为：

$
  N = L / (d + delta) = 3 / (0.005 + 0.0005) = 545
$

单个翅片表面积为：

$
  A_0
  &= 2 (pi (h + d_o / 2)^2 - pi d_o^2 / 4) + 2 pi (h + d_o / 2) delta \
  &= 2 times (pi times (0.015 + 0.025 / 2)^2 - pi times 0.025^2 / 4) + 2 times pi times (0.015 + 0.025 / 2) times 0.0005 "m"^2 \
  &= 3.848 times 10^(-3) "m"^3
$

翅片扩展的总面积为 $A = N A_0 = 545 times 1.971 times 10^(-3) "m"^2 = 2.097 "m"^2$；

未被翅片覆盖的面积为：

$
  A_"uncovered" = pi d_o (L - N delta) = pi times 0.025 times (3 - 544 times 0.0005) = 0.214 "m"^3
$

总传热量为：

$
  q'
  &= alpha A_"uncovered" (T_w - T_oo) + alpha eta A (T_w - T_oo) \
  &= 50 times 0.214 times (80 - 25) + 50 times 0.93474 times 2.097 times (80 - 25) "W" \
  &= 5973 "W"
$

$q'\/q = 9.2$，翅片强化后传热效率几乎是之前的 10 倍，显然翅片强化的效果显著，其作用主要是显著增大了换热面积，从而强化了换热效率。

== 题 2

某高温蒸汽管道（外径 100mm，表面温度 150℃）外包覆保温层，环境温度 25℃，空气自然对流表面传热系数 #{ sym.alpha }=10 W/(m²K)。管道表面可涂覆两种涂层：涂层 A（白漆，ε=0.3）；涂层 B（黑漆，ε=0.9）。请结合计算做出选择。

由题目可得：

$
  T_w = 150#degC = 423 "K" \
  T_oo = 25#degC = 298 "K"
$

涂层 A：

$
  q_A
  &= q_c + q_R \
  &= alpha pi d_o (T_w - T_oo) + epsilon C_0 pi d_o ((T_w / 100)^4 - (T_oo / 100)^4) \
  &= 10 times pi times 0.1 times (150 - 25) + 0.3 times 5.67 times pi times 0.1 times (4.23^4 - 2.98^4) "W/m" \
  &= 521.6 "W/m"
$

涂层 B：

$
  q_B
  &= q_c + q_R \
  &= alpha pi d_o (T_w - T_oo) + epsilon C_0 pi d_o ((T_w / 100)^4 - (T_oo / 100)^4) \
  &= 10 times pi times 0.1 times (150 - 25) + 0.9 times 5.67 times pi times 0.1 times (4.23^4 - 2.98^4) "W/m" \
  &= 779.5 "W/m"
$

显然 $q_A < q_B$，因而应选择涂层 A。

== 题 3

某原油-柴油换热器运行1年后，管内形成油垢（$R = 0.002 "(m²" dot "K)/W"$），已知原工况总传热系数$K_o = 600 "W/(m²" dot "K)"$（无垢时），管内 / 外对流传热系数分别为$alpha_i = 1000 "W/(m²" dot "K)"$、$alpha_o = 2000 "W/(m²" dot "K)"$，金属壁热阻可忽略。试计算结垢后的总传热系数，提出为保持传热量稳定可采取的措施建议。

金属壁热阻可忽略，则结垢前有：

$
  1 / K_o = 1 / alpha_o + d_o / d_i dot 1 / alpha_i
$

从而 $d_o \/ d_i = 1.167$

结垢后，有：

$
  1 / K
  = 1 / K_0 + d_o / d_i dot R_i
  = 1 / 600 + 1.167 times 0.002 "(m²" dot "K)/W"
  = 4 times 10^(-3) "(m²" dot "K)/W"
$

从而结垢后总传热系数 $K = 250 "W/(m²" dot "K)"$，比结垢减少了 $350 "W/(m²" dot "K)"$，降低了 58.3%，不及原来的 1/2。为保持传热量稳定，可采取的措施有：

- 及时清理管内油垢；
- 提高原油流速和柴油流速，增大对流传热系数；
- 增大换热面积（管程和壳程）。
