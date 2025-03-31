from concurrent.futures import ProcessPoolExecutor
from multiprocessing import cpu_count
from typing import Tuple

import numpy as np


def restore_subchain(sub_coords: np.ndarray, box_size, r_cut=0, initial_shift=None) -> Tuple[np.ndarray, np.ndarray]:
  """
  处理子链并返回调整后的坐标及累计平移次数

  参数:
  sub_coords (np.ndarray): 子链坐标数组
  box_size (float/list): 周期盒子尺寸
  r_cut (float): 截断半径，默认为0
  initial_shift (np.ndarray): 初始平移次数，默认为0

  返回:
  tuple: (调整后的坐标, 累计平移次数)
  """
  adjusted_coords = np.zeros_like(sub_coords)
  adjusted_coords[0] = sub_coords[0]

  # set box size [Lx, Ly, Lz]
  if isinstance(box_size, (int, float)):
    L = np.array([box_size] * 3)
  else:
    L = np.array(box_size)

  # set initial shift [shift_x, shift_y, shift_z], default is [0, 0, 0]
  shift = initial_shift.copy() if initial_shift is not None else np.zeros(3, dtype=int)

  for i in range(1, len(sub_coords)):
    for d in range(3):
      prev = adjusted_coords[i - 1, d]
      curr = sub_coords[i, d]
      delta = curr - prev
      threshold = (L[d] - r_cut) / 2

      if delta > threshold:
        shift[d] -= 1
      elif delta < -threshold:
        shift[d] += 1
      adjusted_coords[i, d] = curr + shift[d] * L[d]

  return adjusted_coords, shift


def parallel_restore(coords: np.ndarray, box_size, r_cut=0, n_workers=4):
  """
  并行还原高分子链

  参数:
  coords (np.ndarray): 原始坐标数组
  box_size (float/list): 周期盒子尺寸
  r_cut (float): 截断半径，默认为0
  n_workers (int): 并行子链数

  返回:
  np.ndarray: 调整后的连续坐标
  """
  # 分割为子链（此处均匀分割，可根据需求优化）
  subchains = np.array_split(coords, n_workers)
  n_sub = len(subchains)

  # 并行处理子链（初始平移次数为0）
  with ProcessPoolExecutor(max_workers=n_workers) as executor:
    futures = [executor.submit(restore_subchain, sub, box_size, r_cut) for sub in subchains]
    results = [f.result() for f in futures]

  # 提取调整后的子链和平移次数
  adjusted_subs = [res[0] for res in results]

  # 计算全局平移修正
  global_shifts = [np.zeros(3, dtype=int)]
  for i in range(1, n_sub):
    # 获取相邻子链的衔接坐标
    prev_end = adjusted_subs[i - 1][-1]
    curr_start_raw = subchains[i][0]

    # 计算初始修正
    delta = curr_start_raw - prev_end
    shift_correction = np.zeros(3, dtype=int)
    for d in range(3):
      Ld = box_size[d] if isinstance(box_size, list) else box_size
      threshold = Ld / 2
      if delta[d] > threshold:
        shift_correction[d] = -1
      elif delta[d] < -threshold:
        shift_correction[d] = 1

    # 累计修正
    global_shifts.append(global_shifts[i - 1] + shift_correction)

  # 应用全局修正到各子链
  adjusted = []
  for i in range(n_sub):
    # 计算实际修正量
    actual_shift = global_shifts[i]
    # 调整子链坐标
    adjusted_sub = adjusted_subs[i] + actual_shift * (
      box_size if isinstance(box_size, (int, float)) else np.array(box_size)
    )
    adjusted.append(adjusted_sub)

  # 合并结果
  return np.concatenate(adjusted)


class ChainRestore:
  def __init__(self, box_size, r_cut=0, n_workers=None):
    self.r_cut = r_cut
    self.n_workers = n_workers or cpu_count()
    self.L = np.array(box_size) if isinstance(box_size, list) else np.array([box_size] * 3)

  def set_topology(self, length: int, topology: str):
    pass

  def split_subchains(self, coords):
    pass

  def restore_subchain(self, sub_coords: np.ndarray, r_cut=0, initial_shift=None) -> Tuple[np.ndarray, np.ndarray]:
    """
    处理子链并返回调整后的坐标及累计平移次数

    参数:
    sub_coords (np.ndarray): 子链坐标数组
    box_size (float/list): 周期盒子尺寸
    r_cut (float): 截断半径，默认为0
    initial_shift (np.ndarray): 初始平移次数，默认为0

    返回:
    tuple: (调整后的坐标, 累计平移次数)
    """
    adjusted_coords = np.zeros_like(sub_coords)
    adjusted_coords[0] = sub_coords[0]

    # set initial shift [shift_x, shift_y, shift_z], default is [0, 0, 0]
    shift = initial_shift.copy() if initial_shift is not None else np.zeros(3, dtype=int)

    for i in range(1, len(sub_coords)):
      for d in range(3):
        prev = adjusted_coords[i - 1, d]
        curr = sub_coords[i, d]
        delta = curr - prev
        threshold = (self.L[d] - r_cut) / 2

        if delta > threshold:
          shift[d] -= 1
        elif delta < -threshold:
          shift[d] += 1
        adjusted_coords[i, d] = curr + shift[d] * self.L[d]

    return adjusted_coords, shift

  def restore(self, coords):
    return parallel_restore(coords, self.box_size, self.r_cut, self.n_workers)


# 示例测试
# if __name__ == '__main__':
#   # 测试数据：L=10的立方体，连续跨越边界
#   coords = np.array([[9, 0, 0], [0, 0, 0], [9, 0, 0], [0, 0, 0], [9, 0, 0], [0, 0, 0], [9, 0, 0], [0, 0, 0]])
#   L = 10

#   # 并行处理（分为2个子链）
#   restored = parallel_restore(coords, L, n_workers=2)
#   print('连续调整后的坐标：\n', restored)
