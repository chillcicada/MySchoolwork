# -*- coding: utf-8 -*-

# chapter3_4
from multiprocessing import Pool, cpu_count
from random import random

# we will use cpu count sub 1 to run the monte carlo simulation
use_cpu_count = cpu_count() - 2


def compute_pi(times: int) -> int:
  count = 0
  for _ in range(times):
    x, y = random(), random()
    if x**2 + y**2 < 1:
      count += 1
  return count


def monte_carlo_pi(times: int, processes=use_cpu_count) -> float:
  pool = Pool(processes)
  counts = pool.map(compute_pi, [times] * processes)
  pool.close()
  pool.join()
  count = sum(counts)
  return 4 * count / times / processes


if __name__ == '__main__':
  times = 100
  print(monte_carlo_pi(times))
