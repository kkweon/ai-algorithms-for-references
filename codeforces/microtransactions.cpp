#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> K;
// (d_i, t_i)
vector<pair<int, int>> Q(200001);

bool can(int day) {
  vector<int> lst(n, -1);
  for (int i = 0; i < m; ++i) {
    if (Q[i].first <= day) {
      lst[Q[i].second] = max(lst[Q[i].second], Q[i].first);
    }
  }

  vector<vector<int>> off(200001);
  for (int i = 0; i < n; ++i) {
    if (lst[i] != -1) {
      off[lst[i]].push_back(i);
    }
  }

  vector<int> need = K;
  int curr_money = 0;
  for (int i = 0; i <= day; ++i) {
    ++curr_money;
    if (200000 < i) continue;
    for (auto& it : off[i]) {
      if (need[it] <= curr_money) {
        curr_money -= need[it];
        need[it] = 0;
      } else {
        need[it] -= curr_money;
        curr_money = 0;
        break;
      }
    }
  }

  return accumulate(need.begin(), need.end(), 0) * 2 <= curr_money;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> m;
  K = vector<int>(n);
  for (int i = 0; i < n; ++i) cin >> K[i];

  for (int i = 0; i < m; ++i) {
    cin >> Q[i].first >> Q[i].second;
    Q[i].first--;
    Q[i].second--;
  }

  int l = 0, r = 400000;
  while (l + 1 < r) {
    int m = l + ((r - l) >> 1);
    if (can(m)) r = m;
    else l = m;
  }

  for (int i = l; i <= r; ++i) {
    if (can(i)) {
      cout << i + 1 << '\n';
      return 0;
    }
  }

  return 0;
}
