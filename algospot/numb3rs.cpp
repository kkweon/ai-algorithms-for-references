#include <bits/stdc++.h>
using namespace std;

#define DEBUG_XS(xs) \
    std::cout << #xs << " = [ "; \
    for (auto it = std::begin((xs)); it != std::end((xs)); ++it) \
        std::cout << *it <<  " "; \
    std::cout << "]\n";

int N, D, P, Q;
int connected[50][50];
int deg[50];
double memo[50][101];

/*
   dp[town_id][days] += dp[prev_town][days - 1]
    for prev_town in prev_towns
      dp[prev_town][days - 1]
 */
double get_prob(int city_id, int day) {
  if (day == 0) return city_id == P ? 1.0 : 0.0;
  auto& ret = memo[city_id][day];
  if (0 <= ret) return ret;
  ret = 0;
  for (int i = 0; i < N; ++i) {
    if (connected[i][city_id])
      ret += get_prob(i, day - 1) / static_cast<double>(deg[i]);
  }
  return ret;
}

vector<double> solve(const vector<int>& queries) {
  memset(memo, -1, sizeof(memo));
  vector<double> ret;
  for (auto& q : queries) ret.emplace_back(get_prob(q, D));
  return ret;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int C;
  cin >> C;
  while (C-- > 0) {
    cin >> N >> D >> P;
    memset(deg, 0, sizeof(deg));
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        cin >> connected[i][j];
        if (i < j && connected[i][j]) {
          deg[i]++;
          deg[j]++;
        }
      }
    }
    cin >> Q;
    vector<int> queries(Q, 0);
    for (int i = 0; i < Q; ++i) {
      cin >> queries[i];
    }
    vector<double> probs = solve(queries);
    cout << fixed << setprecision(8);
    for (auto& p : probs) cout << p << " ";
    cout << endl;
  }
  return 0;
}
