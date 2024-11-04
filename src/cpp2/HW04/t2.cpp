#include <Eigen/Dense>
#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, p, q;

  std::cin >> n >> m >> p >> q;

  // This won't happen in this problem...
  if (m != p) {
    std::cerr << "Invalid input m & p" << std::endl;
    return 1;
  }

  Eigen::MatrixXi mat1(n, m);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> mat1(i, j);
    }
  }

  Eigen::MatrixXi mat2(p, q);

  for (int i = 0; i < p; ++i) {
    for (int j = 0; j < q; ++j) {
      std::cin >> mat2(i, j);
    }
  }

  // std::cout << mat1 * mat2 << std::endl;

  Eigen::MatrixXi result = mat1 * mat2;

  for (int i = 0; i < n; ++i) {
    std::cout << result.row(i) << std::endl;
  }

  return 0;
}
