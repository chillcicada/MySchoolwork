/**
 * @file map.hpp
 * @author chillcicada (2210227279@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-06-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <vector>

/**
 * an example of the coordinate system:
 * .-----------> x
 * |
 * |
 * |
 * |
 * v
 * y
 */

/**
 * @brief Point
 * The coordinate of the cell
 *
 */
struct Point {
  short x; ///< x coordinate
  short y; ///< y coordinate

  /**
   * @brief operator+ overload
   *
   * @param p other point
   * @return Point
   */
  Point operator+(const Point &p) const {
    return {short(x + p.x), short(y + p.y)};
  }

  /**
   * @brief operator== overload
   *
   * @param p
   * @return true if the two points are the same
   * @return false if the two points are not the same
   */
  bool operator==(const Point &p) const { return x == p.x && y == p.y; }
};

/**
 * an example of the map:
 * default    ###########
 *  start --> S   # #   #
 *            ### # # # #
 *            # # #   # #
 *            # # ##### #
 *            # # #     #
 *            # # # ### #
 *            # #   # # #
 *            # ### # # #   default
 *            #     #   E <-- end
 *            ###########
 */

/**
 * @brief The map class, used to generate the map and store the map information
 *
 */
class Map {
public:
  /**
   * @brief Construct a new Map object with no parameter
   *
   */
  Map();

  /**
   * @brief Construct a new Map object
   *
   * @param row
   * @param col
   */
  Map(short row, short col);

  /**
   * @brief copy constructor
   *
   * @param m the map to copy
   */
  Map(const Map &m);

  /**
   * @brief Destroy the Map object
   *
   */
  ~Map();

  /**
   * @brief Enum class for the cell type of the map
   *
   */
  enum class CellType : short {
    WALL,    // Wall cell
    EMPTY,   // Empty cell
    START,   // Start point cell
    END,     // End point cell
    VISITED, // Visited cell
    PLAYER,  // Player cell
  };

  /**
   * @brief direction enum class, a wrapper of the direction
   *
   */
  enum class Direction {
    RIGHT, // Right direction
    DOWN,  // Down direction
    LEFT,  // Left direction
    UP,    // Up direction
  };

  /**
   * @brief the direction, used to move the player
   *
   */
  const Point direction[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

  /**
   * @brief the direction, this will get shuffled when generating the map
   *
   */
  std::vector<Point> genDirection = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

  /**
   * @brief generate the map
   *
   */
  void genMap();

  /**
   * @brief Get the Row object
   *
   * @return short
   */
  short getRow();

  /**
   * @brief Get the Col object
   *
   * @return short
   */
  short getCol();

  /**
   * @brief print the cell
   *
   * @param type the cell type
   */
  void printCell(CellType type);
  /**
   * @brief print the cell
   *
   * @param x the x coordinate of the cell
   * @param y the y coordinate of the cell
   */
  void printCell(short x, short y);
  /**
   * @brief print the cell
   *
   * @param p the point of the cell
   */
  void printCell(Point p);

  /**
   * @brief Get whether the game is over
   *
   * @return true if the game is over
   * @return false else
   */
  bool getOver();

  /**
   * @brief Get the Player point
   *
   * @return Point
   */
  Point getPlayer();

  /**
   * @brief Get the Start point
   *
   * @return Point
   */
  Point getStart();

  /**
   * @brief Get the End point
   *
   * @return Point
   */
  Point getEnd();

  /**
   * @brief is the cell empty
   *
   * @param x the x coordinate of the cell
   * @param y the y coordinate of the cell
   * @return true if the cell is empty
   * @return false if the cell is not empty
   */
  bool isEmpty(short x, short y);
  /**
   * @brief is the cell empty
   *
   * @param p the point of the cell
   * @return true if the cell is empty
   * @return false if the cell is not empty
   */
  bool isEmpty(Point p);

  /**
   * @brief move the player
   *
   * @param p the point of the player
   * @param d the direction of the player
   * @return true if the player can move
   * @return false if the player can not move
   */
  bool move(Point p, Direction d);

protected:
  /**
   * @brief Get the Point type
   *
   * @param x the x coordinate of the cell
   * @param y the y coordinate of the cell
   * @return CellType
   */
  CellType getPoint(short x, short y);
  /**
   * @brief Get the Point type
   *
   * @param p the point of the cell
   * @return CellType
   */
  CellType getPoint(Point p);

  /**
   * @brief Set the Point type
   *
   * @param x the x coordinate of the cell
   * @param y the y coordinate of the cell
   * @param type
   */
  void setPoint(short x, short y, CellType type);
  /**
   * @brief Set the Point type
   *
   * @param p the point of the cell
   * @param type
   */
  void setPoint(Point p, CellType type);

  /**
   * @brief reset the map
   *
   */
  void reset();

private:
  /**
   * @brief row and column of the map
   *
   */
  short r, c;

  /**
   * @brief the map
   *
   */
  CellType **map;

  /**
   * @brief the player point
   *
   */
  Point player;

  /**
   * @brief the start point
   *
   */
  Point start{2, 2};

  /**
   * @brief the end point
   *
   */
  Point end;

  /**
   * @brief whether the cell is in the range of the map
   *
   * @param x the x coordinate of the cell
   * @param y the y coordinate of the cell
   * @return true the cell is in the range of the map
   * @return false the cell is not in the range of the map
   */
  bool isInRange(short x, short y);
  /**
   * @brief whether the cell is in the range of the map
   *
   * @param p the point of the cell
   * @return true the cell is in the range of the map
   * @return false the cell is not in the range of the map
   */
  bool isInRange(Point p);

  /**
   * @brief whether the game is over
   *
   */
  bool isOver{false};

  /**
   * @brief check whether the game is over
   *
   */
  void checkOver();

  /**
   * @brief Set the Player point
   *
   */
  void setPlayer();

  /**
   * @brief Set the Start point
   *
   */
  void setStart();

  /**
   * @brief Set the End point
   *
   */
  void setEnd();

  /**
   * @brief use dfs to generate the cell
   *
   * @param x
   * @param y
   * @return true if the cell is generated
   * @return false if the cell is not generated
   */
  bool dfs(short x, short y);
  /**
   * @brief use dfs to generate the cell
   *
   * @param p
   * @return true if the cell is generated
   * @return false if the cell is not generated
   */
  bool dfs(Point p);

  bool isValid(Point p);

  // bool dfsSolve(Point p,, const Point _end,
  //               std::vector<Point> &path);

  /**
   * @brief Get the Next Point from close that the player should move
   *
   * @param p
   * @return Point
   */
  Point getNextPoint(Point p);

  Point useSolve();

  /**
   * @brief friend class UI
   *
   */
  friend class UI;
};

#endif // __MAP_HPP__
