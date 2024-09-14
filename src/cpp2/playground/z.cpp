#include <iostream>
#include <vector>

int main() {
  std::vector<int> vec;
  int n;
  std::cin >> n;
  vec.resize(n);
  for (auto i = 0; i < n; i++) {
    std::cout << vec[i] << ' ';
  }
  return 0;
}
