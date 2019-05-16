#include <bits/stdc++.h>
using namespace std;

#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

vector<int> O;
vector<int> v = {4, 8, 15, 16, 23, 42};

void query(int l, int r) {
  cout << "? " << l << ' ' << r << endl;
  int x;
  cin >> x;
  O.push_back(x);
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  for (int i = 0; i < 4; ++i) {
    query(i + 1, i + 2);
  }

  do {
    bool good = true;
    for (int i = 0; i < 4; ++i) {
      if (v[i] * v[i + 1] != O[i]) {
        good = false;
        break;
      }
    }

    if (good) {
      cout << "!";
      for (auto& x : v) cout << ' ' << x;
      cout << '\n';
      return 0;
    }
  } while (next_permutation(v.begin(), v.end()));

  return 0;
}
