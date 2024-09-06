# -*- coding: utf-8 -*-
from random import randint
from typing import List

from src.log import warn

MIN = 0
MAX = 99

Methods = {
  '+': lambda a, b: a + b,
  '-': lambda a, b: a - b,
  '×': lambda a, b: a * b,
  '÷': lambda a, b: a // b,
}
MethodsEnum = [key for key in Methods.keys()]


def check(num: int | None) -> bool:
  """
  Check if an integer is within the range of MIN(0) to MAX(99).

  :param num: The number to check.
  :return: True if the number is within the range of MIN(0) to MAX(99), False otherwise.
  """
  if num is None:
    return False
  return num >= MIN and num <= MAX


def rand(n=1, min=MIN, max=MAX) -> int | List[int]:
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

  def __init__(self, a: int | None = None, b: int | None = None, method: str | None = None, quiet=True) -> None:
    self.a = a if a is not None and check(a) else rand()
    self.b = b if b is not None and check(b) else rand()

    self.quiet = quiet

    self.recv = None
    self.isSubmitted = False
    self.isCorrect = False  # True if the result is correct, False otherwise and default is False

    self.method = method if method in MethodsEnum else self.setMethod()
    self.result = self.setResult()
    pass

  def __str__(self) -> str:
    common = f'{self.a:>2} {self.method} {self.b:>2}'

    if self.isCorrect:
      return f'{common} = {self.result:>2} (✓)'
    elif self.isSubmitted:
      return f'{common} = {self.result:>2} (recv: {self.recv})'
    elif self.recv is not None:
      return f'{common} = {self.recv:>2}'
    else:
      return f'{common} = ??'

  def __eq__(self, other) -> bool:
    return self.a == other.a and self.b == other.b and self.method == other.method

  def __hash__(self) -> int:
    return hash((self.a, self.b, self.method))

  def __call__(self) -> str:
    return str(self)

  def setMethod(self) -> str:
    return MethodsEnum[randint(0, 3)]

  def setResult(self) -> None:
    try:
      result = Methods[self.method](self.a, self.b)
      if not check(result):
        if not self.quiet:
          warn(f'Invalid result: {result}, IssueItem reset.')
          pass
        result = None
        pass
    except ZeroDivisionError:
      result = None
      pass
    if self.method == '÷':
      while True:
        if self.a > self.b and check(result) and self.b != 0 and self.a % self.b == 0:  # type: ignore
          break
        self.a = rand()
        self.b = rand(min=1)
        pass
      result = Methods['÷'](self.a, self.b)
    while not check(result):
      self.a, self.b = rand(2)  # type: ignore
      result = Methods[self.method](self.a, self.b)
    return result

  def check(self) -> bool:
    return self.result == self.recv

  def setRecv(self, recv: int) -> None:
    self.recv = recv
    return

  def submit(self) -> None:
    if self.recv is not None:
      self.isSubmitted = True
      self.isCorrect = self.check()
    return

  pass


class IssuesGenerator:
  """
  A class to generate issues.
  """

  def __init__(self, n=10) -> None:
    self.len = n
    self.issues = self.init(n)

    self.isCompleted = False
    return

  def __len__(self) -> int:
    return self.len

  def __getitem__(self, index: int) -> IssueItem:
    return self.issues[index]

  def __iter__(self):
    for issue in self.issues:
      yield issue
    pass

  def init(self, n: int) -> List[IssueItem]:
    """
    This generator will generate issues and deputing them from the list.
    """

    temp = 0
    lt = []

    while temp < n:
      issue = IssueItem()
      if issue not in lt:
        lt.append(issue)
        temp += 1
      pass

    return lt

  def checkSubmit(self) -> None:
    self.isCompleted = all([issue.isSubmitted for issue in self.issues])
    return

  def __call__(self) -> List[str]:
    return [issue() for issue in self.issues]

  def getScores(self) -> int:
    return sum([1 for issue in self.issues if issue.isCorrect])

  pass
