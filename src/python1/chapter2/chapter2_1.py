# -*- coding: utf-8 -*-

# chapter2_1


def daffodils(x):
  return x == sum([int(i) ** 3 for i in str(x)])


def slv2_1():
  for i in range(100, 1000):
    if daffodils(i):
      print(i)
