# -*- coding: utf-8 -*-

# chapter2_2.py


def investment(init, rate, years):
  final_value = init * (1 + rate) ** years
  return final_value


init = float(input())

for i in range(1, 31):
  final = investment(init, i / 100, 20)

print(final)
