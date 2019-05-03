#include <bits/stdc++.h>
using namespace std;

int C, N, M;

constexpr int INF = 987654321;
constexpr int MAXM = 1001;
constexpr int MAXN = 1001;

double memo[MAXN][MAXM];

double count(int n, int m) {
  if (n <= 0) return 1;
  if (m <= 0) return 0;
  auto& ret = memo[n][m];
  if (0 <= ret) return ret;
  ret = count(n - 2, m - 1) * 0.75 + count(n - 1, m - 1) * 0.25;
  return ret;
}

double get_prob() {
  memset(memo, -1.0, sizeof(memo));
  return count(N, M);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> C;
  while (C-- > 0) {
    cin >> N >> M;
    cout << fixed << setprecision(10) << get_prob() << endl;
  }

  return 0;
}
