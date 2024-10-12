#include <iostream>

struct Base {}; // ! error

struct Derived : Base {
private:
  char *p;

public:
  Derived(unsigned size) {
    p = new char[size];
    std::cout << "ctor called" << std::endl;
  }
  ~Derived() {
    delete[] p;
    std::cout << "dtor called" << std::endl;
  }
};

int main() {
  Base *b{nullptr};
  b = new Derived(16);
  // [...]
  delete b;
}
