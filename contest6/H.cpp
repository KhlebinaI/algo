#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::vector<std::vector<long long>> dp(n + 1,
                                         std::vector<long long>(n + 1, 0));
  for (int i = 0; i <= n; ++i) {
    dp[i][i] = 1;
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j < std::min(2 * i, n + 1); ++j) {
      for (int k = n; k >= j; --k) {
        dp[i][k] += dp[i][k - j];
      }
    }
  }

  long long ans = 0;
  for (int i = 0; i <= n; ++i) {
    ans += dp[i][n];
  }

  std::cout << ans << "\n";
}
