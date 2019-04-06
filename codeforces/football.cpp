#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string temp;
  cin >> temp;

  int cnt = 0;
  char num = '1';
  for (auto& c : temp) {
    if (c == num) {
      cnt += 1;
      if (7 <= cnt) {
        cout << "YES" << '\n';
        return 0;
      }
    } else {
      cnt = 1;
      num = c;
    }
  }

  cout << "NO" << '\n';
  return 0;
}
