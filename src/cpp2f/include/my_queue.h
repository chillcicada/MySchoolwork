/**
 * @file my_queue.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-25
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include "my_deque.h"

template <typename T, typename MyContainer = MyDeque<T>>
class MyQueue : public MyContainer {
public:
  void push(const T &value) { MyContainer::push(value); }

  void pop() {
    if (!this->empty()) {
      MyContainer::pop();
    }
  }

  T &front() { return MyContainer::front(); }

  const T &front() const { return MyContainer::front(); }

  T &back() { return MyContainer::back(); }

  const T &back() const { return MyContainer::back(); }

  bool empty() const { return MyContainer::empty(); }

  size_t size() const { return MyContainer::size(); }
};

#endif // MY_QUEUE_H
