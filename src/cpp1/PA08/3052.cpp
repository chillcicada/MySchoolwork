#include <stdio.h>

int main() {
  bool flag{false};
  char c{0}, str1[10][10];
  int arr1[10]{0}, arr2[10]{0}, count1{0}, count2{0};

  do {
    if (c == '\n')
      flag = true;
    if (flag) {
      if (c != '\n')
        c != ' ' ? arr2[count2] += c : count2++;
    } else {
      scanf("%s", str1[count1++]);
      for (int i{0}; str1[count1 - 1][i] != '\0'; i++)
        arr1[count1 - 1] += str1[count1 - 1][i];
    };
  } while ((c = getchar()) != EOF);

  for (int i{0}; i <= count2; i++) {
    for (int j{0}; j < count1; j++) {
      if (arr1[j] == arr2[i])
        printf("%s ", str1[j]);
    }
  }

  return 0;
}
