# -*- coding: utf-8 -*-
from random import randint
from itertools import product
from copy import copy
from typing import List

# 复用第二题的 mock 函数
from .chapter5_2 import mock


def gen(n=4) -> List[int]:
  """生成器"""
  return [randint(1, 11) for _ in range(n)]


def calcRPN(tks) -> int | float | None:
  """逆波兰表达式求值"""
  lg = len(tks)
  stk = copy(tks)
  tmp = 2
  while lg > 1:
    if stk[tmp] in ('+', '-', '*', '/'):
      stk[tmp] = mock(stk[tmp - 2], stk[tmp - 1], stk[tmp])
      stk.pop(tmp - 1)
      stk.pop(tmp - 2)
      tmp -= 1
      lg -= 2
      pass
    else:
      tmp += 1
    pass
  return stk[0]


def genRPNs(nums):
  """生成逆波兰表达式"""
  ops = list(product(['+', '-', '*', '/'], repeat=3))

  res = []

  def mergeList(lt1, lt2):
    """
    考虑到列表大小较小，这里直接穷举所有逆波兰表达式的符号排列可能

    以 lt1 = [a, b, c, d], lt2 = [+, -, *] 为例，共五种结合顺序：
      - [a, b, c, d, +, -, *] —— ((ab)c)d
      - [a, b, c, +, d, -, *] —— (a(bc))d
      - [a, b, c, +, -, d, *] —— a((bc)d)
      - [a, b, +, c, d, -, *] —— (ab)(cd)
      - [a, b, +, c, -, d, *] —— a(b(cd))
    """
    return [
      lt1 + lt2,
      lt1[:3] + lt2[0:1] + lt1[3:] + lt2[1:],
      lt1[:3] + lt2[0:2] + lt1[3:] + lt2[2:],
      lt1[:2] + lt2[0:1] + lt1[2:] + lt2[1:],
      lt1[:2] + lt2[0:1] + lt1[2:3] + lt2[1:2] + lt1[3:] + lt2[2:],
    ]

  for op in ops:
    res.extend(mergeList(nums, list(op)))
  return res


def judge24(nums):
  """判断是否能组合成 24"""
  for item in genRPNs(nums):
    tmp = calcRPN(item)
    if tmp is not None and abs(tmp - 24) < 1e-6:
      return (True, item)
  return False


def main() -> None:
  """主函数"""
  for _ in range(10):
    nums = gen()
    print(nums, judge24(nums))
    pass
  return
