# -*- coding: utf-8 -*-
def YN2Bool(yn: str) -> bool:
  """
  Convert a string to a boolean.

  :param yn: The string to convert.
  :return: True if the string is 'Y' or 'y', False otherwise.
  """
  return yn.lower().strip() == 'y' or yn.strip() == ''


def parseInput(s: str) -> int | None:
  """
  Parse a string to an integer.

  :param s: The string to parse.
  :return: The integer if the string is a valid integer, None otherwise.
  """
  return int(s) if s.strip().isdigit() else None
