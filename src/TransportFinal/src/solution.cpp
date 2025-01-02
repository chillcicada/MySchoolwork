#include <algorithm>
#include <iostream>
#include <vector>

const auto R1 = 0.050; // m
const auto R2 = 0.075; // m
const auto R3 = 0.100; // m

const auto rho1 = 2600.0; // kg/m^3
const auto cp1 = 1150.0;  // J/kg*K
const auto k1 = 3.0;      // W/m*K

const auto alpha1 = k1 / (rho1 * cp1); // m^2/s

const auto rho2 = 600.0; // kg/m^3
const auto cp2 = 2000.0; // J/kg*K
const auto k2 = 0.5;     // W/m*K

const auto alpha2 = k2 / (rho2 * cp2); // m^2/s

const auto T_init = 300.0; // K
const auto T_0 = 1500.0;   // K
const auto T_inf = 298.0;  // K

const auto h1 = 500.0; // W/m^2*K
const auto h2 = 10.0;  // W/m^2*K

/**
 * @brief calculate the first temperature
 *
 * @param Ti the temperature at the 1-th node
 * @param dr the delta r
 * @return double
 */
double calc_first(double Ti, double dr) {
  return (h1 * T_0 + k1 * Ti / dr) / (h1 + k1 / dr);
}

/**
 * @brief calculate the last temperature
 *
 * @param Ti the temperature at the n-1th node
 * @param dr the delta r
 * @return double
 */
double calc_last(double Ti, double dr) {
  return (h2 * T_inf + k2 * Ti / dr) / (h2 + k2 / dr);
}

/**
 * @brief calculate the temperature at the i-th node
 *
 * @param Tl the temperature at the i-1th node
 * @param Ti the temperature at the i-th node
 * @param Tr the temperature at the i+1th node
 * @param dr the delta r
 * @param alpha the alpha
 * @param dt the delta t
 * @param i the index
 * @return double
 */
double calc_T(double Tl, double Ti, double Tr, double dr, double alpha,
              double dt, int i) {
  auto ri = R1 + i * dr;
  return Ti + alpha * dt *
                  ((Tl + Tr - 2 * Ti) / dr / dr +
                   (1 / ri) * (Tr - Tl) / (2 * dr) - Ti / ri / ri);
}

/**
 * @brief calculate the middle temperature at R2
 *
 * @param Tl the temperature at the left node
 * @param Tr the temperature at the right node
 * @return double
 */
double calc_middle(double Tl, double Tr) {
  return (Tl * k1 + Tr * k2) / (k1 + k2);
}

/**
 * @brief do one iteration
 *
 * @param T the temperature vector
 * @param n the number of segments
 * @param dr the delta r
 * @param dt the delta t
 * @return std::vector<double>
 */
std::vector<double> iter_once(const std::vector<double> &T, int n, double dr,
                              double dt) {
  std::vector<double> T_new(n + 1);

  std::copy(T.begin(), T.end(), T_new.begin());

  auto boundary_point = n / 3;

  T_new[0] = calc_first(T_new[1], dr);

  for (auto i = 1; i < boundary_point; ++i)
    T_new[i] = calc_T(T_new[i - 1], T_new[i], T_new[i + 1], dr, alpha1, dt, i);

  T_new[boundary_point] =
      calc_middle(T_new[boundary_point - 1], T_new[boundary_point + 1]);

  for (auto i = boundary_point + 1; i < n; ++i)
    T_new[i] = calc_T(T_new[i - 1], T_new[i], T_new[i + 1], dr, alpha2, dt, i);

  T_new[n] = calc_last(T_new[n - 1], dr);

  return T_new;
}

/**
 * @brief do iteration
 *
 * @param n the number of segments
 * @param dt the delta t
 * @param eps the epsilon
 * @return std::vector<double>
 */
std::vector<double> do_iter(int n, double dt, double eps) {
  auto dr = (R3 - R1) / n;

  std::vector<double> T(n + 1, T_init);

  auto T_new = iter_once(T, n, dr, dt);

  while (true) {
    auto max_diff = 0.0;

    for (auto i = 0; i <= n; ++i)
      max_diff = std::max(max_diff, std::abs(T_new[i] - T[i]));

    if (max_diff < eps)
      break;

    T = std::move(T_new);

    T_new = iter_once(T, n, dr, dt);
  }

  return T_new;
};

int main() {
  auto n = 300;
  auto dt = 1e-2;
  auto eps = 1e-5;

  std::cout << "type n (default 300), delta t (default 1e-2), epsilon (default "
               "1e-5): \n";
  std::cin >> n >> dt >> eps;

  if (n <= 0 || dt <= 0 || eps <= 0) {
    std::cerr << "invalid input\n";
    return 1;
  }

  auto T = do_iter(n, dt, eps);

  for (auto i = 0; i <= n; ++i)
    std::cout << "T[" << i << "] = " << T[i] << std::endl;

  return 0;
}
