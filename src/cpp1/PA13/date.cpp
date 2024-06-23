// this file should be encoded in GBK
#include <iostream>
#include <string>
using namespace std;

class Date {
private:
  int day;
  int month;
  int year;
  string monthNames[12] = {"January",   "February", "March",    "April",
                           "May",       "June",     "July",     "August",
                           "September", "October",  "November", "December"};

public:
  // Constructor for format 1 (MM/DD/YYYY)
  Date(int m, int d, int y) : month(m), day(d), year(y) {}

  // Constructor for format 2 (Month DD, YYYY)
  Date(string m, int d, int y) {
    for (int i = 0; i < 12; i++) {
      if (monthNames[i] == m) {
        month = i + 1;
        break;
      }
    }
    day = d;
    year = y;
  }

  // Constructor for format 3 (YYYY年MM月DD日)
  Date(string date) {
    sscanf(date.c_str(), "%d年%d月%d日", &year, &month, &day);
  }

  // Function to print date in format 1 (MM/DD/YYYY)
  void printFormat1() {
    cout << (month < 10 ? "0" : "") << month << "/" << (day < 10 ? "0" : "")
         << day << "/" << year << endl;
  }

  // Function to print date in format 2 (Month DD, YYYY)
  void printFormat2() {
    cout << monthNames[month - 1] << " " << (day < 10 ? "0" : "") << day << ", "
         << year << endl;
  }

  // Function to print date in format 3 (YYYY年MM月DD日)
  void printFormat3() {
    cout << year << "年" << month << "月" << day << "日" << endl;
  }
};

int main() {
  int inputFormat, outputFormat;
  cin >> inputFormat;

  Date *date;
  if (inputFormat == 1) {
    int m, d, y;
    cin >> m >> d >> y;
    date = new Date(m, d, y);
  } else if (inputFormat == 2) {
    string m;
    int d, y;
    cin >> m >> d >> y;
    date = new Date(m, d, y);
  } else if (inputFormat == 3) {
    string dateStr;
    cin >> dateStr;
    date = new Date(dateStr);
  }

  cin >> outputFormat;

  if (outputFormat == 1) {
    date->printFormat1();
  } else if (outputFormat == 2) {
    date->printFormat2();
  } else if (outputFormat == 3) {
    date->printFormat3();
  }

  delete date;
  return 0;
}
