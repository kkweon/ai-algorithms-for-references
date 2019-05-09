#include <bits/stdc++.h>
using namespace std;

int N;

struct Ball {
  int idx;
  int color;
  int size;
  bool operator<(const Ball& b) const {
    if (size == b.size) return color < b.color;
    return size < b.size;
  }
};

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;
  vector<Ball> balls;
  unordered_map<int, vector<Ball>> size2balls;

  for (int i = 0; i < N; ++i) {
    int c, s;
    cin >> c >> s;
    size2balls[s].push_back({ i, c, s });
  }

  int tot = 0;
  unordered_map<int, int> color2size;
  vector<int> ans(N);
  for (int i = 1; i <= 2000; ++i) {
    if (size2balls.find(i) == size2balls.end()) continue;
    for (auto& b : size2balls[i]) {
      ans[b.idx] = tot - color2size[b.color];
    }
    for (auto& b : size2balls[i]) {
      tot += b.size;
      color2size[b.color] += b.size;
    }
  }

  for (auto& a : ans) cout << a << '\n';

  return 0;
}
