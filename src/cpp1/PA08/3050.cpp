#include <stdio.h>

int main() {
  int N;
  scanf("%d", &N);
  int arr[N];
  bool arr2[N]{0};
  for (int i{0}; i < N; i++) {
    scanf("%d", &arr[i]);
    if (arr[i] % 2 == 0)
      arr2[i] = true;
  };
  for (int i{0}; i < N; i++)
    if (!arr2[i])
      printf("%d ", arr[i]);
  printf("\n");
  for (int i{0}; i < N; i++)
    if (arr2[i])
      printf("%d ", arr[i]);
  return 0;
}
