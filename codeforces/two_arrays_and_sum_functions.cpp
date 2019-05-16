#include <bits/stdc++.h>
using namespace std;

constexpr long long MOD(long long x) {
 const long long mod = 998244353;
 return x % mod;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;
  vector<long long> a(n), b(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) cin >> b[i];

  sort(b.begin(), b.end());
  vector<long long> val(n);
  for (int i = 0; i < n; ++i)
    val[i] = (i + 1) * 1LL * (n - i) * a[i];
  sort(val.rbegin(), val.rend());

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    ans = MOD(ans + MOD(MOD(val[i]) * b[i]));
  }
  cout << ans << '\n';

  return 0;
}
