#include <bits/stdc++.h>
using namespace std;

using LL = long long;

constexpr int MAXN = 1e5;
int N;
int d[MAXN];
set<int> value_set;
unordered_map<int, int> val2id;

class BIT {
public:
  BIT() {
    m_tree = vector<LL>(MAXN + 1, 0);
  }

  void update(int i, LL val) {
    for (; i <= MAXN; i += i & -i) m_tree[i] += val;
  }

  void set(int i, LL val) {
    LL old = get(i);
    update(i, val - old);
  }

  LL query(int i) {
    LL ret = 0;
    for (; 0 < i; i -= i & -i) ret += m_tree[i];
    return ret;
  }

  LL get(int i) {
    return query(i) - query(i - 1);
  }

private:
  vector<LL> m_tree;
};

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> d[i];
    value_set.insert(d[i]);
  }

  int id = 1;
  for (auto& val : value_set) {
    val2id[val] = id++;
  }

  BIT a, b, c;

  for (int i = 0; i < N; ++i) {
    auto id = val2id[d[i]];
    a.set(id, 1);
    b.set(id, a.query(id - 1));
    c.set(id, b.query(id - 1));
  }

  cout << c.query(MAXN) << endl;

  return 0;
}
