/**
 * @file my_deque_test.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-25
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#include "my_deque.h"
#include <utest.h>

UTEST(my_deque, base) {
  MyDeque<int> d1;
  ASSERT_TRUE(d1.empty());
  ASSERT_EQ(0, d1.size());

  MyDeque<int> d2(10);
  ASSERT_FALSE(d2.empty());
  ASSERT_EQ(10, d2.size());
}

UTEST(my_deque, push_pop) {
  MyDeque<int> d;
  d.push_back(1);  // 1
  d.push_back(2);  // 1 2
  d.push_front(3); // 3 1 2
  ASSERT_EQ(3, d.size());

  d.pop_back(); // 3 1
  ASSERT_EQ(2, d.size());
  ASSERT_EQ(1, d.back());

  d.pop_front(); // 1
  ASSERT_EQ(1, d.size());
  ASSERT_EQ(1, d.front());

  d.pop_back();
  ASSERT_EQ(0, d.size());
  ASSERT_TRUE(d.empty());
}

UTEST(my_deque, clear) {
  MyDeque<int> d;
  d.push_back(1);
  d.push_back(2);
  d.push_back(3);
  d.clear();
  ASSERT_TRUE(d.empty());
  ASSERT_EQ(0, d.size());
}

UTEST(my_deque, reserve) {
  MyDeque<int> d;
  d.reserve(10);
  ASSERT_EQ(0, d.size());
  ASSERT_GE(64, d.capacity());
}

UTEST(my_deque, resize) {
  MyDeque<int> d;
  d.resize(10);
  ASSERT_EQ(10, d.size());
  ASSERT_GE(64, d.capacity());
}

UTEST(my_deque, at_front_back) {
  MyDeque<int> d;
  d.push_back(1);
  d.push_back(2);
  d.push_back(3);
  ASSERT_EQ(1, d.front());
  ASSERT_EQ(3, d.back());
  ASSERT_EQ(2, d[1]);
}
