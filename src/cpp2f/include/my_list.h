/**
 * @file my_list.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-25
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

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
