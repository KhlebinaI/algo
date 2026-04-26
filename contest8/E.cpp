#include <algorithm>
#include <iostream>
#include <vector>

const int cInf1 = 100000;
const int cInf2 = 1000000;

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> edges;
  std::vector<std::vector<int>> next(n, std::vector<int>(n, -1));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int x;
      std::cin >> x;
      if (x == cInf1) {
        x = cInf2;
      }
      if (i != j && x < cInf2) {
        edges.push_back({i, j, x});
        next[i][j] = j;
      }
      if (i == j) {
        edges.push_back({i, i, std::min(x, 0)});
        next[i][i] = i;
      }
    }
  }

  std::vector<int> dist(n, cInf2);
  std::vector<int> parent(n, -1);
  int cycle_start = -1;
  for (int start = 0; start < n && cycle_start == -1; start++) {
    for (int i = 0; i < n; i++) {
      dist[i] = cInf2;
      parent[i] = -1;
    }
    dist[start] = 0;
    int last = -1;
    for (int i = 0; i < n; i++) {
      last = -1;
      for (const auto& edge : edges) {
        if (dist[edge[0]] < cInf2 && dist[edge[1]] > dist[edge[0]] + edge[2]) {
          dist[edge[1]] = dist[edge[0]] + edge[2];
          parent[edge[1]] = edge[0];
          last = edge[1];
        }
      }
    }
    if (last != -1) {
      cycle_start = last;
      break;
    }
  }

  if (cycle_start == -1) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
    std::vector<bool> visited(n, false);
    std::vector<int> cycle;
    int cur = cycle_start;
    while (!visited[cur]) {
      visited[cur] = true;
      cur = parent[cur];
    }
    int cycle_vertex = cur;
    cur = cycle_vertex;
    do {
      cycle.push_back(cur);
      cur = parent[cur];
    } while (cur != cycle_vertex);
    cycle.push_back(cycle_vertex);
    std::reverse(cycle.begin(), cycle.end());
    std::cout << cycle.size() << "\n";
    for (size_t i = 0; i < cycle.size(); i++) {
      std::cout << cycle[i] + 1 << " ";
    }
    std::cout << "\n";
  }
  return 0;
}
