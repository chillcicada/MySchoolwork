# HW4

<center>刘宽 2022013189</center>

commit ID: 230a96de0905ba08ab0ac3075002a2e388e4f256

相应链接为：<https://git.tsinghua.edu.cn/adv-prog/2024/qt-lab1-liukuan22/-/commit/230a96de0905ba08ab0ac3075002a2e388e4f256>

## 变更历史：

> Last Update Date:  Tue Oct 22 11:27:54 2024 +0800

```bash
$ git log --pretty=oneline --author=chillcicada
b58187d6441fea0b037235bb3417226b8dc8dfb3 (HEAD -> main, origin/main, origin/HEAD) chore: add valgrind to check memory
59ad656f7423804e9c12e2ccc50c563b0cdb0689 chore
fce45ae1947190159d06d8c346dadb2710f5d54c chore: prune project it seems that i just pass the test without big modifying, :/
d1b2f1740707b68c184c3256e7c0426b1490dcf0 Merge remote-tracking branch 'origin/down'
8a934920ad168e4bff3f7942b06540ead0f07f60 chore: update report4
e323049be2c443ce0e64aab3f22d083deba9090c feat: update report4
2ed05a56763cd07a0680df16e72865e51142ff49 chore: update README
b314e977e5054a3ee863f664c830748b8ce755ef chore
230a96de0905ba08ab0ac3075002a2e388e4f256 feat: repentance
85e23e3c9f864f055ee919605991e85e9107c5c9 chore: update config
f1febadc84287cffc1437bfbe76fce1f3219584c chore: update nix config and modify settings
8ec28f348b145d16b859354ff526e26cb8ed0d5a chore: revert lab1.pro for ci
90c490950f1b6f9cd1600283d9f16242ba541de2 refactor: use my preferred toolchains
```

核心变更为：230a96de0905ba08ab0ac3075002a2e388e4f256，实现悔棋功能，相关的 patch 如下：

```diff
$ git diff 85e23e 230a96
diff --git a/src/core/Board.cpp b/src/core/Board.cpp
index 40c6efa..068cc31 100644
--- a/src/core/Board.cpp
+++ b/src/core/Board.cpp
@@ -3,6 +3,9 @@
 
 Board::Board(int rows, int cols) : rows_(rows), cols_(cols) {
   grid_.resize(rows_, std::vector<std::shared_ptr<Piece>>(cols_, nullptr));
+
+  moveHistory_ = std::stack<std::pair<int, int>>();
+  undoHistory_ = std::stack<std::pair<int, int>>();
 }
 
 void Board::clear() {
@@ -16,6 +19,22 @@ bool Board::setPiece(int row, int col, std::shared_ptr<Piece> piece) {
     return false;
   }
   grid_[row][col] = piece;
+  // update move history
+  moveHistory_.push({row, col});
+  // empty undo history
+  while (!undoHistory_.empty()) {
+    undoHistory_.pop();
+  }
+  return true;
+}
+
+bool Board::resetPiece(int row, int col) {
+  if (!isValidPosition(row, col) || !grid_[row][col]) {
+    return false;
+  }
+  grid_[row][col] = nullptr;
+  // update undo history
+  undoHistory_.push({row, col});
   return true;
 }
 
@@ -63,7 +82,12 @@ bool Board::isGameOver(int row, int col) const {
 }
 
 bool Board::undoLastMove() {
-  // TODO: 使用栈实现悔棋功能，并返回是否成功
+  if (moveHistory_.empty()) {
+    return false;
+  }
+  const auto [row, col] = moveHistory_.top();
+  resetPiece(row, col);
+  moveHistory_.pop();
   return true;
 }
 
diff --git a/src/core/Board.h b/src/core/Board.h
index 88855a7..b23f3ac 100644
--- a/src/core/Board.h
+++ b/src/core/Board.h
@@ -12,6 +12,7 @@ public:
 
   void clear();
   bool setPiece(int row, int col, std::shared_ptr<Piece> piece);
+  bool resetPiece(int row, int col);
   bool isValidPosition(int row, int col) const;
   bool isGameOver(int row, int col) const;
   bool undoLastMove();
@@ -23,5 +24,7 @@ public:
 protected:
   int rows_;
   int cols_;
+  std::stack<std::pair<int, int>> moveHistory_;
+  std::stack<std::pair<int, int>> undoHistory_;
   std::vector<std::vector<std::shared_ptr<Piece>>> grid_;
 };
diff --git a/src/core/Game.cpp b/src/core/Game.cpp
index 620f3cd..6cadcdf 100644
--- a/src/core/Game.cpp
+++ b/src/core/Game.cpp
@@ -1,5 +1,4 @@
 #include "Game.h"
-#include <iostream>
 
 Game::Game() {
   board_ = std::make_shared<Board>(15, 15); // 15x15 的标准五子棋棋盘
diff --git a/src/ui/MainWindow.cpp b/src/ui/MainWindow.cpp
index f0e50d8..7338a9c 100644
--- a/src/ui/MainWindow.cpp
+++ b/src/ui/MainWindow.cpp
@@ -33,7 +33,8 @@ void MainWindow::setupUi() {
 void MainWindow::connectSignals() {
   connect(operationWidget_.get(), &OperationWidget::startGameRequested, this,
           &MainWindow::onGameStart);
-  // TODO: 连接悔棋请求信号和悔棋槽函数
+  connect(operationWidget_.get(), &OperationWidget::undoRequested, this,
+          &MainWindow::onUndoRequested);
   connect(boardWidget_.get(), &BoardWidget::moveMade, this,
           &MainWindow::onMoveMade);
 }
@@ -60,7 +61,7 @@ void MainWindow::onMoveMade(int row, int col) {
 }
 
 void MainWindow::onUndoRequested() {
-  // 实现悔棋功能并更新界面显示
+  // TODO 实现悔棋功能并更新界面显示
   if (game_->undoMove()) {
     boardWidget_->update();
     playerInfoWidget_->update();
diff --git a/src/ui/OperationWidget.cpp b/src/ui/OperationWidget.cpp
index c646f2a..501e64b 100644
--- a/src/ui/OperationWidget.cpp
+++ b/src/ui/OperationWidget.cpp
@@ -13,5 +13,6 @@ OperationWidget::OperationWidget(QWidget *parent) : QWidget(parent) {
 
   connect(startButton_.get(), &QPushButton::clicked, this,
           &OperationWidget::startGameRequested);
-  // TODO: 连接悔棋按钮的点击信号和悔棋请求信号
+  connect(undoButton_.get(), &QPushButton::clicked, this,
+          &OperationWidget::undoRequested);
 }
```

1. 在 `Board.h` 中添加了记录移动历史的 `moveHistory_` 和记录变更历史的 `undoHistory_` 同时添加了用于重置棋子的 `resetPiece` 函数原型为 `bool resetPiece(int row, int col);` ，实际上只用添加 `moveHistory_` 和 `resetPiece` 即可。
2. 同时在 `Board.cpp` 中实现了对应的功能。
3. 在 UI 部分连接了悔棋请求信号和悔棋槽函数，以及连接了悔棋按钮的点击信号和悔棋请求信号。
4. 移除了无义代码。

全过程没使用 AI 辅助。

## 其他变更

- 调整了一下目录结构，添加并配置了自己常用的构建工具 xmake，**与 qmake + make 不冲突**，同时配置了一下 vscode，使用 `clangd` 而不是 `c/cpp IntelliSense` 来分析代码。
- 此外就是 code style 的调整，好像没有要求和限制，于是就按自己的口味调整了一下，以及 README 的修改。

## 心得

因为上学期 cpp 基础课大作业就使用了 git + xmake + clangd 等工具，最终从零实现了一个一千多行的 tui 迷宫，项目整体结构与本次提交的项目结构大差不差，所以这次作业在阅读上没什么大的障碍，弄懂思路后就做了。前期花了相当多时间配置构建工具 xmake 与 qt6 和 clangd 的交互，真正花在实现上的时间不到半个小时。其他的心得就是，Qt 库包装得挺好，主体思路都由助教实现了，所以做起了没什么难度，更多是与工具的交互。
