#include <algorithm>
#include <iostream>
#include <list>

void initializeSequence(std::list<int> &sequence, const int &n);

void move(std::list<int> &sequence, const int &i, const int &j);

void query(const std::list<int> &sequence);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;

  std::list<int> sequence;
  initializeSequence(sequence, n);

  while (m--) {
    int op, i, j;
    std::cin >> op;
    switch (op) {
    case 1:
      std::cin >> i >> j;
      move(sequence, i, j);
      break;
    case 2:
      query(sequence);
      break;
    default:
      break;
    }
  }

  return 0;
}

void initializeSequence(std::list<int> &sequence, const int &n) {
  for (int i = 1; i <= n; ++i) {
    sequence.push_back(i);
  }
}

void move(std::list<int> &sequence, const int &i, const int &j) {
  auto it_i = std::find(sequence.begin(), sequence.end(), i);
  auto it_j = std::find(sequence.begin(), sequence.end(), j);

  if (it_i != sequence.end() && it_j != sequence.end()) {
    sequence.erase(it_i);
    it_j = std::find(sequence.begin(), sequence.end(), j);
    sequence.insert(std::next(it_j), i);
  }
}

void query(const std::list<int> &sequence) {
  for (auto num : sequence) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}
