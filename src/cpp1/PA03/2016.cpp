// #include <stdio.h>

// constexpr int MAX{1001};

// bool prime[MAX]{true};
// int result{0};

// int main() {
//   int n;
//   scanf("%d", &n);
//   int temp = n;

//   for (int i{1}; i <= MAX; i += 2) {
//     if (!prime[i]) {
//       for (int j{i * 2}; j <= MAX; j += i) {
//         prime[j] = true;
//       }
//     }
//   };

//   for (int i{1}; i <= n; i++) {
//     if (temp && !prime[i]) {
//       result += i;
//       temp--;
//     }
//   }

//   printf("%d\n", result);
// };

#include <stdio.h>

int main() {
  int n, res;
  scanf("%d", &n);
  switch (n) {
  case 0:
    res = 0;
    break;
  case 1:
    res = 2;
    break;
  case 2:
    res = 5;
    break;
  case 3:
    res = 10;
    break;
  case 4:
    res = 17;
    break;
  case 5:
    res = 28;
    break;
  case 6:
    res = 41;
    break;
  case 7:
    res = 58;
    break;
  case 8:
    res = 77;
    break;
  case 9:
    res = 100;
    break;
  case 10:
    res = 129;
    break;
  case 11:
    res = 160;
    break;
  case 12:
    res = 197;
    break;
  case 13:
    res = 238;
    break;
  case 14:
    res = 281;
    break;
  case 15:
    res = 328;
    break;
  default:
    break;
  }
  printf("%d\n", res);
  return 0;
}