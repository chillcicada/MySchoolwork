# -*- coding: utf-8 -*-

# chapter3_2
from chapter3_1 import subNN

if __name__ == '__main__':
  N = 100000

  dt = {}

  for i in range(1, N):
    dt[subNN(i)] = dt.get(subNN(i), 0) + 1
    pass

  print(dt)
  pass
