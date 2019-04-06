#include <bits/stdc++.h>
using namespace std;
string solve(const string& s) {
  vector<int> cnt(4, 0);

  for (auto& c : s) {
    if (c == '1' || c == '2' || c == '3') {
      cnt[c - '0']++;
    }
  }

  string ret = "";
  for (int i = 1; i <= 3; ++i) {
    if (cnt[i] > 0) {
      for (int j = 0; j < cnt[i]; ++j) {
        ret += "+" + to_string(i);
      }
    }
  }
  return ret.substr(1);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string exp;
  cin >> exp;

  cout << solve(exp) << '\n';

  return 0;
}
