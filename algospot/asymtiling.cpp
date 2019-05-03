#include <bits/stdc++.h>
using namespace std;

int C, N;
constexpr long long MOD = 1000000007;

long long tile(int n) {
  int a = 1, b = 1;
  for (int i = 2; i <= n; ++i) tie(a, b) = make_pair(b, (a + b) % MOD);
  return b;
}

long long get_symmetric(int n) {
  if (n & 1) return tile(n / 2);
  return (tile(n / 2 - 1) + tile(n / 2)) % MOD;
}

long long get_n_tile(int n) {
  return (tile(n) - get_symmetric(n) + MOD) % MOD;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> C;
  while (C-- > 0) {
    cin >> N;
    cout << get_n_tile(N) << endl;
  }

  return 0;
}
