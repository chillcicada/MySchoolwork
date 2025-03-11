#import "@preview/cuti:0.3.0": show-cn-fakebold

#show: show-cn-fakebold
#set page(paper: "a4", margin: 1.27cm)
#set text(lang: "zh", region: "cn")

= 色谱分析

在色谱法中，将填入玻璃管或不锈钢管内静止不动的一相（固体或液体）称为固定相 ；自上而下运动的一相（一般是气体或液体）称为流动相；装有固定相的管子（玻璃管或不锈钢管）称为色谱柱。

- TCD / Thermal Conductivity Detector：热导检测器
- FID / Flame Ionization Detector：氢火焰离子化检测器
- ECD / Electron Capture Detector：电子俘获检测器
- FPD / Flame photometric Detector：火焰光度检测器

压力梯度校正因子 $j$ 的定义为：

$
  j = 3 / 2 ((P_i \/ P_o)^2 - 1) / ((P_i \/ P_o)^3 - 1)
$

其中 $P_i$ 为柱入口压力，$P_o$ 为柱出口压力。
