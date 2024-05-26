# -*- coding: utf-8 -*-
# Path: utils/__tests__/itp_test.py

import numpy as np

from utils.itp import lagrange as lag


# for common types
def test_lagrange():
  X = [0, 1, 2, 3]
  y = [0, 1, 8, 27]
  x_raw = 1.5
  assert lag(X, y, x_raw) == 3.375


test_lagrange()


# for numpy types
def test_lagrange_np():
  X = np.array([0, 1, 2, 3])
  y = np.array([0, 1, 8, 27])
  x_raw = 1.5
  assert lag(X, y, x_raw) == 3.375


test_lagrange_np()
