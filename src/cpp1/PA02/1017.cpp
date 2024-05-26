/**
 * @file 1017.cpp
 * @author chillcicada
 * @License MIT
 */

#include <stdio.h>

auto isLeapYear = [](const int &year) {
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
};

int main() {
  int year;
  scanf("%d", &year);
  printf("%c\n", isLeapYear(year) ? 'Y' : 'N');
  return 0;
}
