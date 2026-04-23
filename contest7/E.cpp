#include <algorithm>
#include <iostream>
#include <vector>

struct Graph {
  int edges;
  int vertices;
  std::vector<std::vector<std::pair<int, int>>> data;
  int initial_edges = 0;
  std::vector<int> time;
  std::vector<int> min_t;
  std::vector<int> color;
  int tick = 0;

  Graph(int n, int m)
      : edges(m),
        vertices(n),
        data(std::vector<std::vector<std::pair<int, int>>>(n)),
        initial_edges(0),
        time(std::vector<int>(n, 0)),
        min_t(std::vector<int>(n, 0)),
        color(std::vector<int>(n, 0)),
        tick(0) {}

  void AddEdge(int u, int v) {
    initial_edges++;
    if (u != v) {
      data[u - 1].push_back({v - 1, initial_edges});
      data[v - 1].push_back({u - 1, initial_edges});
    }
  }
};

void DFS(int i, Graph& g, std::vector<int>& answer, int parent) {
  g.color[i] = 1;
  g.tick++;
  g.time[i] = g.tick;
  g.min_t[i] = g.tick;
  for (size_t j = 0; j < g.data[i].size(); j++) {
    if (g.data[i][j].second != parent) {
      if (g.color[g.data[i][j].first] == 1) {
        g.min_t[i] = std::min(g.min_t[i], g.time[g.data[i][j].first]);
      } else {
        DFS(g.data[i][j].first, g, answer, g.data[i][j].second);
        g.min_t[i] = std::min(g.min_t[i], g.min_t[g.data[i][j].first]);
        if (g.min_t[g.data[i][j].first] > g.time[i]) {
          answer.push_back(g.data[i][j].second);
        }
      }
    }
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n, m);
  std::vector<int> answer;
  int u;
  int v;
  for (int i = 0; i < m; i++) {
    std::cin >> u >> v;
    g.AddEdge(u, v);
  }
  for (int i = 0; i < n; i++) {
    if (g.color[i] == 0) {
      DFS(i, g, answer, 0);
    }
  }
  sort(answer.begin(), answer.end());
  std::cout << answer.size() << "\n";
  for (size_t i = 0; i < answer.size(); i++) {
    std::cout << answer[i] << " ";
  }
  std::cout << "\n";
}
