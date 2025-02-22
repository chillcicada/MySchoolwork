# 生活中的传递现象3

北方城镇的很多建筑物的窗户是双层的，即窗户上装两层玻璃且中间留有一定空隙，两层厚度为d的玻璃夹着一层厚度为 l 的空气，根据常识这样做是为了保暖，减少室内向室外的热量流失，下面建立一个模型来描述热量通过窗户的传导（即流失）过程，并将双层玻璃窗与用同样多材料做成的单层玻璃窗（玻璃厚度为2d）的热量传导进行对比，对双层玻璃窗能够减少多少热量损失给出定量分析。

## 假设与推理

1. 热量的传递过程只有传导，没有对流；
2. 空内温度 T1 和空外温度 T2 保持不变，热传导过程是稳态传热；
3. 玻璃材料均匀，热传导系数是常数。

在考虑热传导问题时，我们通常遵循**傅立叶基本定律**。对于一个厚度为 `d` 的均匀介质，其热传导系数为 `α`，当两侧存在温度差 `Δt` 时，单位时间内通过单位面积的热量 `q` 可以通过以下公式计算：

\[ q = \frac{\alpha \Delta t}{d} \]

其中 `α` 是热传导系数。

### 双层玻璃窗的热流密度分析

考虑一个双层玻璃窗，其内层和外层玻璃的热传导系数分别为 `α1` 和 `α2`。设内层玻璃的外层温度为 `Ta`，外层玻璃的内层温度为 `Tb`。那么，单位时间单位面积的热流密度可表示为：

\[ q_1 = \frac{\alpha_1 (T_1 - Ta)}{d} = \frac{\alpha_2 (Ta - Tb)}{l} = \frac{\alpha_1 (Tb - T_2)}{d} \]

通过消去 `Ta` 和 `Tb`，我们可以得到：

\[ q_1 = \frac{\alpha_1 (T_1 - Ta)}{d(s+2)} \]

其中：

\[ s = h \frac{\alpha_1}{\alpha_2}, \quad h = \frac{l}{d} \]

### 单层玻璃窗的热量传导

对于厚度为 `2d` 的单层玻璃窗，其热量传导为：

\[ q_2 = \frac{\alpha_1 (T_1 - T_2)}{2d} \]

### 双层与单层玻璃窗的比较

二者的比值为：

\[ \frac{q_1}{q_2} = \frac{2}{s+2} \]

显然 `q_1 < q_2`，这表明双层玻璃窗的热量损失更小。

考虑到玻璃和空气的热传导系数，我们有：

- 常用玻璃的热传导系数 $α1 = 4 \times 10^{-3} \text{ to } 8 \times 10^{-3} \mathbf{J/cm·s·km·h}$
- 不流通、干燥空气的热传导系数 $α2 = 2.5 \times 10^{-4} \mathbf{J/cm·s·km·h}$

因此：

\[ \frac{\alpha_1}{\alpha_2} = 16 \text{ to } 32 \]

在最保守的估计下，即取 `α1/α2 = 16`，我们得到：

\[ \frac{q_1}{q_2} = \frac{1}{8h+1} \]

这表明双层玻璃窗在减少热量损失上的功效只与 `h = l/d` 有关。根据建筑规范，`h = 4` 时，双层窗户比单层窗节约的热量约为 `97%` 左右。

## 结论

双层玻璃窗虽然制作工艺复杂、成本较高，但其在减少热量损失方面的效果显著，主要得益于窗户间空气的极低热传导系数 `α2`。
