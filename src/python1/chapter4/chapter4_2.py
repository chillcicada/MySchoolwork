# -*- coding: utf-8 -*-
def getDay(yy: int, mm: int, dd=1) -> int:
  """获得某年某月的某天是星期几，默认第一天，使用基姆拉尔森计算公式"""
  if mm == 1 or mm == 2:
    mm += 12
    yy -= 1
    pass
  return (yy + (yy // 4) - (yy // 100) + (yy // 400) + (3 * (mm + 1) // 5) + 2 * mm + dd + 1) % 7


def getDays(yy: int, mm: int) -> int:
  months = [[31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31], [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]]
  return months[(lambda y: (y % 4 == 0 and y % 100 != 0) or y % 400 == 0)(yy)][mm - 1]


def printMonth(yy: int, mm: int, target=None):
  firstDay = getDay(yy, mm)
  days = getDays(yy, mm)

  usePrint = print if not target else lambda *args, **kwargs: print(*args, **kwargs, file=target)

  usePrint(f'{" " * 7}{yy} 年 {mm} 月')
  usePrint('=' * 27)
  usePrint('Sun Mon Tue Wed Thu Fri Sat')

  usePrint(' ' * 4 * firstDay, end='')

  for i in range(1, days + 1):
    usePrint(f'{i:3} ', end='')
    if (i + firstDay) % 7 == 0:
      usePrint()
      pass
    pass

  usePrint()
  usePrint('=' * 27)
  usePrint()
  pass


def printYear(yy: int, target=None):
  for i in range(1, 13):
    printMonth(yy, i, target)
    pass
  pass
