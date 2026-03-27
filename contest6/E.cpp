#include <iostream>
#include <vector>

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  std::vector<int> weights(n, 0);
  for (int i = 0; i < n; ++i) {
    std::cin >> weights[i];
  }

  std::vector<int> costs(n, 0);
  for (int i = 0; i < n; ++i) {
    std::cin >> costs[i];
  }

  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (weights[i - 1] > j) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = std::max(dp[i - 1][j],
                            dp[i - 1][j - weights[i - 1]] + costs[i - 1]);
      }
    }
  }

  std::vector<int> answer;
  int i = n;
  int j = m;
  while (i > 0 && j > 0) {
    if (weights[i - 1] > j) {
      --i;
    } else if (dp[i][j] == dp[i - 1][j]) {
      --i;
    } else {
      answer.push_back(i);
      j -= weights[i - 1];
      --i;
    }
  }

  for (int i = answer.size() - 1; i >= 0; --i) {
    std::cout << answer[i] << "\n";
  }
}
