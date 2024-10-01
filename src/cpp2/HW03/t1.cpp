#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int a[10];

  // read the array
  for (int i = 0; i < 10; i++)
    std::cin >> a[i];

  // convert array to vector
  std::vector<int> v = {std::vector<int>(a, a + 10)};

  int n;
  std::cin >> n;

  while (n--) {
    /**
     * @brief read the operation
     * 1: read `el` and add `el` to the end of the vector
     * 2: pop the last element
     * 3: read `x` and `y` and insert `y` at position `x`
     * 4: read `z` and remove the element at position `z`
     * 5: print the size of the vector
     * 6: print the vector
     * 7: reverse the vector and print it, then reverse it back
     * 8: read `idx` and print the element at position `idx`, if it exists
     *    otherwise, print `Invalid position`
     *
     * @note check the constraints of the input
     *
     */
    int op;
    std::cin >> op;

    switch (op) {
    case 1: {
      int el;
      std::cin >> el;
      v.push_back(el);
      break;
    }

    case 2:
      // check the constraints
      if (v.empty())
        break;

      v.pop_back();
      break;

    case 3: {
      int x, y;
      std::cin >> x >> y;

      // check the constraints
      if (x < 0 || x > v.size()) // ! hint: x can be equal to v.size()
        break;

      // ? i think that `x > v.size()` can also be a valid condition
      v.insert(v.begin() + x, y);
      break;
    }

    case 4: {
      int z;
      std::cin >> z;

      // check the constraints
      if (z < 0 || z >= v.size())
        break;

      v.erase(v.begin() + z);
      break;
    }

    case 5:
      std::cout << v.size() << '\n';
      break;

    case 6:
      for (const auto &i : v)
        std::cout << i << ' ';
      std::cout << '\n';
      break;

    case 7:
      std::reverse(v.begin(), v.end());
      for (const auto &i : v)
        std::cout << i << ' ';
      std::cout << '\n';
      std::reverse(v.begin(), v.end());
      break;

    case 8: {
      int idx;
      std::cin >> idx;

      // check the constraints
      if (idx < 0 || idx >= v.size()) {
        std::cout << "Invalid position" << '\n';
        break;
      }

      std::cout << v[idx] << '\n';
      break;
    }

    default:
      break;
    } // switch
  }

  return 0;
}
