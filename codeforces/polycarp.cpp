#include <bits/stdc++.h>
using namespace std;

int n;
int A[2 * 100000];

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> A[i];

  sort(A, A + n);

  int p = 1;
  int count = 0;
  for (int i = 0; i < n; ++i) {
    if (p <= A[i]) ++p, ++count;
  }

  cout << count << '\n';

  return 0;
}
