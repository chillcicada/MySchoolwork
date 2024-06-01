# -*- coding: utf-8 -*-
from .chapter4_2 import printMonth, printYear


def printMonth2File(yy: int, mm: int, filename):
  with open(filename, 'w', encoding='utf-8') as f:
    printMonth(yy, mm, target=f)
    pass
  pass


def printYear2File(yy: int, filename):
  with open(filename, 'w', encoding='utf-8') as f:
    printYear(yy, target=f)
    pass
  pass
