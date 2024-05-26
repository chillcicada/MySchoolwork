# -*- coding: utf-8 -*-


def lagrange(_X, _y, _x_raw):
  """
  Interpolates the value of _x_raw using Lagrange's method.
  see examples in `__tests__/itp_test.py`
  :param _X: list of x values
  :param _y: list of y values
  :param _x_raw: value to interpolate
  :return: interpolated value
  """
  n = len(_X)
  result = 0
  for i in range(n):
    term = _y[i]
    for j in range(n):
      if i != j:
        term = term * (_x_raw - _X[j]) / (_X[i] - _X[j])
    result += term
  return result
