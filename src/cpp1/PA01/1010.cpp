/**
 * this is one of chillcicada's c/cpp homework
 *
 * @reference: PA01
 * @author: chillcicada (aka cc) <2210227279@qq.com>
 * @license: MIT
 */

#include <stdio.h>

int main() {
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  int temp = (a + b + c) / 3;
  int res = (a + b + c - temp * 3 > 1) ? temp + 1 : temp;
  printf("%d\n", res);
}
