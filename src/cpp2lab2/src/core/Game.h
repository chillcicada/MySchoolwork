#pragma once
#include "Ball.h"
#include "CollisionSystem.h"
#include "Path.h"
#include "Shooter.h"
#include <QObject>
#include <QRandomGenerator>

class BallList {
public:
  struct BallNode {
    Ball ball;
    BallNode *next;
    BallNode(const Ball &ball, BallNode *next = nullptr)
        : ball(ball), next(next) {}
  };

  BallNode *head;

  BallList();

  ~BallList();

  void append(const Ball &ball);

  void insert(int index, const Ball &ball);

  void erase(int index);

  int size() const;

  bool isEmpty() const;

  Ball &operator[](int index);
  const Ball &operator[](int index) const;

  Ball &first();

  void clear();

  void removeAt(int index);

  Ball &last();

  class Iterator {
  public:
    Iterator(BallNode *node) : node(node) {}

    Ball &operator*() { return node->ball; }

    Iterator &operator++() {
      node = node->next;
      return *this;
    }

    bool operator!=(const Iterator &other) const { return node != other.node; }

  private:
    BallNode *node;
  };

  Iterator begin() { return Iterator(head); }

  Iterator end() { return Iterator(nullptr); }

  const Iterator begin() const { return Iterator(head); }

  const Iterator end() const { return Iterator(nullptr); }

private:
  int size_;
};

class Game : public QObject {
  Q_OBJECT
public:
  explicit Game(QObject *parent = nullptr);

  void initialize();
  void update(float deltaTime);
  void handleClick(const QPointF &point);

  // 获取游戏状态的方法，供UI使用
  int getScore() const { return score; }
  const Path &getPath() const { return path; }
  const Shooter &getShooter() const { return shooter; }
  const QVector<Ball> &getShootingBalls() const { return shootingBalls; }
  BallList &getBallList() { return ballList; }

signals:
  void scoreChanged(int score);
  void gameOver();

private:
  Path path;
  Shooter shooter;
  BallList ballList;
  QVector<Ball> shootingBalls; // 正在飞行的球
  CollisionSystem collisionSystem;
  int score;
  bool gameRunning;

  void checkMatches();
  void removeMatchedBalls();
  void createInitialBalls();
  QColor generateRandomColor() const;
  void updateShootingBalls(float deltaTime);
  void checkGameOver();
};
