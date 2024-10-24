#pragma once

#include "Piece.h"
#include <memory>
#include <stack>
#include <vector>

class Board {
public:
  Board(int rows, int cols);
  ~Board() = default;

  void clear();
  bool setPiece(int row, int col, std::shared_ptr<Piece> piece);
  bool resetPiece(int row, int col);
  bool isValidPosition(int row, int col) const;
  bool isGameOver(int row, int col) const;
  bool undoLastMove();

  int getRows() const { return rows_; }
  int getCols() const { return cols_; }
  std::shared_ptr<Piece> getPiece(int row, int col) const;

protected:
  int rows_;
  int cols_;
  std::stack<std::pair<int, int>> moveHistory_;
  std::vector<std::vector<std::shared_ptr<Piece>>> grid_;
};
