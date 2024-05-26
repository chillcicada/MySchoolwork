# -*- coding: utf-8 -*-

import numpy as np
from utils.clock import clocked


@clocked
def Jacobi(_A, _x, _b, epsilon, max_iter=100000):
  """
  Solves the system of linear equations using Jacobi's method.
  :param _A: matrix of coefficients
  :param _b: vector of results
  :param max_iter: maximum number of iterations
  :param epsilon: error tolerance
  :return: solution vector and number of iterations
  """
  n = len(_b)
  _x_ = np.copy(_x)
  for _iter in range(max_iter):
    x_new = np.zeros(n)
    for i in range(n):
      s1 = np.dot(_A[i, :i], _x_[:i])
      s2 = np.dot(_A[i, i + 1 :], _x_[i + 1 :])
      x_new[i] = (_b[i] - s1 - s2) / _A[i, i]
    if np.linalg.norm(x_new - _x_) < epsilon:
      return x_new, _iter
    _x_ = np.copy(x_new)
  raise ValueError('Jacobi method did not converge')


@clocked
def GaussSeidel(_A, _x, _b, epsilon, max_iter=100000):
  """
  Solves the system of linear equations using Gauss-Seidel's method.
  :param _A: matrix of coefficients
  :param _b: vector of results
  :param max_iter: maximum number of iterations
  :param epsilon: error tolerance
  :return: solution vector and number of iterations
  """
  n = len(_b)
  _x_ = np.copy(_x)
  for _iter in range(max_iter):
    for i in range(n):
      s1 = np.dot(_A[i, :i], _x_[:i])
      s2 = np.dot(_A[i, i + 1 :], _x_[i + 1 :])
      _x_[i] = (_b[i] - s1 - s2) / _A[i, i]
    if np.linalg.norm(np.dot(_A, _x_) - _b) < epsilon:
      return _x_, _iter
  raise ValueError('Gauss-Seidel method did not converge')
