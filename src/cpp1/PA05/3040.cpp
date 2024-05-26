#include <stdio.h>

int main() {
  int grid[8][8] = {
      {0, 9, 8, 7, 6, 5, 4, 3}, {1, 2, 3, 4, 5, 6, 7, 8},
      {2, 3, 4, 6, 7, 8, 9, 6}, {4, 5, 6, 7, 8, 9, 0, 7},
      {4, 3, 2, 1, 6, 7, 8, 9}, {5, 8, 4, 9, 0, 4, 3, 2},
      {3, 4, 6, 7, 8, 4, 3, 2}, {2, 4, 6, 8, 9, 7, 5, 3},
  };
  int N, sum{0};
  scanf("%d", &N);
  int path[N][2];
  for (int i{0}; i < N; i++)
    scanf("%d %d", &path[i][0], &path[i][1]);

  if (N == 1) {
    printf("%d\n", grid[path[0][0] - 1][path[0][1] - 1]);
    return 0;
  }
  for (int i{0}; i < N - 1; i++) {
    int x1 = path[i][0] - 1;
    int y1 = path[i][1] - 1;
    int x2 = path[i + 1][0] - 1;
    int y2 = path[i + 1][1] - 1;
    if (x1 == x2) {
      int start = (y1 < y2) ? y1 : y2;
      int end = (y1 < y2) ? y2 : y1;
      for (int j = start; j <= end; j++)
        sum += grid[x1][j];
    } else if (y1 == y2) {
      int start = (x1 < x2) ? x1 : x2;
      int end = (x1 < x2) ? x2 : x1;
      for (int j = start; j <= end; j++)
        sum += grid[j][y1];
    }
  }
  int count{0};
  if (N > 2) {
    for (int i{1}; i < N - 1; i++) {
      int x = path[i][0] - 1;
      int y = path[i][1] - 1;
      count += grid[x][y];
    }
  }
  printf("%d\n", sum - count);
  return 0;
}
