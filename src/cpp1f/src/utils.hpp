/**
 * @file utils.hpp
 * @author chillcicada (2210227279@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-06-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <chrono>
#include <string>

namespace utils {
/**
 * @brief always return an odd number,
 * if input number is even, return the next odd number
 *
 * @param x input number
 * @return short
 */
inline short alwaysOdd(const short x) { return x % 2 == 1 ? x : x + 1; }
/**
 * @brief always return an odd number,
 * if input number is even, return the next odd number
 *
 * @param x input number
 * @return int
 */
inline int alwaysOdd(const int x) { return x % 2 == 1 ? x : x + 1; }

/**
 * @brief Get the Max Length of a @c std::string array
 *
 * @param items string array
 * @param num number of items
 * @return short
 */
inline short getMaxLength(const std::string *items, const short num) {
  short maxLength{0};

  for (short i{0}; i < num; i++) {
    short length = short(items[i].length());
    maxLength = (length > maxLength ? length : maxLength);
  }

  return maxLength;
}
/**
 * @brief Get the Max Length of a @c std::string array
 *
 * @param items string array
 * @param num number of items
 * @return short
 */
inline short getMaxLength(const char *items[], const short num) {
  short maxLength{0};

  for (short i{0}; i < num; i++) {
    short length = short(strlen(items[i]));
    maxLength = (length > maxLength ? length : maxLength);
  }

  return maxLength;
}

/**
 * @brief Get the random Seed
 *
 * @return unsigned
 */
inline unsigned getSeed() {
  return std::chrono::system_clock::now().time_since_epoch().count();
}
}; // namespace utils

#endif // __UTILS_HPP__
