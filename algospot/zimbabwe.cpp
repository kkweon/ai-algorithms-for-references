#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1000000007;
string e, digits;
int n, m;

int cache[1<<14][20][2];

int price(int index, int taken, int mod, int less) {
  if (index == n) return less && mod == 0 ? 1 : 0;
  int& ret = cache[taken][mod][less];
  if (ret != -1) return ret;
  ret = 0;

  for (int next = 0; next < n; ++next) {
    if ((taken & (1 << next))) continue;
    if (!less && e[index] < digits[next]) continue;

    if (next && digits[next - 1] == digits[next] &&
        (taken & (1 << (next - 1))) == 0) continue;

    int next_taken = taken | (1 << next);
    int next_mod = (mod * 10 + digits[next] - '0') % m;
    int next_less = less || e[index] > digits[next];

    ret += price(index + 1, next_taken, next_mod, next_less);
    ret %= MOD;
  }

  return ret;
}



int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int c;
  cin >> c;


  while(c--) {
    memset(cache, -1, sizeof(cache));
    cin >> e >> m;

    n = e.size();

    digits = e;
    sort(digits.begin(), digits.end());

    cout << price(0, 0, 0, false) << '\n';
  }

  return 0;
}
