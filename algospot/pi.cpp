#include <bits/stdc++.h>
using namespace std;

#define DEBUG_XS(xs) \
    std::cout << #xs << " = [ "; \
    for (auto it = std::begin((xs)); it != std::end((xs)); ++it) \
        std::cout << *it <<  " "; \
    std::cout << "]\n";

int C;
string line;

constexpr int INF = 987654321;

int memo[10001];

int get_cost(const vector<int>& xs, int s, int e) {
  if (all_of(xs.begin() + s, xs.begin() + e,
             [&](int x) { return x == xs[s]; })) {
    return 1;
  }

  auto diff = xs[s + 1] - xs[s];
  bool progressive = true;
  for (int i = s + 1; i < e; ++i) {
    if (xs[i] - xs[i - 1] != diff) {
      progressive = false;
      break;
    }
  }

  if (progressive && abs(diff) == 1) return 2;

  int a = xs[s];
  int b = xs[s + 1];
  bool alternating = a != b;

  for (int i = s + 1; i < e; ++i) {
    if (!alternating) break;
    if (xs[i - 1] == a && xs[i] == b) swap(a, b);
    else {
      alternating = false;
    }
  }
  if (alternating) return 4;
  if (progressive) return 5;
  return 10;
}

int go(const vector<int>& xs, int idx) {
  if (static_cast<int>(xs.size()) <= idx) return 0;
  if (static_cast<int>(xs.size()) - 3 < idx) return INF;
  auto& ret = memo[idx];
  if (ret != -1) return ret;

  ret = INF;

  for (int i = idx + 3; i <= idx + 5; ++i) {
    ret = min(ret, get_cost(xs, idx, i) + go(xs, i));
  }

  return ret;
}

int get_difficulty(const vector<int>& s) {
  memset(memo, -1, sizeof(memo));
  return go(s, 0);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> C;
  while (C-- > 0) {
    cin >> line;
    vector<int> xs;
    for (auto c : line) {
      xs.push_back(c - '0');
    }
    cout << get_difficulty(xs) << endl;
  }
  return 0;
}
