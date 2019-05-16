#include <bits/stdc++.h>
using namespace std;

int n;
string line;

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> line;
  string ret;

  for (auto& c : line) {
    if (ret.size() % 2 == 0 || ret.back() != c) ret.push_back(c);
  }

  if (ret.size() & 1) ret.pop_back();
  cout << (n - ret.size()) << '\n' << ret << '\n';

  return 0;
}
