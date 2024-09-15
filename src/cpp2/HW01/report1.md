# HW

## T1: A+B Problem

没什么难度，提交的代码如下：

```cpp
#include <cstdint>
#include <iostream>

int main() {
  int64_t a, b;
  std::cin >> a >> b;
  std::cout << a + b << std::endl;
  return 0;
}
```

> 根据题目描述，用 `int32_t` 即可。

## T2: C6-2 数组第K小数

涉及到排序，且只用排到第 K 项，优先想到快排。

copilot “自动”补全第一次似乎给了一个奇怪的没有实际排序的代码：

```cpp
int16_t get_kth_smallest(int16_t arr[], const int16_t &n, const int16_t &k) {
  int16_t left{0}, right{n};
  int16_t lower{0}, upper{0};
  while (left < right) {
    int16_t mid{int16_t((left + right) / 2)};
    int16_t cnt{0};
    for (int16_t i{0}; i < n; i++)
      if (arr[i] <= mid)
        cnt++;
    if (cnt < k) {
      left = mid + 1;
      lower = mid;
    } else {
      right = mid;
      upper = mid;
    }
  }
  return upper;
}
```

考虑到数据集不大，先交了份选择排序：

```cpp
#include <cstdint>
#include <iostream>

const int16_t MAX_N{5000};

int main() {
  int16_t n, k, arr[MAX_N];
  std::cin >> n >> k;
  for (auto i{0}; i < n; i++)
    std::cin >> arr[i];
  for (auto i{0}; i < n; i++) {
    int ith = i;
    for (auto j = i + 1; j < n; j++)
      if (arr[j] < arr[ith])
        ith = j;
    std::swap(arr[i], arr[ith]);
  }
  std::cout << arr[k - 1] << std::endl;
}
```

参考资料：https://oi-wiki.org/basic/quick-sort/

## T3:

也是没多少难度和自由度的题目，提交的完整代码如下：

```cpp
#include "poly.h"

std::vector<int> poly_plus(const std::vector<int> &poly0,
                           const std::vector<int> &poly1) {
  std::vector<int> res;
  // TODO #1: Compute res = poly0 + poly1 here
  auto len0 = poly0.size(), len1 = poly1.size();
  auto len = len0 >= len1 ? len0 : len1;
  res.resize(len);
  for (auto i = 0; i < len; i++) {
    auto a = i < len0 ? poly0[i] : 0;
    auto b = i < len1 ? poly1[i] : 0;
    res[i] = a + b;
  }
  return res;
}

std::vector<int> poly_mul(const std::vector<int> &poly0,
                          const std::vector<int> &poly1) {
  std::vector<int> res;
  // TODO #2: Compute res = poly0 * poly1 here
  auto len0 = poly0.size(), len1 = poly1.size();
  auto len = len0 + len1 - 1;
  res.resize(len);
  for (auto i = 0; i < len0; i++)
    for (auto j = 0; j < len1; j++)
      res[i + j] += poly0[i] * poly1[j];
  return res;
}

// TODO #3: Submit this code file to the OJ
```

## 附

翻了一下 oi wiki 了解了一下二叉搜索树和 avl 树，然后结合题目要求，不断调试下写了一份初稿，期间 copilot 也有补全，不过效果参半，基本是对一些重复性代码补全，实现思路基本参考了 oi-wiki 上对 bst 和 avl 的描述，与[最基本的 avl](https://www.cs.usfca.edu/~galles/visualization/AVLtree.html) 的区别在于加入了对 size 和 count 的维护（这一部分的想法源自 bst），提交如下：

```cpp
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>

// reference: https://oi-wiki.org/ds/bst

using Key = int64_t;
using Size = size_t;
using Height = int64_t;

struct TreeNode {
  Key key;
  TreeNode *left;
  TreeNode *right;

  Size size;
  Size count;
  Height height;

  TreeNode(Key key)
      : key(key), size(1), count(1), height(1), left(nullptr), right(nullptr) {}
};

Size getCount(const TreeNode *root) { return root ? root->count : 0; }

Size getSize(const TreeNode *root) { return root ? root->size : 0; }

void updateSize(TreeNode *root) {
  root->size = getCount(root) + getSize(root->left) + getSize(root->right);
}

Height getHeight(const TreeNode *root) { return root ? root->height : 0; }

void updateHeight(TreeNode *root) {
  root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
}

Height getBlanceFactor(const TreeNode *root) {
  return root ? getHeight(root->left) - getHeight(root->right) : 0;
}

TreeNode *leftRotate(TreeNode *oldRoot) {
  TreeNode *newRoot = oldRoot->right;
  TreeNode *temp = newRoot->left;

  newRoot->left = oldRoot;
  oldRoot->right = temp;

  updateSize(oldRoot);
  updateSize(newRoot);

  updateHeight(oldRoot);
  updateHeight(newRoot);

  return newRoot;
}

TreeNode *rightRotate(TreeNode *oldRoot) {
  TreeNode *newRoot = oldRoot->left;
  TreeNode *temp = newRoot->right;

  newRoot->right = oldRoot;
  oldRoot->left = temp;

  updateSize(oldRoot);
  updateSize(newRoot);

  updateHeight(oldRoot);
  updateHeight(newRoot);

  return newRoot;
}

TreeNode *Maitain(TreeNode *root) {
  updateSize(root);
  updateHeight(root);

  Height balance = getBlanceFactor(root);

  // Left Left Case
  if (balance > 1 && getBlanceFactor(root->left) >= 0)
    return rightRotate(root);

  // Right Right Case
  if (balance < -1 && getBlanceFactor(root->right) <= 0)
    return leftRotate(root);

  // Left Right Case
  if (balance > 1 && getBlanceFactor(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  // Right Left Case
  if (balance < -1 && getBlanceFactor(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

TreeNode *insert(TreeNode *root, Key key) {
  if (root == nullptr)
    return new TreeNode(key);

  if (key < root->key) // search in left
    root->left = insert(root->left, key);
  else if (key > root->key) // search in right
    root->right = insert(root->right, key);
  else // key == root->key
    root->count++;

  return Maitain(root);
}

TreeNode *remove(TreeNode *root, Key key) {
  if (root == nullptr)
    return nullptr;

  if (key < root->key) // search in left
    root->left = remove(root->left, key);
  else if (key > root->key) // search in right
    root->right = remove(root->right, key);
  else { // key == root->key
    // more than one key count
    if (root->count > 1) {
      root->count--;
      root->size--;
      return root;
    }

    // no child
    if (root->left == nullptr && root->right == nullptr) {
      delete root;
      return nullptr;
    }

    // one child
    if (root->left == nullptr || root->right == nullptr) {
      TreeNode *temp = root->left ? root->left : root->right;
      delete root;
      return temp;
    }

    // two children
    TreeNode *temp = root->right;
    while (temp->left)
      temp = temp->left; // find the smallest node in right subtree

    root->key = temp->key;
    root->count = temp->count;

    temp->count = 1;
    root->right = remove(root->right, temp->key);
  }

  return Maitain(root);
}

Size getGTKey(const TreeNode *root, Key key) {
  if (root == nullptr)
    return 0;

  if (key < root->key)
    return getCount(root) + getSize(root->right) + getGTKey(root->left, key);
  if (key > root->key)
    return getGTKey(root->right, key);

  return getSize(root->right);
}

Key queryByRank(const TreeNode *root, Size rank) {
  if (root == nullptr)
    return 0;

  Size leftSize = getSize(root->left);

  if (rank <= leftSize)
    return queryByRank(root->left, rank);
  if (rank <= leftSize + getCount(root))
    return root->key;

  return queryByRank(root->right, rank - leftSize - getCount(root));
}

int main() {
  int64_t m;
  std::cin >> m;
  TreeNode *root = nullptr;
  while (m--) {
    int16_t op;
    std::cin >> op;
    switch (op) {
    case 1: // input is key
      Key key1;
      std::cin >> key1;
      root = insert(root, key1);
      std::cout << getGTKey(root, key1) << std::endl;
      break;
    case 2: // input is rank
      Size rank;
      std::cin >> rank;
      rank = getSize(root) + 1 - rank; // reverse rank
      Key key2 = queryByRank(root, rank);
      std::cout << key2 << std::endl;
      root = remove(root, key2);
      break;
    }
  }

  return 0;
}
```

然后报 TLE 了，开始不是很懂，先把 int64 换成了 int32 和 int16，然后问了一下 ai，提供的优化思路是优化内联和 I/O，因为不是很懂 I/O 方面的优化，先用了内联，还是报 TLE，然后知乎上搜索了一下，考虑到只在大数据集（>=200000）才报 TLE，优化了一下 I/O 就过了，之后有发现 int64 和 int32 速度上差别不大，又把类型改了回去，修改的部分如下：

```patch
@@ -25,11 +25,9 @@
       : key(key), size(1), count(1), height(1), left(nullptr), right(nullptr) {}
 };

-Size getCount(const TreeNode *root) { return root ? root->count : 0; }
+inline Size getCount(const TreeNode *root) { return root ? root->count : 0; }

-Size getSize(const TreeNode *root) { return root ? root->size : 0; }
+inline Size getSize(const TreeNode *root) { return root ? root->size : 0; }

 void updateSize(TreeNode *root) {
   root->size = getCount(root) + getSize(root->left) + getSize(root->right);
 }

-Height getHeight(const TreeNode *root) { return root ? root->height : 0; }
+inline Height getHeight(const TreeNode *root) {
+  return root ? root->height : 0;
+}

 void updateHeight(TreeNode *root) {
   root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;

@@ -191,8 +189,5 @@
 }

 int main() {
+  std::ios::sync_with_stdio(false);
+  std::cin.tie(0);
+
+  size_t m;
-  int64_t m;
   std::cin >> m;
   TreeNode *root = nullptr;
   while (m--) {

@@ -205,1 +200,1 @@

       Key key1;
       std::cin >> key1;
       root = insert(root, key1);
-      std::cout << getGTKey(root, key1) << std::endl;
+      std::cout << getGTKey(root, key1) << '\n';
       break;
     case 2: // input is rank
       Size rank;

@@ -212,1 +207,1 @@

       std::cin >> rank;
       rank = getSize(root) + 1 - rank; // reverse rank
       Key key2 = queryByRank(root, rank);
-      std::cout << key2 << std::endl;
+      std::cout << key2 << '\n';
       root = remove(root, key2);
       break;
     }

```

参考资料：

- https://oi-wiki.org/ds/bst/
- https://oi-wiki.org/ds/avl/
- https://zhuanlan.zhihu.com/p/468363541

ai 交互记录如下：

![](./LobeChat_随便聊聊_2024-09-16.webp)
