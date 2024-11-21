#pragma once
#include "Ball.h"
#include "Path.h"
#include <QVector>

class BallList;

class CollisionSystem {
public:
  CollisionSystem();

  bool checkPathCollisions(const Ball &shootingBall, BallList &pathBalls,
                           const Path &path);

  struct CollisionResult {
    bool hasCollision;
    int collisionIndex;
  };

private:
  CollisionResult findCollision(const Ball &ball, BallList &balls) const;

  void handleCollision(Ball ball, BallList &balls, const Path &path,
                       const int &collisionIndex);
};
