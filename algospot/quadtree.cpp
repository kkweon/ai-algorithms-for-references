#include <bits/stdc++.h>
using namespace std;

string rotate(string::iterator& it) {
  char c = *(it++);
  if (c == 'w' || c == 'b') return string(1, c);
  auto top_left = rotate(it);
  auto top_right = rotate(it);
  auto bot_left = rotate(it);
  auto bot_right = rotate(it);

  return "x" + bot_left + bot_right + top_left + top_right;
}

string rotate_upside_down(string& s) {
  auto it = s.begin();
  return rotate(it);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  while (T -- > 0) {
    string line;
    cin >> line;
    cout << rotate_upside_down(line) << endl;
  }

  return 0;
}
