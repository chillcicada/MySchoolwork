from chapter1.chapter1_3 import factorial


def test_factorial():
  assert factorial(0) == 1
  assert factorial(1) == 1
  assert factorial(2) == 2
  assert factorial(3) == 6
  assert factorial(4) == 24
  assert factorial(5) == 120
  assert factorial(6) == 720
  assert factorial(7) == 5040
  assert factorial(8) == 40320
  assert factorial(9) == 362880
  assert factorial(10) == 3628800
  pass
