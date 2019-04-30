#include <bits/stdc++.h>
using namespace std;


bool is_match(const string& pat, const string& word) {
  vector<vector<bool>> dp(word.size() + 1, vector<bool>(pat.size() + 1, false));
  dp[0][0] = true;

  for (int i = 1; i <= pat.size(); ++i) {
    if (pat[i - 1] == '*')
      dp[0][i] = dp[0][i - 1];
  }

  for (int i = 1; i <= word.size(); ++i) {
    for (int j = 1; j <= pat.size(); ++j) {
      if (word[i - 1] == pat[j - 1] || pat[j - 1] == '?') {
        dp[i][j] = dp[i - 1][j - 1];
      } else if (pat[j - 1] == '*') {
        dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
      }
    }
  }

  return dp[word.size()][pat.size()];
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int C;
  string W;
  int n;
  string word;

  cin >> C;
  while(C-- > 0) {
    cin >> W;
    cin >> n;

    vector<string> ans;
    for (int i = 0; i < n; ++i) {
      cin >> word;
      if (is_match(W, word)) ans.push_back(word);
    }

    sort(ans.begin(), ans.end());
    for (auto& w : ans) cout << w << endl;
  }
  return 0;
}
