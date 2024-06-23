/**
 * @file map.cpp
 * @author chillcicada (2210227279@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-06-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "map.hpp"

#include "utils.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <stack>
#include <vector>

// !! public function implementation !! //

Map::Map() : Map(25, 25) {}

Map::Map(short row, short col) {
  r = utils::alwaysOdd(row);
  c = utils::alwaysOdd(col);

  // Initialize the map
  map = new CellType *[r] { 0 };
  for (short i{0}; i < r; i++)
    map[i] = new CellType[c]{CellType::WALL};

  // Generate the map
  genMap();
}

Map::Map(const Map &m) {
  r = m.r;
  c = m.c;

  map = new CellType *[r] { 0 };
  for (short i{0}; i < r; i++)
    map[i] = new CellType[c]{CellType::WALL};

  for (short i{0}; i < r; i++)
    for (short j{0}; j < c; j++)
      map[i][j] = m.map[i][j];

  start = m.start;
  end = m.end;
  player = m.player;
  isOver = m.isOver;
}

Map::~Map() {
  for (short i{0}; i < r; i++)
    delete[] map[i];

  delete[] map;
}

void Map::genMap() {
  setStart();

  dfs(start);

  setEnd();
  setPlayer();
}

short Map::getRow() { return r; }

short Map::getCol() { return c; }

void Map::printCell(CellType type) {
  switch (type) {
  case CellType::WALL:
    std::cout << "墙";
    break;
  case CellType::VISITED:
  case CellType::EMPTY:
    std::cout << "  ";
    break;
  case CellType::START:
    std::cout << "始";
    break;
  case CellType::END:
    std::cout << "终";
    break;
  case CellType::PLAYER:
    std::cout << "你";
  }
}
void Map::printCell(short x, short y) { printCell(getPoint(x, y)); }
void Map::printCell(Point p) { printCell(getPoint(p)); }

Point Map::getPlayer() { return player; }

Point Map::getStart() { return start; }

Point Map::getEnd() { return end; }

bool Map::getOver() { return isOver; }

bool Map::isEmpty(short x, short y) { return getPoint(x, y) != CellType::WALL; }
bool Map::isEmpty(Point p) { return isEmpty(p.x, p.y); }

bool Map::move(Point p, Direction d) {
  Point temp = p + direction[int(d)];

  if (isInRange(temp) && isEmpty(temp)) {
    setPoint(p, CellType::VISITED);
    setPoint(temp, CellType::PLAYER);

    player = temp;
    checkOver();
    return true;
  }

  return false;
}

// !! protected function implementation !! //

Map::CellType Map::getPoint(short x, short y) {
  if (isInRange(x - 1, y - 1)) {
    return map[x - 1][y - 1];
  }

  return CellType::WALL;
}
Map::CellType Map::getPoint(Point p) { return getPoint(p.x, p.y); }

void Map::setPoint(short x, short y, CellType type) {
  if (isInRange(x - 1, y - 1)) {
    map[x - 1][y - 1] = type;
  }
}
void Map::setPoint(Point p, CellType type) { setPoint(p.x, p.y, type); }

void Map::reset() {
  for (short i{0}; i < r; i++) {
    for (short j{0}; j < c; j++) {
      map[i][j] = CellType::WALL;
    }
  }

  genMap();
}

// !! private function implementation !! //

bool Map::isInRange(short x, short y) {
  return x >= 1 && x <= r && y >= 1 && y <= c;
}
bool Map::isInRange(Point p) { return isInRange(p.x, p.y); }

void Map::setPlayer() {
  for (Point d : direction) {
    Point temp = start + d;
    if (getPoint(temp) == CellType::EMPTY) {
      player = temp;
      setPoint(player, CellType::PLAYER);
      return;
    }
  }
}

void Map::setStart() {
  start = {2, 2};
  setPoint(start.x, start.y, CellType::START);
};

void Map::setEnd() {
  for (short i{short(r - 1)}; i >= 1; i--)
    for (short j{short(c - 1)}; j >= 1; j--)
      if (getPoint(i, j) == CellType::EMPTY) {
        end = {i, j};
        setPoint(end, CellType::END);
        return;
      }
}

bool Map::dfs(short x, short y) {
  if (!(isEmpty(x, y)))
    setPoint(x, y, CellType::EMPTY);

  // Generate the shuffled direction
  std::shuffle(genDirection.begin(), genDirection.end(),
               std::default_random_engine(utils::getSeed()));

  for (int i{0}; i < 4; i++) {
    short tempX = x + 2 * genDirection[i].x;
    short tempY = y + 2 * genDirection[i].y;

    if (isInRange(tempX, tempY) && getPoint(tempX, tempY) == CellType::WALL) {
      setPoint(x + genDirection[i].x, y + genDirection[i].y, CellType::EMPTY);

      if (!dfs(tempX, tempY))
        continue;
    }
  }

  return (x == start.x && y == start.y);
}
bool Map::dfs(Point p) { return dfs(p.x, p.y); }

void Map::checkOver() {
  if (player.x == end.x && player.y == end.y)
    isOver = true;
}

bool Map::isValid(Point p) {
  return (getPoint(p) != CellType::VISITED && isInRange(p) &&
          getPoint(p) != CellType::WALL);
}

Point Map::useSolve() {
  Point _start = player;
  Point _end = end;

  std::vector<std::vector<CellType>> backup(
      r, std::vector<CellType>(c, CellType::WALL));

  std::vector<std::vector<bool>> visited(r, std::vector<bool>(c, false));

  for (short i{0}; i < r; i++)
    for (short j{0}; j < c; j++) {
      if (map[i][j] == CellType::WALL)
        backup[i][j] = CellType::WALL;
      else
        backup[i][j] = CellType::EMPTY;
    }

  std::stack<Point> s;

  s.push(_start);
  visited[_start.x][_start.y] = true;

  auto next = [&]() {
    while (!s.empty()) {
      Point current = s.top();
      s.pop();

      if (current == _end)
        return current;

      for (Point d : direction) {
        Point next = current + d;

        if (isValid(next)) {
          s.push(next);
          visited[next.x][next.y] = true;
          return next;
        }
      }
    }

    return player;
  };

  return next();
}
