#include <stdio.h>

int main() {
  int income;
  scanf("%d", &income);
  double tax = 0;
  income -= 3500;

  if (income <= 0) {
    tax = 0;
  } else if (income <= 500) {
    tax = income * 0.05;
  } else if (income <= 2000) {
    tax = 500 * 0.05 + (income - 500) * 0.10;
  } else if (income <= 5000) {
    tax = 500 * 0.05 + 1500 * 0.10 + (income - 2000) * 0.15;
  } else if (income <= 20000) {
    tax = 500 * 0.05 + 1500 * 0.10 + 3000 * 0.15 + (income - 5000) * 0.20;
  } else if (income <= 40000) {
    tax = 500 * 0.05 + 1500 * 0.10 + 3000 * 0.15 + 15000 * 0.20 +
          (income - 20000) * 0.25;
  } else if (income <= 60000) {
    tax = 500 * 0.05 + 1500 * 0.10 + 3000 * 0.15 + 15000 * 0.20 + 20000 * 0.25 +
          (income - 40000) * 0.30;
  } else {
    tax = 500 * 0.05 + 1500 * 0.10 + 3000 * 0.15 + 15000 * 0.20 + 20000 * 0.25 +
          20000 * 0.30 + (income - 60000) * 0.50;
  }

  printf("%.1f\n", tax);
  return 0;
}