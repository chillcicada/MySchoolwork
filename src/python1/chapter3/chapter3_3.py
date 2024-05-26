# -*- coding: utf-8 -*-

# chapter3_3
def C(n: int, m: int) -> int:
  if n < m or m < 0:
    return 0

  return C(n - 1, m - 1) + C(n - 1, m) if m > 0 else 1
