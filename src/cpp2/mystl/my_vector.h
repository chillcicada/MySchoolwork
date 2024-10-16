#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <algorithm>
#include <cstddef>
#include <stdexcept>

template <typename T> class MyVector {
private:
  T *data;
  size_t size_;
  size_t capacity_;

  void realloc(size_t new_capacity);

public:
  // 构造函数
  MyVector();

  explicit MyVector(size_t count);

  // 析构函数
  ~MyVector();

  // 拷贝构造函数
  MyVector(const MyVector &other);

  // 移动构造函数
  MyVector(MyVector &&other) noexcept;

  // 拷贝赋值运算符
  MyVector &operator=(const MyVector &other);

  // 移动赋值运算符
  MyVector &operator=(MyVector &&other) noexcept;

  // operator[]
  T &operator[](size_t index);

  const T &operator[](size_t index) const;

  // at
  T &at(size_t index);

  const T &at(size_t index) const;

  // clear
  void clear();

  // push_back
  void push_back(const T &value);

  // pop_back
  void pop_back();

  // insert
  void insert(size_t index, const T &value);

  // erase
  void erase(size_t index);

  // getter
  size_t size() const;
  size_t capacity() const;

  // iterator
  class iterator {
  private:
    T *ptr;

  public:
    explicit iterator(T *p);

    T &operator*();

    iterator &operator++();

    bool operator!=(const iterator &other) const;
  };

  iterator begin();
  iterator end();
};

#endif // MY_VECTOR_H
