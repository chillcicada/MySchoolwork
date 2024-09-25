#include <iostream>

int main() {
  for (int i = 1; i < 3; i++)
    if (i) {
      std::cout << "xxx" << std::endl;
    }
  std::cout << "zzz" << std::endl;

  std::cout << "\n---\n" << std::endl;

  for (int i = 1; i < 3; i++)
    if (i) {
      std::cout << "yyy" << std::endl;
    };
  std::cout << "zzz" << std::endl;
}
