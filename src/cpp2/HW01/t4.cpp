#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <queue>

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

  ~TreeNode() {
    if (left)
      delete left;
    if (right)
      delete right;

    delete this;
  }

  TreeNode(const TreeNode &) = delete;

  TreeNode &operator=(const TreeNode &) = delete;

  TreeNode(TreeNode &&) = delete;

  TreeNode &operator=(TreeNode &&) = delete;
};

inline Size getCount(const TreeNode *root) { return root ? root->count : 0; }

inline Size getSize(const TreeNode *root) { return root ? root->size : 0; }

void updateSize(TreeNode *root) {
  root->size = getCount(root) + getSize(root->left) + getSize(root->right);
}

inline Height getHeight(const TreeNode *root) {
  return root ? root->height : 0;
}

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

TreeNode *findMin(TreeNode *root) {
  while (root->left)
    root = root->left;
  return root;
}

TreeNode *findMax(TreeNode *root) {
  while (root->right)
    root = root->right;
  return root;
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
      root->size--; // updateSize(root);
      return root;
    }

    // one child or no child
    if (root->left == nullptr || root->right == nullptr) {
      TreeNode *temp = root->left ? root->left : root->right;
      delete root;
      return temp;
    }

    // two children
    TreeNode *temp = findMin(root->right);

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

int maxDepth(TreeNode *root) {
  if (root == nullptr)
    return 0;

  int leftDepth = maxDepth(root->left);
  int rightDepth = maxDepth(root->right);

  return std::max(leftDepth, rightDepth) + 1;
}

// use queue to level order traversal
int maxDepth2(TreeNode *root) {
  if (root == nullptr)
    return 0;

  std::queue<TreeNode *> q;
  q.push(root);

  int depth = 0;
  while (!q.empty()) {
    int size = q.size();
    while (size--) {
      TreeNode *node = q.front();
      q.pop();

      if (node->left)
        q.push(node->left);
      if (node->right)
        q.push(node->right);
    }
    depth++;
  }

  return depth;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  size_t m;
  std::cin >> m;
  TreeNode *root = nullptr;
  while (m--) {
    int16_t op;
    std::cin >> op;
    switch (op) {
    case 1: { // input is key
      Key key;
      std::cin >> key;
      root = insert(root, key);
      std::cout << getGTKey(root, key) << '\n';
      break;
    }
    case 2: { // input is rank
      Size rank;
      std::cin >> rank;
      rank = getSize(root) + 1 - rank; // reverse rank
      Key key = queryByRank(root, rank);
      std::cout << key << '\n';
      root = remove(root, key);
      break;
    }
    default:
      break;
    }
  }

  return 0;
}
