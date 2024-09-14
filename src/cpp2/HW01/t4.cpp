#include <iostream>
#include <cstdint>

// reference: https://oi-wiki.org/ds/bst
struct TreeNode {
  int64_t key;
  TreeNode* left;
  TreeNode* right;

  int size;   // 当前节点为根的子树大小
  int count;  // 当前节点的重复数量

  TreeNode(int64_t value): key(value), size(1), count(1), left(nullptr), right(nullptr) {}
};

void print_key(TreeNode* root) {
  if (root == nullptr) return;
  std::cout << root->key << std::endl;
}

TreeNode* insert(TreeNode* root, int value) {
  if (root == nullptr) return new TreeNode(value);

  if (value < root->key) {
    root->left = insert(root->left, value);
  } else if (value > root->key) {
    root->right = insert(root->right, value);
  } else {
    root->count++;  // 节点值相等，增加重复数量
  }
  root->size = root->count + (root->left ? root->left->size : 0) +
               (root->right ? root->right->size : 0);  // 更新节点的子树大小
  return root;
}

TreeNode* findMinNode(TreeNode* root) {
  while (root->left != nullptr) {
    root = root->left;
  }
  return root;
}

TreeNode* remove(TreeNode* root, int value) {
  if (root == nullptr) {
    std::cout << "No such element" << std::endl;
    return root;
  }

  if (value < root->key) {
    root->left = remove(root->left, value);
  } else if (value > root->key) {
    root->right = remove(root->right, value);
  } else {
    if (root->count > 1) {
      root->count--;  // 节点重复数量大于1，减少重复数量
      print_key(root);
    } else {
      if (root->left == nullptr) {
        TreeNode* temp = root->right;
        print_key(root);
        delete root;
        return temp;
      } else if (root->right == nullptr) {
        TreeNode* temp = root->left;
        print_key(root);
        delete root;
        return temp;
      } else {
        TreeNode* successor = findMinNode(root->right);
        print_key(root);
        root->key = successor->key;
        root->count = successor->count;  // 更新重复数量
        // 当 successor->count > 1时，也应该删除该节点，否则
        // 后续的删除只会减少重复数量
        successor->count = 1;
        root->right = remove(root->right, successor->key);
      }
    }
  }
  return root;
}

int querykth(TreeNode* root, int k) {
  if (root == nullptr) return -1;  // 或者根据需求返回其他合适的值
  if (root->left) {
    if (root->left->size >= k) return querykth(root->left, k);
    if (root->left->size + root->count >= k) return root->key;
  } else {
    if (k == 1) return root->key;
  }
  return querykth(root->right,
                  k - (root->left ? root->left->size : 0) - root->count);
}

int queryRank(TreeNode* root, int v) {
  if (root == nullptr) return 0;
  if (root->key == v) return (root->left ? root->left->size : 0) + 1;
  if (root->key > v) return queryRank(root->left, v);
  return queryRank(root->right, v) + (root->left ? root->left->size : 0) +
         root->count;
}

int main() {
  int m;
  std::cin >> m;
  TreeNode* root = nullptr;
  while (m--) {
    int op, x;
    std::cin >> op >> x;
    int rank = 0;
    switch (op) {
      case 1:
        root = insert(root, x);
        break;
      case 2:
        root = remove(root, x);
        break;
    }
  }
  return 0;
}
