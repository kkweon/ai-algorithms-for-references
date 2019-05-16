#include <bits/stdc++.h>
using namespace std;

const int N = 5 * 10000 + 1;
int P[N];
int R[N];
int G[N];

int k;

int find(int x) {
  if (P[x] != x) P[x] = find(P[x]);
  return P[x];
}

void join(int x, int y) {
  auto px = find(x);
  auto py = find(y);

  if (px != py) {
    if (R[px] < R[py]) swap(px, py);
    P[py] = px;
    R[px] += R[px] == R[py];
    G[px] += G[py];
  }
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  memset(R, 1, sizeof(R));
  memset(P, -1, sizeof(P));
  for (int i = 1; i <= n; ++i) {
    P[i] = i;
    G[i] = 1;
  }

  for (int i = 0; i < m; ++i) {
    cin >> k;
    if (k == 0) continue;

    int first;
    cin >> first;

    for (int j = 0; j < k - 1; ++j) {
      int second;
      cin >> second;
      join(first, second);
    }
  }

  for (int i = 1; i <= n; ++i) {
    cout << G[find(i)] << ' ';
  }
  cout << '\n';


  return 0;
}
