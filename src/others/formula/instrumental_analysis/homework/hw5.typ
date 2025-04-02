#import "../../template.typ": *

#show: defineConfig

#set par(first-line-indent: (amount: 2em, all: true))
#set math.equation(numbering: "(1)")

#set text(font: ("Times New Roman", "SimSun"))

= 高分子材料仪器分析 - 第五周

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

= 题一

聚苯乙烯和聚丙烯的 $lg V_g - 1\/T$ 图像均呈现 Z 字型，其中聚苯乙烯和无规聚丙烯作为非晶聚合物，不存在结晶熔融的转变，因而图像上只有玻璃化转变转变特征，等规聚丙烯作为晶态聚合物，图像上有结晶熔融转变和玻璃化转变特征，二者 $lg V_g - 1\/T$ 图像示意图如#[]所示。

#figure(image("hw5/q1.jpg", height: 5cm), caption: [聚苯乙烯和聚丙烯的 $lg V_g - 1\/T$ 图像示意图])

其中图像高度和 Z 型深度还与聚合物层厚度有关。

= 题二

C-C单键 347 kJ/mol，C-H键 413 kJ/mol，在后文中不再标注。

1. PET：结构式如下图所示

#figure(image("hw5/pet.png", height: 3cm), caption: "PET 结构式")

酯键中 C=O 键能约 732 kJ/mol，C-O 键能约 406 kJ/mol，此外，苯环中C-C键 518 kJ/mol。

2. PC：结构式如下图所示

#figure(image("hw5/pc.jpg", height: 3cm), caption: "PC 结构式")

碳酸酯键中 C=O 键能约 732 kJ/mol，C-O 键能约 406 kJ/mol，此外，苯环中C-C键 518 kJ/mol，酚中C-O键 341 kJ/mol。

3. ABS：结构式如下图所示

#figure(image("hw5/abs.png", height: 3cm), caption: "ABS 结构式")

C≡N 键能约 937 kJ/mol，C=C双键键能约 610 kJ/mol，苯环中C-C键 518 kJ/mol。

4. PA6：结构式如下图所示

#figure(image("hw5/pa6.jpg", height: 3cm), caption: "PA6 结构式")

酰胺键中 C-N 键能约 301 kJ/mol，C-O 键能约 406 kJ/mol，此外，C-N 键约 331 kJ/mol，N-H键：键能约 431 kJ/mol。

#line(length: 100%)

PA6 中酰胺键最容易断裂，其次是 ABS 双键的 $alpha, beta$ 侧基的 C-C 单键，PC 和 PET 差不多，但 PC 中的酚环中的 C-O 键能较低，因而高温下，PET、PC、ABS、PA6的热裂解的难易程度依次为：

#align(center)[PET > PC > ABS > PA6]
