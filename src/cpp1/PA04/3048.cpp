#include <stdio.h>

int main() {
  int scores[10], max, min, total;
  scanf("%d", &scores[0]);
  max = min = total = scores[0];
  for (int i = 1; i < 10; i++) {
    scanf("%d", &scores[i]);
    max = scores[i] > max ? scores[i] : max;
    min = scores[i] < min ? scores[i] : min;
    total += scores[i];
  }

  printf("%d\n", (total - min - max) / 8);
  return 0;
}