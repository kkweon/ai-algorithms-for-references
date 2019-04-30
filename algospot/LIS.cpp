#include <bits/stdc++.h>
using namespace std;

int C, N;
int xs[500];

int LIS() {
  vector<int> tmp;
  for (int i = 0; i < N; ++i) {
    if (tmp.empty() || tmp.back() < xs[i])
      tmp.push_back(xs[i]);
    else {
      auto it = upper_bound(tmp.begin(), tmp.end(), xs[i]);
      *it = xs[i];
    }
  }
  return tmp.size();
}
int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> C;
  while (C-- > 0) {
    cin >> N;
    for (int i = 0; i < N; ++i) {
      cin >> xs[i];
    }

    cout << LIS() << endl;
  }
  return 0;
}
