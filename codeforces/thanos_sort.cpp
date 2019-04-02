#include <bits/stdc++.h>
using namespace std;

int thanos_sort(vector<int>& xs) {
  for (int i = xs.size(); i; i >>= 1) {
    for (int j = 0; j < xs.size(); j += i) {
      bool ok = true;
      for (int k = 1; k < i; ++k) {
        ok &= xs[j + k - 1] <= xs[j + k];
      }

      if (ok) {
        return i;
      }
    }
  }

  return 0;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  vector<int> xs(n);

  for (int i = 0; i < n; ++i) {
    cin >> xs[i];
  }

  cout << thanos_sort(xs) << endl;
  ;

  return 0;
}
