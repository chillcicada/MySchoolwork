#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

typedef std::pair<int, int> dpair;

struct Wine {
  /**
   * @param d 浓度
   * @param p 价格
   */
  int d, p;
  std::unique_ptr<Wine> last;

  static int counter;
  Wine() { ++counter; }
  ~Wine() { --counter; }
};

int Wine::counter = 0;

// 内存检查器, 请勿修改
struct Checker {
  int _;
  ~Checker() {
    if (Wine::counter != 0) {
      std::cout << "你的对象没有正确释放!\n";
    }
  }
} _c;

int main() {
  int n, m;
  std::vector<dpair> wines;
  // read n and m by `%d %d`
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) {
    int d, p;
    // read d and p by `%d %d`
    scanf("%d %d", &d, &p);
    wines.push_back(dpair(d, p));
  }
  // 按照浓度排序
  // ? 根据题目描述，应该不存在两个浓度相同但价格不同的酒
  sort(wines.begin(), wines.end());

  std::unique_ptr<Wine> d; // 链表头节点
  for (int i = 0; i < n; i++) {
    // compiler require >= c++14
    auto q = std::make_unique<Wine>();
    q->d = wines[i].first;
    q->p = wines[i].second;
    while (d != nullptr && d->last != nullptr) {
      // 排除浓度相同的酒
      if (q->d == d->d || q->d == d->last->d)
        break;

      // 若在最后两点连线下方, 则替换掉最后一个点
      if ((q->p - d->p) / (q->d - d->d) <=
          (d->p - d->last->p) / (d->d - d->last->d)) {
        // d = d->last;
        d = std::move(d->last);
      } else {
        break;
      }
    }

    if (!d || q->d != d->d) {
      q->last = std::move(d);
      d = std::move(q);
    }
  }

  // 将链表转换回数组以便二分查找
  wines.clear();
  for (auto i = std::move(d); i != nullptr;) {
    wines.push_back(dpair(i->d, i->p));
    i = std::move(i->last);
  }
  reverse(wines.begin(), wines.end());

  for (int i = 0; i < m; i++) {
    int q;
    scanf("%d", &q);
    // 若 q 小于最小浓度, 则无法购买
    if (q < wines.front().first) {
      printf("-1");
      continue;
    }
    // 二分查找 q 所在的线段
    auto it = lower_bound(wines.begin(), wines.end(), dpair(q, 0));
    auto ib = it - 1;
    double res = (it->first - q) / (double)(it->first - ib->first) * ib->second;
    res += (q - ib->first) / (double)(it->first - ib->first) * it->second;
    printf("%.2lf", res);
  }

  return 0;
}
