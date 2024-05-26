/**
 * this is one of chillcicada's c/cpp homework
 *
 * @reference: PA01
 * @author: chillcicada (aka cc) <2210227279@qq.com>
 * @license: MIT
 */

#include <stdio.h>

auto C2F = [](const double &c) { return c * 9.0 / 5.0 + 32; };

int main() {
  double c;
  scanf("%lf", &c);
  printf("%.1f\n", C2F(c));
  return 0;
}
