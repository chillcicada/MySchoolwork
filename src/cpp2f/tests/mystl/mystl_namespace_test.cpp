/**
 * @file mystl_namespace_test.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-12-06
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#include "mystl.h"
#include <utest.h>

UTEST(mystl, namespace) {
  mystl::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  ASSERT_EQ(3, v.size());

  mystl::list<int> l;
  l.append(1);
  l.append(2);
  l.append(3);
  ASSERT_EQ(3, l.size());

  mystl::deque<int> d;
  d.push_back(1);
  d.push_back(2);
  d.push_back(3);
  ASSERT_EQ(3, d.size());

  mystl::stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  ASSERT_EQ(3, s.size());

  mystl::queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  ASSERT_EQ(3, q.size());
}
