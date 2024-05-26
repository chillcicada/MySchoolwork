from chapter3.chapter3_1 import subN, subNN
from chapter3.chapter3_3 import C


def test_subN():
  assert subN(123) == 6
  assert subN(1234) == 10
  assert subN(12345) == 15
  assert subN(123456) == 21
  assert subN(1234567) == 28
  assert subN(12345678) == 36
  assert subN(123456789) == 45
  pass


def test_subNN():
  assert subNN(123) == 6
  assert subNN(1234) == 1
  assert subNN(12345) == 6
  assert subNN(123456) == 3
  assert subNN(1234567) == 1
  assert subNN(12345678) == 9
  assert subNN(123456789) == 9
  pass


def test_C():
  assert C(5, -1) == 0

  assert C(5, 0) == 1
  assert C(5, 1) == 5
  assert C(5, 2) == 10
  assert C(5, 3) == 10
  assert C(5, 4) == 5
  assert C(5, 5) == 1

  assert C(5, 6) == 0
  pass
