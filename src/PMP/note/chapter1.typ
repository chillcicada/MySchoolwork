#import "@preview/cuti:0.3.0": show-cn-fakebold

#show: show-cn-fakebold
#set page(paper: "a4", margin: 1.27cm)
#set text(lang: "zh")

剪切应力与剪切应变的关系由材料的剪切模量（G）决定，具体如下：

1. *剪切应力（τ）*：作用在材料截面上的切向力（F）与截面面积（A）之比，公式为：
  $ tau := F / A $

2. *剪切应变（γ）*：材料因剪切应力产生的形变，公式为：
  $ gamma := (Delta x) / h $
  其中，Δx 是横向位移，h 是材料厚度。

3. *剪切模量（G）*：剪切应力与剪切应变的比值，公式为：
  $ G := tau / gamma $
  剪切模量反映材料抵抗剪切变形的能力。

4. *胡克定律*：在弹性范围内（在弹性变形阶段），剪切应力与剪切应变成正比：
  $ tau := G / gamma $

#line(length: 100%)

剪切速率，考虑到横向剪切应力作用过程对材料厚度 h 不产生影响，因此剪切速率的计算公式为：

$ dot(gamma) := (dif tau) / (dif t) = (dif x \/ dif t) / h = v / h $

式中 v 为横向位移速度，h 为材料厚度。

对于平行直线流场，可以得到：

$ dot(gamma) = v / y = (dif v) / (dif y) $

#line(length: 100%)

同心圆流场中，剪切形变与位置（半径）有关，因而只存在局部（微分）形式：

$ dif gamma = (dif x) / (dif r) $

从而剪切速率为：

$ dif x = ((r + dif r) (omega + dif omega) - (r + dif r) omega) dif t $

舍去高阶无穷小项，得到：

$ dif x = r dif omega dif t $

$ dot(gamma) = (dif x \/ dif t) / (dif r) = r (dif omega) / (dif r) = r dif (v_theta / r) \/ dif r $

#line(length: 100%)

#figure(image("ch1/non-newtonian.png", width: 80%), caption: "非牛顿流体")

幂律定律：

$ tau = K gamma^n $

式中，K 为材料的稠度系数（consistency index），n 为流变指数（power-law index）或非牛顿指数（non-newton index）。

n = 1 时，称为牛顿流体；n > 1 时，称为偏应力流体；n < 1 时，称为剪切稀化流体。

#line(length: 100%)

表观粘度：流动曲线上某点割线的斜率，即剪切速率与剪切应力的比值。

$
  eta_a = tau / dot(gamma)
$

稠度或微分粘度：流动曲线上某点切线的斜率，即局部剪切应力与局部剪切速率的比值。

$
  eta_c = (dif tau) / (dif dot(gamma))
$

#line(length: 100%)

// TODO: 毛细流变仪
