#include <bits/stdc++.h>
using namespace std;

#define DEBUG_XS(xs)                                                           \
  std::cout << #xs << " = [ ";                                                 \
  for (auto it = std::begin((xs)); it != std::end((xs)); ++it)                 \
    std::cout << *it << " ";                                                   \
  std::cout << "]\n";

constexpr int N_CLOCK = 16;
constexpr int N_SWITCH = 10;
constexpr int INF = 987654321;
int CLOCKS[N_CLOCK];

vector<vector<int>> switches = {
    {0, 1, 2},         {3, 7, 9, 11},   {4, 10, 14, 15}, {0, 4, 5, 6, 7},
    {6, 7, 8, 10, 12}, {0, 2, 14, 15},  {3, 14, 15},     {4, 5, 7, 14, 15},
    {1, 2, 3, 4, 5},   {3, 4, 5, 9, 13}};

void press(int switch_id) {
  for (auto& c : switches[switch_id]) {
    CLOCKS[c] += 3;
    CLOCKS[c] %= 12;
  }
}

bool all_aligned() {
  return all_of(CLOCKS, CLOCKS + N_CLOCK, [](int x) { return x == 0; });
}

int helper(int switch_id) {
  if (switch_id == N_SWITCH) return all_aligned() ? 0 : INF;
  int ret = INF;
  for (int i = 0; i < 4; ++i) {
    ret = min(ret, i + helper(switch_id + 1));
    press(switch_id);
  }
  return ret;
}

/**
 * Returns the min number of switch to toggle
 * Such that all clocks will point 12 o' clock
 */
int solve() {
  // switch cannot be toggled 4 times in a row
  int ret =  helper(0);
  return ret == INF ? -1 : ret;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int C;
  cin >> C;

  while (C-- > 0) {
    for (int i = 0; i < N_CLOCK; ++i) {
      cin >> CLOCKS[i];
      CLOCKS[i] %= 12;
    }

    cout << solve() << endl;
  }

  return 0;
}
