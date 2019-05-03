#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 100;
constexpr int MAXS = 11;
constexpr int INF = 987654321;

int A[MAXN];
int C, N, S;
int memo[MAXN + 1][MAXS];
int prefix[MAXN + 1];
int prefix_sq[MAXN + 1];

// Returns Sum((x - mu)**2)
int get_error(int xs[], int l, int r) {
  auto sq_sum = prefix_sq[r + 1] - prefix_sq[l];
  auto sum = prefix[r + 1] - prefix[l];
  auto m = static_cast<double>(sum) / (r - l + 1);
  int m_ = int(m + 0.5);
  return sq_sum - 2 * m_ * sum + m_ * m_ * (r - l + 1);
}

/*
   1 4 6 744 755 777 890 897 902
*/
int get_min_error_recursively(int xs[], int n, int i, int s) {
  if (n <= i) return 0;
  if (s == 0) return INF;

  int& ret = memo[i][s];
  if (ret != -1) return ret;

  ret = INF;

  for (int j = i; j < n; ++j) {
    ret = min(ret, get_error(xs, i, j) +
                       get_min_error_recursively(xs, n, j + 1, s - 1));
  }

  return ret;
}

int get_min_error(int xs[], int n, int s) {
  memset(memo, -1, sizeof(memo));
  memset(prefix, 0, sizeof(prefix));
  memset(prefix_sq, 0, sizeof(prefix_sq));

  sort(xs, xs + n);

  for (int i = 0; i < n; ++i) {
    prefix[i + 1] = prefix[i] + xs[i];
    prefix_sq[i + 1] = prefix_sq[i] + xs[i] * xs[i];
  }
  return get_min_error_recursively(xs, n, 0, s);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> C;
  while (C-- > 0) {
    cin >> N >> S;
    for (int i = 0; i < N; ++i) cin >> A[i];
    cout << get_min_error(A, N, S) << endl;
  }
  return 0;
}
