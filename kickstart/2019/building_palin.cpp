#include <bits/stdc++.h>
using namespace std;

bool is_palin(const string& s, int l, int r) {
  unordered_map<char, int> m;
  for (int i = l; i <= r; ++i) {
    m[s[i]]++;
  }

  int one_count = 0;
  for (auto& it : m) {
    if (it.second == 1) one_count++;
  }

  return one_count <= 1;
}
vector<vector<bool>> build_table(const string& s) {
  vector<vector<bool>> table(s.size(), vector<bool>(s.size(), false));
  for (int i = 0; i < static_cast<int>(s.size()); ++i) {
    for (int j = i; j < static_cast<int>(s.size()); ++j) {
      table[i][j] = is_palin(s, i, j);
    }
  }
  return table;
}
int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T;
  cin >> T;
  for (int tt = 0; tt < T; ++tt) {
    int N, Q;
    cin >> N >> Q;
    string blocks;
    cin >> blocks;

    vector<vector<bool>> palin_table = build_table(blocks);

    int count = 0;
    for (int i = 0; i < Q; ++i) {
      int from, to;
      cin >> from >> to;

      if (palin_table[from - 1][to - 1]) ++count;
    }

    cout << "Case #" << (tt + 1) << ": " << count << endl;
  }
  return 0;
}
