#import "../../template.typ": *

#show: define-config

#set par(first-line-indent: (amount: 2em, all: true))
#set math.equation(numbering: "(1)")

#set text(font: ((name: "Times New Roman", covers: "latin-in-cjk"), "NSimSun"))

= 高分子材料仪器分析 - 第七周

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

= 题一

THF 作为溶剂的洗脱时间为 15 分钟，考虑到在凝胶色谱过程中大分子先流出，因而 THF 洗脱时体系中不再残余大分子样品，即理论上，上一次进样 15 分钟后即可进行下一次进样。

= 题二

数均分子量：

$
  M_n
  = (sum_(i=1)^N (N_i * M_i) ) / (sum_(i=1)^N N_i)
  = (1 times 10^4 + 2 times 10^5) / (1 + 2) "g/mol"
  = 7 times 10^4 "g/mol"
$

重均分子量：

$
  M_w
  = (sum_(i=1)^N (N_i * M_i^2) ) / (sum_(i=1)^N N_i * M_i)
  = (1 times (10^4)^2 + 2 times (10^5)^2) / (1 times 10^4 + 2 times 10^5) "g/mol"
  = 9.571 times 10^4 "g/mol"
$

= 题三

对于示差折光检测器（RI），其可以自行得到色谱柱流出液体中的样品浓度，因而无需在测量前精确测量样品浓度；

对于光散射检测器，其要求高分子为稀溶液，样品浓度为 1g/L 左右，要计算分子量需要提供精确的浓度用于作图，因而需要在测量前精确测量样品浓度；

对于粘度检测器，使用 Mark-Houwink 方程前需要使用 $[eta] = lim_(c -> 0) n_"sp" \/ c$得到特性粘度，因而也需要样品为稀溶液并在测量前得到样品的精确浓度。

综上，即使用 RI 作为检测计则无需在测量前得到精确浓度，使用光散射检测器和粘度检测器，需要在实验前得到样品的精确浓度。
