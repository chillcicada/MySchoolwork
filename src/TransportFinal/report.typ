#import "@preview/codly:1.1.1": *
#import "@preview/codly-languages:0.1.3": *
#import "@preview/cuti:0.3.0": show-cn-fakebold

#show: show-cn-fakebold

#show: codly-init.with()

#let TITLE_FONT = ("Arial", "SimHei")

#let TEXT_FONT = ("Times New Roman", "SimSun")

#show heading: it => {
  text(it, font: TITLE_FONT)
}

#show heading.where(level: 1): it => {
  text(it, size: 36pt)
}

// pagebreak at heading level 2
#show heading.where(level: 2): it => {
  pagebreak()
  text(it, size: 20pt)
}

#show heading.where(level: 3): it => {
  text(it, size: 16pt)
}

#set page(
  paper: "a4",
  footer: [
    #align(
      center,
      datetime.today().display("[year]年[month]月[day]日"),
    )
  ],
  margin: (left: 1.27cm, right: 1.27cm, top: 1.27cm, bottom: 2.54cm),
)

#set text(font: TEXT_FONT, lang: "zh")

#set math.equation(numbering: (..n) => numbering("(1)", ..n))

#align(center)[
  #v(10%)

  #image("_img/thu_logo.jpg", width: 120%)

  #v(-4%)

  = 作业报告

  #text(size: 20pt)[2024秋 传递过程原理]

  #text(font: ("libertinus serif", "KaiTi"), size: 14pt)[
    刘宽 2022013189 探微-分21

    liukuan22\@mails.tsinghua.edu.cn
  ]
]

#set page(
  footer: [
    #align(center)[
      *2024 传递过程原理大作业*

      #context counter(page).display("- 1 -")
    ]
  ],
)

== 问题描述

#counter(page).update(1)

#figure(
  table(
    columns: 4,
    stroke: none,
    align: horizon,
    table.hline(),
    table.header(
      [],
      [密度 $"kg"\/upright(m)^3$],
      [热容 $upright(J)\/("kg" dot.c upright(K))$],
      [导热系数 $upright(W)\/(upright(m) dot.c upright(K))$],
    ),
    table.hline(stroke: 0.5pt),

    [陶瓷], [$rho_1 = 2600$], [$C_(p 1) = 1150$], [$k_1=3.0$],
    [保温层], [$rho_2 = 600$], [$C_(p 2) = 200$], [$k_2=0.2$],

    table.hline(),
  ),
  caption: [材料参数],
)

陶瓷与反应物流的对流换热系数为 $h_1 = 500 upright(W)\/(upright(m)^2 dot.c upright(K))$，保温层与环境气流的对流换热系数为 $h_2 = 10 upright(W)\/(upright(m)^2 dot.c upright(K))$。

起始时，反应物流温度为 $T_0 = 1500 upright(K)$，环境气流温度为 $T_infinity = 298 upright(K)$，反应器温度为 $T_"init" = 300 upright(K)$。陶瓷厚度 $delta_1 = 0.025 upright(m)$，保温层厚度 $delta_2 = 0.05 upright(m)$。反应器内半径 $R_1 = 0.025 upright(m)$，保温层内半径 $R_2 = 0.05 upright(m)$，反应器外半径 $R_3 = 0.1 upright(m)$，反应器示意图如下@fig:problem。

记陶瓷温度为 $T_1$，热扩散系数为 $alpha_1$；保温层温度为 $T_2$，热扩散系数为 $alpha_2$。

#figure(
  image("_img/problem.png", width: 70%),
  caption: [反应器示意图],
) <fig:problem>

== 问题分析

传热基本方程：

$
  (upright(D) T) / (upright(D) t) = alpha nabla^2 T + dot(q) / (rho C_p)
$<1>

对于陶瓷和保温层的传热过程，其为一维非稳态导热问题，无内热源，边界处均为第三类边界条件（对流换热）。从而，其传热方程@1 简化为：

$
  (partial T) / (partial t) = alpha nabla^2 T
$<2>

陶瓷和保温层均为圆管状，温度分布只与时间 $T$ 和径向变量 $r$ 有关，从而方程@2 进一步简化为：

$
  (partial T) / (partial t) = alpha (1 / r partial / (partial r) (r (partial T) / (partial r)))
$<3>

展开得到：

$
  (partial T) / (partial t) = alpha ((partial^2 T) / (partial r^2) + 1 / r (partial T) / (partial r))
$<3.1>

其中，时间向前差分的表示为：

$
  lr((partial T) / (partial t)|)_i = (T_i^(m+1) - T_i^m) / (Delta t) + O(Delta t)
$<3.2>

空间中心差分的表示为：

$
  lr((partial T) / (partial r)|)_i &= (T_(i+1) - T_(i-1)) / (2 Delta r) + O(Delta r) \
  lr((partial^2 T) / (partial r^2)|)_i &= (T_(i+1) + T_(i-1) - 2 T_i) / (Delta r^2) + O(Delta r^2)
$<3.3>

在传热过程中，涉及到三处边界条件：

- 陶瓷与反应物流
- 陶瓷与保温层
- 保温层与环境气流

简化模型，将所有边界传热视作拟稳态传热，以由内向外为传热方向，即有：

$
  q_1 =& h_1 (T_0 - T_"1w") &= k_1 lr((partial T_1) / (partial r)|)_(r = R_1) \
  q_2 =& k_1 lr((partial T_1) / (partial r)|)_(r = R_2) &= k_2 lr((partial T_2) / (partial r)|)_(r = R_2) \
  q_3 =& h_2 (T_"2w" - T_infinity) &= k_2 lr((partial T_2) / (partial r)|)_(r = R_3)
$<4>

== 解题思路

将圆管视作一层一层的同心环管构成，以半径均分为 $n$ 段，$Delta r = (R_3 - R_1) \/ n$，使用时间向前差分@3.2，空间中心差分@3.3 代入@3.1，舍去尾项，则有：

$
  alpha((T_(i+1)^m + T_(i-1)^m - 2 T_i^m) / (Delta r^2) + 1 / r_i (T_(i+1)^m-T_(i-1)^m) / (2 Delta r)) = (T_i^(m+1) - T_i^m) / (Delta t)
$<5>

其中 $i = 1, 2, 3, ..., n - 1$，$m = 0, 1, 2, 3, ...$，$r_i = R_1 + i Delta r$。

即对于一般情况下：

$
  T_i^(m+1) = T_i^m + alpha Delta t ((T_(i+1)^m + T_(i-1)^m - 2 T_i^m) / (Delta r^2) + 1 / r_i (T_(i+1)^m-T_(i-1)^m) / (2 Delta r))
$<6>

定解条件为：

$
  T_i^0 &= T_"init", &i = 1, 2, 3, ..., n - 1 \
  h_1 (T_0 - T_0^m) &= k_1 (T_0^m - T_1^m) / (Delta r), &m = 0, 1, 2, 3, ... \
  k_1 (T_(n \/ 3 -1)^m - T_(n \/ 3)^m) / (Delta r) &= k_2 (T_(n \/ 3)^m - T_(n \/ 3 + 1)^m) / (Delta r), &m = 0, 1, 2, 3, ... \
  h_2 (T_n^m - T_infinity) &= k_2 (T_(n-1)^m - T_n^m) / (Delta r), &m = 0, 1, 2, 3, ...
$<7>

式中 $n \/ 3$ 由 $R_1 = 0.05$、$R_2 = 0.075$ 和 $R_3 = 0.125$ 确定，$n \/ 3 = n * (R_2 - R_1) \/ (R_3 - R_1)$，即：

$
  T_i^0 = T_"init", i = 1, 2, 3, ..., n - 1
$<8>

$
  T_0^m &= (h_1 T_0 + k_1 T_1^m \/ Delta r) / (h_1 + k_1 \/ Delta r), &m = 0, 1, 2, 3, ... \
  T_(n \/ 3)^m &= (k_1 T_(n \/ 3 - 1)^m + k_2 T_(n \/ 3 + 1)^m) / (k_1 + k_2), &m = 0, 1, 2, 3, ... \
  T_n^m &= (h_2 T_infinity + k_2 T_(n-1)^m \/ Delta r) / (h_2 + k_2 \/ Delta r), &m = 0, 1, 2, 3, ...
$<9>

== 程序设计

将 $Delta r$ 段温度用 $T_i^m$ 表示，$m$ 为时间步数，$i$ 为分隔段端点数，$T_i^m$ 为第 $m$ 步第 $i$ 段的温度，用单个时间内的温度分布数组 $T$ 表示，$T_i^m$ 为 $T[i]$，使用 $T_i^0 = T_"init"$ 初始化，参考@8。

对于陶瓷与反应物流界面处温度 $T_0^m$，陶瓷与保温层界面处温度 $T_(n \/ 3)^m$ 和保温层与环境气流界面处温度 $T_n^m$，根据@9 给出如下计算公式，所有常数已预先定义：

- 计算陶瓷与反应物流界面处温度：

#codly(
  annotations: (
    (
      start: 1,
      end: 5,
      content: block(
        width: 2em,
        rotate(-90deg, align(center)[@9 .1]),
      ),
    ),
  ),
  annotation-format: none,
)

```py
def calc_first(_Ti: float, _dr: float) -> float:
  """
  _Ti: temperature of T[1]
  _dr: delta r
  """
  return (h1 * T_0 + k1 * _Ti / _dr) / (h1 + k1 / _dr)
```

- 计算陶瓷与保温层界面处温度：

#codly(
  annotations: (
    (
      start: 1,
      end: 5,
      content: block(
        width: 2em,
        rotate(-90deg, align(center)[@9 .2]),
      ),
    ),
  ),
  annotation-format: none,
)

```py
def calc_middle(_Tl: float, _Tr: float) -> float:
  """
  _Tl: temperature of T[i - 1]
  _Tr: temperature of T[i + 1]
  """
  return (_Tl * k1 + _Tr * k2) / (k1 + k2)
```

- 计算保温层与环境气流界面处温度：

#codly(
  annotations: (
    (
      start: 1,
      end: 5,
      content: block(
        width: 2em,
        rotate(-90deg, align(center)[@9 .3]),
      ),
    ),
  ),
  annotation-format: none,
)

```py
def calc_last(_Ti: float, _dr: float) -> float:
  """
  _Ti: temperature of T[n - 1]
  _dr: delta r
  """
  return (h2 * T_inf + k2 * _Ti / _dr) / (h2 + k2 / _dr)
```

根据@6，边界条件以外的温度计算公式如下，使用时根据位置区间选择热扩散系数 $alpha$：

#codly(
  annotations: (
    (
      start: 1,
      end: 11,
      content: block(
        width: 2em,
        rotate(-90deg, align(center)[@6]),
      ),
    ),
  ),
  annotation-format: none,
)

```py
def calc(_Tl: float, _Ti: float, _Tr: float, _dr: float, _alpha: float, _dt: float, _i: int) -> float:
  """
  _Tl: temperature of T[i - 1]
  _Ti: temperature of T[i]
  _Tr: temperature of T[i + 1]
  _dr: delta r
  _alpha: alpha
  _dt: delta t
  _i: ith point
  """
  ri_ = R1 + _i * _dr  # r of T[i]
  return _Ti + _alpha * _dt * ((_Tl + _Tr - 2 * _Ti) / _dr**2 + (1 / ri_) * (_Tr - _Tl) / (2 * _dr))
```

基于此，我们可以实现从 $t = m$ 到 $t = m + 1$ 的温度计算过程，除了三处边界外，每个点的温度都依赖于 $Delta t$ 前该点及该点前后的温度，单步迭代具体实现如下：

```py
def iter_once(_T: np.ndarray, _n: int, _dr: float, _dt: float, _bp: int) -> np.ndarray:
  """
  _T: temperature array, n + 1 nodes
  _n: number of segments, n + 1 nodes
  _dr: delta r
  _dt: delta t
  _bp: breakpoint n of R2
  """
  T_ = np.zeros(_n + 1, dtype=np.float64)
  T_[0] = calc_first(_T[1], _dr)
  for i in range(1, _bp):
    T_[i] = calc(_T[i - 1], _T[i], _T[i + 1], _dr, alpha1, _dt, i)
  T_[_bp] = calc_middle(_T[_bp - 1], _T[_bp + 1])
  for i in range(_bp + 1, _n):
    T_[i] = calc(_T[i - 1], _T[i], _T[i + 1], _dr, alpha2, _dt, i)
  T_[_n] = calc_last(_T[_n - 1], _dr)
  return T_
```

最后，可以实现整体迭代过程，直至温度收敛，收敛的判定为前向时间温度差的最大值小于截断误差 $epsilon$，即 $t = m + 1$ 时刻与 $t = m$ 时刻的温度数组的差数组中最大值小于截断误差 $epsilon$，具体实现如下：

```py
def do_iter(_n: int, _dt: float, _eps: float) -> np.ndarray:
  """
  _n: number of segments, n + 1 nodes
  _dt: delta t
  _eps: epsilon
  """
  T_ = np.full(_n + 1, T_init, dtype=np.float64)
  dr_ = (R3 - R1) / _n
  bp_ = _n // 3

  while True:
    T_new = iter_once(T_, _n, dr_, _dt, bp_)
    if np.max(np.abs(T_new - T_)) < _eps:
      break
    T_ = T_new
  return T_new
```

此外，由于 python 脚本运行时间较长且容易占内存，也提供了一份内存管理高效和运行极快的 cpp 的实现和编译结果，相关信息参加附件。

== 程序评估

最终得到在 $delta_2 = 0.05 upright(m)$（即 $R_3$ 为题目值）的情况下，$n$ 取 300，$Delta t$ 取 $0.01 upright(s)$，截断误差 $epsilon$ 取 $10^(-5) upright(K)$ 时运行效果较为合适，总运行时间 $tilde.op 1 "min"$，可以得到光滑的 $T-t-r$ 平面分布。

此外，我同时也提供了基于 cpp 的完整实现（见 `main.cpp`），并提供了编译程序 `main.exe`，可直接运行，运行效率显著高于 python 脚本，*在相同情况下可以在毫秒级完成近200w次收敛迭代，使用滚动数组，内存占用很小*，但由于 cpp 和 python 的舍入精度差异，理论上 python 的结果更为精确，累计误差更小。

由于每次温度计算时实际上只依赖于前 $Delta t$ 的该点温度及前一个点和后一个点的温度，因而程序具备很好的并行性，可以使用一维分隔的方式在多线程环境下进行计算，本程序未进行多线程优化和向量运算优化。

经多次调试，该代码在温度区间较小或半径区间较小时会显著增加计算时间，同时会出现不收敛或难收敛的情况，因此，推荐在适中的范围的取值使用，即 $n tilde.op 10^2$，$t tilde.op 10^(-2) upright(s)$ 且计算时间不大的情况下取得不错的效果。

默认情况下，我使用的截断温度误差为 $10^(-5)$，在题目情景中，温度的数量级为 $10^2 tilde.op 10^3$，二者量级相差 $10^8$，*故而最终结果可以认为达到稳态*，同时会出现需要迭代次数很大的情况，使用 python 脚本较为费时。

== 结果分析

=== 温度分布

温度分布与时间和半径的关系 $T-t-r$ 如下@fig:T_all 所示，包含反应器陶瓷的温度分布和保温层的温度分布，可以看到，整体的温度分布符合物理规律，温度分布较为合理，即反应物流温度较高，升温较快，保温层温度较低，总体温度分布较为平滑，符合预期：

#figure(
  image("_img/T_all.png", width: 70%),
  caption: [反应器温度分布 $T(t, r)$],
) <fig:T_all>

其中 R2 处和 R3 处（即保温层内表面处）温度随时间的分布如下@fig:T_t 所示，可以看到，温度随时间的变化较为平滑，且最终取向稳定值，说明体系达到稳态：

#figure(
  image("_img/T_t.png", width: 65%),
  caption: [R2 处温度随时间变化, R3 处温度随时间变化],
) <fig:T_t>

最终的温度分布 $T-r$ 如下@fig:T 所示，包含陶瓷和保温层两部分：

#figure(
  image("_img/T.png", width: 70%),
  caption: [反应器最终温度分布 $T(r)$],
) <fig:T>

=== 截断误差

结合截断误差，可以定义理论平衡时间为达到截断误差的时间，即达到截断误差收敛时的迭代次数与 $Delta t$ 时间划分的乘积。

在分析过程中，我注意到截断误差的选取对最终实验结果影响还是较大的，在文的温度分布的分析中，我选取的截断误差为 $10^(-5) upright(K)$，这个量级与平衡时的温度量级相差 $10^8$，在这个误差下，可以看到温度分布已经基本稳定（稳定时间曲线趋于水平），作为对比，下图选取了截断误差为 $10^(-2) upright(K)$ 的计算结果，显然，在截断误差为 $10^(-2) upright(K)$ 时最终系统并没有达到较好的平衡效果。虽然截断误差精细的情况下可以取得比较好的效果，但迭代次数和理论平衡时间也会显著增加，可以预见，在更小的截断误差下，温度分布会更加平滑，但是计算时间会显著增加，因此在实际应用中，需要根据实际情况选择合适的截断误差。

#figure(
  image("_img/T_all_2.png", width: 55%),
  caption: [反应器温度分布 $T(t, r)$，截断误差为 $10^(-2) upright(K)$],
) <fig:T_all2>

此时 R2 处和 R3 处（即保温层内表面处）温度随时间的分布如下@fig:T_t2 所示，可以看到，在这时候最外侧的温度几乎没受到内部影响，维持在 300K 左右：

#figure(
  image("_img/T_t_2.png", width: 60%),
  caption: [R2 处温度随时间变化, R3 处温度随时间变化 截断误差为 $10^(-2) upright(K)$],
) <fig:T_t2>

最终的温度分布 $T-r$ 如下@fig:T2 所示，包含陶瓷和保温层两部分，可以明显看到，此时系统的温度分布还呈现出较大的波动，说明系统还未达到稳态：

#figure(
  image("_img/T_2.png", width: 60%),
  caption: [反应器最终温度分布 $T(r)$ 截断误差为 $10^(-2) upright(K)$],
) <fig:T2>

同时，除了截断误差的选择外，其他数值的选取也会影响最终的结果，即 $Delta t$ 的选取和 $n \/ Delta r$ 的选取，实际上，在传热过程中，$Delta t$ 和 $Delta r$ 存在隐式依赖关系，在 $Delta t$ 或 $Delta r$ 其中一个较小的情况下，除了会显著增加计算时间外，也会导致计算结果不稳定，容易出现精度溢出或是无法收敛的情况。

=== 保温层厚度

最后，我讨论了保温层厚度对于保温效果的影响，对于保温层厚度为一般值的情况，修改关键参数 $delta_2$，可以得到 $R_3$ 不同时的最终温度分布图如下：

#figure(
  image("_img/T_r.png", width: 80%),
  caption: [不同 $delta 2$ 下 $T(r)$ 最终图像],
) <fig:T_r>

定义保温效果 $eta$ 为陶瓷界面两端的温度与环境温度之差的比值：

$
  eta = ((T["bp"] - T_infinity) \/ (T_0 - T_infinity)) / ((T[0] - T_infinity) \/ (T_0 - T_infinity)) = (T["bp"] - T_infinity) / (T[0] - T_infinity)
$<12>

$eta$ 越接近 1，说明保温效果越好。

我计算了 $delta_2 = 0.03 upright(m)$ 和 $0.3 upright(m)$ 的 $eta$ 值（最终温度如上图所示），并统计了达到此保温效果的平衡时间，结果如下表所示：

#let data_eta = csv("assets/data_eta.csv")

#figure(
  table(
    columns: 3,
    stroke: none,
    table.hline(),
    table.header(
      [保温层厚度 $delta_2 \/ upright(m)$],
      [保温效果 $eta$],
      [平衡时间 $"time"\/ upright(s)$],
    ),
    table.hline(stroke: 0.5pt),

    ..data_eta.flatten(),

    table.hline(),
  ),
  caption: [不同 $delta 2$ 下的保温效果 $eta$],
) <table:eta>

即保温层厚度从 0.03m 提高一个量级到 0.3m 后，保温效果只从 0.94 提高到了 0.98，在相同平衡时间内则是从 0.94 到 0.96，提升效果微弱。

通过分析可以得知，在稳态条件下体系的温度分布满足如下的规律：

$
  partial / (partial r) (r (partial T) / (partial r)) = 0
$<10>

该方程的通解为：

$
  T = A + B ln r
$<11>

换言之，从理论上讲，单位半径对保温效果提升的贡献会越来越小，这也与得到的结果相符。

根据@table:eta 和@11，可以看出，保温效果与保温层厚度存在正相关性，保温层越厚，保温效果越好，但同时达到平衡的时间也更长，这也与物理常识相符，但由于温度分布呈线性关系，因而保温效果的增长并不是线性的，而是逐渐减小的，可以预见在保温层较厚时，虽然仍有保温效果，但保温效果的变化并不显著，受于计算时间的限制，我们未能计算更大或更小的保温层厚度，但此规律应当是普适的。可以见得，在相同的保温时间的情况下，保温层厚度大的情况实际上有相当的一部分外层保温材料是对保温没有贡献的，因此在实际应用中，需要根据实际情况选择合适的保温层厚度。

== 结论

结合 $T-t-r$ 图像，可以看出，在 $t tilde.op 1 "min"$ 内，温度分布已经收敛，反应器的温度就可以维持在较高的温度区间，本程序的实现是合理的，数值分析过程较为成功。

温度随时间和半径的分布由@fig:T_all 给出（包含陶瓷和保温层两部分），整体图像成楔形状。对于单个点的温度，温度随时间的变化最终会趋向一个稳定值，即达到稳态，其中保温层内表面 R2 和 R3 温度随时间的变化由@fig:T_t 给出；而对于某一时刻的温度分布，同样由@fig:T_all 给出，其中，在时间较小时，温度分布主要在陶瓷部分显著下降，随着时间的推进，陶瓷部分的温度趋于平缓，温度变化主要发生在保温层区域，最终近稳态的温度分布由@fig:T 给出。

最后，通过分析不同保温层厚度 $delta_2$ 情况下的温度分布，可以得到整体的保温效果 $eta$ 随着保温层厚度的增加而增加，但增加的幅度逐渐减小，在厚度较大时这中变化就不显著了，且在保温一定时间的情况下，较厚的保温层中会有一部分外层区域无法对保温做出贡献。

总体数值模拟结果与理论和物理常识相符，分析过程较为合理，程序实现较为成功。

== 附录

=== 最小代码实现

最小程序完整实现（python）如下：

```py
# main.py
import numpy as np

R1 = 0.025  # m
R2 = 0.050  # m
R3 = 0.100  # m

rho1 = 2600  # kg/m^3
cp1 = 1150  # J/kg-K
k1 = 3.0  # W/m-K

alpha1 = k1 / (rho1 * cp1)  # m^2/s

rho2 = 600  # kg/m^3
cp2 = 200  # J/kg-K
k2 = 0.2  # W/m-K

alpha2 = k2 / (rho2 * cp2)  # m^2/s

T_init = 300  # K
T_0 = 1500  # K
T_inf = 298  # K

h1 = 500  # W/m^2-K
h2 = 10  # W/m^2-K

def calc_first(_Ti: float, _dr: float) -> float:
  return (h1 * T_0 + k1 * _Ti / _dr) / (h1 + k1 / _dr)

def calc(_Tl: float, _Ti: float, _Tr: float, _dr: float, _alpha: float, _dt: float, _i: int) -> float:
  ri_ = R1 + _i * _dr  # r of T[i]
  return _Ti + _alpha * _dt * ((_Tl + _Tr - 2 * _Ti) / _dr**2 + (1 / ri_) * (_Tr - _Tl) / (2 * _dr) - _Ti / ri_**2)

def calc_middle(_Tl: float, _Tr: float) -> float:
  return (_Tl * k1 + _Tr * k2) / (k1 + k2)

def calc_last(_Ti: float, _dr: float) -> float:
  return (h2 * T_inf + k2 * _Ti / _dr) / (h2 + k2 / _dr)

def iter_once(_T: np.ndarray, _n: int, _dr: float, _dt: float, _bp: int) -> np.ndarray:
  T_ = np.zeros(_n + 1, dtype=np.float64)
  T_[0] = calc_first(_T[1], _dr)
  for i in range(1, _bp):
    T_[i] = calc(_T[i - 1], _T[i], _T[i + 1], _dr, alpha1, _dt, i)
  T_[_bp] = calc_middle(_T[_bp - 1], _T[_bp + 1])
  for i in range(_bp + 1, _n):
    T_[i] = calc(_T[i - 1], _T[i], _T[i + 1], _dr, alpha2, _dt, i)
  T_[_n] = calc_last(_T[_n - 1], _dr)
  return T_

def do_iter(_n: int, _dt: float, _eps: float) -> np.ndarray:
  T_ = np.full(_n + 1, T_init, dtype=np.float64)
  dr_ = (R3 - R1) / _n
  bp_ = _n // 3

  while True:
    T_new = iter_once(T_, _n, dr_, _dt, bp_)
    if np.max(np.abs(T_new - T_)) < _eps:
      break
    T_ = T_new
  return T_new

# example usage
T = do_iter(300, 1e-2, 1e-2)
print(T)
```

运行 `python main.py` 即可得到结果（依赖 numpy 包），包含绘图，优化和 cpp 实现的更多程序设计内容参考附件。

#pagebreak()

=== 补充数据

#let get_d2_fi = d2 => {
  figure(
    image("_img/T_d2_" + d2 + ".png", width: auto),
    caption: [$delta_2 = #d2 upright(m)$],
    numbering: none,
  )
}

#let data_d2s_1 = (
  "0.030",
  "0.300",
)

#figure(
  grid(
    columns: 2,
    gutter: 1em,

    ..data_d2s_1.map(get_d2_fi),
  ),
  caption: [组图 不同 $delta 2$ 下的最终温度分布 1],
) <fig:T_rs1>

== 附件信息

#figure(
  table(
    columns: (1fr, 1fr, 3fr),
    stroke: none,
    table.hline(),
    table.header(
      [],
      [描述],
      [备注],
    ),
    table.hline(stroke: 0.5pt),

    [report.pdf], [最终报告], [即本文件],
    [main.py], [最小 python 实现], [运行依赖 numpy 和 python 环境],
    [main.ipynb], [jupyter notebook], [包含数据分析和绘图相关代码，运行依赖 numpy、jupyter、matplotlib 和 python 环境],
    [main.cpp], [cpp 实现], [可自行编译],
    [main.exe], [cpp 编译结果], [命令行，可直接运行，数值求解的核心程序],

    [\_img\/], [图片文件夹], [存放图片文件],
    [assets\/], [资源文件夹], [存放保存的数据，csv 格式，部分数据可能未囊括在内，数据可通过 `np.loadtxt` 加载],
    table.hline(),
  ),
  caption: [附件信息],
)

除构建产物外，可以在#underline(link("https://github.com/chillcicada/MySchoolwork/tree/main/src/TransportFinal")[此处])访问本大作业的完整源代码。
