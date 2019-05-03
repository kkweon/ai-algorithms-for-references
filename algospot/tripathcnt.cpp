#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 100;
int C, N;
int triangle[MAXN][MAXN];
int memo[MAXN][MAXN];

constexpr int INF = 987654321;

int count(int i, int j, vector<vector<int>>& triangle_sum) {
  if (N - 1 <= i) return 1;

  auto& ret = memo[i][j];
  if (ret != -1) return ret;

  ret = 0;

  auto left = triangle_sum[i + 1][j];
  auto right = triangle_sum[i + 1][j + 1];

  if (left >= right) {
    ret += count(i + 1, j, triangle_sum);
  }
  if (right >= left) {
    ret += count(i + 1, j + 1, triangle_sum);
  }

  return ret;
}

int count_max_path() {
  memset(memo, -1, sizeof(memo));
  vector<vector<int>> triangle_sum(N);
  copy(triangle[N - 1], triangle[N - 1] + N,
       back_inserter(triangle_sum[N - 1]));

  for (int i = N - 2; 0 <= i; --i) {
    triangle_sum[i] = vector<int>(i + 1, 0);
    for (int j = 0; j <= i; ++j) {
      triangle_sum[i][j] =
          max(triangle_sum[i + 1][j], triangle_sum[i + 1][j + 1]) +
          triangle[i][j];
    }
  }

  return count(0, 0, triangle_sum);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> C;
  while (C-- > 0) {
    cin >> N;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j <= i; ++j) {
        cin >> triangle[i][j];
      }
    }
    cout << count_max_path() << endl;
  }
  return 0;
}
