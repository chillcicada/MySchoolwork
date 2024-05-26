#include <stdio.h>

int main() {
  char str[100];
  scanf("%s", str);

  int i{0};
  while (str[i] != '\0')
    i++;

  char a{str[i - 1]};

  if (a == 's' || a == 'x' || a == 'z') {
    printf("%ses\n", str);
    return 0;
  } else {
    char b{str[i - 2]};

    if (a == 'h' && (b == 'c' || b == 's')) {
      printf("%ses\n", str);
      return 0;
    } else if (a == 'y' && b != 'a' && b != 'e' && b != 'i' && b != 'o' &&
               b != 'u') {
      str[i - 1] = 'i';
      printf("%ses\n", str);
      return 0;
    } else {
      printf("%ss\n", str);
      return 0;
    }
  }
}
