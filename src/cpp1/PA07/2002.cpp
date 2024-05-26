// this file requires GBK encoding
#include <stdio.h>

int main() {
  char str1[100], str2[100];
  scanf("%s\n%s", str1, str2);

  int i1{0}, i2{0};
  while (str1[i1] != '\0')
    i1++;
  while (str2[i2] != '\0')
    i2++;
  for (int i{0}; i < (i1 < i2 ? i1 : i2); i++)
    if (str1[i] != str2[i]) {
      printf("%s\n", str1[i] < str2[i] ? "小于" : "大于");
      return 0;
    };
  printf("%s\n", i1 < i2 ? "小于" : i1 > i2 ? "大于" : "等于");
  return 0;
}
