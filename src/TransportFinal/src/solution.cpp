#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using vector_d = std::vector<double>;

const auto delta1 = 0.025; // m
const auto delta2 = 0.050; // m

const auto R1 = 0.025;       // m
const auto R2 = R1 + delta1; // m
const auto R3 = R2 + delta2; // m

const auto rho1 = 2600.0; // kg/m^3
const auto cp1 = 1150.0;  // J/kg*K
const auto k1 = 3.0;      // W/m*K

const auto alpha1 = k1 / (rho1 * cp1); // m^2/s

const auto rho2 = 600.0; // kg/m^3
const auto cp2 = 200.0;  // J/kg*K
const auto k2 = 0.2;     // W/m*K

const auto alpha2 = k2 / (rho2 * cp2); // m^2/s

const auto T_init = 300.0; // K
const auto T_0 = 1500.0;   // K
const auto T_inf = 298.0;  // K

const auto h1 = 500.0; // W/m^2*K
const auto h2 = 10.0;  // W/m^2*K

/**
 * @brief calculate the boundary temperature
 *
 * @param T the temperature at the boundary of the material
 * @param dr the delta r
 * @param Tb the temperature at the boundary
 * @param h the heat transfer coefficient
 * @param k the thermal conductivity
 * @return double
 */
double calc_boundary(double T, double dr, double Tb, double h, double k) {
  return (h * Tb + k * T / dr) / (h + k / dr);
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
  return Ti +
         alpha * dt * ((Tl + Tr - 2 * Ti) / dr / dr + (Tr - Tl) / 2 / dr / ri);
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
 * @param bp the breakpoint n
 * @return std::vector<double>
 */
vector_d iter_once(const vector_d &T, int n, double dr, double dt, int bp) {
  vector_d T_new(n + 1);

  T_new[0] = calc_boundary(T[1], dr, T_0, h1, k1);

  for (auto i = 1; i < bp; ++i)
    T_new[i] = calc_T(T[i - 1], T[i], T[i + 1], dr, alpha1, dt, i);

  T_new[bp] = calc_middle(T[bp - 1], T[bp + 1]);

  for (auto i = bp + 1; i < n; ++i)
    T_new[i] = calc_T(T[i - 1], T[i], T[i + 1], dr, alpha2, dt, i);

  T_new[n] = calc_boundary(T[n - 1], dr, T_inf, h2, k2);

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
vector_d do_iter(int n, double dt, double eps) {
  std::ofstream file("assets/all_data.csv");
  auto file_status = file.is_open();

  std::ofstream first_pos("assets/first_pos.csv");
  auto first_pos_status = first_pos.is_open();

  std::ofstream middle_pos("assets/middle_pos.csv");
  auto middle_pos_status = middle_pos.is_open();

  std::ofstream last_pos("assets/last_pos.csv");
  auto last_pos_status = last_pos.is_open();

  auto status =
      file_status && first_pos_status && middle_pos_status && last_pos_status;

  if (!status)
    std::cerr << "Cannot open the file!\n";

  vector_d T(n + 1, T_init);
  auto dr = (R3 - R1) / n;
  auto bp = int(n * delta1 / (delta1 + delta2));
  auto T_new = iter_once(T, n, dr, dt, bp);
  auto iter = 0;

  while (true) {
    ++iter;

    auto max_diff = 0.0;

    for (auto i = 0; i <= n; ++i)
      max_diff = std::max(max_diff, std::abs(T_new[i] - T[i]));

    if (max_diff < eps)
      break;

    T = std::move(T_new);
    T_new = iter_once(T, n, dr, dt, bp);

    if (status) {
      if (iter % 1000 == 0) {
        file << iter;

        for (auto i : T_new)
          file << ',' << i;

        file << '\n';
      }

      first_pos << T_new[0] << '\n';
      middle_pos << T_new[bp] << '\n';
      last_pos << T_new[n] << '\n';
    }
  }

  if (status) {
    file.close();
    first_pos.close();
    middle_pos.close();
    last_pos.close();
  }

  std::cout << "The iteration has been done in " << iter << " times\n"
            << "The equilibration time is " << iter * dt << " seconds\n";

  return T_new;
};

int main(int argc, char *argv[], char *envp[]) {
  auto n = 300;
  auto dt = 1e-2;
  auto eps = 1e-5;

  if (argc == 4) {
    n = std::stoi(argv[1]);
    dt = std::stod(argv[2]);
    eps = std::stod(argv[3]);
  } else if (argc != 1) {
    std::cerr << "Please type `n, delta t, epsilon`: (default 300 1e-2 1e-5)\n"
              << "Invalid arguments!\n";
    return 1;
  }

  if (n <= 0 || dt <= 0.0 || eps <= 0.0) {
    std::cerr << "Please type `n, delta t, epsilon`: (default 300 1e-2 1e-5)\n"
              << "Invalid arguments!\n";
    return 1;
  }

  if (!std::filesystem::exists("assets"))
    std::filesystem::create_directory("assets");

  std::ofstream file("assets/final_temperature.csv");

  if (!file.is_open()) {
    std::cerr << "Cannot open the file!\n";
    return 1;
  }

  std::cout << "Output folder has been created or found at `assets/`\n"
            << "The program is running...\n"
            << "You can pass the number of segments, delta t, and epsilon as:\n"
            << "`main.exe 300 1e-2 1e-5`\n\n";

  auto T = do_iter(n, dt, eps);

  for (auto i : T)
    file << i << '\n';

  file.close();

  std::cout << "The result has been saved to `assets/`\n"
            << "Press any key to exit...\n";
  std::cin.get();

  return 0;
}
