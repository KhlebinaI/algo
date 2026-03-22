#include <iostream>
#include <vector>

const long long cInf = 3 * 1e9;

int Binsearch(int first, int last, long long element,
              std::vector<long long>& dp) {
  if (last - first <= 1) {
    return last;
  }
  int mid = (first + last) / 2;
  if (element > dp[mid]) {
    return Binsearch(0, mid, element, dp);
  }
  return Binsearch(mid, last, element, dp);
}

int main() {
  int n;
  std::cin >> n;

  std::vector<long long> data(n, 0);
  for (int i = 0; i < n; ++i) {
    std::cin >> data[i];
  }

  std::vector<long long> dp(n + 1, -cInf);
  dp[0] = cInf;
  std::vector<long long> previous(n, -1);
  std::vector<int> index(n + 1, 0);
  int ans = 0;

  for (int i = 0; i < n; ++i) {
    int j = Binsearch(0, n + 1, data[i], dp);
    ans = std::max(j, ans);
    dp[j] = data[i];
    index[j] = i;
    previous[i] = (j == 1 ? -1 : index[j - 1]);
  }
  std::cout << ans << "\n";

  std::vector<int> answer;
  int t = index[ans];
  while (t != -1) {
    answer.push_back(t + 1);
    t = previous[t];
  }
  for (int k = ans - 1; k >= 0; k--) {
    std::cout << answer[k] << " ";
  }
  std::cout << "\n";
}
