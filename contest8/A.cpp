#include <iostream>
#include <queue>
#include <vector>

const long cInf = 2009000999;

struct Graph {
  int n;
  int m;
  std::vector<std::vector<std::pair<int, int>>> edges;
  std::vector<int> dist;

  Graph(int n, int m)
      : n(n),
        m(m),
        edges(std::vector<std::vector<std::pair<int, int>>>(n)),
        dist(std::vector<int>(n, cInf)) {}

  void AddEdge(int u, int v, int c) {
    edges[u].push_back({v, c});
    edges[v].push_back({u, c});
  }

  void Deikstra(int s) {
    dist[s] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<>>
        pq;
    pq.push({0, s});
    while (!pq.empty()) {
      int d = pq.top().first;
      int v = pq.top().second;
      pq.pop();
      if (d <= dist[v]) {
        for (size_t i = 0; i < edges[v].size(); i++) {
          if (dist[v] + edges[v][i].second < dist[edges[v][i].first]) {
            dist[edges[v][i].first] = dist[v] + edges[v][i].second;
            pq.push({dist[edges[v][i].first], edges[v][i].first});
          }
        }
      }
    }
  }
};

int main() {
  int t;
  std::cin >> t;
  for (int i = 0; i < t; i++) {
    int n;
    int m;
    std::cin >> n >> m;
    Graph g(n, m);
    int u;
    int v;
    int c;
    for (int j = 0; j < m; j++) {
      std::cin >> u >> v >> c;
      g.AddEdge(u, v, c);
    }
    int s;
    std::cin >> s;
    g.Deikstra(s);
    for (int j = 0; j < n; j++) {
      std::cout << g.dist[j] << " ";
    }
    std::cout << "\n";
  }
}
