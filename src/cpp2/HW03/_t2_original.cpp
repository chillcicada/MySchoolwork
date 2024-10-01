#include <iostream>
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
    void addBook(int idx) {
        books_.push_back(new Book(idx));
    }

    void printBooks() const {
        for (const auto& book : books_) {
            std::cout << book->getId() << " ";
        }
      std::cout<<std::endl;
    }

    bool borrowBook(int id, BookBorrower& borrower);
    bool returnBook(int id, BookBorrower& borrower);

    ~Library() {
        for (auto book : books_) {
            delete book;
        }
    }

private:
    std::vector<Book*> books_;
};

class BookBorrower {
public:

    bool borrowBook(std::shared_ptr<Book> book) {
        // TODO
    }

    bool returnBook(int id) {
        // TODO
    }

private:
    std::vector<std::shared_ptr<Book>> borrowedBooks;
};

bool Library::borrowBook(int id, BookBorrower& borrower) {
      // TODO
}

bool Library::returnBook(int id, BookBorrower& borrower) {
      // TODO
}


int main() {
    Library library;
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        library.addBook(i);
    }

    library.printBooks();

    return 0;
}

