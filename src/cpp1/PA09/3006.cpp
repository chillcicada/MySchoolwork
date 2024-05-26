#include <stdio.h>

void sort_digits_asc(int *digits) {
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      if (digits[i] > digits[j]) {
        int temp = digits[i];
        digits[i] = digits[j];
        digits[j] = temp;
      }
    }
  }
}

void sort_digits_desc(int *digits) {
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      if (digits[i] < digits[j]) {
        int temp = digits[i];
        digits[i] = digits[j];
        digits[j] = temp;
      }
    }
  }
}

int digits_to_num(int *digits) {
  int num = 0;
  for (int i = 0; i < 4; i++) {
    num = num * 10 + digits[i];
  }
  return num;
}

int main() {
  int num, prev, digits[4];
  scanf("%d", &num);
  do {
    prev = num;
    for (int i = 0; i < 4; i++) {
      digits[i] = num % 10;
      num /= 10;
    }
    sort_digits_asc(digits);
    int min = digits_to_num(digits);
    sort_digits_desc(digits);
    int max = digits_to_num(digits);
    num = max - min;
    printf("%d\n", num);
  } while (num != prev);
  return 0;
}
