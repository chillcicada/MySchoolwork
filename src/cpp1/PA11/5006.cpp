#include <stdio.h>
#include <stdlib.h>

// 定义多项式的结构体
typedef struct Node {
  int coef;
  int exp;
  struct Node *next;
} Node;

// 创建链表
Node *createList(int n) {
  Node *head{NULL}, *tail{NULL};
  for (int i{0}; i < n; i++) {
    int c, e;
    scanf("%d %d", &c, &e);
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->coef = c;
    newNode->exp = e;
    newNode->next = NULL;
    if (head == NULL) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
  }
  return head;
}

// 打印链表
void printList(Node *head) {
  if (head == NULL) {
    printf("0\n");
    return;
  }

  Node *p = head;
  int k{0};

  do {
    k++;
  } while ((p = p->next) != NULL);

  printf("%d\n", k);

  p = head;
  do {
    printf("%d %d\n", p->coef, p->exp);
  } while ((p = p->next) != NULL);
}

// 多项式加法
Node *addPoly(Node *A, Node *B) {
  Node *result = NULL, *tail = NULL;
  Node *p = A, *q = B;
  while (p != NULL && q != NULL) {
    if (p->exp < q->exp) {
      Node *newNode = (Node *)malloc(sizeof(Node));
      newNode->coef = p->coef;
      newNode->exp = p->exp;
      newNode->next = NULL;
      if (result == NULL) {
        result = newNode;
        tail = newNode;
      } else {
        tail->next = newNode;
        tail = newNode;
      }
      p = p->next;
    } else if (p->exp > q->exp) {
      Node *newNode = (Node *)malloc(sizeof(Node));
      newNode->coef = q->coef;
      newNode->exp = q->exp;
      newNode->next = NULL;
      if (result == NULL) {
        result = newNode;
        tail = newNode;
      } else {
        tail->next = newNode;
        tail = newNode;
      }
      q = q->next;
    } else {
      int sum = p->coef + q->coef;
      if (sum != 0) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->coef = sum;
        newNode->exp = p->exp;
        newNode->next = NULL;
        if (result == NULL) {
          result = newNode;
          tail = newNode;
        } else {
          tail->next = newNode;
          tail = newNode;
        }
      }
      p = p->next;
      q = q->next;
    }
  }
  while (p != NULL) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->coef = p->coef;
    newNode->exp = p->exp;
    newNode->next = NULL;
    if (result == NULL) {
      result = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    p = p->next;
  }
  while (q != NULL) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->coef = q->coef;
    newNode->exp = q->exp;
    newNode->next = NULL;
    if (result == NULL) {
      result = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    q = q->next;
  }
  return result;
}

int main() {
  int z;
  scanf("%d", &z);
  Node *A = createList(z);
  scanf("%d", &z);
  Node *B = createList(z);
  Node *result = addPoly(A, B);
  printList(result);
  return 0;
}
