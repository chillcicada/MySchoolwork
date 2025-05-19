#import "../../template.typ": *
#import "@preview/typsium:0.2.0": ce

#show: define-config

#set par(first-line-indent: (amount: 2em, all: true))
#set math.equation(numbering: "(1)")

= 化学工程基础 - 第二十五次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

在连续精馏塔中分离A、B两组分溶液。原料液的处理量为100 kmol/h，其组成为0.45（易挥发组分A的摩尔分数，下同），饱和液体进料，要求馏出液中易挥发组分的回收率为96 %，釜液的组成为0.033。试求（1）馏出液的流量和组成；（2）若操作回流比为2.5，写出精馏段的操作线方程；（3）提馏段的液相负荷。

（1）由题意得：

$
  F &= 100 "kmol/h" \
  x_F &= 0.45 \
  eta_A &= 0.96 \
  x_W &= 0.033 \
$

由：

$
  cases(
    eta_A = (D x_D) slash (F x_F),
    F = D + W,
    F x_F = D x_D + W x_W,
  ) => cases(
    W = 54.545 "kmol/h",
    D = 45.455 "kmol/h",
    x_D = 0.95,
  )
$

（2）

== 题 2

氯仿（#ce("CHCl3")）和四氯化碳（#ce("CCl4")）的混合物在一连续精馏塔中分离。馏出液中氯仿的浓度为0.95（摩尔分率），馏出液流量为50 kmol/h，平均相对挥发度为1.6，塔顶为全凝器，回流比 $R = 2$。求：（1）塔内由上向下数第二块理论板的上升气相组成；（2）精馏段各板上升蒸气量V及下降液体量L（以kmol/h表示）。

（1）由题意得：

$
  x_D &= 0.95 \
  D &= 50 "kmol/h" \
  alpha &= 1.6 \
  R &= 2 \
$
