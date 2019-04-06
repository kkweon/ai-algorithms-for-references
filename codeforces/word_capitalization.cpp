#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string A;
  cin >> A;

  for (int i = 0; i < A.size(); ++i) {
    if (i == 0) cout << char(toupper(A[i]));
    else cout << A[i];
  }
  return 0;
}
