#include "my_queue.h"
#include <utest.h>

UTEST(my_queue, default_constructor) {
  MyQueue<int> my_queue;
  ASSERT_TRUE(my_queue.empty());
  ASSERT_EQ(0, my_queue.size());
}

UTEST(my_queue, push) {
  MyQueue<int> my_queue;
  my_queue.push(1);
  my_queue.push(2);
  my_queue.push(3);
  ASSERT_FALSE(my_queue.empty());
  ASSERT_EQ(3, my_queue.size());
}

UTEST(my_queue, pop) {
  MyQueue<int> my_queue;
  my_queue.push(1);
  my_queue.push(2);
  my_queue.push(3);
  my_queue.pop();
  ASSERT_EQ(2, my_queue.size());
  my_queue.pop();
  ASSERT_EQ(1, my_queue.size());
  my_queue.pop();
  ASSERT_TRUE(my_queue.empty());
}

UTEST(my_queue, front) {
  MyQueue<int> my_queue;
  my_queue.push(1);
  my_queue.push(2);
  my_queue.push(3);
  ASSERT_EQ(1, my_queue.front());
  my_queue.pop();
  ASSERT_EQ(1, my_queue.front());
  my_queue.pop();
  ASSERT_EQ(1, my_queue.front());
}

UTEST(my_queue, back) {
  MyQueue<int> my_queue;
  my_queue.push(1);
  my_queue.push(2);
  my_queue.push(3);
  ASSERT_EQ(3, my_queue.back());
  my_queue.pop();
  ASSERT_EQ(2, my_queue.back());
  my_queue.pop();
  ASSERT_EQ(1, my_queue.back());
}

UTEST(my_queue, size) {
  MyQueue<int> my_queue;
  ASSERT_EQ(0, my_queue.size());
  my_queue.push(1);
  ASSERT_EQ(1, my_queue.size());
  my_queue.push(2);
  ASSERT_EQ(2, my_queue.size());
  my_queue.pop();
  ASSERT_EQ(1, my_queue.size());
  my_queue.pop();
  ASSERT_EQ(0, my_queue.size());
}
