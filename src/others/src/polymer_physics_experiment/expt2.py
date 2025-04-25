"""
Experiment 2: DSC

@author: Liu Kuan
@date: 2025-04-25
"""

import logging
import os

import colorlog

# import matplotlib.pyplot as plt
# import numpy as np

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
data_dir = os.path.join(current_dir, 'expt2-data')
output_dir = os.path.join(current_dir, 'expt2-results')


def main():
    if not os.path.exists(data_dir):
        logging.error(f'Data directory {data_dir} does not exist.')
        return None

    os.makedirs(output_dir, exist_ok=True)

    return


if __name__ == '__main__':
    main()
