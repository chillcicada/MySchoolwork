"""
@author: Liu Kuan
@date: 2025-05-11
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
output_dir = os.path.join(current_dir, 'expt3-results')


# plot data
def plot_data(water_flow, air_rate, k_xa_1, k_xa_2):
    water_flow = np.log10(water_flow)
    air_rate = np.log10(air_rate)
    k_xa_1 = np.log10(k_xa_1)
    k_xa_2 = np.log10(k_xa_2)

    # analyze water flow vs k_xa_1
    linear_fit_1 = np.polyfit(water_flow, k_xa_1, 1)
    r2_1 = np.corrcoef(water_flow, k_xa_1)[0, 1] ** 2
    logging.info(f'R^2 for water flow vs k_xa_1: {r2_1:.4f}')

    water_flow_fit_1 = np.linspace(min(water_flow), max(water_flow), 100)
    k_xa_1_fit = np.polyval(linear_fit_1, water_flow_fit_1)
    logging.info(
        f'Linear fit for log water flow vs log k_xa_1: y = {linear_fit_1[0]:.4f}x + {linear_fit_1[1]:.4f}'
    )

    # plot water flow vs k_xa_1
    plt.figure(figsize=(10, 6))
    plt.plot(water_flow, k_xa_1, 'o', label='Data')
    plt.plot(water_flow_fit_1, k_xa_1_fit, 'r-', label=f'Linear Fit, R$^2$={r2_1:.4f}')
    plt.xlabel('lg(L) [lg(L/h)]')
    plt.ylabel('lg($K_x a$) [lg(koml/(m$^3$ h))]')
    plt.title('lg(L) vs lg($K_x a$)')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'water_flow_vs_k_xa.png'))
    plt.close()

    # analyze air rate vs k_xa_2
    linear_fit_2 = np.polyfit(air_rate, k_xa_2, 1)
    r2_2 = np.corrcoef(air_rate, k_xa_2)[0, 1] ** 2
    logging.info(f'R^2 for air rate vs k_xa_2: {r2_2:.4f}')

    air_rate_fit_2 = np.linspace(min(air_rate), max(air_rate), 100)
    k_xa_2_fit = np.polyval(linear_fit_2, air_rate_fit_2)
    logging.info(
        f'Linear fit for log air rate vs log k_xa_2: y = {linear_fit_2[0]:.4f}x + {linear_fit_2[1]:.4f}'
    )

    # plot air rate vs k_xa_2
    plt.figure(figsize=(10, 6))
    plt.plot(air_rate, k_xa_2, 'o', label='Data')
    plt.plot(air_rate_fit_2, k_xa_2_fit, 'r-', label=f'Linear Fit, R$^2$={r2_2:.4f}')
    plt.xlabel('lg(u) [lg(L/h)]')
    plt.ylabel('lg($K_x a$) [lg(koml/(m$^3$ h))]')
    plt.title('lg(u) vs lg($K_x a$)')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'air_rate_vs_k_xa.png'))
    plt.close()

    return


def main():
    os.makedirs(output_dir, exist_ok=True)

    water_flow = np.array([60, 85, 110, 135, 160])  # L/h
    k_xa_1 = np.array([2289.3, 2817.0, 3230.3, 3620.9, 3726.5])  # koml/(m^3 h)

    air_rate = np.array([0.3537, 0.5305, 0.7074, 0.8842, 0.9903])  # m/s
    k_xa_2 = np.array([2869.1, 2979.1, 3230.3, 3456.7, 3565.7])  # koml/(m^3 h)

    # plot data
    plot_data(water_flow, air_rate, k_xa_1, k_xa_2)

    return


if __name__ == '__main__':
    main()
