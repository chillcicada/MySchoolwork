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
    int64_t op;
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
