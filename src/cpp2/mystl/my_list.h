#ifndef MY_LIST_H
#define MY_LIST_H

template <typename T> class ListNode {
public:
  T data;
  ListNode *prev;
  ListNode *next;

  ListNode(T value) : data(value), prev(nullptr), next(nullptr) {}
};

// 双向链表类
template <typename T> class DoublyLinkedList {
private:
  ListNode<T> *head;
  ListNode<T> *tail;

public:
  DoublyLinkedList() : head(nullptr), tail(nullptr) {}

  ~DoublyLinkedList() { clear(); }

  // 清空链表
  void clear() {
    ListNode<T> *current = head;
    while (current != nullptr) {
      ListNode<T> *nextNode = current->next;
      delete current;
      current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
  }

  // 在链表末尾插入新节点
  void append(T value) {
    ListNode<T> *newNode = new ListNode<T>(value);
    if (tail == nullptr) { // 如果链表为空
      head = tail = newNode;
    } else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
  }

  // 删除指定值的节点
  void remove(T value) {
    ListNode<T> *current = head;
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
        return;
      }
      current = current->next;
    }
  }
};

#endif // MY_LIST_H
