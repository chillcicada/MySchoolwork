#ifndef MY_CONTAINER_H
#define MY_CONTAINER_H

#include <cstddef>

template <typename T> class MyContainer {
public:
  virtual ~MyContainer() = default;

  // add element
  virtual void push(const T &value) = 0;

  // pop element
  virtual void pop() = 0;

  // get the top element
  virtual T &top() = 0;
  virtual const T &top() const = 0;

  // is the container empty
  virtual bool empty() const = 0;

  // get the size of container
  virtual size_t size() const = 0;

  // clear the container
  virtual void clear() = 0;
};

#endif // MY_CONTAINER_H
