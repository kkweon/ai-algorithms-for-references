#include <bits/stdc++.h>
using namespace std;

int solve(const string& s1, const string& s2) {
  for (int i = 0; i < s1.size(); ++i) {
    if (tolower(s1[i]) < tolower(s2[i])) return -1;
    else if (tolower(s1[i]) > tolower(s2[i])) return 1;
  }
  return 0;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string A, B;
  cin >> A >> B;

  cout << solve(A, B) << '\n';

  return 0;
}
