#include <bits/stdc++.h>
using namespace std;

string has_op(const string& s) {
  int left = s.size();
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '8') {
      left = i;
      break;
    }
  }

  if (11 <= s.size() - left) return "YES";
  return "NO";
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) {
    int n;
    string s;
    cin >> n >> s;

    cout << has_op(s) << '\n';
  }

  return 0;
}
