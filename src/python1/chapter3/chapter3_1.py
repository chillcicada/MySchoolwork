# -*- coding: utf-8 -*-

# chapter3_1
def subN(n):
  return sum(map(int, str(n)))


def subNN(n):
  return n if n < 10 else subNN(subN(n))
