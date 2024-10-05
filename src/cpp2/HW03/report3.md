# HW3

## Vector 操作练习

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int a[10];

  // read the array
  for (int i = 0; i < 10; i++)
    std::cin >> a[i];

  // convert array to vector
  std::vector<int> v = {std::vector<int>(a, a + 10)};

  int n;
  std::cin >> n;

  while (n--) {
    /**
     * @brief read the operation
     * 1: read `el` and add `el` to the end of the vector
     * 2: pop the last element
     * 3: read `x` and `y` and insert `y` at position `x`
     * 4: read `z` and remove the element at position `z`
     * 5: print the size of the vector
     * 6: print the vector
     * 7: reverse the vector and print it, then reverse it back
     * 8: read `idx` and print the element at position `idx`, if it exists
     *    otherwise, print `Invalid position`
     *
     * @note check the constraints of the input
     *
     */
    int op;
    std::cin >> op;

    switch (op) {
    case 1: {
      int el;
      std::cin >> el;
      v.push_back(el);
      break;
    }

    case 2:
      // check the constraints
      if (v.empty())
        break;

      v.pop_back();
      break;

    case 3: {
      int x, y;
      std::cin >> x >> y;

      // check the constraints
      if (x < 0 || x > v.size()) // ! hint: x can be equal to v.size()
        break;

      // ? i think that `x > v.size()` can also be a valid condition
      v.insert(v.begin() + x, y);
      break;
    }

    case 4: {
      int z;
      std::cin >> z;

      // check the constraints
      if (z < 0 || z >= v.size())
        break;

      v.erase(v.begin() + z);
      break;
    }

    case 5:
      std::cout << v.size() << '\n';
      break;

    case 6:
      for (const auto &i : v)
        std::cout << i << ' ';
      std::cout << '\n';
      break;

    case 7:
      std::reverse(v.begin(), v.end());
      for (const auto &i : v)
        std::cout << i << ' ';
      std::cout << '\n';
      std::reverse(v.begin(), v.end());
      break;

    case 8: {
      int idx;
      std::cin >> idx;

      // check the constraints
      if (idx < 0 || idx >= v.size()) {
        std::cout << "Invalid position" << '\n';
        break;
      }

      std::cout << v[idx] << '\n';
      break;
    }

    default:
      break;
    } // switch
  }

  return 0;
}
```

首先是理解题意，先写好了一个能通过测例的 benchmark，然后就是细节检查，主要是插值/取值/删值的边界检查，即 2、3、4 和 8 这几个的的边界，其他调用接口即可。

## 图书管理系统

```cpp
#include <iostream>
#include <memory>
#include <vector>

class Book {
public:
  Book(int id) : id_(id) {}
  int getId() const { return id_; }

private:
  int id_;
};

class BookBorrower;

class Library {
public:
  void addBook(int idx) { books_.push_back(std::make_shared<Book>(idx)); }

  void printBooks() const {
    for (const auto &book : books_)
      if (book.use_count() == 1)
        std::cout << book->getId() << " ";

    std::cout << std::endl;
  }

  bool borrowBook(int id, BookBorrower &borrower);
  bool returnBook(int id, BookBorrower &borrower);

  ~Library() {
    for (auto book : books_) {
      book.reset();
    }
  }

private:
  std::vector<std::shared_ptr<Book>> books_;
};

class BookBorrower {
public:
  bool borrowBook(std::shared_ptr<Book> book) {
    if (book == nullptr)
      return false;

    borrowedBooks.push_back(book);
    return true;
  }

  bool returnBook(int id) {
    for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it)
      if ((*it)->getId() == id) {
        borrowedBooks.erase(it);
        return true;
      };

    return false;
  }

private:
  std::vector<std::shared_ptr<Book>> borrowedBooks;
};

bool Library::borrowBook(int id, BookBorrower &borrower) {
  for (const auto &book : books_)
    if (book->getId() == id && book.use_count() == 1)
      return borrower.borrowBook(book);

  return false;
}

bool Library::returnBook(int id, BookBorrower &borrower) {
  return borrower.returnBook(id);
}

int main() {
  Library library;
  int n;
  std::cin >> n;

  for (int i = 0; i < n; ++i)
    library.addBook(i);

  // library.printBooks();

  int m;
  std::cin >> m;

  BookBorrower borrower;

  while (m--) {
    /**
     * @brief read the operation
     * 1 - read the book id `x` and borrow it
     * 2 - read the book id `x` and return it
     * 3 - print the books in the library that are not borrowed
     *
     */
    int op;
    std::cin >> op;

    switch (op) {
    case 1: {
      int x;
      std::cin >> x;
      std::cout << (library.borrowBook(x, borrower) ? 1 : 0) << std::endl;
      break;
    }

    case 2: {
      int x;
      std::cin >> x;
      std::cout << (library.returnBook(x, borrower) ? 1 : 0) << std::endl;
      break;
    }

    case 3:
      library.printBooks();
      break;

    default:
      break;
    } // switch
  }

  return 0;
}
```

这个题主要的思路就是追踪共享指针的引用计数，计数为 1 就视作没被借，此外一个点就是一本书被借了就不能再被借了，还书就搜索再销毁即可。

## 总结

本次作业难度不大，侧重于对细节的考察，总体花了 50 分钟，尤其在第一题上花了很多时间，主要在于几个插值/取值/删值的边界性检查，而且边界还不完全一样，比如插值就可以在插值就可以在末尾后加上，但删值和取值肯定不行。

此外本次作业基本没什么难点，代码结构上好像也没硬性要求，简单写了点注释，然后把核心逻辑全放一个大 switch 里面就完事了。
