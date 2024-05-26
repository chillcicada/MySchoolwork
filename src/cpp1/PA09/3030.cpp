#include <stdio.h>

int main() {
  char str[100];
  fgets(str, 100, stdin);

  int count[128]{0}, len{0};
  while (str[len] != '\n')
    len++;

  for (int i = 0; i < len; i++) {
    if (str[i] == ' ' || count[str[i]] == 0 || count[str[i]] == 2 ||
        count[str[i]] == 5) {
      count[str[i]]++;
    } else {
      count[str[i]]++;
      str[i] = '\0';
    }
    if (str[i] != '\0')
      printf("%c", str[i]);
  }

  return 0;
}
