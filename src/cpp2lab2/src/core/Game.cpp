#include "Game.h"

#include "Parameter.h"
#include <QDebug>

// #region BallList

BallList::BallList() : head(nullptr), size_(0) {}

BallList::~BallList() { clear(); }

void BallList::append(const Ball &ball) {
  BallNode *node = head;
  if (!node) {
    head = new BallNode(ball, nullptr);
    size_++;
    return;
  }

  while (node->next) {
    node = node->next;
  }
  node->next = new BallNode(ball, nullptr);
  size_++;
}

void BallList::insert(int index, const Ball &ball) {
  if (index == 0) {
    BallNode *node = new BallNode(ball, head);
    head = node;
    size_++;
    return;
  }

  BallNode *prev = nullptr;
  BallNode *node = head;
  for (int i = 0; i < index; i++) {
    prev = node;
    node = node->next;
  }

  BallNode *newNode = new BallNode(ball, node);
  prev->next = newNode;
  size_++;
}

void BallList::erase(int index) {
  if (index == 0) {
    BallNode *node = head;
    head = head->next;
    delete node;
    size_--;
    return;
  }

  BallNode *prev = nullptr;
  BallNode *node = head;
  for (int i = 0; i < index; i++) {
    prev = node;
    node = node->next;
  }

  prev->next = node->next;
  delete node;
  size_--;
}

int BallList::size() const { return size_; }

bool BallList::isEmpty() const { return size_ == 0; }

void BallList::clear() {
  BallNode *node = head;
  while (node) {
    BallNode *next = node->next;
    delete node;
    node = next;
  }
  head = nullptr;
  size_ = 0;
}

Ball &BallList::operator[](int index) {
  BallNode *node = head;
  for (int i = 0; i < index; i++) {
    node = node->next;
  }
  return node->ball;
}
const Ball &BallList::operator[](int index) const {
  BallNode *node = head;
  for (int i = 0; i < index; i++) {
    node = node->next;
  }
  return node->ball;
}

void BallList::removeAt(int index) { erase(index); }

Ball &BallList::last() {
  BallNode *node = head;
  while (node->next) {
    node = node->next;
  }
  return node->ball;
}

Ball &BallList::first() { return head->ball; }

// #endregion

// #region Game

Game::Game(QObject *parent)
    : QObject(parent), shooter(QPointF(300, 300)) // 发射器位置调整到中间
      ,
      score(0), gameRunning(false) {}

void Game::initialize() {
  ballList.clear();
  shootingBalls.clear();
  score = 0;
  gameRunning = true;

  float ballDiameter = BALL_RADIUS * 2;
  float cornerOffset = ballDiameter * 1.5f;

  path.clear();

  // 起点（左上角）
  path.addPoint(QPointF(50, 50));

  // 第一个转角（右上角）
  path.addPoint(QPointF(550 - cornerOffset, 50));
  path.addPoint(QPointF(550, 50 + cornerOffset));

  // 第二个转角（右下角，180度）
  path.addPoint(QPointF(550, 550 - cornerOffset));
  path.addPoint(QPointF(550 - cornerOffset * 1, 550));
  path.addPoint(QPointF(550 - cornerOffset * 2, 550));
  path.addPoint(QPointF(550 - cornerOffset * 3, 550 - cornerOffset));

  // 第三个转角（右上角靠里）
  path.addPoint(QPointF(550 - cornerOffset * 3, 50 + cornerOffset * 3));
  path.addPoint(QPointF(550 - cornerOffset * 4, 50 + cornerOffset * 2));

  // 第四个转角（左上角靠里）
  path.addPoint(QPointF(50 + cornerOffset, 50 + cornerOffset * 2));
  path.addPoint(QPointF(50, 50 + cornerOffset * 3));

  // 第五个转角（左下角靠里）
  path.addPoint(QPointF(50, 550 - cornerOffset));
  path.addPoint(QPointF(50 + cornerOffset, 550));

  // 终点（画面底部）
  path.addPoint(QPointF(300, 550));

  createInitialBalls();
  shooter.setNextBall(Ball(shooter.getPosition(), generateRandomColor()));
}

void Game::update(float deltaTime) {
  if (!gameRunning)
    return;

  // 更新发射的球
  updateShootingBalls(deltaTime);

  float pathLength = path.getTotalLength();

  // 更新路径上的球，从前向后更新
  for (int i = 0; i < ballList.size(); ++i) {
    float currentDistance = path.getDistanceAtPoint(
        ballList[i].getPosition()); // 计算球在路径上的当前位置
    float newDistance =
        currentDistance + BALL_SPEED * deltaTime; // 计算球在路径上的新位置
    QPointF newPos = path.getPointAtDistance(newDistance); // 计算球的新位置
    ballList[i].setPosition(newPos); // 设置球的新位置
    if (i < ballList.size() - 1 &&
        ballList[i].distanceTo(ballList[i + 1]) > BALL_RADIUS * 2 + EPS)
      break; // 如果这个球和下一个球之间有空隙，则后面的所有球都不移动
  }

  // 检查游戏是否结束
  checkGameOver();
}

void Game::handleClick(const QPointF &point) {
  if (!gameRunning || !shooter.isReady())
    return;

  // 计算发射角度
  QPointF shooterPos = shooter.getPosition();
  QPointF direction = point - shooterPos;
  float angle = std::atan2(direction.y(), direction.x());

  // 设置发射角度并发射
  shooter.setAngle(angle);
  Ball shotBall = shooter.shoot();
  shootingBalls.append(shotBall);

  // 准备下一个球
  shooter.setNextBall(Ball(shooter.getPosition(), generateRandomColor()));
}

void Game::updateShootingBalls(float deltaTime) {
  for (int i = shootingBalls.size() - 1; i >= 0; --i) {
    Ball &ball = shootingBalls[i];
    ball.update(deltaTime);

    // 检查球是否飞出屏幕范围
    QPointF pos = ball.getPosition();
    float radius = ball.getRadius();

    if (pos.x() + radius < SCREEN_MIN_X || pos.x() - radius > SCREEN_MAX_X ||
        pos.y() + radius < SCREEN_MIN_Y || pos.y() - radius > SCREEN_MAX_Y) {
      shootingBalls.removeAt(i);
      continue;
    }

    // 检查碰撞
    bool hasCollision =
        collisionSystem.checkPathCollisions(ball, ballList, path);
    if (hasCollision) {
      shootingBalls.removeAt(i);
      checkMatches();
    }
  }
  checkGameOver();
}

void Game::checkMatches() {
  // get current size
  int size = ballList.size();

  removeMatchedBalls();

  // get new size
  int newSize = ballList.size();

  while (newSize < size) {
    size = newSize;
    removeMatchedBalls();
    newSize = ballList.size();
  }
}

void Game::removeMatchedBalls() {
  // guard clause
  if (ballList.size() < 3)
    return;

  // use the top ball's color as the initial color
  QColor c_ = ballList.first().getColor();

  // set flag
  int matchedCount = 1;

  // store the indices of matched balls
  std::vector<int> matchedBallIndices;

  const int size = ballList.size();

  // check the rest of the balls
  for (int i = 1; i < size; ++i) {
    // get the color of the current ball
    QColor c = ballList[i].getColor();

    if (c == c_) {
      matchedCount++;
    } else {
      if (matchedCount >= 3) {
        // add the matched balls' indices
        for (int j = i - matchedCount; j < i; ++j) {
          matchedBallIndices.push_back(j);
        }
      }

      // update flag
      c_ = c;
      matchedCount = 1;
    }
  }

  // check the last group of balls
  if (matchedCount >= 3) {
    for (int j = ballList.size() - matchedCount; j < ballList.size(); ++j) {
      matchedBallIndices.push_back(j);
    }
  }

  if (matchedBallIndices.empty())
    return;

  // remove the matched balls
  for (int i = matchedBallIndices.size() - 1; i >= 0; --i) {
    ballList.removeAt(matchedBallIndices[i]);
  }

  // update score
  score += matchedBallIndices.size() * 100;
  emit scoreChanged(score);
}

void Game::createInitialBalls() {
  const float ballSpacing = BALL_RADIUS * 2;
  float distance = 0;

  while (distance < path.getTotalLength() / 2) { // 只创建一半的路径长度
    QPointF pos = path.getPointAtDistance(distance);
    QPointF nextPos = path.getPointAtDistance(
        distance + 0.1f); // 获取稍远一点的位置来计算方向

    // 计算单位方向向量
    QPointF direction = nextPos - pos;
    float length = std::sqrt(QPointF::dotProduct(direction, direction));
    if (length > 0) {
      direction /= length;
    }

    // 创建球并设置飞行速度为0
    Ball ball(pos, generateRandomColor());
    ballList.append(ball);

    distance += ballSpacing;
  }
}

QColor Game::generateRandomColor() const {
  return COLORS[QRandomGenerator::global()->bounded(COLORS.size())];
}

void Game::checkGameOver() {
  if (!ballList.isEmpty()) {
    QPointF ballPos = ballList.last().getPosition();
    QPointF endPoint = path.getPoints().last();

    // 计算两点之间的距离
    QPointF diff = ballPos - endPoint;
    float distance = std::sqrt(QPointF::dotProduct(diff, diff));

    if (distance < BALL_RADIUS) {
      gameRunning = false;
      emit gameOver();
    }
  } else {
    score += 200;
    emit scoreChanged(score);
    gameRunning = false;
    emit gameOver();
  }
}

// #endregion
