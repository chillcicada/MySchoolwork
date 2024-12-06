#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {
private:
  int V;                              // 顶点的数量
  vector<vector<pair<int, int>>> adj; // 邻接表

public:
  Graph(int V) : V(V), adj(V) {}

  // 添加边
  void addEdge(int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w}); // 对于无向图
  }

  // Dijkstra算法的实现
  vector<int> dijkstra(int src) {
    vector<int> dist(V, INT_MAX); // 存储从源点到每个顶点的最短距离
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq; // 小顶堆
    vector<bool> visited(V, false);

    dist[src] = 0;
    pq.push({0, src}); // 将源点加入优先队列

    while (!pq.empty()) {
      int u = pq.top().second; // index of vertex
      int d = pq.top().first;  // distance from source
      pq.pop();

      if (visited[u])
        continue; // 如果当前顶点已经被访问过，则跳过
      visited[u] = true;

      if (d > dist[u])
        continue; // 如果当前距离大于已记录的最短距离，则跳过

      for (auto &p : adj[u]) {
        int v = p.first;
        int weight = p.second;

        if (dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight;
          pq.push({dist[v], v});
        }
      }
    }

    return dist;
  }
};

int main() {
  Graph g(5);
  g.addEdge(0, 1, 10);
  g.addEdge(0, 4, 50);
  g.addEdge(1, 2, 20);
  g.addEdge(1, 3, 10);
  g.addEdge(1, 4, 40);
  g.addEdge(2, 3, 30);
  g.addEdge(3, 4, 10);

  vector<int> distances = g.dijkstra(0);
  cout << "Vertex Distance from Source" << endl;
  for (int i = 0; i < distances.size(); ++i) {
    if (distances[i] == INT_MAX)
      cout << i << " \t\t INF" << endl;
    else
      cout << i << " \t\t " << distances[i] << endl;
  }

  return 0;
}
