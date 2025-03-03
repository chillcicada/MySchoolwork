#import "@preview/cuti:0.3.0": show-cn-fakebold

#show: show-cn-fakebold
#set page(paper: "a4", margin: 1.27cm)
#set text(lang: "zh", region: "cn")

= 聚合物成型加工作业 - 第一周

#align(center)[
  刘宽 ~ 2022013189 ~ 探微分21
]

== 题 1

#figure(image("hw1/coaxial_tube.png", width: 40%), caption: "同轴管隙库特流")

建立柱坐标系，由题意可知，该流动为*同轴管隙库特流*，满足流动方程：

$
  cases(
    1 / R (partial u_theta) / (partial theta) = 0,
    u_theta^2 / R = 1 / rho (partial p) / (partial r),
    1 / (rho R) (partial p) / (partial theta) = nu [1 /R partial / (partial R) (R (partial u_theta) / partial R) - u_theta / R^2] = 0,
    (partial p) / (partial z) = 0 => p = f(r)
  )
$

化简得：

$
  (dif^2 u_theta) / (dif R^2) + (dif u_theta) / (R dif R) - u_theta / R^2 = 0
$

其通解形式为：

$
  u_theta = C_1 R + C_2 / R
$

式中 $u_theta$ 为流体的切向速度，$R$ 为径向距离，$C_1$ 和 $C_2$ 为积分常数。

代入边界条件 $R = R_1$ 处 $u_theta = omega R_1$ 和 $R = R_2$ 处 $u_theta = 0$ 得：

$
  cases(
    C_1 R_1 + C_2 / R_1 = omega R_1,
    C_1 R_2 + C_2 / R_2 = 0
  ) =>
  cases(
    C_1 = - (omega R_1^2) / (R_2^2 - R_1^2),
    C_2 = (omega R_1^2 R_2^2) / (R_2^2 - R_1^2)
  )
$

从而有：

$
  u_theta = - (omega R_1^2) / (R_2^2 - R_1^2) R + (omega R_1^2 R_2^2) / (R_2^2 - R_1^2) dot 1 / R
$

由 $omega_R = u_theta \/ R$ 得：

$
  omega_R = - (omega R_1^2) / (R_2^2 - R_1^2) + (omega R_1^2 R_2^2) / (R_2^2 - R_1^2) dot 1 / R^2
$

同心圆流场中，$dif R$ 处的剪切形变 $dif gamma$ 为：

$
  dif gamma = (dif s) / (dif R)
$

代入 $dif s = (R + dif R)(omega_R + dif omega_R) dif t - (R + dif R) omega_R dif t$ 和 $dot(gamma) := dif gamma \/ dif t$，舍去高阶无穷小项得：

$
  dot(gamma) = R (dif omega_R) / (dif R)
$

得剪切速率为：

$
  dot(gamma) = - (2 omega R_1^2 R_2^2) / (R_2^2 - R_1^2) dot 1 / R^2
$

#align(center, line(length: 80%, stroke: .2pt))

思维链：

+ 同心圆流场中，剪切速率 $dot(gamma)$ 计算公式为 $dot(gamma) = r dif omega \/ dif r$，因而需要知道角速度 $omega$ 与 $r$ 的关系，而 $omega$ 又与切向速率 $u_theta$ 存在比值关系；
+ 而该情景为同轴管隙库特流，可以通过流动方程求解得到切向速度 $u_theta$ 的通解形式，其只与 $r$ 有关，进一步可以得到 $omega$ 与 $r$ 的关系；
+ 代入 $dot(gamma) = r dif omega \/ dif r$ 即可得到剪切速率 $dot(gamma)$ 的表达式。

== 题 2

#figure(image("hw1/linear_bingham_plastic.png", width: 40%), caption: "线性宾汉塑性流体")

以轴心建立柱坐标系，设圆柱的内半径为 $R$，不考虑屈服应力和滑移。

根据宾汉塑性流体性质，推测在中轴段的流体不发生相对流动，取轴心上 $r$ 为半径长度为 $d$ 的一小段流体进行分析，其在流动方向上有：

$
  (dif p) / (dif z) dot pi r^2 d = tau dot 2 pi r d
$

从而有：

$
  tau = (dif p) / (dif z) r / 2, r = (2 tau) / (dif p\/dif z)
$

由宾汉流体的临界剪切应力为 $tau_y$，得到临界半径 $r_c$ 为：

$
  r_c = (2 tau_y) / (dif p\/dif z)
$

即在 $r <= r_c$ 时，流体不发生相对流动，而在 $r > r_c$ 时，流体存在相对流动。

若 $R <= r_c$，则流体整体不发生相对流动，即整个圆柱内的流体都是静止的，此时流体剪切速率为 0，流速为 0。

若 $R > r_c$，则在 $r_c < r < R$ 段内，流体存在相对流动，此时在流动方向上有：

$
  (dif p) / (dif z) dot pi r^2 d = tau_r dot 2 pi r d
$

从而：

$
  tau_r = (dif p) / (dif z) r / 2, r > r_c
$

由 $tau = tau_y + eta dot(gamma)$ 得剪切速率 $dot(gamma)$ 为：

$
  dot(gamma) = (tau - tau_y) / eta = 1 / eta ((dif p) / (dif z) r / 2 - tau_y) , r > r_c
$

由 $dot(gamma) = - dif v_r \/ dif r$，得：

$
  dif v_r = - 1 / eta ((dif p) / (dif z) r / 2 - tau_y) dif r
$

从 $r_c$ 到 $R$ 积分，代入 $r = R$ 时 $v_r = 0$ 得：

$
  v_r = 1 / eta ((dif p) / (dif z) (R^2 - r^2) / 4 - tau_y (R - r)), r > r_c
$

从而，流体在圆柱内的流速分布为：

$
  v_r = cases(
    1 / eta ((dif p) / (dif z) (R - r_c)^2 / 4)\, r <= r_c,
    1 / eta ((dif p) / (dif z) (R^2 - r^2) / 4 - tau_y (R - r))\, r > r_c
  )
$

综上，若 $R <= (2 tau_y) / (dif p\/dif z)$，此时流体剪切速率为 0，流速为 0；若 $R > (2 tau_y) / (dif p\/dif z)$，则流体剪切速率为：

$
  dot(gamma) = cases(
    0\, r <= (2 tau_y) / (dif p\/dif z),
    1 / eta ((dif p) / (dif z) r / 2 - tau_y)\, r > (2 tau_y) / (dif p\/dif z)
  )
$

流体流速为：

$
  v_r = cases(
    1 / eta ((dif p) / (dif z) (R - (2 tau_y) / (dif p\/dif z))^2 / 4)\, r <= (2 tau_y) / (dif p\/dif z),
    1 / eta ((dif p) / (dif z) (R^2 - r^2) / 4 - tau_y (R - r))\, r > (2 tau_y) / (dif p\/dif z)
  )
$

#align(center, line(length: 80%, stroke: .2pt))

思维链：

+ 首先根据宾汉塑性流体性质，推测在中轴段的流体不发生相对流动，取轴心上 $r$ 为半径长度为 $d$ 的一小段流体进行分析，根据平衡得到不存在相对流动的临界半径；
+ 越过临界半径后，同样根据平衡得到剪切应力的表达式，进一步根据宾汉塑性流体性质得到剪切速率 $dot(gamma)$ 的表达式；
+ 由 $dot(gamma) = - dif v_r \/ dif r$ 得到流速 $v_r$ 的表达式，进而用积分得到流体在圆柱内的流速分布。

== 题 3

由题意得，半径 $R = 0.01 "m"$，体积流量 $Q = Q_"mass" \/ rho = 0.000125 "m"^3\/"s"$。

从而，毛细管管壁处牛顿流体的剪切速率为：

$
  dot(gamma)_(w, "newtonian") = (4 Q) / (pi R^3) = 159 "s"^(-1)
$

由测量到的 $dot(gamma)$ 和 $tau_w$，使用幂律定律的对数形式 $ln(tau_w) = n ln(dot(gamma)) + ln(K)$ 拟合 $n$ 和 $K$，其中 $n$ 为非牛顿流体指数，$K$ 为稠度系数，拟合图像如下图所示。

#figure(image("hw1/non-newton_index.png", width: 40%), caption: "非牛顿流体指数")

根据拟合结果，得到 $n = 0.5$，$K = 3162 "Pa" dot "s"^0.5$，其中拟合系数 $R^2 = 1.0000$。

从而，校正非牛顿流体的真实剪切速率 $dot(gamma)_(w, "non-newtonian")$ 为：

$
  dot(gamma)_(w, "non-newtonian") = (3 n + 1) / (4 n) dot(gamma)_(w, "newtonian") = 199 "s"^(-1)
$

代入幂律对数得校正后的剪切应力 $tau_(w, "non-newtonian")$ 为：

$
  tau_(w, "non-newtonian") = K dot(gamma)_(w, "non-newtonian")^n = 4.46 times 10^4 "Pa"
$

从而真实粘度 $eta$ 为：

$
  eta = tau_(w, "non-newtonian") / dot(gamma)_(w, "non-newtonian") = 224 "Pa" dot "s"
$

#align(center, line(length: 80%, stroke: .2pt))

思维链：

+ 根据题目提供的已知信息，先把数据转化为毛细管流变仪的测量原理计算中需要的数据，即半径 $R$ 和体积流量 $Q$；
+ 进一步可以计算对牛顿流体时毛细管管壁处的剪切速率 $dot(gamma)_(w, "newtonian")$；
+ 题目提供了等比数列的剪切速率下的剪切应力，可以使用幂律定律的对数形式拟合非牛顿流体指数 $n$ 和稠度系数 $K$；
+ 有了非牛顿因子后就可以得到校正后的非牛顿流体的真实剪切速率，进一步得到校正后的剪切应力；
+ 最后根据剪切应力和剪切速率的比值得到真实粘度。

== 问卷调研

+ 你对什么聚合物成型加工问题最感兴趣？

  目前只对聚合物成型加工的知识有一些皮毛的理解，按照我的理解，聚合物成型加工本质上是给高分子塑性，涉及高分子的流变学和加工工艺，现在只讲了流变学，我很疑惑*流变学和流体力学乃至传递过程原理的关系是怎么样的？*具体的说，我注意到课程上讲的一些情景和课后题目都与传递过程原理的内容有一定的相似性，比如圆管内的稳态层流，但二者在解题思路上有很大的不同，传递过程原理里面使用的主要是 N-S 方程和连续性方程，流变学里面用剪切力相关概念和受力平衡来描述情景，可以得到相近的答案。

+ 你目前在做的研究训练或SRT，是否有和成型加工相关的内容（含流变学、配方设计和混合分散、材料（可以不是聚合物材料）的成型等）？

  本学期暂无相关内容，上学期的科学训练有涉及用流变仪器测量聚电解质溶液表观粘度来表征聚电解质溶液状态。

+ 关于本课程，你希望在课外每周投入几个小时？（计划）

  计划是每周10小时左右，但第一周现投入时长已经大大超过了10小时，未来可能视内容辅以增加。

+ 对本课程，你希望最后达到的学习目标是什么？

  掌握理论知识，能够较为熟练运用到实际问题中，比如解决一些工程问题，或者对一些实验数据进行分析。

+ 对于本课程的教学，你有什么建议？

  - PPT 上很多物理量的出现都不加说明，或者在后面出现定义，有些定义不鲜明，导致理解上有困难，希望这种情况可以得到改善；

  - 希望可以强化 PPT 公式排版，好几页 PPT 的物理量字母变来变去，理解上加了不必要的负担；

  - 希望讲课的时候能多一些原理和推导的内容。
