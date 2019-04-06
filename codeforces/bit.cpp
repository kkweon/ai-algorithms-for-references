#include <bits/stdc++.h>
using namespace std;

int n;

int parse(int x, const string& s) {
  if (s == "X") return x;
  if (s == "++X" || s == "X++") return ++x;
  if (s == "--X" || s == "X--") return --x;

  assert(false);
  return 0;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n;
  int x = 0;

  while (n-- > 0) {
    string exp;
    cin >> exp;
    x = parse(x, exp);
  }
  cout << x << '\n';

  return 0;
}
