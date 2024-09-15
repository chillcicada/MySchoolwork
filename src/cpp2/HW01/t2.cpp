#include <cstdint>
#include <iostream>

const int16_t MAX_N{5000};

// TODO: refactor this function to use quicksort
int main() {
  int16_t n, k, arr[MAX_N];
  std::cin >> n >> k;
  for (auto i{0}; i < n; i++)
    std::cin >> arr[i];
  for (auto i{0}; i < n; i++) {
    int ith = i;
    for (auto j = i + 1; j < n; j++)
      if (arr[j] < arr[ith])
        ith = j;
    std::swap(arr[i], arr[ith]);
  }
  std::cout << arr[k - 1] << std::endl;
}
