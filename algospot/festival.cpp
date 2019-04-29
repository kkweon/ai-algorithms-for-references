#include <bits/stdc++.h>
using namespace std;

int N, L;
int cost[1000];

int query(int l, int r, vector<int>& prefix) {
  return prefix[r + 1] - prefix[l];
}

double find_min_avg() {
  double ans = numeric_limits<double>::max();
  vector<int> prefix(N + 1, 0);
  for (int i = 0; i < N; ++i) {
    prefix[i + 1] = prefix[i] + cost[i];
  }

  for (int l = L; l <= N; ++l) {
    for (int i = l - 1; i < N; ++i) {
      double avg = query(i - l + 1, i, prefix) * 1.0 / l;
      if (avg < ans) ans = avg;
    }
  }

  return ans;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int C;
  cin >> C;

  for (int cc = 0; cc < C; ++cc) {
    cin >> N >> L;
    for (int i = 0; i < N; ++i) {
      cin >> cost[i];
    }
    cout << fixed << setprecision(8) << find_min_avg() << endl;
  }


  return 0;
}
