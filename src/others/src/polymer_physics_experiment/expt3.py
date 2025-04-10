"""
Experiment 3: SALS

@author: Liu Kuan
@date: 2025-04-10
"""

import numpy as np

point = np.array([184, 213])

center = np.array([200, 200])

d = np.linalg.norm(point - center)
d_real = d / 200 * 50.45  # mm
L = 300.1  # mm
lambda_ = 780e-9  # m

theta = np.arctan(d_real / L)

R = 4.09 * lambda_ / np.sin(theta / 2) / 4 / np.pi
print(R)
