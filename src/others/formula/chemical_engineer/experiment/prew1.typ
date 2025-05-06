#import "../../template.typ": *
#import "@preview/tablem:0.2.0": tablem, three-line-table

#show: define-config.with(margin-style: "normal")

#show heading.where(level: 1): it => {
  align(center, text(size: font-size.三号, it))
}

#show heading.where(level: 2): it => {
  text(size: font-size.小四, it)
}

#set math.equation(numbering: "(1)")

#set par(first-line-indent: (amount: 2em, all: true))

= 化工基础实验报告

#line(length: 0%)

#set text(size: font-size.小四)

#let info = (
  // row 1
  "实验名称": "离心泵与管路内流体阻力表征",
  // row 2
  "班级": "探微-分21",
  "姓名": "刘宽",
  "学号": "2022013189",
  "成绩": "",
  // row 3
  "实验时间": "2025年3月18日",
  "同组成员": "侯仁哲、王一涵",
)

#let dict2list(dict) = { for (key, value) in dict { (key, value) } }

#table(
  align: center + horizon,
  columns: (auto, 1fr),
  stroke: (x, y) => if calc.odd(x) {
    (bottom: 0.5pt + black)
  },

  ..dict2list(info).slice(0, 2)
)

#v(-12pt)

#table(
  align: center + horizon,
  columns: (auto, 1fr, auto, 1fr, auto, 1fr, auto, 1fr),
  stroke: (x, y) => if calc.odd(x) {
    (bottom: 0.5pt + black)
  },

  ..dict2list(info).slice(2, 10)
)

#v(-12pt)

#table(
  align: center + horizon,
  columns: (auto, 1fr, auto, 1.5fr),
  stroke: (x, y) => if calc.odd(x) {
    (bottom: 0.5pt + black)
  },

  ..dict2list(info).slice(10)
)

#set text(size: font-size.五号)

== 一、实验任务与方案

离心泵的特性曲线取决于泵的结构、尺寸和转速。对于一定的离心泵，在一定的转速下，泵的扬程 $H$ 与流量 $q$ 之间存在一定的关系。此外，离心泵的轴功率 $P$ 和效率 $η$ 亦随泵的流量 $q$ 而改变。因此 $H$ - $q$、$P$ - $q$ 和 $η$ - $q$ 三条关系曲线反应了离心泵的特性，称为离心泵的特性曲线。

（1）流量 q 的测定：

本实验装置采用涡轮流量计直接测量泵流量 $q'$：$q = q' / 3600 unit("m^3/s")$

（2）扬程的计算：

根据伯努利方程：

$
  H = (Delta P) / (rho dot g) times 10^6 quad ["m 液柱"]
$

$(1)$ 式中，$H$ 为扬程 $Delta P$ 为压差；$rho$ 为水在操作温度下的密度；$g$ 为重力加速度。其中，本实验装置的 $Delta P$ 由差压计直接测量。

（3）泵的总效率：

$
  eta = "泵的有效功率" / "泵的轴功率" = P_e / P_轴 = (q H rho g) / P_轴 times 100%
$

（4）泵的轴功率 $P_轴$：

$P_轴$ —— 电动机的功率乘以电机的效率，其中电机功率用三项功率变送器直接测定 [kW]。

（5）转速校核：

将以上所测得的参数校正为额定转速 $n' = 2850 rpm$ 下的数据来绘制泵的特性曲线图，即：

$
  q' / q = n' / n quad
  H' / H = (n' / n)^2 quad
  P' / P = (n' / n)^3
$

式中 $n'$ 为额定转速 2850 rpm，$n$ 为实际转速 [rpm]。

== 二、实验记录

（1）数据记录：


#align(
  center,
  table(
    align: center + horizon,
    columns: (3cm, 3cm),
    [实验环境], [数据],
    [温度 ℃], [],
    [水密度 $rho$ #unit("kg/m^3")], [],
    [水粘度 $mu Pa dot "s"$],
  ),
)

== 三、实验结果及讨论

== 四、自评
