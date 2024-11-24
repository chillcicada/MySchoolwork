#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 数据点类
class Point {
public:
  vector<double> features; // 特征向量
  int label;               // 类别标签
  double distance;         // 到查询点的距离

  Point(vector<double> f, int l) : features(f), label(l), distance(0) {}
};

class KNN {
private:
  vector<Point> dataset;
  int k;

  double calculateDistance(const vector<double> &p1, const vector<double> &p2) {
    double sum = 0;
    for (size_t i = 0; i < p1.size(); i++) {
      sum += pow(p1[i] - p2[i], 2);
    }
    return sqrt(sum);
  }

public:
  KNN(int kValue) : k(kValue) {}

  void addTrainingPoint(const vector<double> &features, int label) {
    dataset.emplace_back(features, label);
  }

  int predict(const vector<double> &queryPoint) {
    priority_queue<pair<double, int>> maxHeap;

    for (const Point &point : dataset) {
      double dist = calculateDistance(queryPoint, point.features);

      // 第1空：当堆的大小小于k时，直接将元素{距离，标签}加入堆中
      if (maxHeap.size() < k) {
        maxHeap.push({dist, point.label});
      }
      // 第2空：当前距离小于堆顶元素时，删除堆顶元素
      else if (dist < maxHeap.top().first) {
        maxHeap.pop();
        // 第3空：将新元素{距离，标签}插入堆中
        maxHeap.push({dist, point.label});
      }
    }

    return maxHeap.top().second;
  }
};
// 测试代码
int main() {
  // 创建KNN分类器，k=3
  KNN knn(3);

  // 添加训练数据
  knn.addTrainingPoint({1.0, 1.0}, 0);
  knn.addTrainingPoint({1.0, 2.0}, 0);
  knn.addTrainingPoint({2.0, 2.0}, 0);
  knn.addTrainingPoint({5.0, 5.0}, 1);
  knn.addTrainingPoint({5.0, 6.0}, 1);
  knn.addTrainingPoint({6.0, 5.0}, 1);

  // 测试预测
  vector<double> queryPoint = {1.5, 1.5};
  int prediction = knn.predict(queryPoint);

  cout << "查询点 (1.5, 1.5) 的预测类别是: " << prediction << endl;

  return 0;
}
