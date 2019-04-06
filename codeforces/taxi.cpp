#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  unordered_map<int, int> m_cnt;

  for (int i = 0; i < n; ++i) {
    int temp;
    cin >> temp;
    m_cnt[temp]++;
  }

  int taxi = 0;
  taxi += m_cnt[4];
  taxi += m_cnt[3];
  taxi += (m_cnt[2] * 2 + max(0, m_cnt[1] - m_cnt[3]) + 3) / 4;
  cout << taxi << '\n';

  return 0;
}
