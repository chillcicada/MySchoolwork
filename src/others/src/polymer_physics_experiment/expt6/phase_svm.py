import os

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.colors import ListedColormap
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.svm import SVC

current_dir = os.path.dirname(os.path.abspath(__file__))

output_dir = os.path.join(current_dir, 'expt6-results')
os.makedirs(output_dir, exist_ok=True)

# 数据集
rows = [
    (0, ['-', '-', '-', '-', '-']),
    (1.53, ['-', '-', '-', '-', '-']),
    (3.06, ['-', 'C', 'L', 'C', '-']),
    (4.59, ['S', 'C', 'L', 'C', 'S']),
    (6.12, ['S', 'G', 'L', 'G', 'S']),
    (7.65, ['S', 'G', 'G', 'G', 'S']),
    (9.17, ['S', 'G', 'G', 'G', 'S']),
    (10.7, ['S', 'G', 'G', 'G', 'S']),
]
x_values = [0.1125, 0.3, 0.5, 0.7, 0.8875]

data = []
for y, labels in rows:
    for x, label in zip(x_values, labels):
        data.append([x, y, label])

# 转换为特征和标签
X = np.array([[d[0], d[1]] for d in data])
y = np.array([d[2] for d in data])

# 标签编码
le = LabelEncoder()
y_encoded = le.fit_transform(y)

# 特征标准化
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# 训练SVM模型
model = SVC(kernel='rbf', C=1.0, gamma=0.5, class_weight='balanced')
model.fit(X_scaled, y_encoded)

# 生成网格数据
x_min, x_max = X[:, 0].min() - 0.1, X[:, 0].max() + 0.1
y_min, y_max = X[:, 1].min() - 0.5, X[:, 1].max() + 0.5
xx, yy = np.meshgrid(np.linspace(x_min, x_max, 500), np.linspace(y_min, y_max, 500))

# 预测网格点类别
Z = model.predict(scaler.transform(np.c_[xx.ravel(), yy.ravel()]))
Z = Z.reshape(xx.shape)

# 定义颜色和标签
classes = le.classes_
colors = ['white', 'red', 'green', 'blue', 'purple']  # 对应 '-', 'C', 'G', 'L', 'S'
cmap = ListedColormap(colors)

# 绘制相图
plt.figure(figsize=(10, 8))
plt.contourf(xx, yy, Z, cmap=cmap, levels=len(classes) - 1)

# 绘制原始数据点（排除无相区域）
for i, cls in enumerate(classes):
    if cls == '-':
        continue
    mask = y == cls
    plt.scatter(X[mask, 0], X[mask, 1], label=cls, edgecolor='k', s=80, linewidths=1)

plt.legend(loc='upper right')
plt.xlabel('fraction of A')
plt.ylabel('Chi N')
plt.title('Phase Diagram Predicted by SVM')
plt.xlim(x_min, x_max)
plt.ylim(y_min, y_max)
plt.grid(False)
plt.savefig(dirname=os.path.join(output_dir, 'phase_diagram.png'), dpi=600)
plt.close()
