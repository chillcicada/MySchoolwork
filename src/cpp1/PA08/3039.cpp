#include <stdio.h>

int main() {
  char ch, stack[7];
  int top{0}, temp;
  while ((ch = getchar()) != EOF) {
    if (ch == ' ')
      continue;
    switch (ch) {
    case '0' ... '9':
      stack[top++] = ch - '0';
      break;
    case '+':
      stack[top - 2] += stack[top - 1];
      top--;
      break;
    case '-':
      stack[top - 2] -= stack[top - 1];
      top--;
      break;
    case '*':
      stack[top - 2] *= stack[top - 1];
      top--;
      break;
    case '/':
      stack[top - 2] /= stack[top - 1];
      top--;
      break;
    case '^':
      temp = 1;
      for (int i{0}; i < stack[top - 1]; i++)
        temp *= stack[top - 2];
      stack[top - 2] = temp;
      top--;
      break;
    default:
      break;
    }
  }
  printf("%d\n", stack[0]);
}
