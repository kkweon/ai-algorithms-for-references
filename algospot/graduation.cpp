#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 987654321;
constexpr int MAXN = 12;
constexpr int MAXM = 10;

int C;
int N, K, M, L;

int preqs[MAXN];
int classes[MAXM];
int cache[MAXM][1 << MAXN];

int bitCount(int n) {
  int count = 0;
  while (n) {
    n &= (n - 1);
    ++count;
  }
  return count;
}

int graduate(int semester, int taken) {
  if (K <= bitCount(taken)) return 0;
  if (semester == M) return INF;

  int& ret = cache[semester][taken];
  if (ret != -1) return ret;

  ret = INF;
  int can_take = classes[semester] & ~taken;
  for (int i = 0; i < N; ++i) {
    if ((can_take & (1 << i)) && ((taken & preqs[i]) != preqs[i])) {
      can_take &= ~(1 << i);
    }
  }

  for (int take = can_take; 0 < take; take = ((take - 1) & can_take)) {
    if (L < bitCount(take)) break;
    ret = min(ret, graduate(semester + 1, taken | take) + 1);
  }
  ret = min(ret, graduate(semester + 1, taken));
  return ret;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> C;
  for (int cc = 0; cc < C; ++cc) {
    memset(cache, -1, sizeof(cache));
    memset(preqs, 0, sizeof(preqs));
    memset(classes, 0, sizeof(classes));
    cin >> N >> K >> M >> L;

    for (int i = 0; i < N; ++i) {
      int n_preqs;
      cin >> n_preqs;

      int& ret = preqs[i];
      for (int j = 0; j < n_preqs; ++j) {
        int preq;
        cin >> preq;
        ret |= (1 << preq);
      }
    }

    for (int i = 0; i < M; ++i) {
      int n_course;
      cin >> n_course;

      int& ret = classes[i];
      for (int j = 0; j < n_course; ++j) {
        int course;
        cin >> course;

        ret |= (1 << course);
      }
    }

    int ret = graduate(0, 0);
    if (ret == INF)
      cout << "IMPOSSIBLE" << endl;
    else
      cout << ret << endl;
  }

  return 0;
}
