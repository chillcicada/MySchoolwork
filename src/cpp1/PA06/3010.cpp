#include <stdio.h>

/**
 *   0 1
 * 0 0 1
 * 1 2 3
 * 2 4 5
 */

int main() {
  int m[3][2];
  bool a[3][2]{false}, flag{false};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++)
      scanf("%d", &m[i][j]);
  }

  if (m[0][0] > m[0][1] && m[0][0] > m[1][0] && m[0][0] > m[2][0])
    a[0][0] = true, flag = true;
  if (m[0][1] > m[0][0] && m[0][1] > m[1][1] && m[0][1] > m[2][1])
    a[0][1] = true, flag = true;
  if (m[1][0] > m[0][0] && m[1][0] > m[1][1] && m[1][0] > m[2][0])
    a[1][0] = true, flag = true;
  if (m[1][1] > m[0][1] && m[1][1] > m[1][0] && m[1][1] > m[2][1])
    a[1][1] = true, flag = true;
  if (m[2][0] > m[0][0] && m[2][0] > m[1][0] && m[2][0] > m[2][1])
    a[2][0] = true, flag = true;
  if (m[2][1] > m[0][1] && m[2][1] > m[1][1] && m[2][1] > m[2][0])
    a[2][1] = true, flag = true;

  if (!flag) {
    printf("N\n");
    return 0;
  };
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      if (a[i][j]) {
        printf("%d %d\n", i, j);
      }
    }
  }
}
