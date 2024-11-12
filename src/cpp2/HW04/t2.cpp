#include <Eigen/Dense>
#include <cstdint>
#include <iostream>

int main() {
  using matrix_t = Eigen::Matrix<int64_t, Eigen::Dynamic, Eigen::Dynamic>;

  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m, p, q;

  std::cin >> n >> m >> p >> q;

  // This won't happen in this problem...
  if (m != p) {
    std::cerr << "Invalid input m & p" << std::endl;
    return 1;
  }

  matrix_t mat1(n, m), mat2(p, q);

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      std::cin >> mat1(i, j);

  for (int i = 0; i < p; ++i)
    for (int j = 0; j < q; ++j)
      std::cin >> mat2(i, j);

  matrix_t result = mat1 * mat2;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < q; ++j)
      std::cout << result(i, j) << (j != q - 1 ? ' ' : '\n');

  std::cout << std::endl;

  return 0;
}
