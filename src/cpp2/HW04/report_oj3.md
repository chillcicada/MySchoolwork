## OJ3

### Linked List

最终提交的代码如下：

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
 * @brief query
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

拿到题目，通过样例不难，容器直接用 STL 的 `list` 用 `algorithm` 的 `find` 方法（应该是线性查找）写了个 `move` 即可，核心实现如下：

```cpp
void init(std::list<int> &sequence, const int &n) {
  for (int i = 1; i <= n; ++i) {
    sequence.push_back(i);
  }
}

void move(std::list<int> &sequence, const int &i, const int &j) {
  auto it_i = std::find(sequence.begin(), sequence.end(), i);
  auto it_j = std::find(sequence.begin(), sequence.end(), j);

  if (it_i != sequence.end() && it_j != sequence.end()) {
    sequence.erase(it_i);
    it_j = std::find(sequence.begin(), sequence.end(), j);
    sequence.insert(std::next(it_j), i);
  }
}

void query(const std::list<int> &sequence) {
  for (auto num : sequence) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}
```

显然 TLE 了，然后转换了一下思路，直接维护数组，同时维护序列和对应的位置信息（指针信息），核心实现如下：

```cpp
void init(int *sequence, int *position, const int &n) {
  for (int i = 0; i < n; ++i) {
    sequence[i] = i + 1;
    position[i + 1] = i;
  }
}

void move(int *sequence, int *position, const int &i, const int &j) {
  const int pos_i = position[i];
  const int pos_j = position[j];

  if (pos_i < pos_j) { // i at left of j
    for (int k = pos_i; k < pos_j; ++k) {
      sequence[k] = sequence[k + 1];
      position[sequence[k]] = k;
    }
    sequence[pos_j] = i;
    position[i] = pos_j;
  } else { // i at right of j
    for (int k = pos_i; k > pos_j + 1; --k) {
      sequence[k] = sequence[k - 1];
      position[sequence[k]] = k;
    }
    sequence[pos_j + 1] = i;
    position[i] = pos_j + 1;
  }
}

void query(const int *sequence, const int &n) {
  for (int i = 0; i < n; ++i) {
    std::cout << sequence[i] << " ";
  }
  std::cout << std::endl;
}
```

由于 `move` 部分仍然是 $O(n)$ 的复杂度，仍然会 TLE，这时想到最简单的思路是空间换时间，即用 hash map 来维护位置信息，把 `move` 的时间复杂度降低到 $O(1)$，然后 AC 了，核心代码即上面提到的代码。

当然，如果不想用 hash map 开空间来维护，可以直接用 vector 乃至 array 来维护位置信息，核心实现分别如下：

```cpp
// vector
void init(list_t &sequence, iter_t &iter_v, const int &n) {
  for (int i = 1; i <= n; ++i) {
    sequence.push_back(i);
    iter_v[i] = --sequence.end();
  }
}

void move(list_t &sequence, iter_t &iter_v, const int &i, const int &j) {
  auto it_i = iter_v[i];
  auto it_j = iter_v[j];

  sequence.erase(it_i);
  iter_v[i] = sequence.insert(++it_j, i);
}

void query(const list_t &sequence) {
  for (int num : sequence) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}
```

```cpp
// pointer array
void init(list_t &sequence, iter_t *iter_p, const int &n) {
  for (int i = 1; i <= n; ++i) {
    sequence.push_back(i);
    iter_p[i] = --sequence.end();
  }
}

void move(list_t &sequence, iter_t *iter_p, const int &i, const int &j) {
  auto it_i = iter_p[i];
  auto it_j = iter_p[j];

  sequence.erase(it_i);
  iter_p[i] = sequence.insert(++it_j, i);
}

void query(const list_t &sequence) {
  for (int num : sequence) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}
```

此外，经过测试，上面的所有空间换时间的实现中，用 vector 维护位置信息的内存最小，为 ～5MB，而用 hashmap 和 point array 的内存在 9MB 左右，考虑到此题的输入中 sequence 均为有序整数，因而本题目的最佳实践是用 vector 来维护位置信息，不过对于一般情况，即输入并不完全规范，hashmap 更为通用。

所有相关文件的构建脚本如下：

```makefile
t1:
  g++ -std=c++17 -o2 HW04/t1.cpp -o HW04/t1 \
    && ./HW04/t1 < HW04/t1.in > HW04/t1.out \
    && rm HW04/t1

t1_1:
  g++ -std=c++17 -o2 HW04/t1_1.cpp -o HW04/t1 \
    && ./HW04/t1 < HW04/t1.in > HW04/t1.out \
    && rm HW04/t1

t1_2:
  g++ -std=c++17 -o2 HW04/t1_2.cpp -o HW04/t1 \
    && ./HW04/t1 < HW04/t1.in > HW04/t1.out \
    && rm HW04/t1

t1_3:
  g++ -std=c++17 -o2 HW04/t1_3.cpp -o HW04/t1 \
    && ./HW04/t1 < HW04/t1.in > HW04/t1.out \
    && rm HW04/t1

t1_4:
  g++ -std=c++17 -o2 HW04/t1_4.cpp -o HW04/t1 \
    && ./HW04/t1 < HW04/t1.in > HW04/t1.out \
    && rm HW04/t1
```

### GEMM

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

客观上讲这题没什么好讲的，不过需要注意的一点是结果的输出，原则上 `Eigen::Matrix<T>` 是可以直接输出的或是逐行输出的，不过由于其中会自动调整空格以对齐数据，在样例上不明确，但在数据波动范围较大时可能会有空格多于单个的情况，所以应选择手动输出。

构建时使用 `xmake` 作为包管理器和构建工具，其配置如下：

```lua
-- xmake.lua
add_rules("mode.debug", "mode.release")
add_requires("eigen")

target("t2")
  set_kind("binary")
  set_languages("c++17")
  add_files("HW04/t2.cpp")
  add_packages("eigen")
```

构建脚本如下：

```makefile
t2:
  xmake && xmake r t2 < HW04/t2.in > HW04/t2.out
```

---

总结：难度上不大，但需要注意细节，比如第二题的打印输出费了我很大功夫，一度让我以为题目错了z。第一题的话，因为做的时候就把思路抽象的比较好，因而实际写的时候没花多少时间，大部分时候改改容器、函数签名和初始化就可以跑了，以至于只放了核心代码上去，主函数部分基本一样，也算是一个应用程设思想的收获吧。
