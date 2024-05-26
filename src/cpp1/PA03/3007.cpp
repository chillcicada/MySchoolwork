#include <stdio.h>

bool isLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int firstDayOfYear(int year) {
  int days{0};
  for (int i{1998}; i < year; i++) {
    days += isLeapYear(i) ? 366 : 365;
  }
  return (days + 4) % 7;
}

int main() {
  int year, count{0};
  scanf("%d", &year);
  int firstDay{firstDayOfYear(year)};
  for (int month = 1; month <= 12; month++) {
    int daysInMonth;
    if (month == 2) {
      daysInMonth = isLeapYear(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
      daysInMonth = 30;
    } else {
      daysInMonth = 31;
    }

    if ((firstDay + 12) % 7 == 5) {
      count++;
    }
    firstDay = (firstDay + daysInMonth) % 7;
  }
  printf("%d\n", count);
}