#include <cmath>
#include <iostream>
using namespace std;

double area(double side);
double area(double length, double width);
double area(double a, double b, double c);
double area(double radius, int);

int main() {
  int shape;
  cin >> shape;
  double result;

  switch (shape) {
  case 0:
    double side;
    cin >> side;
    result = area(side);
    break;
  case 1:
    double length, width;
    cin >> length >> width;
    result = area(length, width);
    break;
  case 2:
    double a, b, c;
    cin >> a >> b >> c;
    result = area(a, b, c);
    break;
  case 3:
    double radius;
    cin >> radius;
    result = area(radius, 0);
    break;
  default:
    cout << "Invalid shape" << endl;
    return 0;
  }

  cout << fixed;
  cout.precision(2);
  cout << result << endl;

  return 0;
}

double area(double side) { return side * side; }

double area(double length, double width) { return length * width; }

double area(double a, double b, double c) {
  double s = (a + b + c) / 2;
  return sqrt(s * (s - a) * (s - b) * (s - c));
}

double area(double radius, int) { return 3.14159 * radius * radius; }
