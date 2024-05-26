#include <stdio.h>

int main() {
  long long x;
  scanf("%lld", &x);

  while (x >= 10) {
    long product = 1;
    while (x > 0) {
      long digit = x % 10;
      if (digit != 0)
        product *= digit;
      x /= 10;
    }
    x = product;
  }

  printf("%lld\n", x);
  return 0;
}