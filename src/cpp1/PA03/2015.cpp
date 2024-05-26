#include <stdio.h>

bool isPerfectNumber(int n) {
  int sum{1};
  for (int i{2}; i * i <= n; i++) {
    if (n % i == 0) {
      sum += i;
      if (i * i != n)
        sum += n / i;
    }
  }
  return sum == n && n != 1;
};

int main() {
  int n;
  scanf("%d", &n);
  printf("%s\n", isPerfectNumber(n) ? "Y" : "N");
  return 0;
}