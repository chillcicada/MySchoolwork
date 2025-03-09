#import "@preview/cuti:0.3.0": show-cn-fakebold
#import "@preview/tablem:0.2.0": three-line-table

#show: show-cn-fakebold
#set page(paper: "a4", margin: 1.27cm)
#set text(lang: "zh", region: "cn")

= 高分子材料仪器分析 - 第三周

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

= 题一

分配容量的定义为：

$
  k' = K V_s / V_m
$

其中 $K$ 为分配系数，满足 $K = C_L \/ C_G $。

使用塔板理论，认为色谱峰为高斯曲线，从而在流动项中有：

$
  C = C_0 / (sigma sqrt(2 pi)) exp(- (t - t_R)^2 / (2 sigma^2))
$

其中 $C_0$ 为进样量，$sigma = t_R / sqrt(n)$，n 为塔板数。



= 题二

色谱柱的色谱柱效可以使用分离效率，分离时间，分离度等来描述，从塔板理论的角度讲，理论塔板高度越低，说明分离时间越短；有效塔板数越多，说明分离效率越高；对于具体的组分，如果对应分离度越大，说明色谱柱对这些组分的分离能力越强。

分离度 $R$ 的定义为：

$
  R = 2 (t_(R 2) - t_(R 1)) / (W_1 + W_2)
$

当 $R ≥ 1.5$ 时，认为两组分完全分离，显然，仅仅满足两个组分的保留时间不同，是不足以满足 $R ≥ 1.5$ 的条件的，还要满足 $W_1 + W_2$ 足够小，即两组分色谱峰宽足够小以使 $R$ 较大才能在色谱图上一定能分辨开。

= 题三

当色谱的条件一定时，各组分的死时间是相同的，因为死时间由流动相决定，即流动相的流出时间，而与组分无关，在色谱条件不变的时候，流动相从固定相中流出的时间也是固定的，即死时间是不变的。

= 题四



= 题五

Van Deemter 方程为：

$
  H = A + B / overline(u) + C overline(u) quad (*)
$

由题意根据 $H = L / n$ 可列出如下表格，反映不同流速下的理论塔板高度：

#figure(
  three-line-table[
    | $overline(u)$ / mL/min | $n$ | $H$ / m |
    | ---------------------- | --- | ------- |
    | 10 | 1205 | 8.299e-4 |
    | 20 | 1205 | 8e-4 |
    | 40 | 1000 | 1e-3 |
  ],
  caption: "不同流速下的理论塔板高度",
)

带入方程 $(*)$ 得（单位已略去）：

$
  cases(
    8.299 times 10^(-4) &= A + B / 10 + C times 10,
    8 times 10^(-4) &= A + B / 20 + C times 20,
    1 times 10^(-3) &= A + B / 40 + C times 40,
  ) => cases(
    A = 3.402 times 10^(-4),
    B = 3.464 times 10^(-3),
    C = 1.433 times 10^(-5),
  )
$

令 $overline(u) = sqrt(B \/ C)$ 得载气最佳流速 $overline(u)_m = 15.548$ mL/min，此时的板高 $H = 7.858 times 10^(-4)$ m。

= 题六
