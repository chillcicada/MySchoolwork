#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace __gnu_pbds;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int m;
  cin >> m;

  ordered_set candies;
  vector<int> results;
  results.reserve(m);

  int index = 0;

  for (int i = 0; i < m; ++i) {
    int op;
    cin >> op;

    if (op == 1) {
      int x;
      cin >> x;
      int count = candies.order_of_key({-x, 0});
      results.push_back(count);
      candies.insert({-x, index++});
    } else if (op == 2) {
      int k;
      cin >> k;
      auto it = candies.find_by_order(k - 1);
      results.push_back(-it->first);
      candies.erase(it);
    }
  }

  for (int result : results) {
    cout << result << '\n';
  }

  return 0;
}
