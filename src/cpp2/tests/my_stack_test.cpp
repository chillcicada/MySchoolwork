#include "my_stack.h"
#include <utest.h>

UTEST(my_stack, constructor) {
  MyStack<int> s;
  EXPECT_EQ(0, s.size());
}

UTEST(my_stack, push) {
  MyStack<int> s;
  s.push(1);
  EXPECT_EQ(1, s.size());
  s.push(2);
  EXPECT_EQ(2, s.size());
}

UTEST(my_stack, pop) {
  MyStack<int> s;
  s.push(1);
  s.push(2);
  s.pop();
  EXPECT_EQ(1, s.size());
  s.pop();
  EXPECT_EQ(0, s.size());
}

UTEST(my_stack, top) {
  MyStack<int> s;
  s.push(1);
  s.push(2);
  EXPECT_EQ(2, s.top());
  s.pop();
  EXPECT_EQ(1, s.top());
}

UTEST(my_stack, empty) {
  MyStack<int> s;
  EXPECT_TRUE(s.empty());
  s.push(1);
  EXPECT_FALSE(s.empty());
  s.pop();
  EXPECT_TRUE(s.empty());
}
