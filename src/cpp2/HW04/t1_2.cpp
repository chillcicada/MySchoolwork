#include <iostream>

/**
 * @brief init
 *
 * @param sequence
 * @param position the position of each element in the sequence
 * @param n the length of the sequence
 */
void init(int *sequence, int *position, const int &n);

/**
 * @brief move - move i to j's right, here we assume i != j
 *
 * @param sequence
 * @param position the position of each element in the sequence
 * @param i the element to move to j's right
 * @param j the element to move i to its right
 */
void move(int *sequence, int *position, const int &i, const int &j);

/**
 * @brief query
 *
 * @param sequence
 * @param n the length of the sequence
 */
void query(const int *sequence, const int &n);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;

  int *sequence = new int[n];
  int *position = new int[n + 1];

  init(sequence, position, n);

  while (m--) {
    int i, j;
    std::cin >> position[0]; // the operation
    switch (position[0]) {
    case 1:
      std::cin >> i >> j;
      move(sequence, position, i, j);
      query(sequence, n);
      break;

    case 2:
      query(sequence, n);
      break;

    default:
      break;
    } // switch
  }

  delete[] position;
  delete[] sequence;

  return 0;
}

void init(int *sequence, int *position, const int &n) {
  for (int i = 0; i < n; ++i) {
    sequence[i] = i + 1;
    position[i + 1] = i;
  }
}

void move(int *sequence, int *position, const int &i, const int &j) {
  const int pos_i = position[i];
  const int pos_j = position[j];

  if (pos_i < pos_j) { // i at left of j
    for (int k = pos_i; k < pos_j; ++k) {
      sequence[k] = sequence[k + 1];
      position[sequence[k]] = k;
    }
    sequence[pos_j] = i;
    position[i] = pos_j;
  } else { // i at right of j
    for (int k = pos_i; k > pos_j + 1; --k) {
      sequence[k] = sequence[k - 1];
      position[sequence[k]] = k;
    }
    sequence[pos_j + 1] = i;
    position[i] = pos_j + 1;
  }
}

void query(const int *sequence, const int &n) {
  for (int i = 0; i < n; ++i) {
    std::cout << sequence[i] << " ";
  }
  std::cout << std::endl;
}
