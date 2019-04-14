#include <bits/stdc++.h>
using namespace std;

#define FOR(i, l, r) for (int (i) = (l); (i) < (r); ++(i))

string board[5];

bool dfs(int i, int j, const string& s, int& s_idx) {
  if (s.size() <= s_idx) return true;
  else if (s[s_idx] != board[i][j]) return false;

  s_idx++;

  FOR(r, i - 1, i + 2) {
    FOR(c, j - 1, j + 2) {
      if (0 <= r && r < 5 &&
          0 <= c && c < 5 &&
          dfs(i, j, s, s_idx)) {
        return true;
      }
    }
  }
  return false;
}

string find(const string& s) {
  FOR(i, 0, 5) {
    FOR(j, 0, 5) {
      if (board[i][j] == s[0]) {
        int s_idx = 0;
        if (dfs(i, j, s, s_idx)) {
          return "YES";
        }
      }
    }
  }

  return "NO";
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  while (T-- > 0) {
    for (int i = 0; i < 5; ++i) {
      cin >> board[i];
    }
    int n_word;
    cin >> n_word;
    for (int i = 0; i < n_word; ++i) {
      string word;
      cin >> word;
      cout  << '\n' << find(word) << endl;
    }
  }

  return 0;
}
