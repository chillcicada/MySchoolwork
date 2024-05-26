#include <stdio.h>

int Inverse(int n) {
  int result{0};
  while (n > 0) {
    result = result * 10 + n % 10;
    n /= 10;
  }
  return result;
}

int main() {
  int a{0}, b{0};
  scanf("%d %d", &a, &b);
  printf("%d\n", Inverse(Inverse(a) + Inverse(b)));
}
