#include <bits/stdc++.h>
using namespace std;

string board[5];
int memo[10][5][5];

/**
 * IF board[i][j] == s[s_idx]
 *
 *   x x x
 *   x _ x
 *   x x x
 *
 * Next step: check(r, c, s, s_idx + 1) for (r, c) == x
 *
 */
bool check(int i, int j, const string& s, int s_idx) {
  if (s.size() <= s_idx) return true;
  if (i < 0 || j < 0 || 5 <= i || 5 <= j) return false;

  auto& ret = memo[s_idx][i][j];
  if (ret != -1) return ret;

  ret = false;

  if (s[s_idx] == board[i][j]) {
    for (int r = i - 1; r <= i + 1; ++r) {
      for (int c = j - 1; c <= j + 1; ++c) {
        if (r == i && c == j) continue;
        ret |= check(r, c, s, s_idx + 1);
        if (ret) return ret;
      }
    }
  }

  return ret;
}

bool find(const string& s) {
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (check(i, j, s, 0)) {
        return true;
      }
    }
  }
  return false;
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
      memset(memo, -1, sizeof(memo));
      string word;
      cin >> word;
      bool ret = find(word);
      cout << word << " " << (ret ? "YES" : "NO") << endl;
    }
  }

  return 0;
}
