#import "../../template.typ": *

#show: defineConfig

= 生物化学 2 - 第二次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

=== (a)

由 $Delta G^0 ' = - R T ln K_"eq" = 13800 "J"\/"mol", T = 310 "K", R = 8.314 "J"\/"mol"$ 得 $K_"eq" = 4.73 times 10^(-3)$

对 Glucose + Pi $->$ glucose 6-phosphate + $"H"_2"O"$，有：

$
  K_"eq" = ["glucose 6-phosphate"] / (["Glucose"] ["Pi"])
$

得 $["glucose 6-phosphate"] = 1.090 times 10^(-7) "M"$。

该反应无法代表合理的葡糖糖代谢过程，因为该反应的标准吉布斯自由能 $Delta G^0 ' > 0$，在生物体正常情况下不会自发发生，因而也不会是代谢途径。

=== (b)

令 $Delta G = Delta G^0 ' + R T ln ["glucose 6-phosphate"] / (["Glucose"] ["Pi"]) = 0$，代入 $["glucose 6-phosphate"] = 2.5 times 10^(-4) "M", ["Pi"] = 4.8 times 10^(-3) "M"$ 得：

$
  ["Glucose"] = 11.011 "M" > 1 "M"
$

显然从生理角度这个葡萄糖浓度是不合理的。

=== (c)

#align(center)[
  Glucose + ATP $->$ Glucose 6-phosphate + ADP $quad Delta G^0 ' = -16.7$ kJ/mol
]

令 $Delta G = Delta G^0 ' + R T ln (["glucose 6-phosphate"] ["ADP"]) / (["Glucose"] ["ATP"]) = 0$，代入 $["glucose 6-phosphate"] = 2.5 times 10^(-4) "M", ["ATP"] = 3.38 times 10^(-3) "M", ["ADP"] = 1.32 times 10^(-3) "M"$ 得：

$
  ["Glucose"] = 1.498 times 10^(-7) "M"
$

此时只需极少量的葡萄糖即可使反应正向进行 G6P，显然此途径对于生理过程是可行的。

=== (d)

显然不合理，先水解产生磷酸基团再转移到葡萄糖上本质上还是提高浓度，在 (b) 中已经论证过要想提高浓度使葡萄糖磷酸化的反应正向进行在细胞内是不现实的，细胞内的各物质浓度往往在一定范围内波动，因而无论是 ATP，ADP 还是磷酸基团，都不可能实现此路径，在这个路径下，ATP 水解的自由能在第一步即耗散，从代谢的角度讲也是不利于生物的，因而这条路径显然是不合理的。

=== (e)

磷酸基团直接在葡萄糖-ATP-酶复合物上从 ATP 转移到葡萄糖上，此过程不需要水分子的参与，同时能确保 ATP 断裂高能磷酸键的能量大部分储存在生成的 G6P 中，最后，在酶的控制下，能确保此过程精确高效无误地发生。

== 题 2

=== (a) Oxidation-Reduction Reaction

catalyzed by *dehydrogenase*, requires $"NAD"^+$ or other electron acceptors as a cofactor and produces NADH (with a $"H"^+$) or other electron donors.

use $"NAD"^+$ as an instance:

#align(center)[
  Palmitoyl-CoA + $"NAD"^+$ $->$ _trans_-$Delta^2$-Enoyl-CoA + NADH + $"H"^+$
]

=== (b) Isomerization Reaction

catalyzed by *isomerase* and requires no cofactor or reactant with no other products

#align(center)[
  L-Leucine $->$ D-Leucine
]

=== (c) Isomerization Reaction

catalyzed by *isomerase* and requires no cofactor or reactant with no other products

#align(center)[
  Glucose $->$ Fructose
]

=== (d) Group Transfer Reaction

catalyzed by *kinase*, requires ATP (or other phosphate donors) as a reactant products and produces one ADP and one $"H"_2"O"$

use ATP as an instance:

#align(center)[
  Glycerol + ATP $->$ Glycerol 3-Phosphate + ADP + $"H"_2"O"$
]

=== (e) Hydrolysis Reaction

catalyzed by *hydrolase* and requires $"H"_2"O"$ as a reactant with no other products

#align(center)[
  Glycylalanine + $"H"_2"O"$ $->$ Glycine + Alanine
]

=== (f) Oxidation-Reduction Reaction

catalyzed by *dehydrogenase*, requires $"NAD"^+$ or other electron acceptors as a cofactor and produces NADH (with a $"H"^+$) or other electron donors.

use $"NAD"^+$ as an instance:

#align(center)[
  Glycerol + $"NAD"^+$ $->$ Dihydroxyacetone Phosphate + NADH + $"H"^+$
]

=== (g) Oxidation-Reduction Reaction

catalyzed by *dehydrogenase*, requires $"NAD"^+$ (with one $"H"_2"O"$) or other electron acceptors as a cofactor and produces NADH (with one $"H"^+$) or other electron donors.

use $"NAD"^+$ as an instance:

#align(center)[
  Acetaldehyde + $"NAD"^+$ + $"H"_2"O"$ $->$ Acetic Acid + NADH + $"H"^+$
]

== 题 3

核心代谢途径的高度保守性反映了进化历史、功能约束和路径依赖的综合作用，在进化上，生命体可能可以追溯到同一个起源，因而具有相同或相近的代谢途径；从功能上讲，代谢网络往往不是单一途径，而是高度耦合的网络，其中某一处更改都可能使得整体代谢网络瘫痪，因而维持着高保守性；同时，进化过程往往不是跳跃式的，而是渐进式的，因而很多代谢过程都会尽可能地复用而不是推倒重来。这些核心代谢途径并非绝对意义上的“最优解”，而是在长期进化中形成的稳定、鲁棒且兼容性强的解决方案。尽管存在理论上的优化空间，但在自然选择压力下，彻底重构核心代谢需要突破多重限制，因此生物体更倾向于在核心框架内进行局部优化（如调控表达水平或辅因子利用）。这一现象也提示，生命系统的适应性不仅依赖于底层代谢的“最优性”，更依赖于对现有结构的灵活调控和再利用。
