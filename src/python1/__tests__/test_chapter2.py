from chapter2.chapter2_1 import daffodils
from chapter2.chapter2_3 import formatOutput


def test_daffodils():
  assert daffodils(153)
  assert not daffodils(154)
  pass


def test_formatOutput():
  assert formatOutput(1, 1) == '\033[94m1*1\033[93m=\033[92m 1\033[0m'
  assert formatOutput(1, 2).__len__() == 25
  pass
