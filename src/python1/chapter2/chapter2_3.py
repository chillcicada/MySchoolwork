# -*- coding: utf-8 -*-

# chapter2_3
GREEN, YELLOW, BLUE, END = '\033[92m', '\033[93m', '\033[94m', '\033[0m'


def formatOutput(i, j):
  return f'{BLUE}{i}*{j}{YELLOW}={GREEN}{i * j :>2}{END}'


def slv2_3():
  for i in range(1, 10):
    for j in range(1, i + 1):
      print(formatOutput(j, i), end=' ')
    print()
