#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "my_container.h"

#include <algorithm>
#include <stdexcept>

template <typename T> class MyVector : public MyContainer<T> {
private:
  T *data;
  size_t size_;
  size_t capacity_;

  void realloc(size_t new_capacity) {
    T *new_data = new T[new_capacity];
    std::copy(data, data + size_, new_data);
    delete[] data;
    data = new_data;
    capacity_ = new_capacity;
  };

public:
  // constructor without arguments
  MyVector() : data(nullptr), size_(0), capacity_(0) {};

  // constructor with count
  explicit MyVector(size_t count, const T &value = T())
      : data(new T[count]), size_(count), capacity_(count) {
    for (size_t i = 0; i < count; ++i)
      data[i] = T();
  };

  // destructor
  ~MyVector() override { delete[] data; };

  // copy constructor
  MyVector(const MyVector &other)
      : data(new T[other.capacity_]), size_(other.size_),
        capacity_(other.capacity_) {
    std::copy(other.data, other.data + size_, data);
  };

  // move constructor
  MyVector(MyVector &&other) noexcept
      : data(other.data), size_(other.size_), capacity_(other.capacity_) {
    other.data = nullptr;
    other.size_ = other.capacity_ = 0;
  };

  // copy assignment operator
  MyVector &operator=(const MyVector &other) {
    if (this == &other)
      return *this;

    delete[] data;
    size_ = other.size_;
    capacity_ = other.capacity_;
    data = new T[capacity_];
    std::copy(other.data, other.data + size_, data);
    return *this;
  };

  // move assignment operator
  MyVector &operator=(MyVector &&other) noexcept {
    if (this == &other)
      return *this;

    delete[] data;
    data = other.data;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data = nullptr;
    other.size_ = other.capacity_ = 0;
    return *this;
  };

  // operator[]
  T &operator[](size_t index) {
    if (index >= size_)
      throw std::out_of_range("index out of range");
    return data[index];
  };

  const T &operator[](size_t index) const {
    if (index >= size_)
      throw std::out_of_range("index out of range");
    return data[index];
  };

  // at
  T &at(size_t index) {
    if (index >= size_)
      throw std::out_of_range("index out of range");
    return data[index];
  };
  const T &at(size_t index) const {
    if (index >= size_)
      throw std::out_of_range("index out of range");
    return data[index];
  };

  // is empty
  bool empty() const override { return size_ == 0; };

  // clear
  void clear() override {
    delete[] data;
    data = nullptr;
    size_ = capacity_ = 0;
  };

  // push
  void push(const T &value) override {
    if (size_ == capacity_) {
      size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
      realloc(new_capacity);
    }
    data[size_++] = value;
  };

  // push_back
  void push_back(const T &value) { return push(value); };

  // pop
  void pop() override {
    if (size_ == 0)
      throw std::out_of_range("pop_back on empty MyVector");
    --size_;
  };

  // pop_back
  void pop_back() { return pop(); };

  // top
  T &top() override {
    if (size_ == 0)
      throw std::out_of_range("top on empty MyVector");
    return data[size_ - 1];
  };
  const T &top() const override {
    if (size_ == 0)
      throw std::out_of_range("top on empty MyVector");
    return data[size_ - 1];
  };

  // back
  T &back() { return top(); };
  const T &back() const { return top(); };

  // insert
  void insert(size_t index, const T &value) {
    if (index > size_)
      throw std::out_of_range("index out of range");
    if (size_ == capacity_) {
      size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
      realloc(new_capacity);
    }
    for (size_t i = size_; i > index; --i)
      data[i] = data[i - 1];
    data[index] = value;
    ++size_;
  };

  // erase
  void erase(size_t index) {
    if (index >= size_)
      throw std::out_of_range("index out of range");
    for (size_t i = index; i < size_ - 1; ++i)
      data[i] = data[i + 1];
    --size_;
  };

  // resize
  void resize(size_t new_size) {
    if (new_size > capacity_) {
      size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
      while (new_capacity < new_size)
        new_capacity *= 2;
      realloc(new_capacity);
    }
    size_ = new_size;
  };

  // reserve
  void reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
      realloc(new_capacity);
    }
  };

  // get size
  size_t size() const override { return size_; };

  // get capacity
  size_t capacity() const { return capacity_; };

  // iterator
  class iterator {
  private:
    T *ptr;

  public:
    explicit iterator(T *p) : ptr(p) {}

    T &operator*() { return *ptr; };

    iterator &operator++() {
      ++ptr;
      return *this;
    };

    bool operator!=(const iterator &other) const { return ptr != other.ptr; };
  };

  iterator begin() { return iterator(data); };
  iterator end() { return iterator(data + size_); };
};

#endif // MY_VECTOR_H
