# -*- coding: utf-8 -*-

# chapter1_2
# data inherited from `chapter1_1`

# below is the old part of `chapter1_1.py`
# region chapter1_1
(principalRaw, rateRaw) = input('Type two numbers as `principal rate`:').split()

principal, rate = float(principalRaw), float(rateRaw)

newPrincipal = principal * (1 + rate)
# endregion
# below is the new part of `chapter1_2.py`

PrincipalDumpOnce = newPrincipal * (1 + rate)
PrincipalDumpTwice = PrincipalDumpOnce * (1 + rate)

print(f'The principal plus interest dumped one year is: {PrincipalDumpOnce:.2f}')
print(f'The principal plus interest dumped two years is: {PrincipalDumpTwice:.2f}')
