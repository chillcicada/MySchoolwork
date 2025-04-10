"""
Experiment 5: Rheology

@author: Liu Kuan
@date: 2025-04-01
"""

import glob
import logging
import os
from typing import Dict, Literal

import colorlog
import numpy as np
import pandas as pd

handler = colorlog.StreamHandler()
handler.setFormatter(
  colorlog.ColoredFormatter(
    '[%(asctime)s] %(log_color)s%(message)s',
    datefmt='%Y-%m-%d %H:%M:%S',
    reset=True,
    log_colors={
      'INFO': 'green',
      'WARNING': 'yellow',
      'ERROR': 'red',
      'CRITICAL': 'red,bg_white',
    },
  )
)

logging.basicConfig(level=logging.INFO, handlers=[handler])

current_dir = os.path.dirname(os.path.abspath(__file__))
data_dir = os.path.join(current_dir, 'expt5-data')
output_dir = os.path.join(current_dir, 'expt5-results')


def load_data():
  data_raw: Dict[
    Literal['pre-expt', 'sampleA-1', 'sampleA-2', 'sampleB', 'sampleC', 'sampleD', 'sampleE'], pd.DataFrame
  ] = {}
  for filename in glob.glob(os.path.join(data_dir, '*.csv')):
    name = os.path.basename(filename).split('.')[0]
    data_raw[name] = pd.read_csv(
      filename,
      delimiter='\t',
      skiprows=10,
      encoding='utf-16-le',
      header=None,
    )
  logging.info(f'Loaded {len(data_raw)} files from {data_dir}')

  data: Dict[Literal['pre-expt', 'sampleA-1', 'sampleA-2', 'sampleB', 'sampleC', 'sampleD', 'sampleE'], np.ndarray] = {}

  for key, value in data_raw.items():
    # skip the first column
    data[key] = value.iloc[:, 1:].to_numpy()
  return data


def resolve_pre_expt_data(expt_data):
  return


def main():
  os.makedirs(output_dir, exist_ok=True)

  data = load_data()

  print(data['pre-expt'])
  return


if __name__ == '__main__':
  main()
