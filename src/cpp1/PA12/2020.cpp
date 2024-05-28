#include <stdio.h>

int main() {
  int arr[20], a, b, n;
  scanf("%d %d %d %d %d", &arr[0], &arr[1], &a, &b, &n);
  for (int i = 2; i < n; i++)
    arr[i] = a * arr[i - 2] + b * arr[i - 1];
  printf("%d", arr[n - 1]);
}
