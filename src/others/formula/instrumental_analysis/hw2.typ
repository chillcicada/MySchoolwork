#import "@preview/cuti:0.3.0": show-cn-fakebold

#show: show-cn-fakebold
#set page(paper: "a4", margin: 1.27cm)
#set text(lang: "zh", region: "cn")

= 高分子材料仪器分析 - 第二周

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题一

聚合物熔点和聚合度存在如下关系：

$
  1 / T_m = 1 / T_m^0 + R / (Delta H_f) times 2 / P
$

式中 $P$ 为聚合度，满足 $P prop overline(M)_n$，$overline(M)_n$ 为聚合物分子量，$T_m^0$ 为无限大聚合度时的熔点，$R$ 为气体常数，$Delta H_f$ 为熔化焓。

由此可知，绘制 $1/T_m$ 与 $1/overline(M)_n$ 拟合图像，根据纵轴截距，即可得到 $T_m^0$。

初次拟合图像如下图所示：

#figure(image("assets/first_output.png", width: 60%), caption: "初次拟合图像")

其中拟合系数 $R^2 = 0.6133$，可见此次拟合效果并不好，注意到图像第三个点（对应第二组数据）明显偏离拟合直线，因此考虑将其剔除，重新拟合，得到如下图像：

#figure(image("assets/final_output.png", width: 60%), caption: "剔除第三个点后的拟合图像")

其中拟合系数 $R^2 = 0.9895$，可见此次拟合效果较好。

此时纵轴截距为 $0.00292 "K"^(-1)$，即 $T_m^0 = 342.10 "K", 68.95 "°C"$。

== 题二

#figure(image("assets/dsc.png", width: 80%), caption: "热流型 DSC（左图）和功率补偿 DSC（右图）")

相同点：

两者均通过测量样品与参比物之间的热流差异来定量分析材料的热性能，如熔点、玻璃化转变温度、热容等，广泛应用于高分子材料、药物、食品、金属等领域的热分析。

不同点：

热流型DSC：通过测量样品与参比物之间的温度差来计算热流，通常使用热电堆或热流传感器，结构简单，成本较低，灵敏度较低，分辨率较差，响应较慢，适合常规热分析和慢速扫描，多为常规实验和一般热分析。

功率补偿型DSC：通过调节加热功率使样品与参比物温度保持一致，测量所需的补偿功率来反映热流，结构复杂，成本较高，灵敏度高，分辨率好，响应快，适合高精度测量和快速扫描和高动态范围测量，多为高精度研究和复杂热分析。


== 题三

参考 Choi 对聚乙烯-醋酸乙烯酯脱乙酰化物的热解行为研究[1]，明确 EVA 热重分析第一阶段为乙酸乙烯酯脱乙酰释放乙酸，因而可以从第一阶段的失重比推算出 EVA 中乙酸乙烯酯的含量。

由 $M_r("乙酸乙烯酯") : M_r("乙酸") = 86 : 60$ 得乙酸乙烯酯的质量分数为：

$
  w_("乙酸乙烯酯")= M_r("乙酸乙烯酯") / M_r("乙酸") times w_("乙酸") = 14.62%
$

则 $w_("乙烯") = 85.38%$，由 $M_r("乙烯") = 26$ 得乙酸乙烯酯的摩尔分数为：

$
  x_("乙酸乙烯酯") = (w_("乙酸乙烯酯") \/ M_r("乙酸乙烯酯")) / (w_("乙酸乙烯酯") \/ M_r("乙酸乙烯酯") + w_("乙烯") \/ M_r("乙烯")) times 100% = 4.92%
$

#line(length: 100%, stroke: .5pt)

== 参考文献

[1] CHOI S S, KIM E. Pyrolysis behaviors of deacetylated poly(ethylene-co-vinyl acetate) depending on pyrolysis temperature[J/OL]. Journal of Analytical and Applied Pyrolysis, 2018, 130: 29-35. DOI:10.1016/j.jaap.2018.02.001.

