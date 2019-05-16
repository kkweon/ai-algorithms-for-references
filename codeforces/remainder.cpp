#include <bits/stdc++.h>
using namespace std;


char A[2 * 100000];

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, x, y;
  cin >> n >> x >> y;

  for (int i = 0; i < n; ++i) cin >> A[i];

  // target: 10^y

  int count = 0;
  for (int i = 0; i < x; ++i) {
    if (i == y && A[n - 1 - i] == '0') ++count;
    else if (i != y && A[n - 1 - i] == '1') ++count;
  }

  cout << count << '\n';

  return 0;
}
