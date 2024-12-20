/**
 * @file my_vector_test.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-25
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#include "my_vector.h"
#include <utest.h>

UTEST(my_vector, base) {
  MyVector<int> v1;
  ASSERT_TRUE(v1.empty());
  ASSERT_EQ(0, v1.size());

  MyVector<int> v2(10);
  ASSERT_FALSE(v2.empty());
  ASSERT_EQ(10, v2.size());
}

UTEST(my_vector, push_pop) {
  MyVector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push(3);
  ASSERT_EQ(3, v.size());

  v.pop_back();
  ASSERT_EQ(2, v.size());
  ASSERT_EQ(2, v[1]);

  v.pop_back();
  ASSERT_EQ(1, v.size());
  ASSERT_EQ(1, v[0]);

  v.pop();
  ASSERT_EQ(0, v.size());
  ASSERT_TRUE(v.empty());
}

UTEST(my_vector, clear) {
  MyVector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.clear();
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(0, v.size());
}

UTEST(my_vector, reserve) {
  MyVector<int> v;
  v.reserve(10);
  ASSERT_EQ(0, v.size());
  ASSERT_GE(10, v.capacity());
}

UTEST(my_vector, resize) {
  MyVector<int> v;
  v.resize(10);
  ASSERT_EQ(10, v.size());
  ASSERT_GE(16, v.capacity());
}

UTEST(my_vector, at_top_back) {
  MyVector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  ASSERT_EQ(1, v.at(0));
  ASSERT_EQ(2, v.at(1));
  ASSERT_EQ(3, v.at(2));
  ASSERT_EQ(3, v.top());
  ASSERT_EQ(3, v.back());
}

UTEST(my_vector, insert_erase) {
  MyVector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.insert(1, 4);
  ASSERT_EQ(4, v.at(1));
  ASSERT_EQ(2, v.at(2));
  v.erase(1);
  ASSERT_EQ(2, v.at(1));
  ASSERT_EQ(3, v.at(2));
}
