#include <bits/stdc++.h>
using namespace std;

unsigned N, S, P, Q;

constexpr unsigned LIMIT = 1U << 31;

constexpr unsigned MOD(unsigned val) { return val % LIMIT; }

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> S >> P >> Q;
  vector<bool> bs(LIMIT, false);

  unsigned long a = MOD(S);
  bs[a] = true;
  unsigned long cnt = 1;
  for (int i = 0; i < N - 1; ++i) {
    a = MOD(MOD(a * P) + Q);
    if (bs[a]) break;
    bs[a] = true;
    ++cnt;
  }
  cout << cnt << endl;
  return 0;
}
