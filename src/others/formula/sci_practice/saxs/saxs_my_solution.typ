#set page(height: auto, width: auto, margin: 1em)

高 $q$ 区域的拟合，采用了以下公式：

$
  I(q)_"high q" = I_0 1 / q ((2 "j1"(q r_p)) / (q r_p))^2 + S_"inc", q > 0.16
$

式中 $I_0$ 为强度，$r_p$ 为半径，$"j1"$ 为第一类球贝塞尔函数，$S_"inc"$ 为常数。

第二部分引入了结构因子 $S(q)$：

$
  I(q)_"fit" = P(q) S(q) = k I(q)_"high q" / (1 + beta exp(-q^2 xi^2) I(q)_"high q"), q > 0.08
$

式中 $k$ 为常数，$beta$ 为常数，$xi$ 为常数。

第三部分引入了幂律项：

$
  I(q) = P(q) S(q) + I_"pow" = I(q)_"fit" + I_"pow"
$

其中，式中 $k$ 为常数，$m$ 为常数。

$
  I_"pow" = k q^(m)
$

上述模型对于低浓度，净电荷比例高的样品较为适用。
