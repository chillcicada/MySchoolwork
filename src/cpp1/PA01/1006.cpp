/**
 * this is one of chillcicada's c/cpp homework
 *
 * @reference: PA01
 * @author: chillcicada (aka cc) <2210227279@qq.com>
 * @license: MIT
 */

#include <iostream>

int main() {
  long long a, b;
  std::cin >> a >> b;
  [&]() { std::cout << (b + a) * (b - a + 1) / 2 << std::endl; }();
}
