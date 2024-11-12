# OJ3

## Linked List

```cpp
#include <iostream>
#include <list>
#include <unordered_map>

using list_t = std::list<int>;
using mph_t = std::unordered_map<int, list_t::iterator>;

/**
 * @brief init
 *
 * @param sequence
 * @param mph_its the hash map of the position of each element in the sequence
 * @param n the length of the sequence
 */
void init(list_t &sequence, mph_t &mph_its, const int &n);

/**
 * @brief move - move i to j's right, here we assume i != j
 *
 * @param sequence
 * @param mph_its the hash map of the position of each element in the sequence
 * @param i the element to move to j's right
 * @param j the element to move i to its right
 */
void move(list_t &sequence, mph_t &mph_its, const int &i, const int &j);

/**
 * @brief
 *
 * @param sequence
 */
void query(const list_t &sequence);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;

  list_t sequence;
  mph_t mph_its;

  init(sequence, mph_its, n);

  while (m--) {
    int op, i, j;
    std::cin >> op; // the operation
    switch (op) {
    case 1:
      std::cin >> i >> j;
      move(sequence, mph_its, i, j);
      break;

    case 2:
      query(sequence);
      break;

    default:
      break;
    } // switch
  }

  return 0;
}

void init(list_t &sequence, mph_t &mph_its, const int &n) {
  for (int i = 1; i <= n; ++i) {
    sequence.push_back(i);
    mph_its[i] = --sequence.end();
  }
}

void move(list_t &sequence, mph_t &mph_its, const int &i, const int &j) {
  auto it_i = mph_its[i];
  auto it_j = mph_its[j];

  sequence.erase(it_i);
  mph_its[i] = sequence.insert(++it_j, i);
}

void query(const list_t &sequence) {
  for (int num : sequence) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}
```





## GEMM

```cpp
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

  return 0;
}
```
