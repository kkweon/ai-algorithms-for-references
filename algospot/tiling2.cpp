#include <bits/stdc++.h>
using namespace std;

int C, N;
constexpr int MOD = 1000000007;

int solve(int n) {
  int a = 0, b = 1;
  for (int i = 1; i <= n; ++i) {
    tie(a, b) = make_pair(b, (a + b) % MOD);
  }
  return b;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> C;
  while (C-- > 0) {
    cin >> N;
    cout << solve(N) << endl;
  }
  return 0;
}
