import glob
import os
import xml.etree.ElementTree as ET

import matplotlib.pyplot as plt
import numpy as np


def unwrap_coordinates(positions, box_size):
  """处理周期性边界条件，返回连续坐标"""
  if len(positions) == 0:
    return np.empty((0, 3))

  unwrapped = [positions[0]]
  prev = positions[0]
  for current in positions[1:]:
    new_pos = []
    for dim in range(3):
      delta = current[dim] - prev[dim]
      if delta > box_size[dim] / 2:
        new_pos.append(current[dim] - box_size[dim])
      elif delta < -box_size[dim] / 2:
        new_pos.append(current[dim] + box_size[dim])
      else:
        new_pos.append(current[dim])
    unwrapped.append(new_pos)
    prev = new_pos
  return np.array(unwrapped)


def calculate_metrics(coordinates):
  """计算均方末端距和回转半径与平均键长"""
  if len(coordinates) < 2:
    return 0.0, 0.0

  # 均方末端距
  end_to_end = coordinates[-1] - coordinates[0]
  R_squared = np.sum(end_to_end**2)

  # 均方回转半径
  com = np.mean(coordinates, axis=0)
  displacements = coordinates - com
  S_squared = np.mean(np.sum(displacements**2, axis=1))

  # 平均键长
  distances = np.linalg.norm(np.diff(coordinates, axis=0), axis=1)
  Avg_bond_length = np.mean(distances) if len(distances) > 0 else 0.0

  return R_squared, S_squared, Avg_bond_length


def process_chain_folder(chain_dir, output_dir):
  """处理单个高分子链文件夹"""
  xml_files = sorted(
    glob.glob(os.path.join(chain_dir, 'particle.*.xml')),
    key=lambda x: int(os.path.splitext(os.path.basename(x).split('.')[1])[0]),
  )

  time_steps = []
  R_values = []
  S_values = []
  Avg_bd_values = []

  for idx, xml_file in enumerate(xml_files):
    try:
      tree = ET.parse(xml_file)
      root = tree.getroot()

      # 解析盒子尺寸
      box_elem = root.find('.//box')
      box_size = [float(box_elem.get('lx')), float(box_elem.get('ly')), float(box_elem.get('lz'))]

      # 解析粒子坐标
      pos_elem = root.find('.//position')
      pos_num = int(pos_elem.get('num'))
      positions = np.loadtxt(pos_elem.text.split(), dtype=float).reshape((pos_num, 3))[1:]

      # 处理周期性边界
      unwrapped = unwrap_coordinates(positions, box_size)

      # 计算指标
      R_sq, S_sq, Avg_bd = calculate_metrics(unwrapped)

      time_steps.append(idx)
      R_values.append(R_sq)
      S_values.append(S_sq)
      Avg_bd_values.append(Avg_bd)

    except Exception as e:
      print(f'Error processing {xml_file}: {str(e)}')

  # 绘制图表
  R_values_variance = np.var(R_values)
  S_values_variance = np.var(S_values)
  Avg_bd_values_variance = np.var(Avg_bd_values)

  plt.figure(figsize=(10, 6))
  plt.plot(time_steps, R_values, label=f'Mean Square End-to-End Distance, Variance: {R_values_variance:.4f}')
  plt.plot(time_steps, S_values, label=f'Mean Square Radius of Gyration, Variance: {S_values_variance:.4f}')
  plt.plot(time_steps, Avg_bd_values, label=f'Average Bond Length, Variance: {Avg_bd_values_variance:.4f}')
  plt.xlabel('Time Step')
  plt.ylabel('Value')
  plt.title(f'Chain Metrics: {os.path.basename(chain_dir)}')
  plt.legend()
  plt.grid(True)

  # 保存图片
  output_path = os.path.join(output_dir, f'{os.path.basename(chain_dir)}_metrics.png')
  plt.savefig(output_path, dpi=300)
  plt.close()

  return np.mean(R_values), np.mean(S_values), np.mean(Avg_bd_values)


def main():
  # 配置参数
  current_dir = os.path.dirname(os.path.abspath(__file__))
  data_dir = os.path.join(current_dir, 'expt6-data')
  output_dir = os.path.join(current_dir, 'expt6-results')
  os.makedirs(output_dir, exist_ok=True)

  # 处理所有链文件夹
  chain_folders = glob.glob(os.path.join(data_dir, 'l=*'))
  results = []

  for folder in chain_folders:
    if os.path.isdir(folder):
      avg_R, avg_S, avg_bd = process_chain_folder(folder, output_dir)
      results.append({'chain': os.path.basename(folder), 'avg_R_sq': avg_R, 'avg_S_sq': avg_S, 'avg_bd': avg_bd})

  results.sort(key=lambda x: x['chain'])

  # 输出统计结果
  print('Final Results:')
  print('{:<7} {:<10} {:<10} {:<5}'.format('Chain', 'Avg R²', 'Avg S²', 'Avg Bond Length'))
  for res in results:
    print(
      '{:<7} {:<10.4f} {:<10.4f} {:<15.4f}'.format(
        res['chain'].split('_')[0],
        res['avg_R_sq'],
        res['avg_S_sq'],
        res['avg_bd'],
      )
    )

  # save results to file
  with open(os.path.join(output_dir, 'final_results.txt'), 'w') as f:
    f.write('{:<7} {:<10} {:<10} {:<15}\n'.format('Chain', 'Avg R²', 'Avg S²', 'Avg Bond Length'))
    for res in results:
      f.write(
        '{:<7} {:<10.4f} {:<10.4f} {:<15.4f}\n'.format(
          res['chain'].split('_')[0], res['avg_R_sq'], res['avg_S_sq'], res['avg_bd']
        )
      )


if __name__ == '__main__':
  main()
