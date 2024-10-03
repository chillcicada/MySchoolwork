#include "my_vector.h"

// maybe the file should be renamed to my_vector.tpp

// private
template <typename T> void MyVector<T>::realloc(size_t new_capacity) {
  T *new_data = new T[new_capacity];
  std::copy(data, data + size_, new_data);
  delete[] data;
  data = new_data;
  capacity_ = new_capacity;
}

// public
template <typename T>
MyVector<T>::MyVector() : data(nullptr), size_(0), capacity_(0) {}

template <typename T>
MyVector<T>::MyVector(size_t count)
    : data(new T[count]), size_(count), capacity_(count) {
  for (size_t i = 0; i < count; ++i)
    data[i] = T();
}

template <typename T> MyVector<T>::~MyVector() { delete[] data; }

template <typename T>
MyVector<T>::MyVector(const MyVector &other)
    : data(new T[other.capacity_]), size_(other.size_),
      capacity_(other.capacity_) {
  std::copy(other.data, other.data + size_, data);
}

template <typename T>
MyVector<T>::MyVector(MyVector &&other) noexcept
    : data(other.data), size_(other.size_), capacity_(other.capacity_) {
  other.data = nullptr;
  other.size_ = other.capacity_ = 0;
}

template <typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector &other) {
  if (this == &other)
    return *this;

  // this != &other
  delete[] data;
  size_ = other.size_;
  capacity_ = other.capacity_;
  data = new T[capacity_];
  std::copy(other.data, other.data + size_, data);
  return *this;
}

template <typename T>
MyVector<T> &MyVector<T>::operator=(MyVector &&other) noexcept {
  if (this == &other)
    return *this;

  // this != &other
  delete[] data;
  data = other.data;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.data = nullptr;
  other.size_ = other.capacity_ = 0;
  return *this;
}

template <typename T> T &MyVector<T>::operator[](size_t index) {
  if (index >= size_)
    throw std::out_of_range("index out of range");
  return data[index];
}

template <typename T> const T &MyVector<T>::operator[](size_t index) const {
  if (index >= size_)
    throw std::out_of_range("index out of range");
  return data[index];
}

template <typename T> T &MyVector<T>::at(size_t index) {
  if (index >= size_)
    throw std::out_of_range("index out of range");
  return data[index];
}

template <typename T> const T &MyVector<T>::at(size_t index) const {
  if (index >= size_)
    throw std::out_of_range("index out of range");
  return data[index];
}

template <typename T> void MyVector<T>::clear() {
  delete[] data;
  data = nullptr;
  size_ = capacity_ = 0;
}

template <typename T> void MyVector<T>::push_back(const T &value) {
  if (size_ == capacity_) {
    size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    realloc(new_capacity);
  }
  data[size_++] = value;
}

template <typename T> void MyVector<T>::pop_back() {
  if (size_ == 0)
    throw std::out_of_range("pop_back on empty MyVector");
  --size_;
}

template <typename T> void MyVector<T>::insert(size_t index, const T &value) {
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
}

template <typename T> void MyVector<T>::erase(size_t index) {
  if (index >= size_)
    throw std::out_of_range("index out of range");
  for (size_t i = index; i < size_ - 1; ++i)
    data[i] = data[i + 1];
  --size_;
}

template <typename T> std::size_t MyVector<T>::size() const { return size_; }

template <typename T> std::size_t MyVector<T>::capacity() const {
  return capacity_;
}

// iterator
template <typename T> MyVector<T>::iterator::iterator(T *p) : ptr(p) {}

template <typename T> T &MyVector<T>::iterator::operator*() { return *ptr; }

template <typename T>
typename MyVector<T>::iterator &MyVector<T>::iterator::operator++() {
  ++ptr;
  return *this;
}

template <typename T>
bool MyVector<T>::iterator::operator!=(const iterator &other) const {
  return ptr != other.ptr;
}

template <typename T> typename MyVector<T>::iterator MyVector<T>::begin() {
  return iterator(data);
}

template <typename T> typename MyVector<T>::iterator MyVector<T>::end() {
  return iterator(data + size_);
}
