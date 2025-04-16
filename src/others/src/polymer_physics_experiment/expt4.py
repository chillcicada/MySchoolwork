"""
Experiment 4: DMA

@author: Liu Kuan
@date: 2025-04-10
"""

import logging
import os

import colorlog
import matplotlib.pyplot as plt
import numpy as np

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
data_dir = os.path.join(current_dir, 'expt4-data')
output_dir = os.path.join(current_dir, 'expt4-results')


def resolve_pre_expt():
  filename = 'pre-expt.csv'
  filepath = os.path.join(data_dir, filename)
  if not os.path.exists(filepath):
    logging.error(f'File {filepath} does not exist.')
    return None
  data = np.loadtxt(filepath, delimiter=',', skiprows=72).T

  logging.info('Pre-experiment data loaded successfully.')

  (
    angular_freq,
    step_time,
    temperature,
    strain,
    stress,
    tan_delta,
    storage_modulus,
    loss_modulus,
  ) = data

  # plot strain vs modulus and tan delta
  plt.figure(figsize=(10, 6))
  plt.plot(strain, storage_modulus, label='Storage Modulus', color='blue')
  plt.plot(strain, loss_modulus, label='Loss Modulus', color='red')
  plt.xscale('log')
  plt.yscale('log')
  plt.xlabel('Strain (%)')
  plt.ylabel('Modulus (MPa)')
  plt.title('Storage and Loss Modulus vs Strain')
  plt.legend()
  plt.tight_layout()
  plt.savefig(os.path.join(output_dir, 'pre_expt_modulus.png'))
  plt.close()

  return None


def resolve_associative():
  filename = 'associative.csv'
  filepath = os.path.join(data_dir, filename)
  if not os.path.exists(filepath):
    logging.error(f'File {filepath} does not exist.')
    return None
  data = np.loadtxt(filepath, delimiter=',', skiprows=72).T

  logging.info('Associative data loaded successfully.')

  (
    angular_freq,
    step_time,
    temperature,
    strain,
    stress,
    tan_delta,
    storage_modulus,
    loss_modulus,
  ) = data

  # plot temperature vs modulus and tan delta
  plt.figure(figsize=(10, 6))

  plt.subplot(2, 1, 1)
  plt.plot(temperature, storage_modulus, label='Storage Modulus', color='blue')
  plt.plot(temperature, loss_modulus, label='Loss Modulus', color='red')
  plt.ylim(1e-3, 1e4)
  plt.yscale('log')
  plt.xlabel('Temperature (°C)')
  plt.ylabel('Modulus (MPa)')
  plt.title('Storage and Loss Modulus vs Temperature')
  plt.legend()

  plt.subplot(2, 1, 2)
  plt.plot(temperature, tan_delta, label='Tan Delta', color='green')
  plt.ylim(0, 0.4)
  plt.xlabel('Temperature (°C)')
  plt.ylabel('Tan Delta')
  plt.title('Tan Delta vs Temperature')
  plt.legend()

  plt.tight_layout()
  plt.savefig(os.path.join(output_dir, 'associative_modulus.png'))
  plt.close()

  return None


def resolve_dissociative():
  filename = 'dissociative.csv'
  filepath = os.path.join(data_dir, filename)
  if not os.path.exists(filepath):
    logging.error(f'File {filepath} does not exist.')
    return None
  data = np.loadtxt(filepath, delimiter=',', skiprows=87).T

  logging.info('Dissociative data loaded successfully.')

  (
    angular_freq,
    step_time,
    temperature,
    strain,
    stress,
    tan_delta,
    storage_modulus,
    loss_modulus,
  ) = data

  # plot temperature vs modulus and tan delta
  plt.figure(figsize=(10, 6))

  plt.subplot(2, 1, 1)
  plt.plot(temperature, storage_modulus, label='Storage Modulus', color='blue')
  plt.plot(temperature, loss_modulus, label='Loss Modulus', color='red')
  plt.ylim(1e-2, 1e4)
  plt.yscale('log')
  plt.xlabel('Temperature (°C)')
  plt.ylabel('Modulus (MPa)')
  plt.title('Storage and Loss Modulus vs Temperature')
  plt.legend()

  plt.subplot(2, 1, 2)
  plt.plot(temperature, tan_delta, label='Tan Delta', color='green')
  plt.ylim(0, 0.8)
  plt.xlabel('Temperature (°C)')
  plt.ylabel('Tan Delta')
  plt.title('Tan Delta vs Temperature')
  plt.legend()

  plt.tight_layout()
  plt.savefig(os.path.join(output_dir, 'dissociative_modulus.png'))
  plt.close()

  return None


def main():
  if not os.path.exists(data_dir):
    logging.error(f'Data directory {data_dir} does not exist.')
    return None

  os.makedirs(output_dir, exist_ok=True)

  resolve_pre_expt()
  resolve_associative()
  resolve_dissociative()

  return


if __name__ == '__main__':
  main()
