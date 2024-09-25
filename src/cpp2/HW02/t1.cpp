#include <cctype>
#include <iostream>
#include <string>

inline bool isDigit(char c) { return c >= '0' && c <= '9'; }

int main() {
  // iterate over each line of input
  for (std::string str; getline(std::cin, str);) {
    // flag: is the first integer of the current line, default to true
    bool isFirstInt{true};
    size_t strLength = str.size();

    for (size_t i = 0; i < strLength; i++)
      if (isDigit(str[i])) { // str[i] is a digit
        size_t r = i + 1;
        while (isDigit(str[r]))
          ++r; // now str[r - 1] is a digit, str[r] is not a digit

        // use the flag
        if (isFirstInt)
          isFirstInt = false;
        else
          putchar(' ');

        for (size_t j = i; j < r; j++)
          putchar(str[j]);

        i = r; // skip the current integer
      }
    putchar('\n');
  }
  return 0;
}
