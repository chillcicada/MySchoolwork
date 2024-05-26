#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char binary[33];
  scanf("%s", binary);
  printf("%d\n", strtol(binary, NULL, 2));
  return 0;
}