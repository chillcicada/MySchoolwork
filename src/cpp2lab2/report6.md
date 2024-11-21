# HW6

<center>刘宽 2022013189</center>

commit ID: [f64b9ea0090e964afbbf5cb25def776def3e9a92](https://git.tsinghua.edu.cn/adv-prog/2024/qt-lab2-liukuan22/-/commit/f64b9ea0090e964afbbf5cb25def776def3e9a92)

## 提交历史

> Last Update Date: Thu Nov 21 18:05:29 2024 +0800

```bash
$ git log --pretty=oneline --author=chillcicada
f64b9ea0090e964afbbf5cb25def776def3e9a92 (HEAD -> main, origin/main, origin/HEAD) feat: now it work
e9e84eec95c0373fc09f68b8b0ac11fbbf11f375 chore: merge origin/down
1cb83ecaac4e8bc60c2832ec586e036d987fcecc feat: update balllist
49593e419df96cdd237e33ed3597cfa6ea98c1ce chore: build deps
4131d60e6de9e6958621a64b2831cd8d6eef830a fix: build script
9e517b9e97a3bccd552202038ca056eb8208255c refactor: use my preferred toolchains
```

核心变更如下：

- `1cb83e`：用单向链表实现替换了动态数组实现
- `f64b9e`：完成了核心逻辑，同时修剪了一下代码，把 `Game.h` 涉及 `BallList` 的实现放到了 `Game.cpp` 中。

链表部分的实现及迭代器部分直接照本宣科来的，核心逻辑部分我的理解如下：因为`removeMatchedBalls` 和 `checkMatches` 的函数签名都是 void，`checkMatches` 用来检查是否有匹配情况并进行操作，因而我使用 size 和循环来检查 `removeMatchedBalls` 后 `BallList` 是否有变化，使得 `removeMatchedBalls` 后 `BallList` 一定是无匹配序列的。`removeMatchedBalls` 的实现上单次遍历 `BallList` 元素，用 count 作为 flag 记录序列，并将匹配的索引保存到动态数组中，注意对末端序列进行检查，遍历完成后按索引移除元素，最后加上分数即可。

总体 patch 如下：

```diff
$ git diff -p 49593e f64b9e
diff --git a/.vscode/settings.json b/.vscode/settings.json
index bf709bb..8e48921 100644
--- a/.vscode/settings.json
+++ b/.vscode/settings.json
@@ -89,5 +89,23 @@
     "text_encoding": "cpp",
     "qwidget": "cpp"
   },
-  "cSpell.enabled": false
+  "cSpell.enabled": false,
+  "markdownlint.config": {
+    "MD036": false
+  },
+  "files.exclude": {
+    "**/.git": true,
+    "**/.svn": true,
+    "**/.hg": true,
+    "**/CVS": true,
+    "**/.DS_Store": true,
+    "**/Thumbs.db": true,
+    "**/node_modules": true,
+    "**/.venv": true,
+    ".direnv": true,
+    ".xmake": true,
+    ".gitlab-ci.yml": true,
+    "*.pro": true
+  },
+  "explorerExclude.backup": {}
 }
diff --git a/flake.lock b/flake.lock
index 0b70238..36b5f26 100644
--- a/flake.lock
+++ b/flake.lock
@@ -30,12 +30,12 @@
     },
     "nixpkgs": {
       "locked": {
-        "lastModified": 1730785428,
-        "narHash": "sha256-Zwl8YgTVJTEum+L+0zVAWvXAGbWAuXHax3KzuejaDyo=",
-        "rev": "4aa36568d413aca0ea84a1684d2d46f55dbabad7",
-        "revCount": 703931,
+        "lastModified": 1731319897,
+        "narHash": "sha256-PbABj4tnbWFMfBp6OcUK5iGy1QY+/Z96ZcLpooIbuEI=",
+        "rev": "dc460ec76cbff0e66e269457d7b728432263166c",
+        "revCount": 706477,
         "type": "tarball",
-        "url": "https://api.flakehub.com/f/pinned/NixOS/nixpkgs/0.1.703931%2Brev-4aa36568d413aca0ea84a1684d2d46f55dbabad7/0192ff5f-ff6a-733b-b9db-be6b562a64ba/source.tar.gz"
+        "url": "https://api.flakehub.com/f/pinned/NixOS/nixpkgs/0.1.706477%2Brev-dc460ec76cbff0e66e269457d7b728432263166c/01932982-ec3a-7ecf-9466-c74a102f55d1/source.tar.gz"
       },
       "original": {
         "type": "tarball",
diff --git a/flake.nix b/flake.nix
index 487630d..ec45fb3 100644
--- a/flake.nix
+++ b/flake.nix
@@ -40,7 +40,7 @@
             just
             valgrind
             qt6.full
-            llvm_18
+            gcc
           ];
         };
       });
diff --git a/justfile b/justfile
new file mode 100644
index 0000000..94c36bb
--- /dev/null
+++ b/justfile
@@ -0,0 +1,8 @@
+dev:
+  xmake f --toolchain=gcc -m release
+  xmake && xmake r
+
+valgrind:
+  xmake f --toolchain=gcc -m valgrind
+  xmake
+  valgrind --tool=memcheck ./build/linux/x86_64/valgrind/lab2 -s
diff --git a/src/core/CollisionSystem.cpp b/src/core/CollisionSystem.cpp
index 292b9f7..548f70d 100644
--- a/src/core/CollisionSystem.cpp
+++ b/src/core/CollisionSystem.cpp
@@ -1,14 +1,12 @@
 #include "CollisionSystem.h"
-
 #include "Game.h"
 #include "Parameter.h"
-#include <algorithm>
+#include "Path.h"
 
 CollisionSystem::CollisionSystem() {}
 
-// TODO: modify BallList
 bool CollisionSystem::checkPathCollisions(const Ball &shootingBall,
-                                          QVector<Ball> &pathBalls,
+                                          BallList &pathBalls,
                                           const Path &path) {
   CollisionResult result = findCollision(shootingBall, pathBalls);
 
@@ -19,10 +17,8 @@ bool CollisionSystem::checkPathCollisions(const Ball &shootingBall,
   return result.hasCollision;
 }
 
-// TODO: modify BallList
 CollisionSystem::CollisionResult
-CollisionSystem::findCollision(const Ball &ball,
-                               const QVector<Ball> &balls) const {
+CollisionSystem::findCollision(const Ball &ball, BallList &balls) const {
   CollisionResult result = {false, -1};
 
   for (int i = 0; i < balls.size(); ++i) {
@@ -38,8 +34,7 @@ CollisionSystem::findCollision(const Ball &ball,
   return result;
 }
 
-// TODO: modify BallList
-void CollisionSystem::handleCollision(Ball ball, QVector<Ball> &balls,
+void CollisionSystem::handleCollision(Ball ball, BallList &balls,
                                       const Path &path,
                                       const int &collisionIndex) {
   // 获取碰撞点前后的球
diff --git a/src/core/CollisionSystem.h b/src/core/CollisionSystem.h
index d7ab188..1048bca 100644
--- a/src/core/CollisionSystem.h
+++ b/src/core/CollisionSystem.h
@@ -3,12 +3,14 @@
 #include "Path.h"
 #include <QVector>
 
+class BallList;
+
 class CollisionSystem {
 public:
   CollisionSystem();
 
-  bool checkPathCollisions(const Ball &shootingBall, QVector<Ball> &pathBalls,
-                           const Path &path); // TODO: modify BallList
+  bool checkPathCollisions(const Ball &shootingBall, BallList &pathBalls,
+                           const Path &path);
 
   struct CollisionResult {
     bool hasCollision;
@@ -16,9 +18,8 @@ public:
   };
 
 private:
-  CollisionResult
-  findCollision(const Ball &ball,
-                const QVector<Ball> &balls) const; // TODO: modify BallList
-  void handleCollision(Ball ball, QVector<Ball> &balls, const Path &path,
-                       const int &collisionIndex); // TODO: modify BallList
+  CollisionResult findCollision(const Ball &ball, BallList &balls) const;
+
+  void handleCollision(Ball ball, BallList &balls, const Path &path,
+                       const int &collisionIndex);
 };
diff --git a/src/core/Game.cpp b/src/core/Game.cpp
index 82f7ef9..9d2e043 100644
--- a/src/core/Game.cpp
+++ b/src/core/Game.cpp
@@ -3,13 +3,121 @@
 #include "Parameter.h"
 #include <QDebug>
 
+// #region BallList
+
+BallList::BallList() : head(nullptr), size_(0) {}
+
+BallList::~BallList() { clear(); }
+
+void BallList::append(const Ball &ball) {
+  BallNode *node = head;
+  if (!node) {
+    head = new BallNode(ball, nullptr);
+    size_++;
+    return;
+  }
+
+  while (node->next) {
+    node = node->next;
+  }
+  node->next = new BallNode(ball, nullptr);
+  size_++;
+}
+
+void BallList::insert(int index, const Ball &ball) {
+  if (index == 0) {
+    BallNode *node = new BallNode(ball, head);
+    head = node;
+    size_++;
+    return;
+  }
+
+  BallNode *prev = nullptr;
+  BallNode *node = head;
+  for (int i = 0; i < index; i++) {
+    prev = node;
+    node = node->next;
+  }
+
+  BallNode *newNode = new BallNode(ball, node);
+  prev->next = newNode;
+  size_++;
+}
+
+void BallList::erase(int index) {
+  if (index == 0) {
+    BallNode *node = head;
+    head = head->next;
+    delete node;
+    size_--;
+    return;
+  }
+
+  BallNode *prev = nullptr;
+  BallNode *node = head;
+  for (int i = 0; i < index; i++) {
+    prev = node;
+    node = node->next;
+  }
+
+  prev->next = node->next;
+  delete node;
+  size_--;
+}
+
+int BallList::size() const { return size_; }
+
+bool BallList::isEmpty() const { return size_ == 0; }
+
+void BallList::clear() {
+  BallNode *node = head;
+  while (node) {
+    BallNode *next = node->next;
+    delete node;
+    node = next;
+  }
+  head = nullptr;
+  size_ = 0;
+}
+
+Ball &BallList::operator[](int index) {
+  BallNode *node = head;
+  for (int i = 0; i < index; i++) {
+    node = node->next;
+  }
+  return node->ball;
+}
+const Ball &BallList::operator[](int index) const {
+  BallNode *node = head;
+  for (int i = 0; i < index; i++) {
+    node = node->next;
+  }
+  return node->ball;
+}
+
+void BallList::removeAt(int index) { erase(index); }
+
+Ball &BallList::last() {
+  BallNode *node = head;
+  while (node->next) {
+    node = node->next;
+  }
+  return node->ball;
+}
+
+Ball &BallList::first() { return head->ball; }
+
+// #endregion
+
+// #region Game
+
 Game::Game(QObject *parent)
     : QObject(parent), shooter(QPointF(300, 300)) // 发射器位置调整到中间
       ,
       score(0), gameRunning(false) {}
 
 void Game::initialize() {
-  balls.clear();
+  ballList.clear();
   shootingBalls.clear();
   score = 0;
   gameRunning = true;
@@ -60,17 +168,16 @@ void Game::update(float deltaTime) {
 
   float pathLength = path.getTotalLength();
 
-  // TODO: modify BallList
   // 更新路径上的球，从前向后更新
-  for (int i = 0; i < balls.size(); ++i) {
+  for (int i = 0; i < ballList.size(); ++i) {
     float currentDistance = path.getDistanceAtPoint(
-        balls[i].getPosition()); // 计算球在路径上的当前位置
+        ballList[i].getPosition()); // 计算球在路径上的当前位置
     float newDistance =
         currentDistance + BALL_SPEED * deltaTime; // 计算球在路径上的新位置
     QPointF newPos = path.getPointAtDistance(newDistance); // 计算球的新位置
-    balls[i].setPosition(newPos); // 设置球的新位置
-    if (i < balls.size() - 1 &&
-        balls[i].distanceTo(balls[i + 1]) > BALL_RADIUS * 2 + EPS)
+    ballList[i].setPosition(newPos); // 设置球的新位置
+    if (i < ballList.size() - 1 &&
+        ballList[i].distanceTo(ballList[i + 1]) > BALL_RADIUS * 2 + EPS)
       break; // 如果这个球和下一个球之间有空隙，则后面的所有球都不移动
   }
 
@@ -111,9 +218,9 @@ void Game::updateShootingBalls(float deltaTime) {
       continue;
     }
 
-    // TODO: modify BallList
     // 检查碰撞
-    bool hasCollision = collisionSystem.checkPathCollisions(ball, balls, path);
+    bool hasCollision =
+        collisionSystem.checkPathCollisions(ball, ballList, path);
     if (hasCollision) {
       shootingBalls.removeAt(i);
       checkMatches();
@@ -122,7 +229,78 @@ void Game::updateShootingBalls(float deltaTime) {
   checkGameOver();
 }
 
-void Game::checkMatches() {}
+void Game::checkMatches() {
+  // get current size
+  int size = ballList.size();
+
+  removeMatchedBalls();
+
+  // get new size
+  int newSize = ballList.size();
+
+  while (newSize < size) {
+    size = newSize;
+    removeMatchedBalls();
+    newSize = ballList.size();
+  }
+}
+
+void Game::removeMatchedBalls() {
+  // guard clause
+  if (ballList.size() < 3)
+    return;
+
+  // use the top ball's color as the initial color
+  QColor c_ = ballList.first().getColor();
+
+  // set flag
+  int matchedCount = 1;
+
+  // store the indices of matched balls
+  std::vector<int> matchedBallIndices;
+
+  const int size = ballList.size();
+
+  // check the rest of the balls
+  for (int i = 1; i < size; ++i) {
+    // get the color of the current ball
+    QColor c = ballList[i].getColor();
+
+    if (c == c_) {
+      matchedCount++;
+    } else {
+      if (matchedCount >= 3) {
+        // add the matched balls' indices
+        for (int j = i - matchedCount; j < i; ++j) {
+          matchedBallIndices.push_back(j);
+        }
+      }
+
+      // update flag
+      c_ = c;
+      matchedCount = 1;
+    }
+  }
+
+  // check the last group of balls
+  if (matchedCount >= 3) {
+    for (int j = ballList.size() - matchedCount; j < ballList.size(); ++j) {
+      matchedBallIndices.push_back(j);
+    }
+  }
+
+  if (matchedBallIndices.empty())
+    return;
+
+  // remove the matched balls
+  for (int i = matchedBallIndices.size() - 1; i >= 0; --i) {
+    ballList.removeAt(matchedBallIndices[i]);
+  }
+
+  // update score
+  score += matchedBallIndices.size() * 100;
+  emit scoreChanged(score);
+}
 
 void Game::createInitialBalls() {
   const float ballSpacing = BALL_RADIUS * 2;
@@ -140,10 +318,9 @@ void Game::createInitialBalls() {
       direction /= length;
     }
 
-    // TODO: modify BallList
     // 创建球并设置飞行速度为0
     Ball ball(pos, generateRandomColor());
-    balls.append(ball);
+    ballList.append(ball);
 
     distance += ballSpacing;
   }
@@ -154,9 +331,8 @@ QColor Game::generateRandomColor() const {
 }
 
 void Game::checkGameOver() {
-  // TODO: modify BallList
-  if (!balls.isEmpty()) {
-    QPointF ballPos = balls.last().getPosition();
+  if (!ballList.isEmpty()) {
+    QPointF ballPos = ballList.last().getPosition();
     QPointF endPoint = path.getPoints().last();
 
     // 计算两点之间的距离
@@ -174,3 +350,5 @@ void Game::checkGameOver() {
     emit gameOver();
   }
 }
+
+// #endregion
diff --git a/src/core/Game.h b/src/core/Game.h
index 439bd02..9186d2f 100644
--- a/src/core/Game.h
+++ b/src/core/Game.h
@@ -11,11 +11,64 @@ public:
   struct BallNode {
     Ball ball;
     BallNode *next;
-    BallNode(const Ball &ball, BallNode *next) : ball(ball), next(next) {}
+    BallNode(const Ball &ball, BallNode *next = nullptr)
+        : ball(ball), next(next) {}
   };
+
   BallNode *head;
 
-  BallList() : head(nullptr) {}
+  BallList();
+
+  ~BallList();
+
+  void append(const Ball &ball);
+
+  void insert(int index, const Ball &ball);
+
+  void erase(int index);
+
+  int size() const;
+
+  bool isEmpty() const;
+
+  Ball &operator[](int index);
+  const Ball &operator[](int index) const;
+
+  Ball &first();
+
+  void clear();
+
+  void removeAt(int index);
+
+  Ball &last();
+
+  class Iterator {
+  public:
+    Iterator(BallNode *node) : node(node) {}
+
+    Ball &operator*() { return node->ball; }
+
+    Iterator &operator++() {
+      node = node->next;
+      return *this;
+    }
+
+    bool operator!=(const Iterator &other) const { return node != other.node; }
+
+  private:
+    BallNode *node;
+  };
+
+  Iterator begin() { return Iterator(head); }
+
+  Iterator end() { return Iterator(nullptr); }
+
+  const Iterator begin() const { return Iterator(head); }
+
+  const Iterator end() const { return Iterator(nullptr); }
+
+private:
+  int size_;
 };
 
 class Game : public QObject {
@@ -31,7 +84,6 @@ public:
   int getScore() const { return score; }
   const Path &getPath() const { return path; }
   const Shooter &getShooter() const { return shooter; }
-  const QVector<Ball> &getBalls() const { return balls; }
   const QVector<Ball> &getShootingBalls() const { return shootingBalls; }
   BallList &getBallList() { return ballList; }
 
@@ -42,7 +94,6 @@ signals:
 private:
   Path path;
   Shooter shooter;
-  QVector<Ball> balls;
   BallList ballList;
   QVector<Ball> shootingBalls; // 正在飞行的球
   CollisionSystem collisionSystem;
diff --git a/src/test/GameTest.cpp b/src/test/GameTest.cpp
index cfff5b2..d548e0d 100644
--- a/src/test/GameTest.cpp
+++ b/src/test/GameTest.cpp
@@ -16,6 +16,9 @@ private:
 
 void GameTest::testBallCollisionAndMatch() {
   Game game;
+  // 设置游戏初始状态
+  game.initialize();
+  game.getBallList().clear();
 
   // 创建一个固定的初始球序列
   BallList ballList;
@@ -24,24 +27,12 @@ void GameTest::testBallCollisionAndMatch() {
                             COLORS[2], COLORS[2], COLORS[1], COLORS[1],
                             COLORS[0], COLORS[1]};
   float distance = 0;
-  BallList::BallNode *currentNode = nullptr;
   for (const QColor &color : colors) {
     Ball ball(QPointF(50 + distance, 50), color);
-    if (ballList.head == nullptr) {
-      ballList.head = new BallList::BallNode(ball, nullptr);
-      currentNode = ballList.head;
-    } else {
-      BallList::BallNode *newNode = new BallList::BallNode(ball, nullptr);
-      currentNode->next = newNode;
-      currentNode = newNode;
-    }
+    game.getBallList().append(ball);
     distance += BALL_RADIUS * 2;
   }
 
-  // 设置游戏初始状态
-  game.initialize();
-  game.getBallList() = ballList;
-
   // 验证初始序列
   verifyBallSequence(game.getBallList(), colors);
 
diff --git a/src/ui/GameWidget.cpp b/src/ui/GameWidget.cpp
index 005de59..60636e2 100644
--- a/src/ui/GameWidget.cpp
+++ b/src/ui/GameWidget.cpp
@@ -55,10 +55,9 @@ void GameWidget::drawPath(QPainter &painter) {
 }
 
 void GameWidget::drawBalls(QPainter &painter) {
-  // TODO: draw BallList
   // 绘制路径上的球
-  const QVector<Ball> &balls = game->getBalls();
-  for (const Ball &ball : balls) {
+  const BallList &ballList = game->getBallList();
+  for (const Ball &ball : ballList) {
     QPointF pos = ball.getPosition();
     float radius = ball.getRadius();
 
diff --git a/structure.txt b/structure.txt
index b8854ab..698f2ce 100644
--- a/structure.txt
+++ b/structure.txt
@@ -1,4 +1,4 @@
-lab2/
+.
 ├── src/
 │   ├── core/
 │   │   ├── Game.h              // 游戏核心逻辑
@@ -20,8 +20,17 @@ lab2/
 │   │   ├── ScoreBoard.h        // 计分板
 │   │   └── ScoreBoard.cpp
 │   │
+│   ├── test/
+│   │   └── GameTest.cpp
+│   │
 │   └── main.cpp
 |
+├── default.nix
+├── flake.lock
+├── flake.nix
+├── justfile
 ├── lab2.pro
 ├── lab2-test.pro
-└── README.md
\ No newline at end of file
+├── README.md
+├── shell.nix
+└── xmake.lua
```

## 其他

### 基础设施与工具链

使用 nix 作为环境管理，xmake 作为构建工具，同时保留 qmake 的构建方式，代码分析及格式化工具使用 clangd （in vscode）。

相关提交见于：[9e517b](https://git.tsinghua.edu.cn/adv-prog/2024/qt-lab2-liukuan22/-/commit/9e517b9e97a3bccd552202038ca056eb8208255c)。

### 内存检查

使用了一下 `valgrind` 检查有无重大内存泄漏，报告如下，可认为内存管理基本安全。

```bash
$ valgrind --tool=memcheck ./build/linux/x86_64/valgrind/lab2 -s
  Memcheck, a memory error detector
  Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
  Using Valgrind-3.23.0 and LibVEX; rerun with -h for copyright info
  Command: ./build/linux/x86_64/valgrind/lab2 -s
  
  
  HEAP SUMMARY:
      in use at exit: 2,911,019 bytes in 27,583 blocks
    total heap usage: 793,853 allocs, 766,270 frees, 112,047,690 bytes allocated
  
  LEAK SUMMARY:
     definitely lost: 17,728 bytes in 4 blocks
     indirectly lost: 7,366 bytes in 301 blocks
       possibly lost: 4,837 bytes in 57 blocks
     still reachable: 2,716,528 bytes in 25,754 blocks
          suppressed: 0 bytes in 0 blocks
  Rerun with --leak-check=full to see details of leaked memory
  
  For lists of detected and suppressed errors, rerun with: -s
  ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### AI 辅助声明

全过程没使用 AI 辅助思路，copilot 偶尔会补一些懒代码和注释。

## 心得

提供的基础代码解耦不是很好，主要是 BallList 和 Game 部分，没有前向声明的话 clangd 分析的时候会报错，不过我还是照着提供的文件架构写了。

从提交时间线可以看到作业基本是分两个阶段写的，发布作业的几天就把项目配置部分和 BallList 重构部分完成了，中间因为其他事情的耽搁使得在这方面花的时间不多，因而第二次捡起代码已经是十几天后了，之前写的往得差不多了，不得不花时间重新读了一下逻辑和意图，果然事情还是得一次做完 :sweat: 。
