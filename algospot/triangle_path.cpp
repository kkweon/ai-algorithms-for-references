#include <bits/stdc++.h>
using namespace std;

int N;

int max_sum_path(vector<vector<int>>& triangle) {
  vector<int> dp(N, 0);
  copy(triangle.back().begin(), triangle.back().end(), dp.begin());
  for (int i = N - 2; 0 <= i; --i) {
    for (int j = 0; j <= i; ++j) {
      dp[j] = max(dp[j], dp[j + 1]) + triangle[i][j];
    }
  }
  return dp.front();
}
int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int C;
  cin >> C;
  while(C-- > 0) {
    cin >> N;
    vector<vector<int>> triangle(N);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j <= i; ++j) {
        int value;
        cin >> value;
        triangle[i].push_back(value);
      }
    }
    cout << max_sum_path(triangle) << endl;
  }

  return 0;
}
