## MySTL

### MyContainer

实现了 `Container` 的基本接口，代码如下：

```cpp
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
```

### MyVector

基于数组动态分配大小。

```cpp
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
```

### MyDeque

基于课上讲的「中控器」模式实现内存管理。

```cpp
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
```

### MyList

考虑到实际使用场景，把 `MyListNode` 作为 `MyList` 的一部分放进去了，当然解耦合也是可以的，实现上没有太多的细节。

```cpp
#ifndef MY_LIST_H
#define MY_LIST_H

template <typename T> class MyList {
public:
  class MyListNode {
  public:
    T data;

    MyListNode *prev;
    MyListNode *next;

    MyListNode(T value) : data(value), prev(nullptr), next(nullptr) {}
  };

  MyListNode *head;
  MyListNode *tail;

  // constructor
  MyList() : head(nullptr), tail(nullptr), size_(0) {}

  // destructor
  ~MyList() { clear(); }

  // copy constructor
  MyList(const MyList &other) {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
    MyListNode *current = other.head;
    while (current != nullptr) {
      append(current->data);
      current = current->next;
    }
  }

  // move constructor
  MyList(MyList &&other) {
    head = other.head;
    tail = other.tail;
    size_ = other.size_;
    other.head = nullptr;
    other.tail = nullptr;
    other.size_ = 0;
  }

  // copy assignment
  MyList &operator=(const MyList &other) {
    if (this != &other) {
      clear();
      MyListNode *current = other.head;
      while (current != nullptr) {
        append(current->data);
        current = current->next;
      }
    }
    return *this;
  }

  // move assignment
  MyList &operator=(MyList &&other) {
    if (this != &other) {
      clear();
      head = other.head;
      tail = other.tail;
      size_ = other.size_;
      other.head = nullptr;
      other.tail = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  // operator[]
  T &operator[](int index) {
    MyListNode *current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current->data;
  }

  // clear the list
  void clear() {
    MyListNode *current = head;
    while (current != nullptr) {
      MyListNode *next = current->next;
      delete current;
      current = next;
    }
    head = nullptr;
    tail = nullptr;
    size_ = 0;
  }

  // append a value to the list
  void append(T value) {
    MyListNode *newNode = new MyListNode(value);
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
    size_++;
  }

  // remove a value from the list
  void remove(T value) {
    MyListNode *current = head;
    while (current != nullptr) {
      if (current->data == value) {
        if (current->prev != nullptr) {
          current->prev->next = current->next;
        } else {
          head = current->next;
        }
        if (current->next != nullptr) {
          current->next->prev = current->prev;
        } else {
          tail = current->prev;
        }
        delete current;
        size_--;
        return;
      }
      current = current->next;
    }
  }

  // append at index
  void appendAt(int index, T value) {
    MyListNode *newNode = new MyListNode(value);
    MyListNode *current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    if (current->prev != nullptr) {
      current->prev->next = newNode;
      newNode->prev = current->prev;
    } else {
      head = newNode;
    }
    newNode->next = current;
    current->prev = newNode;
    size_++;
  }

  // remove at index
  void removeAt(int index) {
    MyListNode *current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    if (current->prev != nullptr) {
      current->prev->next = current->next;
    } else {
      head = current->next;
    }
    if (current->next != nullptr) {
      current->next->prev = current->prev;
    } else {
      tail = current->prev;
    }
    delete current;
    size_--;
  }

  // get size
  int size() const { return size_; }

  // check if the list is empty
  bool empty() const { return size_ == 0; }

private:
  int size_;
};

#endif // MY_LIST_H
```

### MyStack

基于 `MyDeque` 实现，`MyContainer` 的适配器。

```cpp
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
```

### MyQueue

基于 `MyDeque` 实现，`MyContainer` 的适配器。

```cpp
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
```

### 单元测试

单元测试使用的框架是 `utest.h`，以 `vector` 为例，测试结构如下：

```cpp
#include "../mystl/my_vector.h"
#include <utest.h>

UTEST(my_vector, base) {
  MyVector<int> v1;
  ASSERT_TRUE(v1.empty());
  ASSERT_EQ(0, v1.size());

  MyVector<int> v2(10);
  ASSERT_FALSE(v2.empty());
  ASSERT_EQ(10, v2.size());
}

UTEST(my_vector, push_pop) {
  MyVector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push(3);
  ASSERT_EQ(3, v.size());

  v.pop_back();
  ASSERT_EQ(2, v.size());
  ASSERT_EQ(2, v[1]);

  v.pop_back();
  ASSERT_EQ(1, v.size());
  ASSERT_EQ(1, v[0]);

  v.pop();
  ASSERT_EQ(0, v.size());
  ASSERT_TRUE(v.empty());
}

UTEST(my_vector, clear) {
  MyVector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.clear();
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(0, v.size());
}

UTEST(my_vector, reserve) {
  MyVector<int> v;
  v.reserve(10);
  ASSERT_EQ(0, v.size());
  ASSERT_GE(10, v.capacity());
}

UTEST(my_vector, resize) {
  MyVector<int> v;
  v.resize(10);
  ASSERT_EQ(10, v.size());
  ASSERT_GE(16, v.capacity());
}

UTEST(my_vector, at_top_back) {
  MyVector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  ASSERT_EQ(1, v.at(0));
  ASSERT_EQ(2, v.at(1));
  ASSERT_EQ(3, v.at(2));
  ASSERT_EQ(3, v.top());
  ASSERT_EQ(3, v.back());
}

UTEST(my_vector, insert_erase) {
  MyVector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.insert(1, 4);
  ASSERT_EQ(4, v.at(1));
  ASSERT_EQ(2, v.at(2));
  v.erase(1);
  ASSERT_EQ(2, v.at(1));
  ASSERT_EQ(3, v.at(2));
}
```

测试部分的构建选项为：

```lua
-- xmake.lua
add_requires("utest.h")

target("tests")
  set_languages("c++17")
  add_headerfiles("mystl/*.h")
  -- add the main entry file
  add_files("tests/main.cpp")
  -- source files will automatically be added and bundled to the target
  add_files("tests/*_test.cpp")
  add_packages("utest.h")
```

其中入口文件 `main.cpp` 内容如下：

```cpp
#include <utest.h>

UTEST_MAIN()
```

构建脚本为：

```makefile
test:
  xmake && xmake r tests

test-snap: # generate snapshot
  xmake && xmake r tests > tests/test.snap
```

生成的测试快照即 `test.snap`，内容如下：

```snap
[==========] Running 34 test cases.
[ RUN      ] my_vector.base
[       OK ] my_vector.base (1000ns)
[ RUN      ] my_vector.push_pop
[       OK ] my_vector.push_pop (2000ns)
[ RUN      ] my_vector.clear
[       OK ] my_vector.clear (1000ns)
[ RUN      ] my_vector.reserve
[       OK ] my_vector.reserve (0ns)
[ RUN      ] my_vector.resize
[       OK ] my_vector.resize (1000ns)
[ RUN      ] my_vector.at_top_back
[       OK ] my_vector.at_top_back (0ns)
[ RUN      ] my_vector.insert_erase
[       OK ] my_vector.insert_erase (0ns)
[ RUN      ] my_stack.constructor
[       OK ] my_stack.constructor (1000ns)
[ RUN      ] my_stack.push
[       OK ] my_stack.push (1000ns)
[ RUN      ] my_stack.pop
[       OK ] my_stack.pop (0ns)
[ RUN      ] my_stack.top
[       OK ] my_stack.top (0ns)
[ RUN      ] my_stack.empty
[       OK ] my_stack.empty (1000ns)
[ RUN      ] my_list.base
[       OK ] my_list.base (1000ns)
[ RUN      ] my_list.copy_constructor
[       OK ] my_list.copy_constructor (1000ns)
[ RUN      ] my_list.move_constructor
[       OK ] my_list.move_constructor (0ns)
[ RUN      ] my_list.copy_assignment
[       OK ] my_list.copy_assignment (1000ns)
[ RUN      ] my_list.move_assignment
[       OK ] my_list.move_assignment (1000ns)
[ RUN      ] my_list.operator_brackets
[       OK ] my_list.operator_brackets (1000ns)
[ RUN      ] my_list.append_remove
[       OK ] my_list.append_remove (1000ns)
[ RUN      ] my_list.append_at
[       OK ] my_list.append_at (1000ns)
[ RUN      ] my_list.remove_at
[       OK ] my_list.remove_at (0ns)
[ RUN      ] my_list.clear
[       OK ] my_list.clear (0ns)
[ RUN      ] my_queue.default_constructor
[       OK ] my_queue.default_constructor (0ns)
[ RUN      ] my_queue.push
[       OK ] my_queue.push (0ns)
[ RUN      ] my_queue.pop
[       OK ] my_queue.pop (1000ns)
[ RUN      ] my_queue.front
[       OK ] my_queue.front (1000ns)
[ RUN      ] my_queue.back
[       OK ] my_queue.back (1000ns)
[ RUN      ] my_queue.size
[       OK ] my_queue.size (1000ns)
[ RUN      ] my_deque.base
[       OK ] my_deque.base (1000ns)
[ RUN      ] my_deque.push_pop
[       OK ] my_deque.push_pop (0ns)
[ RUN      ] my_deque.clear
[       OK ] my_deque.clear (1000ns)
[ RUN      ] my_deque.reserve
[       OK ] my_deque.reserve (1000ns)
[ RUN      ] my_deque.resize
[       OK ] my_deque.resize (0ns)
[ RUN      ] my_deque.at_front_back
[       OK ] my_deque.at_front_back (0ns)
[==========] 34 test cases ran.
[  PASSED  ] 34 tests.
```
