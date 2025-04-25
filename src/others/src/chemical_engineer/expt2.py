"""
@author: Liu Kuan
@date: 2025-04-10
"""

import logging
import os
from typing import Dict, List, Literal

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
data_dir = os.path.join(current_dir, 'expt2-data')
output_dir = os.path.join(current_dir, 'expt2-results')

target_sheet_names: List[Literal['expt1', 'expt2', 'expt3.1', 'expt3.2']] = [
    'expt1',
    'expt2',
    'expt3.1',
    'expt3.2',
]

# load the data
if not os.path.exists(data_dir):
    logging.error(f'Directory {data_dir} does not exist.')
    raise FileNotFoundError(f'Directory {data_dir} does not exist.')

data: Dict[Literal['expt1', 'expt2', 'expt3.1', 'expt3.2'], pd.DataFrame] = {}

for sheet_name in target_sheet_names:
    data[sheet_name] = pd.read_excel(
        os.path.join(data_dir, 'data.xlsx'),
        sheet_name=sheet_name,
        header=None,
        skiprows=1,  # Skip the first row
    )
    pass
logging.info('Data loaded successfully.')

# set constants
mu_oil = 70e-3  # Pa.s
rho_oil = 820  # kg/m^3, 50°C
Cp_oil = 0.5e3  # J/(kg.K), 50°C


# 套管换热器
def resolve_expt1(rho_water: float, Cp_water: float) -> pd.DataFrame:
    logging.info('Resolving expt1...')

    # set parameters
    A = 0.18  # m2

    # load data
    Q_oil_raw = data['expt1'].iloc[:, 1].to_numpy()  # m3/h
    Q_oil = Q_oil_raw / 3600  # m3/s

    Q_water_raw = data['expt1'].iloc[:, 2].to_numpy()  # L/min
    Q_water = Q_water_raw / 60 / 1000  # m3/s

    # delta_p_oil_raw = data['expt1'].iloc[:, 3].to_numpy()  # KPa
    # delta_p_oil = delta_p_oil_raw * 1e3  # Pa

    # delta_p_water_raw = data['expt1'].iloc[:, 4].to_numpy()  # KPa
    # delta_p_water = delta_p_water_raw * 1e3  # Pa

    t_oil_in = data['expt1'].iloc[:, 5].to_numpy()  # °C
    t_water_in = data['expt1'].iloc[:, 6].to_numpy()  # °C

    t_oil_out = data['expt1'].iloc[:, 7].to_numpy()  # °C
    t_water_out = data['expt1'].iloc[:, 8].to_numpy()  # °C

    # calculate
    delta_t_m = ((t_oil_in - t_water_out) - (t_oil_out - t_water_in)) / np.log(
        (t_oil_in - t_water_out) / (t_oil_out - t_water_in)
    )  # K

    Q_oil = Q_oil * rho_oil * Cp_oil * (t_oil_in - t_oil_out)  # W
    Q_water = Q_water * rho_water * Cp_water * (t_water_out - t_water_in)  # W

    K_oil = Q_oil / delta_t_m / A  # W/(m2.K)
    K_water = Q_water / delta_t_m / A  # W/(m2.K)

    # save results
    results = pd.DataFrame(
        {
            'delta_t_m': delta_t_m,
            'Q_oil': Q_oil,
            'Q_water': Q_water,
            'K_oil': K_oil,
            'K_water': K_water,
        }
    )

    logging.info('expt1 completed successfully.')

    return results


# 板式换热器
def resolve_expt2(rho_water: float, Cp_water: float) -> pd.DataFrame:
    logging.info('Resolving expt2...')

    # set parameters
    A = 0.3  # m2

    # load data
    Q_oil_raw = data['expt2'].iloc[:, 1].to_numpy()  # m3/h
    Q_oil = Q_oil_raw / 3600  # m3/s

    Q_water_raw = data['expt2'].iloc[:, 2].to_numpy()  # L/min
    Q_water = Q_water_raw / 60 / 1000  # m3/s

    # delta_p_oil_raw = data['expt2'].iloc[:, 3].to_numpy()  # KPa
    # delta_p_oil = delta_p_oil_raw * 1e3  # Pa

    # delta_p_water_raw = data['expt2'].iloc[:, 4].to_numpy()  # KPa
    # delta_p_water = delta_p_water_raw * 1e3  # Pa

    t_oil_in = data['expt2'].iloc[:, 5].to_numpy()  # °C
    t_water_in = data['expt2'].iloc[:, 6].to_numpy()  # °C

    t_oil_out = data['expt2'].iloc[:, 7].to_numpy()  # °C
    t_water_out = data['expt2'].iloc[:, 8].to_numpy()  # °C

    # calculate
    delta_t_m = ((t_oil_in - t_water_out) - (t_oil_out - t_water_in)) / np.log(
        (t_oil_in - t_water_out) / (t_oil_out - t_water_in)
    )  # K

    Q_oil = Q_oil * rho_oil * Cp_oil * (t_oil_in - t_oil_out)  # W
    Q_water = Q_water * rho_water * Cp_water * (t_water_out - t_water_in)  # W

    K_oil = Q_oil / delta_t_m / A  # W/(m2.K)
    K_water = Q_water / delta_t_m / A  # W/(m2.K)

    # save results
    results = pd.DataFrame(
        {
            'delta_t_m': delta_t_m,
            'Q_oil': Q_oil,
            'Q_water': Q_water,
            'K_oil': K_oil,
            'K_water': K_water,
        }
    )

    logging.info('expt2 completed successfully.')

    return results


# 列管换热器 逆流
def resolve_expt3_1(rho_water: float, Cp_water: float) -> pd.DataFrame:
    logging.info('Resolving expt3.1...')

    # set parameters
    A = 0.3  # m2

    # load data
    Q_oil_raw = data['expt3.1'].iloc[:, 1].to_numpy()  # m3/h
    Q_oil = Q_oil_raw / 3600  # m3/s

    Q_water_raw = data['expt3.1'].iloc[:, 2].to_numpy()  # L/min
    Q_water = Q_water_raw / 60 / 1000  # m3/s

    # delta_p_oil_raw = data['expt3.1'].iloc[:, 3].to_numpy()  # KPa
    # delta_p_oil = delta_p_oil_raw * 1e3  # Pa

    # delta_p_water_raw = data['expt3.1'].iloc[:, 4].to_numpy()  # KPa
    # delta_p_water = delta_p_water_raw * 1e3  # Pa

    t_oil_in = data['expt3.1'].iloc[:, 5].to_numpy()  # °C
    t_water_in = data['expt3.1'].iloc[:, 6].to_numpy()  # °C

    t_oil_out = data['expt3.1'].iloc[:, 7].to_numpy()  # °C
    t_water_out = data['expt3.1'].iloc[:, 8].to_numpy()  # °C

    # calculate
    delta_t_m = ((t_oil_in - t_water_out) - (t_oil_out - t_water_in)) / np.log(
        (t_oil_in - t_water_out) / (t_oil_out - t_water_in)
    )  # K

    Q_oil = Q_oil * rho_oil * Cp_oil * (t_oil_in - t_oil_out)  # W
    Q_water = Q_water * rho_water * Cp_water * (t_water_out - t_water_in)  # W

    K_oil = Q_oil / delta_t_m / A  # W/(m2.K)
    K_water = Q_water / delta_t_m / A  # W/(m2.K)

    # save results
    results = pd.DataFrame(
        {
            'delta_t_m': delta_t_m,
            'Q_oil': Q_oil,
            'Q_water': Q_water,
            'K_oil': K_oil,
            'K_water': K_water,
        }
    )

    logging.info('expt3.1 completed successfully.')

    return results


# 列管换热器 并流
def resolve_expt3_2(rho_water: float, Cp_water: float) -> pd.DataFrame:
    logging.info('Resolving expt3.2...')

    # set parameters
    A = 0.3  # m2

    # load data
    Q_oil_raw = data['expt3.2'].iloc[:, 1].to_numpy()  # m3/h
    Q_oil = Q_oil_raw / 3600  # m3/s

    Q_water_raw = data['expt3.2'].iloc[:, 2].to_numpy()  # L/min
    Q_water = Q_water_raw / 60 / 1000  # m3/s

    # delta_p_oil_raw = data['expt3.2'].iloc[:, 3].to_numpy()  # KPa
    # delta_p_oil = delta_p_oil_raw * 1e3  # Pa

    # delta_p_water_raw = data['expt3.2'].iloc[:, 4].to_numpy()  # KPa
    # delta_p_water = delta_p_water_raw * 1e3  # Pa

    t_oil_in = data['expt3.2'].iloc[:, 5].to_numpy()  # °C
    t_water_in = data['expt3.2'].iloc[:, 6].to_numpy()  # °C

    t_oil_out = data['expt3.2'].iloc[:, 7].to_numpy()  # °C
    t_water_out = data['expt3.2'].iloc[:, 8].to_numpy()  # °C

    # calculate
    delta_t_m = ((t_oil_in - t_water_in) - (t_oil_out - t_water_out)) / np.log(
        (t_oil_in - t_water_in) / (t_oil_out - t_water_out)
    )  # K

    Q_oil = Q_oil * rho_oil * Cp_oil * (t_oil_in - t_oil_out)  # W
    Q_water = Q_water * rho_water * Cp_water * (t_water_out - t_water_in)  # W

    K_oil = Q_oil / delta_t_m / A  # W/(m2.K)
    K_water = Q_water / delta_t_m / A  # W/(m2.K)

    # save results
    results = pd.DataFrame(
        {
            'delta_t_m': delta_t_m,
            'Q_oil': Q_oil,
            'Q_water': Q_water,
            'K_oil': K_oil,
            'K_water': K_water,
        }
    )

    logging.info('expt3 completed successfully.')

    return results


def main():
    os.makedirs(output_dir, exist_ok=True)

    results: Dict[Literal['expt1', 'expt2', 'expt3.1', 'expt3.2'], pd.DataFrame] = {}

    rho_water = 997.0479  # kg/m3, 50°C
    Cp_water = 4.2e3  # J/(kg.K), 50°C

    results['expt1'] = resolve_expt1(rho_water, Cp_water)
    print(results['expt1'])
    results['expt2'] = resolve_expt2(rho_water, Cp_water)
    print(results['expt2'])
    results['expt3.1'] = resolve_expt3_1(rho_water, Cp_water)
    print(results['expt3.1'])
    results['expt3.2'] = resolve_expt3_2(rho_water, Cp_water)
    print(results['expt3.2'])

    # save the results to xlsx
    with pd.ExcelWriter(os.path.join(output_dir, 'results.xlsx')) as writer:
        for sheet_name, df in results.items():
            df.to_excel(writer, sheet_name=sheet_name, index=False)
            logging.info(f'Sheet {sheet_name} saved successfully.')
            pass
        pass

    logging.info('All experiments completed successfully.')

    return


if __name__ == '__main__':
    main()
