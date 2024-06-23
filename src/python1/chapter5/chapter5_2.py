# -*- coding: utf-8 -*-
def mock(a: int | float | None, b: int | float | None, op: str) -> int | float | None:
  """模拟运算"""
  if a is None or b is None:
    return None

  if op == '+':
    return a + b
  if op == '-':
    return a - b
  if op == '*':
    return a * b
  if op == '/':
    if b == 0:
      return None
    return a / b

  return None


def calc(raw: str) -> int | float:
  nums = []
  ops = []

  priority = {'+': 1, '-': 1, '*': 2, '/': 2}

  for token in raw.split():
    if token.isdigit():
      nums.append(int(token))
      pass
    else:
      while ops and priority[ops[-1]] >= priority[token]:
        nums.append(mock(nums.pop(-2), nums.pop(), ops.pop()))
        pass
      ops.append(token)
      pass

    pass

  opsLen = len(ops)

  while opsLen:
    opsLen -= 1
    nums.append(mock(nums.pop(-2), nums.pop(), ops.pop()))
    pass

  return nums[0]


def calc_2(raw: str) -> int | float:
  nums = []
  ops = []

  priority = {'+': 1, '-': 1, '*': 2, '/': 2}

  temp = 0

  for char in raw:
    if char.isdigit():
      temp = temp * 10 + int(char)
      pass
    elif char in priority:
      nums.append(temp)
      temp = 0
      while ops and priority[ops[-1]] >= priority[char]:
        nums.append(mock(nums.pop(-2), nums.pop(), ops.pop()))
        pass
      ops.append(char)
      pass
    pass

  nums.append(temp)

  opsLen = len(ops)

  while opsLen:
    opsLen -= 1
    nums.append(mock(nums.pop(-2), nums.pop(), ops.pop()))
    pass

  return nums[0]


def main():
  raw = input()
  print('input: ', raw)
  print(calc(raw))
  return
