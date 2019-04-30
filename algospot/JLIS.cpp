#include <bits/stdc++.h>
using namespace std;

int C, N, M;
int A[100], B[100];
int memo[101][101];

constexpr long long NEG_INF = numeric_limits<long long>::min();


int JLIS(int a_idx, int b_idx) {
  long long a = a_idx == -1 ? NEG_INF : A[a_idx];
  long long b = b_idx == -1 ? NEG_INF : B[b_idx];
  long long max_val = max(a, b);

  int& cache = memo[a_idx + 1][b_idx + 1];
  if (cache != -1) return cache;

  int ret = 0;

  for (int i = a_idx + 1; i < N; ++i) {
    if (max_val < A[i]) ret = max(ret, 1 + JLIS(i, b_idx));
  }

  for (int j = b_idx + 1; j < M; ++j) {
    if (max_val < B[j]) ret = max(ret, 1 + JLIS(a_idx, j));
  }

  cache = ret;
  return cache;
}

int get_JLIS() {
  memset(memo, -1, sizeof(memo));
  return JLIS(-1, -1);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> C;
  while (C-- > 0) {
    cin >> N >> M;

    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < M; ++i) cin >> B[i];

    cout << get_JLIS() << endl;
  }
  return 0;
}
