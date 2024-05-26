#include <stdio.h>

constexpr int MAX_SIZE = 20;

int main() {
  int N, arr[MAX_SIZE], count[MAX_SIZE]{0};

  scanf("%d", &N);

  for (int i = 0; i < N; i++)
    scanf("%d", &arr[i]);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (arr[i] == arr[j])
        count[i]++;
    }
  }

  int max_count = count[0];
  int max_index = 0;

  for (int i = 1; i < N; i++) {
    if (count[i] > max_count) {
      max_count = count[i];
      max_index = i;
    }
  }

  printf("%d\n", arr[max_index]);
  return 0;
}