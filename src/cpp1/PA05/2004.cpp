#include <stdio.h>

int main() {
  int num[20];
  int i = 0;
  int max = 0;
  int secondMax = -1000000000;

  while (1) {
    scanf("%d", &num[i]);
    if (num[i] == 0) {
      break;
    }
    i++;
  }

  max = num[0];
  for (int j = 1; j < i; j++) {
    if (num[j] > max) {
      secondMax = max;
      max = num[j];
    } else if (num[j] > secondMax) {
      secondMax = num[j];
    }
  }

  printf("%d\n", secondMax);
  return 0;
}