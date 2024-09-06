# -*- coding: utf-8 -*-
from os import path


class FS:
  def __init__(self) -> None:
    self.TARGET_FILE = path.join(path.dirname(__file__), 'record.txt')
    return

  def load(self) -> str:
    if path.exists(self.TARGET_FILE):
      with open(self.TARGET_FILE, 'r') as f:
        data = f.read()
        pass
      pass
      return data
    return ''

  def save(self, data: str) -> None:
    with open(self.TARGET_FILE, 'w') as f:
      f.write(data)
      pass
    return

  def clear(self) -> None:
    if path.exists(self.TARGET_FILE):
      with open(self.TARGET_FILE, 'w') as f:
        f.write('')
        pass
      pass
    return

  pass
