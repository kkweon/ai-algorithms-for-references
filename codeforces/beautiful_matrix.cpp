#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  for (int r = 0; r < 5; ++ r) {
    for (int c = 0; c < 5; ++c) {
      int v;
      cin >> v;
      if (v == 1) {
        cout << abs(r - 2) + abs(c - 2) << '\n';
      }
    }
  }

  return 0;
}
