#include <bits/stdc++.h>
using namespace std;
constexpr int MOD = 10000000;

int memo[101][101];

static int depth = 0;

int poly(int n, int first) {
  if (n == first) {
    return 1;
  }
  auto& ret = memo[n][first];
  if (ret != -1) {
    return ret;
  }
  ret = 0;
  for (int i = 1; i <= n - first; ++i) {
    int t1 = poly(n - first, i);
    int t2 = first + i - 1;
    ret += (t1 * t2) % MOD;
    ret %= MOD;
  }
  return ret;
}

int n_polyomino(int n) {
  memset(memo, -1, sizeof(memo));
  int ret = 0;
  for (int i = 1; i <= n; ++i) {
    ret += poly(n, i);
    ret %= MOD;
  }
  return ret;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int C, N;
  cin >> C;
  while (C-- > 0) {
    cin >> N;
    cout << n_polyomino(N) << endl;
  }
  return 0;
}
