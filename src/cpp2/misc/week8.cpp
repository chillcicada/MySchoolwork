#include <vector>
using namespace std;

class Solution {
public:
  vector<vector<int>> multiply(vector<vector<int>> &A, vector<vector<int>> &B) {
    vector<vector<int>> ans(A.size(), vector<int>(B[0].size(), 0));
    int i, j, k, sum;
    for (i = 0; i < A.size(); ++i)
      for (j = 0; j < B[0].size(); ++j) {
        sum = 0;
        for (k = 0; k < A[0].size(); ++k)
          sum += A[i][k] * B[k][j];
        ans[i][j] = sum;
      }
    return ans;
  }
};
