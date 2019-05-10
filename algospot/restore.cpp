#include <bits/stdc++.h>
using namespace std;

int k;
constexpr int MAXN = 15;
string words[MAXN];

int cache[MAXN][1<<MAXN];
int overlap[MAXN][MAXN];

int restore(int last, int used) {
  if (used == (1 << k) - 1) return 0;
  int& ret = cache[last][used];
  if (ret != -1) return ret;
  ret = 0;
  for (int next = 0; next < k; ++next) {
    if ((used & (1 << next)) == 0) {
      int cand = overlap[last][next] + restore(next, used | 1 << next);
      ret = max(ret, cand);
    }
  }
  return ret;
}

int get_overlap(const string& s1, const string& s2) {
  int i = s1.size() - 1;
  int j = 0;

  while (0 <= i && j < s2.size() && s1[i] == s2[j]) {
    --i;
    ++j;
  }

  return j - (++i);
}

void init() {
  memset(cache, -1, sizeof(cache));
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      overlap[i][j] = get_overlap(words[i], words[j]);
    }
  }
}

string reconstruct(int last, int used) {
  if (used == (1 << k) - 1) return "";
  for (int i = 0; i < k; ++i) {
    if (used & (1 << i)) continue;
    int if_used = restore(i, used | (1 << i));
    if (restore(last, used) == if_used)
      return words[i].substr(overlap[last][i]) + reconstruct(i, used | (1 << i));
  }
  return "";
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int C;
  cin >> C;
  while(C--) {
    cin >> k;
    for (int i = 0; i < k; ++i) cin >> words[i];
    init();
    cout << reconstruct(0, 0) << '\n';
  }
  return 0;
}
