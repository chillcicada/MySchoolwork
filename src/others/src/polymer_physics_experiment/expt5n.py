"""
Experiment 5: Rheology

@author: Liu Kuan
@date: 2025-05-08
"""

import glob
import logging
import os
from typing import Dict, Literal

import colorlog
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

plt.rcParams['font.sans-serif'] = ['Noto Sans CJK SC', 'Maple Mono NF CN']
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
data_dir = os.path.join(current_dir, 'expt5n-data')
output_dir = os.path.join(current_dir, 'expt5n-results')


def load_data():
    data_raw: Dict[
        Literal[
            '口香糖1-振幅',
            '口香糖2-频率',
            '口香糖3-频率',
            '口香糖4-频率',
            '口香糖5-频率',
            '口香糖2-稳态',
            '口香糖3-稳态',
            '口香糖4-稳态',
            '口香糖5-稳态',
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
            '口香糖1-振幅',
            '口香糖2-频率',
            '口香糖3-频率',
            '口香糖4-频率',
            '口香糖5-频率',
            '口香糖2-稳态',
            '口香糖3-稳态',
            '口香糖4-稳态',
            '口香糖5-稳态',
        ],
        np.ndarray,
    ] = {}

    for key, value in data_raw.items():
        # skip the first column and second column
        data[key] = value.iloc[:, 2:].to_numpy()
    return data


def resolve_all_frequency(expt_data, expt_name):
    frequency_data_list = list(expt_data.values())

    frequency = []
    storage_modulus = []
    loss_modulus = []
    loss_factor = []

    for i in range(len(frequency_data_list)):
        frequency_data_list[i] = frequency_data_list[i].T
        frequency.append(
            frequency_data_list[i][0] / (2 * np.pi)
        )  # convert to frequency in Hz
        storage_modulus.append(frequency_data_list[i][1])
        loss_modulus.append(frequency_data_list[i][2])
        loss_factor.append(frequency_data_list[i][3])
        pass

    _, (ax1, ax2, ax3) = plt.subplots(
        1, 3, figsize=(11, 8), gridspec_kw={'width_ratios': [4, 4, 3]}
    )

    # plot storage modulus vs frequency
    for i in range(len(frequency_data_list)):
        ax1.plot(
            frequency[i],
            storage_modulus[i] * 10**i,
            label=expt_name[i],
            color=f'C{i}',
        )
        ax1.axhline(y=10 ** (4.5 + i), color=f'C{i}', linestyle='--')
        pass
    ax1.set_xscale('log')
    ax1.set_yscale('log')
    ax1.set_ylim(1e4, 1e8)
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
    for i in range(len(frequency_data_list)):
        ax2.plot(
            frequency[i],
            loss_modulus[i] * 10**i,
            label=expt_name[i],
            color=f'C{i}',
        )
        ax2.axhline(y=10 ** (4.5 + i), color=f'C{i}', linestyle='--')
        pass
    ax2.set_xscale('log')
    ax2.set_yscale('log')
    ax2.set_ylim(1e4, 1e8)
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
    for i in range(len(frequency_data_list)):
        ax3.plot(
            frequency[i],
            loss_factor[i] + i,
            label=expt_name[i],
            color=f'C{i}',
        )
        pass
    ax3.axvline(x=1, color='red', linestyle='--')
    ax3.set_xscale('log')
    ax3.set_ylim(0, 4)
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


def resolve_all_homeostasis(expt_data, expt_name):
    homeostasis_data_list = list(expt_data.values())

    rate = []
    viscosity = []

    for i in range(len(homeostasis_data_list)):
        homeostasis_data_list[i] = homeostasis_data_list[i].T
        rate.append(homeostasis_data_list[i][0])
        viscosity.append(homeostasis_data_list[i][2])

        pass

    plt.figure(figsize=(8, 6))
    for i in range(len(homeostasis_data_list)):
        plt.plot(
            rate[i],
            viscosity[i],
            label=expt_name[i],
            color=f'C{i}',
        )
        pass
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Rate (s$^{-1}$)')
    plt.ylabel('Viscosity (mPa.s)')
    plt.title('Viscosity vs Rate')
    plt.legend(loc='upper right')

    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'homeostasis.png'))
    plt.close()

    return


def main():
    if not os.path.exists(data_dir):
        logging.error(f'Data directory {data_dir} does not exist.')
        return None

    os.makedirs(output_dir, exist_ok=True)
    data = load_data()

    picked_names = ['大大', '绿箭', '炫迈', '益达']

    frequency_data = {key: value for key, value in data.items() if key.endswith('频率')}

    logging.info(f'Picked frequency_data names: {sorted(frequency_data)}')

    frequency_data = dict(sorted(frequency_data.items()))

    homeostasis_data = {
        key: value for key, value in data.items() if key.endswith('稳态')
    }

    logging.info(f'Picked homeostasis_data names: {sorted(homeostasis_data)}')

    homeostasis_data = dict(sorted(homeostasis_data.items()))

    resolve_all_frequency(frequency_data, picked_names)

    resolve_all_homeostasis(homeostasis_data, picked_names)

    logging.info('All experiments completed successfully.')

    return


if __name__ == '__main__':
    main()
