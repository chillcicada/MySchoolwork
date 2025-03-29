#import "../../template.typ": *

#show: defineConfig

#set par(first-line-indent: (amount: 2em, all: true))
#set math.equation(numbering: "(1)")

= 传热过程和传热设备

== 对流传热

=== 牛顿冷却定律

壁面向流体传热时：

$
  phi = alpha A (t_w - t)
$

流体向壁面传热时：

$
  phi = alpha A (T - T_w)
$

式中：

- $phi$：热流量（W）；
- $A$：传热面积（$"m"^2$）；
- $t$：冷流体温度（K）；
- $t_w$：冷流体壁面温度（K）；
- $T$：热流体温度（K）；
- $T_w$：热壁面壁面温度（K）；
- $alpha$：对流换热系数（W/($"m"^2$ K)）；

=== 管内强制对流换热

Dittus-Boelter 关系式（激烈湍流，低粘度流体）：

$
  "Nu" = 0.023 "Re"^0.8 "Pr"^n
$

对流换热系数：

$
  alpha = 0.023 lambda / d_i "Re"^0.8 "Pr"^n
$

当液体被加热时，n = 0.4；当液体被冷却时，n = 0.3。

Dittus-Boelter 关系式适用于：

- 定性温度：流体进出口温度算数平均值；
- 定性尺寸：管道内径 $d_i$；
- 应用范围：
  - $"Re" > 10^4$；
  - $0.5 < "Pr" < 120$；
  - 管内表面光滑；
  - 管长与管径比 $L\/d_i >= 50$（流体流动充分发展）

Dittus-Boelter 关系式的外推与修正 $alpha' = alpha phi.alt$：

+ 短管 $L\/d_i < 50$：

  $
    phi.alt_L = 1 + (d_i \/ L)^0.7
  $

+ 过渡流 $2300 < "Re" < 10000$：

  $
    phi.alt = 1 - (6 times 10^5) / "Re"^1.8
  $

+ 圆形弯管（如螺旋蛇管）：

  $
    phi.alt_R = 1 + 1.77 d_i / R
  $

  式中 $R$ 为弯管轴的曲率半径。

+ 非圆形管：使用当量直径

  $
    d_i = 4 A / P
  $

  式中 $A$ 为管道的流动截面积，$P$ 为管道的湿周长。

#line(length: 100%)

小管径直管层流，同时流体和壁面温差不大（$"Gr" < 25000$）：

$
  "Nu" = 1.86 "Re"^(1\/3) "Pr"^(1\/3) (d_i\/L)^(1\/3) (mu\/mu_w)^(1\/3)
$

要求如下：

- $"Re" < 2300$
- $"Pr" > 0.6$
- $"Re" dot "Pr" dot d_i \/ L > 10$

对于 $"Gr" > 25000$，给出如下修正系数：

$
  f = 0.8 (1 + 0.015 "Gr"^(1\/3))
$
