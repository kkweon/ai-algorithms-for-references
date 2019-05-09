#include <bits/stdc++.h>
using namespace std;

int N, Q;
static int last_answer = 0;

size_t get_idx(int x) {
  return (x ^ last_answer) % N;
}

void append(int x, int y, vector<vector<int>>& seq_list) {
  seq_list[get_idx(x)].push_back(y);
}

void update(int x, int y, vector<vector<int>>& seq_list) {
  size_t value_idx = y % seq_list[get_idx(x)].size();
  last_answer = seq_list[get_idx(x)][value_idx];
  cout << last_answer << '\n';
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> Q;
  vector<vector<int>> seq_list(N);

  for (int i = 0; i < Q; ++i) {
    int type, x, y;
    cin >> type >> x >> y;
    if (type == 1) append(x, y, seq_list);
    else update(x, y, seq_list);
  }
  return 0;
}
