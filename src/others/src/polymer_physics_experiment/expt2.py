"""
Experiment 2: DSC

@author: Liu Kuan
@date: 2025-04-25
"""

import logging
import os
from io import StringIO

import colorlog
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy.signal import find_peaks

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


status_arr = ['Heating', 'Isothermal', 'Cooling', 'Isothermal']
process_arr = ['Melting', 'Crystallization']


def preprocess_data(filename: str):
    filepath = os.path.join(data_dir, filename)
    if not os.path.exists(filepath):
        logging.error(f'File {filepath} does not exist.')
        return None

    logging.info(f'Processing file {filepath}...')

    with open(filepath, 'r') as f:
        raw = f.read()
        pass

    # split by `[step]`
    ctxs = raw.split('[step]')[1:]

    data = []

    for ctx in ctxs:
        ctx = ctx.strip()
        df = pd.read_csv(StringIO(ctx), sep='\t', skiprows=1)
        df.drop(0, inplace=True)  # remove the first row
        df.dropna(inplace=True)
        df.reset_index(drop=True, inplace=True)

        data.append(df.to_numpy(dtype=np.float32).T)
        pass

    return data


def resolve(filename: str, target: str, xlim=None):
    data = preprocess_data(filename)

    plt.figure(figsize=(12, 8))

    plt.subplot(2, 1, 1)
    for idx, dt in enumerate(data):
        plt.plot(dt[0], dt[1], label=status_arr[idx % 4])
    plt.xlabel('Time (s)')
    plt.ylabel('Temperature (°C)')
    plt.title('Heating/Cooling Curve')
    plt.legend()

    plt.subplot(2, 1, 2)
    for idx, dt in enumerate(data):
        if idx % 2 != 0:  # Isothermal
            continue
        x, y = dt[1], dt[2]
        plt.plot(x, y, label=process_arr[(idx % 4) // 2])

        peaks = find_peaks(abs(y), height=4, distance=10)
        if len(peaks[0]) == 0:
            continue
        assert len(peaks[0]) == 1, f'Found {len(peaks[0])} peaks, expected 1.'
        peak_idx = peaks[0][0]
        peak_x = x[peak_idx]
        peak_y = y[peak_idx]
        delta_peak_y = -0.8 if peak_y > 0 else 0.4
        plt.text(
            peak_x,
            peak_y + delta_peak_y,
            f'{process_arr[(idx % 4) // 2]}: {peak_x:.1f} °C',
            ha='center',
            color='red' if peak_y > 0 else 'blue',
        )
        plt.vlines(
            peak_x,
            min(y),
            max(y),
            color='red' if peak_y > 0 else 'blue',
            linestyles='dashed',
        )
        pass
    plt.xlim(xlim) if xlim else plt.xlim(30, 80)
    plt.xlabel('Temperature (°C)')
    plt.ylabel('Heat Flow (W/g)')
    plt.title('Heat Flow vs Temperature')
    plt.legend()

    plt.tight_layout()

    plt.savefig(os.path.join(output_dir, target))
    plt.close()

    logging.info(f'Saved figure to {os.path.join(output_dir, target)}')

    return


def main():
    if not os.path.exists(data_dir):
        logging.error(f'Data directory {data_dir} does not exist.')
        return None

    os.makedirs(output_dir, exist_ok=True)

    resolve('PEO_100k.txt', 'PEO_100k_failed.png')
    resolve('PEO_100k(1).txt', 'PEO_100k.png')
    resolve('PEO_300k.txt', 'PEO_300k.png')

    return


if __name__ == '__main__':
    main()
