# -*- coding: utf-8 -*-

# chapter1_1
(principalRaw, rateRaw) = input('Type two numbers as `principal rate`:').split()

principal, rate = float(principalRaw), float(rateRaw)

newPrincipal = principal * (1 + rate)
print(f'The principal plus interest is: {newPrincipal:.2f}')
