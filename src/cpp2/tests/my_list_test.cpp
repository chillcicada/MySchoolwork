#include "my_list.h"
#include <utest.h>

UTEST(my_list, base) {
  MyList<int> l;
  ASSERT_TRUE(l.empty());
  ASSERT_EQ(0, l.size());
}

UTEST(my_list, copy_constructor) {
  MyList<int> l;
  l.append(1);
  l.append(2);
  l.append(3);
  MyList<int> l2 = l;
  ASSERT_EQ(3, l2.size());
  ASSERT_EQ(1, l2.head->data);
  ASSERT_EQ(3, l2.tail->data);
}

UTEST(my_list, move_constructor) {
  MyList<int> l;
  l.append(1);
  l.append(2);
  l.append(3);
  MyList<int> l2 = std::move(l);
  ASSERT_EQ(3, l2.size());
  ASSERT_EQ(1, l2.head->data);
  ASSERT_EQ(3, l2.tail->data);
  ASSERT_TRUE(l.empty());
}

UTEST(my_list, copy_assignment) {
  MyList<int> l;
  l.append(1);
  l.append(2);
  l.append(3);
  MyList<int> l2;
  l2 = l;
  ASSERT_EQ(3, l2.size());
  ASSERT_EQ(1, l2.head->data);
  ASSERT_EQ(3, l2.tail->data);
}

UTEST(my_list, move_assignment) {
  MyList<int> l;
  l.append(1);
  l.append(2);
  l.append(3);
  MyList<int> l2;
  l2 = std::move(l);
  ASSERT_EQ(3, l2.size());
  ASSERT_EQ(1, l2.head->data);
  ASSERT_EQ(3, l2.tail->data);
  ASSERT_TRUE(l.empty());
}

UTEST(my_list, operator_brackets) {
  MyList<int> l;
  l.append(1);
  l.append(2);
  l.append(3);
  ASSERT_EQ(1, l[0]);
  ASSERT_EQ(2, l[1]);
  ASSERT_EQ(3, l[2]);
}

UTEST(my_list, append_remove) {
  MyList<int> l;
  l.append(1); // 1
  l.append(2); // 1 2
  l.append(3); // 1 2 3
  ASSERT_EQ(3, l.size());

  l.remove(2); // 1 3
  ASSERT_EQ(2, l.size());
  ASSERT_EQ(1, l.head->data);
  ASSERT_EQ(3, l.tail->data);

  l.remove(1); // 3
  ASSERT_EQ(1, l.size());
  ASSERT_EQ(3, l.head->data);
  ASSERT_EQ(3, l.tail->data);

  l.remove(3);
  ASSERT_EQ(0, l.size());
  ASSERT_TRUE(l.empty());
}

UTEST(my_list, append_at) {
  MyList<int> l;
  l.append(1);      // 1
  l.append(2);      // 1 2
  l.append(3);      // 1 2 3
  l.appendAt(1, 4); // 1 4 2 3
  ASSERT_EQ(4, l.size());
  ASSERT_EQ(1, l.head->data);
  ASSERT_EQ(3, l.tail->data);
  ASSERT_EQ(4, l.head->next->data);
  ASSERT_EQ(2, l.head->next->next->data);
}

UTEST(my_list, remove_at) {
  MyList<int> l;
  l.append(1);   // 1
  l.append(2);   // 1 2
  l.append(3);   // 1 2 3
  l.removeAt(1); // 1 3
  ASSERT_EQ(2, l.size());
  ASSERT_EQ(1, l.head->data);
  ASSERT_EQ(3, l.tail->data);
}

UTEST(my_list, clear) {
  MyList<int> l;
  l.append(1);
  l.append(2);
  l.append(3);
  l.clear();
  ASSERT_TRUE(l.empty());
  ASSERT_EQ(0, l.size());
}
