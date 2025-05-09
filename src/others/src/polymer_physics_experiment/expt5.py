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

plt.rcParams['font.sans-serif'] = ['Maple Mono NF CN']
plt.rcParams['axes.unicode_minus'] = False

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


def resolve_all(expt_data, expt_name):
    """
    Plot all experiments' result in one figure
    """

    data_list = list(expt_data.values())

    frequency = []
    storage_modulus = []
    loss_modulus = []
    loss_factor = []

    for i in range(len(data_list)):
        data_list[i] = data_list[i].T
        frequency.append(data_list[i][0] / (2 * np.pi))  # convert to frequency in Hz
        storage_modulus.append(data_list[i][1])
        loss_modulus.append(data_list[i][2])
        loss_factor.append(data_list[i][3])
        pass

    _, (ax1, ax2, ax3) = plt.subplots(
        1, 3, figsize=(11, 8), gridspec_kw={'width_ratios': [4, 4, 3]}
    )

    # plot storage modulus vs frequency
    for i in range(len(data_list)):
        ax1.plot(
            frequency[i],
            storage_modulus[i] * 10**i,
            label=expt_name[i],
            color=f'C{i}',
        )
        ax1.axhline(y=10 ** (5 + i), color=f'C{i}', linestyle='--')
        pass
    ax1.set_xscale('log')
    ax1.set_yscale('log')
    ax1.set_ylim(1e4, 1e10)
    ax1.set_xlabel('Frequency (Hz)')
    ax1.set_ylabel('Modulus (Pa)')
    ax1.set_title('Storage Modulus')
    ax1.yaxis.set_ticklabels([])
    ax1.legend(loc='upper right')
    ax1.text(
        x=0.04,
        y=0.98,
        s='(a)',
        transform=ax1.transAxes,  # 关键参数：使用相对坐标
        fontsize=18,
        va='top',
    )

    # plot loss modulus vs frequency
    for i in range(len(data_list)):
        ax2.plot(
            frequency[i],
            loss_modulus[i] * 10**i,
            label=expt_name[i],
            color=f'C{i}',
        )
        ax2.axhline(y=10 ** (5 + i), color=f'C{i}', linestyle='--')
        pass
    ax2.set_xscale('log')
    ax2.set_yscale('log')
    ax2.set_ylim(1e4, 1e10)
    ax2.set_xlabel('Frequency (Hz)')
    ax2.set_ylabel('Modulus (Pa)')
    ax2.set_title('Loss Modulus')
    ax2.yaxis.set_ticklabels([])
    ax2.legend(loc='upper right')
    ax2.text(
        x=0.04,
        y=0.98,
        s='(b)',
        transform=ax2.transAxes,  # 关键参数：使用相对坐标
        fontsize=18,
        va='top',
    )

    # plot loss factor vs frequency
    for i in range(len(data_list)):
        ax3.plot(
            frequency[i],
            loss_factor[i] + i,
            label=expt_name[i],
            color=f'C{i}',
        )
        pass
    ax3.axvline(x=1, color='red', linestyle='--')
    ax3.set_xscale('log')
    ax3.set_ylim(0, 5)
    ax3.set_xlabel('Frequency (Hz)')
    ax3.set_ylabel('Loss Factor')
    ax3.set_title('Loss Factor')
    ax3.yaxis.set_ticklabels([])
    ax3.legend(loc='upper right')
    ax3.text(
        x=0.04,
        y=0.98,
        s='(c)',
        transform=ax3.transAxes,  # 关键参数：使用相对坐标
        fontsize=18,
        va='top',
    )

    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'all.png'))
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

    picked_data_labels = ['sampleA-1', 'sampleB', 'sampleC', 'sampleD', 'sampleE']

    picked_data = {key: data[key] for key in picked_data_labels}

    logging.info(f'Picked data: {picked_data.keys()}')

    picked_names = ['酷滋', '炫迈', '绿箭', '比巴卜', '大大']

    resolve_all(picked_data, picked_names)

    logging.info('All experiments completed successfully.')

    return


if __name__ == '__main__':
    main()
