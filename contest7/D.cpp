#include <iostream>
#include <vector>

void DFS(int i, std::vector<int>& color, std::vector<int>& time,
         std::vector<std::vector<int>>& data) {
  color[i] = 1;
  for (size_t k = 0; k < data[i].size(); k++) {
    if (color[data[i][k]] == 0) {
      DFS(data[i][k], color, time, data);
    }
  }
  color[i] = 2;
  time.push_back(i);
}

void DFS2(int i, std::vector<int>& color, std::vector<int>& answer,
          std::vector<std::vector<int>>& data, int ans) {
  color[i] = 3;
  for (size_t k = 0; k < data[i].size(); k++) {
    if (color[data[i][k]] == 2) {
      DFS2(data[i][k], color, answer, data, ans);
    }
  }
  color[i] = 4;
  answer[i] = ans;
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> data(n);
  std::vector<std::vector<int>> invert_data(n);
  int u;
  int v;
  for (int i = 0; i < m; i++) {
    std::cin >> u >> v;
    if (u != v) {
      data[u - 1].push_back(v - 1);
      invert_data[v - 1].push_back(u - 1);
    }
  }
  std::vector<int> time;
  std::vector<int> color(n, 0);
  for (int i = 0; i < n; i++) {
    if (color[i] == 0) {
      DFS(i, color, time, invert_data);
    }
  }
  std::vector<int> answer(n, 0);
  int ans = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (color[time[i]] == 2) {
      ans++;
      DFS2(time[i], color, answer, data, ans);
    }
  }
  std::cout << ans << "\n";
  for (int i = 0; i < n; i++) {
    std::cout << ans + 1 - answer[i] << " ";
  }
  std::cout << "\n";
}
