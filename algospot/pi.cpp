#include <bits/stdc++.h>
using namespace std;

int C;
string line;

constexpr int INF = 987654321;

int memo[10001];

int go(const vector<int>& xs, int idx) {
  if (xs.size() <= idx) return 0;
  if (xs.size() - idx < 3) return INF;
  auto& cache = memo[idx];
  if (cache != -1) return cache;
  int ret = INF;
  if (xs[idx] == xs[idx + 1] && xs[idx + 1] == xs[idx + 2]) {
    for (int i = idx + 2; i <= idx + 5; ++i) {
      if (xs[i] == xs[idx])
        ret = min(ret, 1 + go(xs, i + 1));
      else
        break;
    }
  }
  if (xs[idx + 1] - xs[idx] == 1 && xs[idx + 2] - xs[idx + 1] == 1 ||
      xs[idx + 1] - xs[idx] == -1 && xs[idx + 2] - xs[idx + 1] == -1) {
    for (int i = idx + 2; i <= idx + 5; ++i) {
      if (xs[i] - xs[i - 1] == xs[idx + 1] - xs[idx])
        ret = min(ret, 2 + go(xs, i + 1));
      else
        break;
    }
  }
  if (xs[idx] == xs[idx + 2] && xs[idx] != xs[idx + 1]) {
    int a = xs[idx];
    int b = xs[idx + 1];
    for (int i = idx + 3; i <= idx + 5; ++i) {
      if (xs[i] == b) {
        swap(a, b);
        ret = min(ret, 4 + go(xs, i + 1));
      } else
        break;
    }
    ret = min(ret, 4 + go(xs, idx + 3));
  }

  if (xs[idx + 1] - xs[idx] == xs[idx + 2] - xs[idx + 1] &&
      xs[idx + 1] - xs[idx] != 1) {
    auto diff = xs[idx + 1] - xs[idx];

    for (int i = idx + 3; i <= idx + 5; ++i) {
      if (xs[i] - xs[i - 1] == diff)
        ret = min(ret, 5 + go(xs, i + 1));
      else
        break;
    }
    ret = min(ret, 5 + go(xs, idx + 3));
  }

  // xs[idx], idx+1, idx+2, idx+3, idx+4
  for (int i = idx + 3; i <= idx + 5; ++i) {
    ret = min(ret, 10 + go(xs, i));
  }

  cache = ret;
  return cache;
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
