#include <stdio.h>

constexpr double PI = 3.141592653589793;

int main() {
  double r;
  scanf("%lf", &r);
  printf("%.2f\n", PI * r * r);
  return 0;
}