#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  string s;
  cin >> s;

  char ch = '.';
  int cnt = 0;

  int ans = 0;
  for (auto& c : s) {
    if (ch == c) {
      cnt++;
    } else {
      if (cnt > 1) ans += cnt - 1;
      ch = c;
      cnt = 1;
    }
  }

  if (cnt > 1) ans += cnt - 1;
  cout << ans << '\n';
  return 0;
}
