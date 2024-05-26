#include <stdio.h>
#include <stdlib.h>

int **CreateMatrix(int m, int n) {
  int **matrix = (int **)malloc(m * sizeof(int *));
  for (int i = 0; i < m; i++) {
    matrix[i] = (int *)malloc(n * sizeof(int));
  }
  return matrix;
}

void InputMatrix(int m, int n, int **matrix) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &matrix[i][j]);
    }
  }
}

void OutputMatrix(int m, int n, int **matrix) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void MultiMatrix(int ma, int na, int mb, int nb, int **A, int **B, int **C) {
  if (na != mb) {
    printf("Error: matrix dimensions do not allow multiplication.\n");
    return;
  }
  for (int i = 0; i < ma; i++) {
    for (int j = 0; j < nb; j++) {
      C[i][j] = 0;
      for (int k = 0; k < na; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

void FreeMatrix(int m, int n, int **matrix) {
  for (int i = 0; i < m; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

int main() {
  int ma, na, mb, nb;
  scanf("%d %d", &ma, &na);
  int **A = CreateMatrix(ma, na);
  InputMatrix(ma, na, A);

  scanf("%d %d", &mb, &nb);
  int **B = CreateMatrix(mb, nb);
  InputMatrix(mb, nb, B);

  if (na != mb) {
    printf("Error: matrix dimensions do not allow multiplication.\n");
    FreeMatrix(ma, na, A);
    FreeMatrix(mb, nb, B);
    return 1;
  }

  int **C = CreateMatrix(ma, nb);
  MultiMatrix(ma, na, mb, nb, A, B, C);
  OutputMatrix(ma, nb, C);

  FreeMatrix(ma, na, A);
  FreeMatrix(mb, nb, B);
  FreeMatrix(ma, nb, C);

  return 0;
}
