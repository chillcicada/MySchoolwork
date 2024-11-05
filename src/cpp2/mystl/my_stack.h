#ifndef MY_STACK_H
#define MY_STACK_H

#include "my_deque.h"

template <typename T, typename MyContainer = MyDeque<T>>
class MyStack : public MyContainer {
public:
  void push(const T &value) { MyContainer::push(value); }

  void pop() {
    if (!this->empty()) {
      MyContainer::pop();
    }
  }

  T &top() { return MyContainer::top(); }

  const T &top() const { return MyContainer::top(); }

  bool empty() const { return MyContainer::empty(); }

  size_t size() const { return MyContainer::size(); }
};

#endif // MY_STACK_H
