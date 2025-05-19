#import "../../template.typ": *
#import "@preview/typsium:0.2.0": ce

#show: define-config

#set par(first-line-indent: (amount: 2em, all: true))
#set math.equation(numbering: "(1)")

= 化学工程基础 - 第二十四次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

在一连续精馏塔中分离苯的含量为0.5（苯的质量分数，下同）的苯-甲苯混合液，其流量为100 kmol/h。已知馏出液组成为0.95，釜液组成为0.05，试求：（1）馏出液流量及苯的回收率；（2）保持馏出液组成0.95不变，馏出液最大可能流量。

（1）由题意得：

$
  F = 100 "kmol/h" \
  M_(r, ce("C6H6")) = 78 \
  M_(r, ce("C7H8")) = 92 \
  x_F = (w_A slash M_(r, ce("C6H6"))) / (w_A slash M_(r, ce("C6H6")) + (1 - w_A) slash M_(r, ce("C7H8"))) = 0.541 \
  x_D = (w_(A, D) slash M_(r, ce("C6H6"))) / (w_(A, D) slash M_(r, ce("C6H6")) + (1 - w_(A, D)) slash M_(r, ce("C7H8"))) = 0.957 \
  x_W = (w_(A, W) slash M_(r, ce("C6H6"))) / (w_(A, W) slash M_(r, ce("C6H6")) + (1 - w_(A, W)) slash M_(r, ce("C7H8"))) = 0.058 \
$

由物料衡算可知：

$
  cases(
    F = W + D,
    F x_F = W x_W + D x_D,
  ) => cases(
    W = 46.274 "kmol/h",
    D = 53.726 "kmol/h",
  )
$

苯的回收率为：

$
  eta_A = (D x_D) / (F x_F) times 100% = 95.04%
$

（2）馏出液最大可能流量时即釜液组成 $x_W -> 0$，由物料守恒可知：

$
  F x_F = D_max x_D
$

由此可得最大可能流量为 $D_max = 56.531 "kmol/h"$

== 题 2

对于逆流操作的气液传质过程，理论板数和传质单元数都可以用来描述分离过程的难易，请简述1个理论板和1个传质单元的物理意义。

理论板关注分离的热力学极限（平衡状态），反映组分本身分离的难易，适合级式操作的设计。

传质单元关注分离的动力学过程（推动力和速率），反映实际传质过程的效率，适合连续接触设备的设计。
