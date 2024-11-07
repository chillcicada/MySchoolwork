#ifndef MY_DEQUE_H
#define MY_DEQUE_H

#include "my_container.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

template <typename T> class MyDeque : public MyContainer<T> {
private:
  static const size_t CHUNK_SIZE = 8; // 每个块的大小

  T **map;             // 中控器
  size_t map_capacity; // 中控器容量
  size_t start_chunk;  // 起始块索引
  size_t start_pos;    // 起始块中的位置
  size_t size_;

  void initialize_map(size_t n) {
    map_capacity = std::max(size_t(8), n / CHUNK_SIZE + 1);
    map = new T *[map_capacity];
    for (size_t i = 0; i < map_capacity; i++) {
      map[i] = new T[CHUNK_SIZE];
    }
    start_chunk = map_capacity / 2;
    start_pos = CHUNK_SIZE / 2;
    size_ = 0;
  }

  void ensure_capacity(size_t needed_chunks) {
    if (needed_chunks > map_capacity) {
      size_t new_capacity = map_capacity * 2;
      T **new_map = new T *[new_capacity];

      // 重新分配并移动现有块到中间位置
      size_t new_start = (new_capacity - needed_chunks) / 2;
      for (size_t i = 0; i < map_capacity; i++) {
        new_map[new_start + i] = map[i];
      }

      // 分配新块
      for (size_t i = 0; i < new_start; i++) {
        new_map[i] = new T[CHUNK_SIZE];
      }
      for (size_t i = new_start + map_capacity; i < new_capacity; i++) {
        new_map[i] = new T[CHUNK_SIZE];
      }

      delete[] map;
      map = new_map;
      start_chunk = new_start;
      map_capacity = new_capacity;
    }
  }

public:
  // constructor without arguments
  MyDeque() { initialize_map(0); }

  // constructor with count
  explicit MyDeque(size_t count) {
    initialize_map(count);
    size_ = count;
  }

  // destructor
  ~MyDeque() override {
    for (size_t i = 0; i < map_capacity; i++) {
      delete[] map[i];
    }
    delete[] map;
  }

  // copy constructor
  MyDeque(const MyDeque &other) {
    initialize_map(other.size_);
    for (size_t i = 0; i < other.size_; i++) {
      push_back(other[i]);
    }
  }

  // move constructor
  MyDeque(MyDeque &&other) noexcept {
    map = other.map;
    map_capacity = other.map_capacity;
    start_chunk = other.start_chunk;
    start_pos = other.start_pos;
    size_ = other.size_;

    other.map = nullptr;
    other.map_capacity = 0;
    other.start_chunk = 0;
    other.start_pos = 0;
    other.size_ = 0;
  }

  // copy assignment operator
  MyDeque &operator=(const MyDeque &other) {
    if (this == &other) {
      return *this;
    }

    clear();
    for (size_t i = 0; i < other.size_; i++) {
      push_back(other[i]);
    }
    return *this;
  }

  // move assignment operator
  MyDeque &operator=(MyDeque &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    clear();
    map = other.map;
    map_capacity = other.map_capacity;
    start_chunk = other.start_chunk;
    start_pos = other.start_pos;
    size_ = other.size_;

    other.map = nullptr;
    other.map_capacity = 0;
    other.start_chunk = 0;
    other.start_pos = 0;
    other.size_ = 0;

    return *this;
  }

  // operator[]
  T &operator[](size_t n) {
    size_t chunk = start_chunk + (start_pos + n) / CHUNK_SIZE;
    size_t pos = (start_pos + n) % CHUNK_SIZE;
    return map[chunk][pos];
  }

  // front
  T &front() { return map[start_chunk][start_pos]; }
  const T &front() const { return map[start_chunk][start_pos]; }

  // back
  T &back() {
    size_t end_chunk = (start_chunk + (start_pos + size_ - 1) / CHUNK_SIZE);
    size_t end_pos = (start_pos + size_ - 1) % CHUNK_SIZE;
    return map[end_chunk][end_pos];
  }
  const T &back() const {
    size_t end_chunk = (start_chunk + (start_pos + size_ - 1) / CHUNK_SIZE);
    size_t end_pos = (start_pos + size_ - 1) % CHUNK_SIZE;
    return map[end_chunk][end_pos];
  }

  // top
  T &top() override { return back(); }
  const T &top() const override { return back(); }

  // at
  T &at(size_t n) {
    if (n >= size_) {
      throw std::out_of_range("index out of range");
    }
    return operator[](n);
  }
  const T &at(size_t n) const {
    if (n >= size_) {
      throw std::out_of_range("index out of range");
    }
    return operator[](n);
  }

  // pop back
  void pop_back() {
    if (size_ == 0) {
      throw std::out_of_range("pop on empty MyDeque");
    }
    size_--;
  }

  // pop front
  void pop_front() {
    if (size_ == 0) {
      throw std::out_of_range("pop on empty MyDeque");
    }
    size_--;
    start_pos++;
    if (start_pos == CHUNK_SIZE) {
      start_chunk++;
      start_pos = 0;
    }
  }

  // pop
  void pop() override { pop_back(); }

  // push back
  void push_back(const T &value) {
    size_t end_chunk = (start_chunk + (start_pos + size_) / CHUNK_SIZE);
    size_t end_pos = (start_pos + size_) % CHUNK_SIZE;

    if (end_chunk >= map_capacity) {
      ensure_capacity(end_chunk + 1);
    }

    map[end_chunk][end_pos] = value;
    size_++;
  }

  // push front
  void push_front(const T &value) {
    if (start_pos == 0) {
      if (start_chunk == 0) {
        ensure_capacity(map_capacity + 1);
      }
      start_chunk--;
      start_pos = CHUNK_SIZE;
    }
    start_pos--;
    map[start_chunk][start_pos] = value;
    size_++;
  }

  // push
  void push(const T &value) override { push_back(value); }

  // reserve
  void reserve(size_t new_capacity) {
    if (new_capacity > capacity()) {
      ensure_capacity(new_capacity / CHUNK_SIZE + 1);
    }
  }

  // resize
  void resize(size_t new_size) {
    if (new_size < size_) {
      size_ = new_size;
    } else {
      reserve(new_size);
      for (size_t i = size_; i < new_size; i++) {
        push_back(T());
      }
    }
  }

  // is empty
  bool empty() const override { return size_ == 0; }

  // get size
  size_t size() const override { return size_; }

  // get capacity
  size_t capacity() const { return map_capacity * CHUNK_SIZE; }

  // clear
  void clear() override {
    for (size_t i = 0; i < map_capacity; i++) {
      delete[] map[i];
    }
    delete[] map;
    initialize_map(0);
  }
};

#endif // MY_DEQUE_H
