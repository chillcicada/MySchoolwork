# -*- coding: utf-8 -*-
from .chapter4_2 import getDay, getDays
from typing import List


def parseMonth(yy: int, mm: int) -> List[str]:
  firstDay = getDay(yy, mm)
  days = getDays(yy, mm)

  res = ''.join([f'{i:3}\n' if (i + firstDay) % 7 == 0 else f'{i:3} ' for i in range(1, days + 1)]).split('\n')

  res[0] = res[0].rjust(27)
  if res[-1].strip() == '':
    res.pop()
    pass
  else:
    res[-1] = res[-1].ljust(27)
    pass
  return res


def printSeason(yy: int, ss: int, target=None, ch='=='):
  """水平打印一个季度"""
  length = len(ch)
  ch_blank = ' ' * length

  months = [[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]]

  usePrint = print if not target else lambda *args, **kwargs: print(*args, **kwargs, file=target)

  usePrint(f'{" " * (length + 34)}{yy} 年第 {ss} 季度')
  usePrint(ch.join(['=' * 27 for _ in range(3)]))

  usePrint(ch_blank.join([f'{" " * 7}{yy:4} 年 {mm:2} 月{" " * 7}' for mm in months[ss - 1]]))
  usePrint(ch_blank.join(['=' * 27 for _ in range(3)]))
  usePrint(ch_blank.join(['Sun Mon Tue Wed Thu Fri Sat' for _ in range(3)]))

  monthsParsed = [parseMonth(yy, mm) for mm in months[ss - 1]]

  height = max([len(m) for m in monthsParsed])

  for i in range(height):
    for j in range(3):
      usePrint(monthsParsed[j][i] if i < len(monthsParsed[j]) else ' ' * 27, end=ch_blank)
      pass
    usePrint()
    pass

  usePrint(ch.join(['=' * 27 for _ in range(3)]))
  usePrint()
  pass


def printYearWithSeasons(yy: int, target=None, ch='=='):
  """水平打印一年的四个季度"""
  for i in range(1, 5):
    printSeason(yy, i, target, ch)
    pass
  pass


def printSeason2File(yy: int, ss: int, filename: str, ch='=='):
  with open(filename, 'w', encoding='utf-8') as f:
    printSeason(yy, ss, target=f, ch=ch)
    pass
  pass


def printYearWithSeasons2File(yy: int, filename: str, ch='=='):
  with open(filename, 'w', encoding='utf-8') as f:
    printYearWithSeasons(yy, target=f, ch=ch)
    pass
  pass
