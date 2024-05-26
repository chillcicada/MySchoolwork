#include <stdio.h>

int main() {
  int ch, prev{0}, cur{0}, max{0};
  while ((ch = getchar()) != EOF) {
    ch >= prev ? cur++ : cur > max ? max = cur, cur = 1 : cur = 1;
    prev = ch;
  }
  printf("%d", max);
  return 0;
}
