"""
@author: Liu Kuan
@date: 2025-06-07
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
output_dir = os.path.join(current_dir, 'expt4-results')


def main():
    os.makedirs(output_dir, exist_ok=True)

    alpha = 2.1
    N_e = 9

    x = np.array([0.53, 0.88, 1.23])  # kW

    x_aD = np.array([0.9392, 0.9640, 0.9834])
    x_aW = np.array([0.4046, 0.4126, 0.4163])

    N_min = np.log((x_aD / (1 - x_aD)) / (x_aW / (1 - x_aW))) / np.log(alpha) - 1

    E = N_min / N_e * 100  # Efficiency in percent

    logging.info('Calculated N_min: %s', N_min)
    logging.info('Calculated Efficiency: %s', E)

    # plot the results
    plt.figure(figsize=(8, 5))
    plt.plot(x, E, 'o-', label='Efficiency vs Power Input (kW)', color='blue')
    plt.xlabel('Power Input (kW)')
    plt.ylabel('Efficiency (%)')
    plt.title('Efficiency of Distillation Column')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'output.png'))
    plt.close()


if __name__ == '__main__':
    logging.info('Starting Experiment 4...')
    main()
    logging.info('Experiment 4 completed. Results saved to %s', output_dir)
