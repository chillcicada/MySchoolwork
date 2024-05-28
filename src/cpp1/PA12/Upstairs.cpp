#include <stdio.h>

int main() {
  int n, N[30]{1, 2, 4};
  scanf("%d", &n);
  for (int i = 3; i < n; i++)
    N[i] = N[i - 1] + N[i - 2] + N[i - 3];
  printf("%d", N[n - 1]);
}
