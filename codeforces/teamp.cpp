#include <bits/stdc++.h>
using namespace std;

int n;
int Q[1000][1000];
int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n;

  int count = 0;
  for (int i = 0; i < n; ++i) {
    int sure = 0;
    for (int j = 0; j < 3; ++j) {
      cin >> Q[i][j];
      sure += Q[i][j] == 1;
    }
    if (2 <= sure) count++;
  }

  cout << count << '\n';

  return 0;
}
