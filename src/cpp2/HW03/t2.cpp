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
