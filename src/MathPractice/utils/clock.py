# -*- coding: utf-8 -*-

import time


def clocked(func):
  def clock(*args, **kwargs):
    start = time.time()
    result = func(*args, **kwargs)
    end = time.time()
    print(f'Function {func.__name__} executed in {end - start} seconds')
    return result

  return clock
