#include <iostream>
#include <vector>

int main() {
  std::vector<int> v = {1, 2, 3, 4, 5};

  v.insert(v.begin() + 6, 10);

  for (const auto &el : v) {
    std::cout << el << " ";
  }

  return 0;
}
