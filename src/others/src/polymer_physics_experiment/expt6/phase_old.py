import os

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.svm import SVC

current_dir = os.path.dirname(os.path.abspath(__file__))
data_file = os.path.join(current_dir, 'expt6-data/phase.xlsx')

df = pd.read_excel(data_file, sheet_name=0, header=None)

N = 10
chiN = df.iloc[1:, 0].to_numpy() * N

f_A = df.iloc[0, 1:].to_numpy()

phase = df.iloc[1:, 1:]

le = LabelEncoder()
y = le.fit_transform(phase.values.flatten())

scaler = StandardScaler()
X_scaled = scaler.fit_transform(f_A, chiN)

model = SVC(kernel='rbf', C=1.0, gamma=0.5)
model.fit(X_scaled, y)

# 生成密集网格点
x_min, x_max = X_scaled[:, 0].min() - 1, X_scaled[:, 0].max() + 1
y_min, y_max = X_scaled[:, 1].min() - 1, X_scaled[:, 1].max() + 1
xx, yy = np.meshgrid(np.linspace(x_min, x_max, 1000), np.linspace(y_min, y_max, 1000))
grid = np.c_[xx.ravel(), yy.ravel()]

# 预测网格点相态
Z = model.predict(grid)
Z = Z.reshape(xx.shape)
# 将网格坐标还原到原始尺度
xx_orig = scaler.inverse_transform(np.c_[xx.ravel(), yy.ravel()])[:, 0].reshape(xx.shape)
yy_orig = scaler.inverse_transform(np.c_[xx.ravel(), yy.ravel()])[:, 1].reshape(yy.shape)
# 绘制相图

plt.figure(figsize=(10, 8))
plt.contourf(xx_orig, yy_orig, Z, alpha=0.3, cmap='viridis')
