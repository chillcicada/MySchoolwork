#set page(margin: (x: 1em, y: 1em), height: auto, width: 6in)

Gibbs 吸附等温式如下：

$
  Gamma = - 1 / (R T) ((diff gamma) / (diff ln alpha))_T approx^(alpha = c) - 1 / (R T) ((diff gamma) / (diff ln c))_T
$

式中 Gamma 为溶质的(相对)表面吸附量，gamma 为溶液的表面张力，alpha 为活度，c 为溶质的浓度(活度系数为1的活度值)，R 为气体常数，T 为温度。

Langmuir 吸附等温式在溶液表面吸附过程的推广：

$
  Gamma = Gamma_oo (K c) / (1 + K c)
$

式中 $Gamma_oo$ 为溶质的最大表面吸附量，K 为一常数，c 为溶质的浓度。

数据处理部分用到的公式如下：

$
  \
  K = gamma_"water" / (Delta P_"water") ==> gamma = (Delta P) / K ==> gamma_1, gamma_2, dots.c , gamma_n \
  Z = - c (diff gamma) / (diff c) ==> gamma = Z c ==> Z_1, Z_2, dots.c , Z_n \
  Gamma = Z / (R T) ==> Gamma_1, Gamma_2, dots.c , Gamma_n ==> c_1 / Gamma_1, c_2 / Gamma_2, dots.c, c_n / Gamma_n \
  c / Gamma - c ==> Gamma_oo \
$

溶质分子表面积的计算：

$
  q = 1 / (N_A Gamma_oo)
$
