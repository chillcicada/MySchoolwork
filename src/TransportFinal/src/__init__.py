import numpy as np

# define constants
R1 = 0.050  # m
R2 = 0.075  # m
R3 = 0.125  # m

rho1 = 2600  # kg/m^3
cp1 = 1150  # J/kg-K
k1 = 3.0  # W/m-K

alpha1 = k1 / (rho1 * cp1)  # m^2/s

rho2 = 600  # kg/m^3
cp2 = 200  # J/kg-K
k2 = 0.2  # W/m-K

alpha2 = k2 / (rho2 * cp2)  # m^2/s

T_init = 300  # K
T_0 = 1500  # K
T_inf = 298  # K

h1 = 500  # W/m^2-K
h2 = 10  # W/m^2-K


def calc_first(_Ti: float, _dr: float) -> float:
  """
  _Ti: temperature of T[1]
  _dr: delta r
  """
  return (h1 * T_0 + k1 * _Ti / _dr) / (h1 + k1 / _dr)


def calc(_Tl: float, _Ti: float, _Tr: float, _dr: float, _alpha: float, _dt: float, _i: int) -> float:
  """
  _Tl: temperature of T[i - 1]
  _Ti: temperature of T[i]
  _Tr: temperature of T[i + 1]
  _dr: delta r
  _alpha: alpha
  _dt: delta t
  _i: ith point
  """
  ri_ = R1 + _i * _dr  # r of T[i]
  return _Ti + _alpha * _dt * ((_Tl + _Tr - 2 * _Ti) / _dr**2 + (1 / ri_) * (_Tr - _Tl) / (2 * _dr) - _Ti / ri_**2)


def calc_middle(_Tl: float, _Tr: float) -> float:
  """
  _Tl: temperature of T[i - 1]
  _Tr: temperature of T[i + 1]
  """
  return (_Tl * k1 + _Tr * k2) / (k1 + k2)


def calc_last(_Ti: float, _dr: float) -> float:
  """
  _Ti: temperature of T[n - 1]
  _dr: delta r
  """
  return (h2 * T_inf + k2 * _Ti / _dr) / (h2 + k2 / _dr)


def iter_once(_T: np.ndarray, _n: int, _dr: float, _dt: float) -> np.ndarray:
  """
  _T: temperature array, n + 1 nodes
  _n: number of segments, n + 1 nodes
  _dr: delta r
  _dt: delta t
  """
  T_ = _T.copy()

  T_[0] = calc_first(T_[1], _dr)

  bp_ = _n // 3  # breakpoint n of R1 and R2

  for i in range(1, bp_):
    T_[i] = calc(T_[i - 1], T_[i], T_[i + 1], _dr, alpha1, _dt, i)

  T_[bp_] = calc_middle(T_[bp_ - 1], T_[bp_ + 1])

  for i in range(bp_ + 1, _n):
    T_[i] = calc(T_[i - 1], T_[i], T_[i + 1], _dr, alpha2, _dt, i)

  T_[_n] = calc_last(T_[_n - 1], _dr)

  return T_


def do_iter(_n: int, _dt: float, _eps: float) -> np.ndarray:
  """
  _n: number of segments, n + 1 nodes
  _dt: delta t
  _eps: epsilon
  """
  T_ = np.full(_n + 1, T_init, dtype=np.float64)
  dr_ = (R3 - R1) / _n
  while True:
    T_new = iter_once(T_, _n, dr_, _dt)
    if np.max(np.abs(T_new - T_)) < _eps:
      break
    T_ = T_new
  return T_new


T = do_iter(300, 1e-2, 1e-2)
print(T)
