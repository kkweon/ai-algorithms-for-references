#include <bits/stdc++.h>
using namespace std;

constexpr int MAX = 1000000000 + 100;
int C, N, M, K;
int bino[201][201];
int skip;


void calculate_binomial_coeff() {
  memset(bino, 0, sizeof(bino));
  for (int i = 0; i <= 200; ++i) {
    bino[i][0] = bino[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      bino[i][j] = min(MAX, bino[i - 1][j - 1] + bino[i - 1][j]);
    }
  }
}

string generate3(int n, int m, int skip) {
  if (n == 0) return string(m, 'o');
  if (skip < bino[n + m - 1][n - 1]) return '-' + generate3(n - 1, m, skip);
  return 'o' + generate3(n, m - 1, skip - bino[n + m - 1][n - 1]);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> C;

  calculate_binomial_coeff();
  while (C-- > 0) {
    cin >> N >> M >> K;
    cout << generate3(N, M, K - 1) << '\n';
  }
  return 0;
}
