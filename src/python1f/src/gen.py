# -*- coding: utf-8 -*-

from random import randint
from typing import Any

MIN = 0
MAX = 99

methods = {
  '+': lambda a, b: a + b,
  '-': lambda a, b: a - b,
  '×': lambda a, b: a * b,
  '÷': lambda a, b: a // b,
}
methodsEnum = [key for key in methods.keys()]


def check(num: int) -> bool:
  """
  Check if an integer is within the range of MIN(0) to MAX(99).

  :param num: The number to check.
  :return: True if the number is within the range of MIN(0) to MAX(99), False otherwise.
  """
  return num >= MIN and num <= MAX


def rand(n=1, min=MIN, max=MAX) -> int:
  """
  A wrapper of the randint function.

  :param n: the times for randint.
  :param min: min for randint.
  :param max: max for randint.
  :return: A number if n is equal to 1, or return a number list
  """
  return randint(min, max) if n == 1 else [randint(min, max) for _ in range(n)]


class IssueItem:
  """
  A class to generate an issue item.
  """

  def __init__(self, a: int = None, b: int = None) -> None:
    self.a = a if a and check(a) else rand()
    self.b = b if b and check(b) else rand()

    self.recv = None
    self.isSubmitted = False
    self.isCorrect = False  # True if the result is correct, False otherwise and default is False

    self.setMethod()
    self.setResult()
    pass

  def __str__(self) -> str:
    common = f'{self.a:>2} {self.method} {self.b:>2}'

    if self.isSubmitted:
      return f'{common} = {self.result:>2} (recv: {self.recv})'
    elif self.recv:
      return f'{common} = {self.recv:>2}'
    else:
      return f'{common} = ??'

  def __eq__(self, other) -> bool:
    return self.a == other.a and self.b == other.b and self.method == other.method

  def __hash__(self) -> int:
    return hash((self.a, self.b, self.method))

  def __call__(self, *args: Any, **kwds: Any) -> Any:
    return self.__str__()

  def setMethod(self) -> None:
    self.method = methodsEnum[randint(0, 3)]
    pass

  def setResult(self) -> None:
    result = methods[self.method](self.a, self.b)
    if self.method == '÷':
      while not (self.a > self.b and check(result) and self.b != 0 and self.a % self.b == 0):
        self.a, self.b = rand(2)
        result = methods['÷'](self.a, self.b)
    while not check(result):
      self.a, self.b = rand(2)
      result = methods[self.method](self.a, self.b)
    self.result = result
    pass

  def check(self) -> bool:
    return self.result == self.recv

  def setRecv(self, recv: int) -> None:
    self.recv = recv
    pass

  def submit(self) -> None:
    if self.recv:
      self.isSubmitted = True
      self.isCorrect = self.check()
    pass


class IssuesGenerator:
  """
  A class to generate issues.
  """

  def __init__(self, n=10) -> None:
    self.len = n
    self.issues = [IssueItem() for _ in range(n)]

    self.isCompleted = False
    pass

  def __len__(self) -> int:
    return self.len

  def __iter__(self):
    return iter(self.issues)

  def __getitem__(self, index: int) -> IssueItem:
    return self.issues[index]

  def __next__(self) -> IssueItem:
    if self.isCompleted:
      raise StopIteration
    return self.issues.pop(0)

  def __call__(self, *args: Any, **kwds: Any) -> Any:
    # return
    pass

  def generate(self, n: int) -> None:
    """
    This generator will generate issues and deputing them from the list.
    """

    temp = 0

    while temp < n:
      issue = IssueItem()
      if issue not in self.issues:
        self.issues.append(issue)
        temp += 1
      pass

    pass

  def check(self) -> bool:
    return all([issue.check() for issue in self.issues])
