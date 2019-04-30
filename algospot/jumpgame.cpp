#include <bits/stdc++.h>
using namespace std;

constexpr int MAX = 100;
int N;
int board[MAX][MAX];
int memo[MAX][MAX];

bool can_reach(int r, int c) {
  if (r < 0 || c < 0 || N <= r || N <= c) return false;
  if (r == N - 1 && c == N - 1) return true;
  auto& ret = memo[r][c];
  if (ret != -1) return ret;

  int jump = board[r][c];
  ret = can_reach(r + jump, c) || can_reach(r, c + jump);
  return ret;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int C;
  cin >> C;
  while (C-- > 0) {
    cin >> N;

    memset(memo, -1, sizeof(memo));

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        cin >> board[i][j];
      }
    }

    cout << (can_reach(0, 0) ? "YES" : "NO") << endl;
  }

  return 0;
}
