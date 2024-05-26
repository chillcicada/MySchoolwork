#include <stdio.h>

int main() {
  int M, N;
  int arr1[100], arr2[100], merged[200];
  int i, j, k;

  scanf("%d %d", &M, &N);

  for (i = 0; i < M; i++) {
    scanf("%d", &arr1[i]);
  }

  for (i = 0; i < N; i++) {
    scanf("%d", &arr2[i]);
  }

  i = j = k = 0;
  while (i < M && j < N) {
    if (arr1[i] < arr2[j]) {
      merged[k++] = arr1[i++];
    } else if (arr1[i] > arr2[j]) {
      merged[k++] = arr2[j++];
    } else {
      merged[k++] = arr1[i++];
      j++;
    }
  }

  while (i < M) {
    merged[k++] = arr1[i++];
  }
  while (j < N) {
    merged[k++] = arr2[j++];
  }

  for (i = 0; i < k; i++) {
    printf("%d ", merged[i]);
  }
  printf("\n");

  return 0;
}