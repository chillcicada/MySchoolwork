#set math.equation(numbering: "(1)")

_>hint: all the equations are based on Gaussian Units System_

Old condition: $f_"-" = f_+ = f, theta dash.en "solution"$

New confition: $f_"-" eq.not f_+ ("in the real case that" f_"-" = 1 > f_+), theta dash.en "solution"$

$
  e Z_"net" = e (N_"-" f_"-" - N_+ f_+) \
  Delta N = N_"-" - N_+ \
$

Here the $e Z_"net"$ is the net charge, $N_"-"$ and $N_+$ are the number of the negative charged and positive charged monomers, $f_"-"$ and $f_+$ are the fraction of the negative charged and positive charged monomers, $e$ is the elementary (negative) charge.

== High Charge Asymmetry

_*Assumption1*_: All Charges under Mean Distribution both negative area and positive area when the polyelectrolyte elongated.

_>hint: If the influence of external charge distribution is not considered, the uniform distribution is the state with the lowest energy, and the actual distribution may be a distribution function with slightly higher ends and slightly lower middle._

$
  cases(
    (e^2 f^2 g_"el"^2) / (epsilon xi_"el") approx k_B T \
    xi_"el" = b g_"el"^(1 / 2)
  ) => cases(
    xi_"el" = b (u f^2)^(-1 / 3) \
    g_"el" = (u f^2)^(-2 / 3)
  )
$

Here $u equiv l_B / b, l_B = e^2 / (epsilon k_B T)$ and the $l_B$ is Bjerrum length, $b$ is the Kuhn length. For the positive and negative charges, we have two blobs $f_"-" dash.en xi_"el-" dash.en g_"el-"$ and $f_+ dash.en xi_"el+" dash.en g_"el+"$.

Then we get:

$
  F_"polyel" / (k_B T) &approx N_+ / g_"el+" + N_"-" / g_"el-" \
  &approx N_+ (u f_+^2)^(2 / 3) + N_"-" (u f_"-"^2)^(2 / 3) \
$

== Charge-Symmetric Case

i.e. $Z_"net" = 0, N_"-"f_"-" = N_+ f_+$

Since different blobs have different sizes, which results in different piling patterns, but this error can be neglected so we ignore it.

$
  R_"gl"^3 &= N_+ dot xi_+^3 / g_+ + N_"-" dot xi_"-"^3 / g_"-" \
  R_"gl" &= b(N_+(u f_+^2)^(-1 / 3) + N_"-" (u f_"-"^2)^(-1 / 3))^(1 / 3) \
$

Then:

$
  F_"gl" &= - (N_+ / g_+ + N_"-" / g_"-") \
  &approx - (N_+ (u f_+^2)^(2 / 3) + N_"-" (u f_"-"^2)^(2 / 3)) \
$

_*Assumption2*_: All Charges under Mean Distribution on the surface, then we get:

$
  F_"surf" / (k_B T) &approx R_"gl"^2 / (1 / 2(xi_+^2 + xi_"-"^2)) \
  &approx 2 (N_+ (u f_+^2)^(-1 / 3) + N_"-" (u f_"-"^2)^(-1 / 3))^(2 / 3) / ((u f_+^2)^(-2 / 3)+(u f_"-"^2)^(-2 / 3))
$

// TODO: meed more detail!

$
  b N_"neutr" approx min(xi_+, xi_"-") => N_"neutr" approx (u f_+^2)^(-2 / 3) \
$

== Intermediate Charge Asymmetry

The number of positive and negative charge monomers and the fraction of charged groups can both cause this situation, but here we only discuss the latter.

i.e. $f_"-" > f_+, N_"-" = N_+ = N_(1 / 2)$

_*Assumption3*_: the tail is all with the nevative charge

for the conservation of electric charge:

$
  Z_"net" = Z_"head" + Z_"tail" \
$

Use $N_"-"^'$ as the nevative blob number in the head, then:

$
  Z_"head" = N_"-"^' f_"-" - N_+ f_+ \
  Z_"tail" = (N_"-" - N_"-"^') f_"-" \
$

In the below we use the $N_"-"^'$ as the number of the negative charged monomers in the head, and the $N_"-" - N_"-"^'$ as the number of the negative charged monomers in the tail.

$
  xi approx xi_"el" => g approx g_"el"
$

This condition for the partitioning of monomers between the head and the tail of the tadpole can be rewritten in terms of the reduced electrostatic potentials of the head and of the tail.

$
  (e Z_"head") / R_"head" = (e Z_"tail") / R_"tail" \
$

_> hint: the electrostatic potential need more refinement_

For the head, since the $Delta N << N$, we have: $R_"gl" approx R_"head"$, notice that the right-hand side of the equation (10) is proportional to the linear charge density of the tail $(g_"el" f_"-") / xi_"el" tilde (xi_"el" f_"-") / b^2 tilde f_"-" (u f_"-"^2)^(-1 / 3) / b$

Then we have:

$
  Z_"head" &approx R_"gl" / b f_"-" (u f_"-"^2)^(-1 / 3) \
  &approx (N_+(u f_+^2)^(-1 / 3) + N_"-"^' (u f_"-"^2)^(-1 / 3))^(1 / 3) f_"-" (u f_"-"^2)^(-1 / 3) \
  &approx N f_+ (N_"neutr" / N)^(2 / 3) 2^(-1 / 3) (k + k^(-2 / 3))^(1 / 3) \
$

Here $k equiv f_"-" / f_+$.

$
  R_"tail" approx b Delta N (u f^2)^(1 / 3)
$

The critical situation is that the head is amost neutral, i.e. $Z_"head" approx 0$, use the equation (4) and (5), then we have:

$
  Delta N = 1 / f_"-" Z_"net"
$

here the $Delta N$ is $N_"-" - N_"-"^'$ (accoding to the Assumption3), then use the equation above we get:

$
  R_"tail" = b / f_"-" Z_"net" (u f_"-"^2)^(1 / 3)
$

When the $R_"head" approx R_"tail"$, we have:

$
  Z_"tadpole" approx N f_+ (N_"neutr" / N)^(2 / 3) 2^(-1 / 3) (k + k^(-2 / 3))^(1 / 3) \
$

which is the same as the $Z_"head"$ (equation 13), here $k equiv f_"-" / f_+$, when $f_"-" = 1$, then we have:

$
  Z_"tadpole" |_(f_"-" = 1) = N (N_"neutr" / N)^(1 / 3) 2^(-1 / 3) (f_+ + f_+^(2 / 3))^(1 / 3) f_+ \
$

and the electrostatic energy of the tail is:

$
  F_"el"^"tail" / (k_B T) &approx (l_B Z_"tail"^2) / R_"tial" \
  &approx Z_"net" / f_"-" (u f_"-"^2)^(2 / 3)
$

For the $Z_"unimer"$, the surface energy of the head (equation 6, note that we should take the $N_"-"^'$) and the electrostatic energy of tail (equation 15) are equal, then we have:

$
  Z_"unimer" = N f_+ (N_"neutr" / N)^(1 / 3) 2^(1 / 3) k (1+k^(-5 / 3))^(2 / 3) / (1+k^(4 / 3)) \
$

Here $k equiv f_"-" / f_+$, when $f_"-" = 1$, then we have:

$
  Z_"unimer" |_(f_"-" = 1) = N (N_"neutr" / N)^(1 / 3) 2^(1 / 3) (1 + f_+^(5 / 3))^(2 / 3) / (1+f_+^(-4 / 3)) \
$

// The figure of $2^(-1 / 3) (f_+ + f_+^(2 / 3))^(1 / 3) f_+$ and $2^(1 / 3) (1 + f_+^(5 / 3))^(2 / 3) / (1+f_+^(-4 / 3))$ is below:

// == Appendix

// At the same time, we assume another extreme case of Intermediate Charge Asymmetry.

// _*Assumption1'*_: In the area with positive charge, a portion of the charge is polarized towards the end close to the negative charge (and the $f_+^' = f_"-"$), while the other end remains uncharged.

// For the uncharged area, since it's $theta dash.en "solution"$ we have:

// $
//   R_"gl" = xi_T (N / g_T)^(1 / 3) \
// $

// For the $xi$ for the positive and negative charges and uncharged can be regarded as constants for a given polyelectrolyte and solvent, then we have:

// $
//   (dif F_"surf") / (dif R_"gl") approx 2 R_"gl" / "const" > 0 \
// $
