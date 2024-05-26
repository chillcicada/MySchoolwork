# -*- coding: utf-8 -*-

# chapter1_3

from functools import lru_cache


@lru_cache(maxsize=None)
def factorial(n: int) -> int:
  """
  use function tool `lru_cache` as a cache mechanism to speed the recursion

  :param n: an integer to calc its factorial
  :return: the factorial of `n`
  """
  return 1 if n == 0 else factorial(n - 1) * n
