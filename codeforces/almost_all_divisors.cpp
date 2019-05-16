#include <bits/stdc++.h>
using namespace std;

int T;
int n;

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> T;
  for (int i = 0; i < T; ++i) {
    cin >> n;

    vector<long long> d(n);
    for (int i = 0; i < n; ++i) {
      cin >> d[i];
    }

    sort(d.begin(), d.end());
    long long x = d[0] * d[n - 1];

    vector<long long> dd;

    for (long long i = 2; i * i <= x; ++i) {
      if (x % i == 0)  {
        dd.push_back(i);
        if (i != x / i) dd.push_back(x / i);
      }
    }

    sort(dd.begin(), dd.end());

    if (d == dd) cout << x << '\n';
    else cout << -1 << '\n';
  }

  return 0;
}
