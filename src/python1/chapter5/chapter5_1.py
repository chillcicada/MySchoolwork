# -*- coding: utf-8 -*-
from re import findall


def filter_chars(string: str) -> str:
  return ''.join(findall(r'[a-zA-Z]', string))


def main() -> None:
  raw = input()
  print('input: ', raw)
  print(filter_chars(raw))
  return
