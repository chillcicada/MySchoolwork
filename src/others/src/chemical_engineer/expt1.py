"""
离心泵与管路内流体阻力表征

@author: Liu Kuan
@date: 2025-04-01
"""

import logging
import os
from typing import Dict, Literal

import colorlog
import matplotlib.pyplot as plt
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
data_dir = os.path.join(current_dir, 'expt1-data')
output_dir = os.path.join(current_dir, 'expt1-results')

target_sheet_names = [
    'expt1',
    'expt2.1',
    'expt2.2',
    'expt2.3',
    'expt3',
    'expt4',
]

# load the data
if not os.path.exists(data_dir):
    logging.error(f'Directory {data_dir} does not exist.')
    raise FileNotFoundError(f'Directory {data_dir} does not exist.')

data: Dict[
    Literal['expt1', 'expt2.1', 'expt2.2', 'expt2.3', 'expt3', 'expt4'], pd.DataFrame
] = {}
for sheet_name in target_sheet_names:
    data[sheet_name] = pd.read_excel(
        os.path.join(data_dir, 'expt1.xlsx'),
        sheet_name=sheet_name,
        header=None,
        skiprows=1,  # Skip the first row
    )
    pass
logging.info('Data loaded successfully.')

# set constants
g = 9.81  # m/s^2


# expt1
def expt1(rho: float, mu: float) -> pd.DataFrame:
    logging.info('Running expt1...')

    # set the parameters
    d_ = 0.0213  # m
    l_ = 1.5  # m

    # load the data
    Q_raw = data['expt1'].iloc[:, 1].to_numpy()  # m3/h
    Q = Q_raw / 3600  # m3/s
    u = 4 * Q / (np.pi * d_**2)  # m/s
    delta_P_raw = data['expt1'].iloc[:, 2].to_numpy()  # kPa
    delta_P = delta_P_raw * 1000  # Pa
    h_f = delta_P / rho  # m

    Re = rho * u * d_ / mu  # Reynolds number
    lg_Re = np.log10(Re)

    lambda_ = d_ / l_ * 2 * h_f / u**2  # Darcy friction factor

    model = np.polyfit(lg_Re, lambda_, 1)  # linear regression
    r_squared = np.corrcoef(lg_Re, lambda_)[0, 1] ** 2
    logging.info('Fitting lambda vs log10(Re):')
    logging.info(
        f'Intercept: {model[0]:.4f}, Slope: {model[1]:.4f}, R-squared: {r_squared:.4f}'
    )

    lg_Re_plot = np.linspace(lg_Re.min(), lg_Re.max(), 100)
    lambda_plot = np.polyval(model, lg_Re_plot)

    filtered = (lambda_ > 0.0221) & (lambda_ < 0.025)
    filtered_lg_Re = lg_Re[filtered]
    filtered_Re = Re[filtered]
    filtered_lambda = lambda_[filtered]

    model_filtered = np.polyfit(filtered_lg_Re, filtered_lambda, 1)  # linear regression
    r_squared_filtered = np.corrcoef(filtered_lg_Re, filtered_lambda)[0, 1] ** 2
    logging.info('Fitting lambda vs log10(Re) (filtered):')
    logging.info(
        f'Intercept: {model_filtered[0]:.4f}, Slope: {model_filtered[1]:.4f}, R-squared: {r_squared_filtered:.4f}'
    )

    filtered_lg_Re_plot = np.linspace(filtered_lg_Re.min(), filtered_lg_Re.max(), 100)
    lambda_plot_filtered = np.polyval(model_filtered, filtered_lg_Re_plot)

    # plot the results
    plt.figure()
    plt.plot(Re, lambda_, 'o', label='Data')
    plt.plot(filtered_Re, filtered_lambda, 'o', label='Filtered Data')
    plt.xlabel('Re')
    plt.ylabel('lambda')
    plt.title('Lambda vs Re')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'expt1-1.png'))
    plt.close()

    plt.figure()
    plt.plot(lg_Re, lambda_, 'o', label='Data')
    plt.plot(lg_Re_plot, lambda_plot, '--', label=f'Linear fit, $R^2$={r_squared:.4f}')
    plt.plot(filtered_lg_Re, filtered_lambda, 'o', label='Filtered Data')
    plt.plot(
        filtered_lg_Re_plot,
        lambda_plot_filtered,
        '-',
        label=f'Filtered fit, $R^2$={r_squared_filtered:.4f}',
    )
    plt.xlabel('log10(Re)')
    plt.ylabel('lambda')
    plt.title('Lambda vs Re')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'expt1-2.png'))
    plt.close()

    logging.info('Plot saved successfully.')

    # save the results
    results = pd.DataFrame(
        {
            'Q': Q,
            'u': u,
            'delta P': delta_P,
            'h_f': h_f,
            'Re': Re,
            'lg Re': lg_Re,
            'lambda': lambda_,
        }
    )

    logging.info('expt1 completed successfully.')

    return results


def expt2_1(rho: float, mu: float) -> pd.DataFrame:
    logging.info('Running expt2.1...')

    # set the parameters
    d_ = 0.0213  # m

    # load the data
    Q_raw = data['expt2.1'].iloc[:, 1].to_numpy()  # m3/h
    Q = Q_raw / 3600  # m3/s
    u = 4 * Q / (np.pi * d_**2)  # m/s
    delta_P_raw = data['expt2.1'].iloc[:, 2].to_numpy()  # kPa
    delta_P = delta_P_raw * 1000  # Pa
    h_f = delta_P / rho  # m
    Re = rho * u * d_ / mu  # Reynolds number
    lg_Re = np.log10(Re)

    xi = 2 * h_f / (u**2)
    xi_avg = np.mean(xi)

    xi_avg_plot = np.full_like(lg_Re, xi_avg)

    # plot the results
    plt.figure()
    plt.plot(lg_Re, xi, 'o', label='Data')
    plt.plot(lg_Re, xi_avg_plot, '--', label=f'Average xi={xi_avg:.4f}')
    plt.xlabel('log10(Re)')
    plt.ylabel('xi')
    plt.title('Xi vs Re')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'expt2.1.png'))
    plt.close()

    logging.info('Plot saved successfully.')

    # save the results
    results = pd.DataFrame(
        {
            'Q': Q,
            'u': u,
            'delta P': delta_P,
            'h_f': h_f,
            'Re': Re,
            'lg Re': lg_Re,
            'xi': xi,
        }
    )

    logging.info('expt2.1 completed successfully.')

    return results


def expt2_2(rho: float, mu: float) -> pd.DataFrame:
    logging.info('Running expt2.2...')

    # set the parameters
    d_ = 0.0213  # m

    # load the data
    Q_raw = data['expt2.2'].iloc[:, 1].to_numpy()  # m3/h
    Q = Q_raw / 3600  # m3/s
    u = 4 * Q / (np.pi * d_**2)  # m/s
    delta_P_raw = data['expt2.2'].iloc[:, 2].to_numpy()  # kPa
    delta_P = delta_P_raw * 1000  # Pa
    h_f = delta_P / rho  # m
    Re = rho * u * d_ / mu  # Reynolds number
    lg_Re = np.log10(Re)
    xi = 2 * h_f / (u**2)
    xi_avg = np.mean(xi)

    xi_avg_plot = np.full_like(lg_Re, xi_avg)

    # plot the results
    plt.figure()
    plt.plot(lg_Re, xi, 'o', label='Data')
    plt.plot(lg_Re, xi_avg_plot, '--', label=f'Average xi={xi_avg:.4f}')
    plt.xlabel('log10(Re)')
    plt.ylabel('xi')
    plt.title('Xi vs Re')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'expt2.2.png'))
    plt.close()

    logging.info('Plot saved successfully.')

    # save the results
    results = pd.DataFrame(
        {
            'Q': Q,
            'u': u,
            'delta P': delta_P,
            'h_f': h_f,
            'Re': Re,
            'lg Re': lg_Re,
            'xi': xi,
        }
    )

    logging.info('expt2.2 completed successfully.')

    return results


def expt2_3(rho: float, mu: float) -> pd.DataFrame:
    logging.info('Running expt2.3...')

    # set the parameters
    d_1 = 16e-3  # m
    d_2 = 41e-3  # m

    # load the data
    Q_raw = data['expt2.3'].iloc[:, 1].to_numpy()  # m3/h
    Q = Q_raw / 3600  # m3/s
    u_1 = 4 * Q / (np.pi * d_1**2)  # m/s
    u_2 = 4 * Q / (np.pi * d_2**2)  # m/s
    delta_P_raw = data['expt2.3'].iloc[:, 2].to_numpy()  # kPa
    delta_P = delta_P_raw * 1000  # Pa
    Re_1 = rho * u_1 * d_1 / mu  # Reynolds number
    Re_2 = rho * u_2 * d_2 / mu  # Reynolds number
    lg_Re_1 = np.log10(Re_1)
    lg_Re_2 = np.log10(Re_2)

    xi_1 = (u_1**2 - u_2**2) / (u_1**2) - 2 * delta_P / (rho * u_1**2)
    xi_1_avg = np.mean(xi_1)

    xi_1_avg_plot = np.full_like(lg_Re_1, xi_1_avg)

    xi_1_theory = (1 - (d_1 / d_2) ** 2) ** 2

    xi_1_theory_plot = np.full_like(lg_Re_1, xi_1_theory)

    xi_2 = (u_1**2 - u_2**2) / (u_2**2) - 2 * delta_P / (rho * u_2**2)

    xi_2_theory = (1 - (d_2 / d_1) ** 2) ** 2

    # plot the results
    plt.figure()
    plt.plot(lg_Re_1, xi_1, 'o', label='Data 1')
    plt.plot(lg_Re_1, xi_1_avg_plot, '--', label=f'Average xi={xi_1_avg:.4f}')
    plt.plot(lg_Re_1, xi_1_theory_plot, '-', label=f'Theoretical xi={xi_1_theory:.4f}')
    plt.xlabel('log10($Re_1$)')
    plt.ylabel('$xi_1$')
    plt.title('$Xi_1$ vs $Re_1$')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'expt2.3.png'))
    plt.close()

    logging.info('Plot saved successfully.')

    # save the results
    results = pd.DataFrame(
        {
            'Q': Q,
            'u_1': u_1,
            'u_2': u_2,
            'delta P': delta_P,
            'Re_1': Re_1,
            'lg Re_1': lg_Re_1,
            'xi_1': xi_1,
            'xi_1_theory': xi_1_theory,
            'Re_2': Re_2,
            'lg Re_2': lg_Re_2,
            'xi_2': xi_2,
            'xi_2_theory': xi_2_theory,
        }
    )

    logging.info('expt2.3 completed successfully.')

    return results


def expt3(rho: float, mu: float) -> pd.DataFrame:
    logging.info('Running expt3...')

    # set the parameters
    d_ = 3e-3  # m
    l_ = 1.2  # m

    # load the data
    m_raw = data['expt3'].iloc[:, 1].to_numpy()  # g
    m = m_raw / 1000  # kg
    delta_P_raw = data['expt3'].iloc[:, 2].to_numpy()  # kPa
    delta_P = delta_P_raw * 1000  # Pa
    time = data['expt3'].iloc[:, 3].to_numpy()  # s

    Q = m / time / rho  # m3/s

    u = 4 * Q / (np.pi * d_**2)  # m/s
    Re = rho * u * d_ / mu  # Reynolds number
    Re_rev = 1 / Re  # Reynolds number for reverse flow

    lambda_ = 2 * d_ / l_ * delta_P / (rho * u**2)  # Darcy friction factor

    model = np.polyfit(Re_rev, lambda_, 1)  # linear regression
    r_squared = np.corrcoef(Re_rev, lambda_)[0, 1] ** 2
    logging.info('Fitting lambda vs 1/Re:')
    logging.info(
        f'Intercept: {model[0]:.4f}, Slope: {model[1]:.4f}, R-squared: {r_squared:.4f}'
    )

    Re_rev_plot = np.linspace(Re_rev.min(), Re_rev.max(), 100)
    lambda_plot = np.polyval(model, Re_rev_plot)

    filtered = (Re > 200) & (Re < 2000)
    filtered_Re = Re[filtered]
    filtered_Re_rev = Re_rev[filtered]
    filtered_lambda = lambda_[filtered]

    model_filtered = np.polyfit(
        filtered_Re_rev, filtered_lambda, 1
    )  # linear regression
    r_squared_filtered = np.corrcoef(filtered_Re_rev, filtered_lambda)[0, 1] ** 2
    logging.info('Fitting lambda vs 1/Re (filtered):')
    logging.info(
        f'Intercept: {model_filtered[0]:.4f}, Slope: {model_filtered[1]:.4f}, R-squared: {r_squared_filtered:.4f}'
    )

    filtered_Re_rev_plot = np.linspace(
        filtered_Re_rev.min(), filtered_Re_rev.max(), 100
    )
    lambda_plot_filtered = np.polyval(model_filtered, filtered_Re_rev_plot)

    # plot the results
    plt.figure()
    plt.plot(Re, lambda_, 'o', label='Data')
    plt.plot(filtered_Re, filtered_lambda, 'o', label='Filtered Data')
    plt.xlabel('Re')
    plt.ylabel('lambda')
    plt.title('Lambda vs Re')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'expt3-1.png'))
    plt.close()

    plt.figure()
    plt.plot(Re_rev, lambda_, 'o', label='Data')
    plt.plot(Re_rev_plot, lambda_plot, '--', label=f'Fit, $R^2$={r_squared:.4f}')
    plt.plot(filtered_Re_rev, filtered_lambda, 'o', label='Filtered Data')
    plt.plot(
        filtered_Re_rev_plot,
        lambda_plot_filtered,
        '-',
        label=f'Filtered fit, $R^2$={r_squared_filtered:.4f}',
    )
    plt.xlabel('1/Re')
    plt.ylabel('lambda')
    plt.title('Lambda vs 1/Re')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'expt3-2.png'))
    plt.close()

    logging.info('Plot saved successfully.')

    # save the results
    results = pd.DataFrame(
        {
            'm': m,
            'time': time,
            'Q': Q,
            'u': u,
            'delta P': delta_P,
            'Re': Re,
            'Re_rev': Re_rev,
            'lambda': lambda_,
        }
    )

    logging.info('expt3 completed successfully.')

    return results


def expt4() -> pd.DataFrame:
    logging.info('Running expt4...')

    # set the parameters
    delta_H = 0.25  # m

    # load the data
    Q_raw = data['expt4'].iloc[:, 1].to_numpy()  # m3/h
    Q = Q_raw / 3600  # m3/s
    H_out = data['expt4'].iloc[:, 2].to_numpy()  # m
    H_in = data['expt4'].iloc[:, 3].to_numpy()  # m
    N_raw = data['expt4'].iloc[:, 4].to_numpy()  # kW
    N = N_raw * 1000  # W

    H = H_out - H_in + delta_H  # m
    delta_P = H / 0.102 * 1000  # Pa

    N_e = Q * delta_P
    eta_raw = N_e / N  # efficiency
    eta = eta_raw * 100  # percentage

    Q_squared = Q**2
    eta_slash = eta_raw / Q  # efficiency per unit flow rate

    model_H = np.polyfit(Q_squared, H, 1)  # linear regression
    R_squared_H = np.corrcoef(Q_squared, H)[0, 1] ** 2
    logging.info('Fitting H vs Q^2:')
    logging.info(
        f'Intercept: {model_H[0]:.4f}, Slope: {model_H[1]:.4f}, R-squared: {R_squared_H:.4f}'
    )

    model_eta = np.polyfit(Q, eta_slash, 1)  # linear regression
    R_squared_eta = np.corrcoef(Q, eta_slash)[0, 1] ** 2
    logging.info('Fitting eta/Q vs Q:')
    logging.info(
        f'Intercept: {model_eta[0]:.4f}, Slope: {model_eta[1]:.4f}, R-squared: {R_squared_eta:.4f}'
    )

    Q_plot = np.linspace(Q.min(), Q.max(), 100)
    H_plot = np.polyval(model_H, Q_plot**2)
    eta_slash_plot = np.polyval(model_eta, Q_plot)
    eta_plot = eta_slash_plot * Q_plot
    eta_plot_raw = eta_plot * 100  # convert to percentage
    Q_plot_raw = Q_plot * 3600  # convert to m3/h

    # plot the results
    # plot the efficiency vs flow rate
    plt.figure()
    plt.plot(Q_raw, eta, 'o', label='Data')
    plt.plot(Q_plot_raw, eta_plot_raw, '-', label=f'Fit, $R^2$={R_squared_eta:.4f}')
    plt.xlabel('Flow rate ($m^3/h$)')
    plt.ylabel('Efficiency (%)')
    plt.title('Efficiency vs Flow rate')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'expt4-eta.png'))
    plt.close()
    # plot the H vs flow rate
    plt.figure()
    plt.plot(Q_raw, H, 'o', label='Data')
    plt.plot(Q_plot_raw, H_plot, '-', label=f'Fit, $R^2$={R_squared_H:.4f}')
    plt.xlabel('Flow rate ($m^3/h$)')
    plt.ylabel('H (m)')
    plt.title('H vs Flow rate')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'expt4-H.png'))
    plt.close()
    # plot the N vs flow rate
    plt.figure()
    plt.plot(Q_raw, N_raw, 'o', label='Data')
    plt.xlabel('Flow rate ($m^3/h$)')
    plt.ylabel('N (kW)')
    plt.title('N vs Flow rate')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, 'expt4-N.png'))
    plt.close()

    logging.info('Plot saved successfully.')

    # save the results
    results = pd.DataFrame(
        {
            'Q': Q,
            'H_out': H_out,
            'H_in': H_in,
            'H': H,
            'delta P': delta_P,
            'eta': eta,
            'Ne': N_e,
            'N': N,
        }
    )

    logging.info('expt4 completed successfully.')

    return results


def main():
    os.makedirs(output_dir, exist_ok=True)

    results: Dict[
        Literal['expt1', 'expt2.1', 'expt2.2', 'expt2.3', 'expt3', 'expt4'],
        pd.DataFrame,
    ] = {}

    rho = 997.7  # kg/m3
    mu = 9.635e-4  # Pa.s

    # run the expt1
    results['expt1'] = expt1(rho, mu)

    rho = 997.2  # kg/m3
    mu = 9.23e-4  # Pa.s

    # run the expt2.1
    results['expt2.1'] = expt2_1(rho, mu)

    # run the expt2.2
    results['expt2.2'] = expt2_2(rho, mu)

    # run the expt2.3
    results['expt2.3'] = expt2_3(rho, mu)

    rho = 996.7  # kg/m3
    mu = 8.825e-4  # Pa.s

    # run the expt3
    results['expt3'] = expt3(rho, mu)

    # run the expt4
    results['expt4'] = expt4()

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
