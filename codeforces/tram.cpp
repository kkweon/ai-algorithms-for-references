#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  int total = 0;
  int max_tot = 0;

  for (int i = 0; i < n; ++i) {
    int exit, enter;
    cin >> exit >> enter;
    total -= exit - enter;

    max_tot = max(max_tot, total);
  }

  cout << max_tot << '\n';

  return 0;
}
