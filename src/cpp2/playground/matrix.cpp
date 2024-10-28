#include <iostream>
#include <vector>

int main() {
  std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  auto z = matrix[0]; // z = {1, 2, 3}

  // range-based for loop
  for (const auto &item : matrix) {
    for (const auto &element : item) {
      std::cout << element << " ";
    }
    std::cout << std::endl;
  }

  // for (int i = 0; i < matrix.size(); i++) {
  //   for (int j = 0; j < matrix[i].size(); j++) {
  //     std::cout << matrix[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }

  return 0;
}
