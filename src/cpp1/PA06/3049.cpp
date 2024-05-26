#include <stdio.h>

int main() {
  int N, max, a, b, c;
  scanf("%d", &N);
  int arr[N];
  scanf("%d:%d:%d", &a, &b, &c);
  arr[0] = a * 3600 + b * 60 + c;
  max = arr[0];
  for (int i{1}; i < N; i++) {
    scanf("%d:%d:%d", &a, &b, &c);
    arr[i] = a * 3600 + b * 60 + c;
    max = (max < arr[i] - arr[i - 1]) ? arr[i] - arr[i - 1] : max;
  };

  printf("%d:%d:%d", max / 3600, (max % 3600) / 60, max % 60);

  return 0;
}
