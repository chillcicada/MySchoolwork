"""
Experiment 5: Rheology

@author: Liu Kuan
@date: 2025-04-10
"""

import glob
import logging
import os
from typing import Dict, Literal

import colorlog
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

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
        Literal[
            'pre-expt',
            'sampleA-1',
            'sampleA-2',
            'sampleB',
            'sampleC',
            'sampleD',
            'sampleE',
        ],
        pd.DataFrame,
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

    data: Dict[
        Literal[
            'pre-expt',
            'sampleA-1',
            'sampleA-2',
            'sampleB',
            'sampleC',
            'sampleD',
            'sampleE',
        ],
        np.ndarray,
    ] = {}

    for key, value in data_raw.items():
        # skip the first column and second column
        data[key] = value.iloc[:, 2:].to_numpy()
    return data


def resolve_pre_expt_data(expt_data):
    (
        strain,
        stress,
        storage_modulus,
        loss_modulus,
        loss_factor,
        torque,
        status,
    ) = expt_data.T

    strain = strain * 100  # convert to percentage

    # plot modulus vs strain
    plt.figure(figsize=(10, 6))
    plt.plot(strain, storage_modulus, label='Storage Modulus', color='blue')
    plt.plot(strain, loss_modulus, label='Loss Modulus', color='green')
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Strain (%)')
    plt.ylabel('Modulus (Pa)')
    plt.title('Modulus vs Strain')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'pre-expt.png'))
    plt.close()

    logging.info('Pre-experiment data processed and saved.')

    return


def resolve(expt_data, expt_name):
    (
        angular_frequency,
        storage_modulus,
        loss_modulus,
        loss_factor,
        strain,
        stress,
        torque,
        status,
    ) = expt_data.T

    frequency = angular_frequency / (2 * np.pi)  # convert to frequency in Hz

    # plot modulus vs frequency and loss factor vs frequency
    plt.figure(figsize=(10, 6))

    plt.subplot(2, 1, 1)
    plt.plot(frequency, storage_modulus, label='Storage Modulus', color='blue')
    plt.plot(frequency, loss_modulus, label='Loss Modulus', color='green')
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Modulus (Pa)')
    plt.title(f'Modulus vs Frequency - {expt_name}')
    plt.legend()

    plt.subplot(2, 1, 2)
    plt.plot(frequency, loss_factor, label='Loss Factor', color='red')
    plt.xscale('log')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Loss Factor')
    plt.title(f'Loss Factor vs Frequency - {expt_name}')
    plt.legend()

    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, f'{expt_name}.png'))
    plt.close()

    return


def main():
    if not os.path.exists(data_dir):
        logging.error(f'Data directory {data_dir} does not exist.')
        return None

    os.makedirs(output_dir, exist_ok=True)
    data = load_data()

    resolve_pre_expt_data(data['pre-expt'])

    # batch resolve
    for key in ['sampleA-1', 'sampleA-2', 'sampleB', 'sampleC', 'sampleD', 'sampleE']:
        resolve(data[key], key)
        pass

    logging.info('All experiments completed successfully.')

    return


if __name__ == '__main__':
    main()
