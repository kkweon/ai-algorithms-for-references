#include <bits/stdc++.h>
using namespace std;

int C, N, W;

struct Item {
  string name;
  int weight;
  int value;
};

Item items[100];

struct Result {
  int value;
  vector<string> items;
};

void reconstruct(vector<vector<int>>& dp, int r, int c, vector<string>& ret) {
  if (r <= 0 || c <= 0) return;
  if (dp[r][c] == dp[r - 1][c]) reconstruct(dp, r - 1, c, ret);
  else {
    ret.push_back(items[r - 1].name);
    reconstruct(dp, r - 1, c - items[r - 1].weight, ret);
  }
}

Result solve() {
  Result ret;
  vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));
  for (int i = 1; i <= N; ++i) {
    auto& item = items[i - 1];
    for (int j = W; 0 <= j; --j) {
      if (item.weight <= j) {
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - item.weight] + item.value);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  ret.value = dp[N][W];
  reconstruct(dp, N, W, ret.items);
  return ret;
}


int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> C;
  while (C-- > 0) {
    cin >> N >> W;
    for (int i = 0; i < N; ++i) {
      string name;
      int weight, value;
      cin >> name >> weight >> value;
      items[i] = {name, weight, value};
    }

    auto ret = solve();
    cout << ret.value << ' ' << ret.items.size() << '\n';
    for (auto& item : ret.items) {
      cout << item << '\n';
    }
  }
  return 0;
}
