#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<vector<bool>> is_friend;

int helper(int curr_student, vector<bool>& used, int n_student) {
  if (curr_student == N) return n_student == N;
  if (used[curr_student]) return helper(curr_student + 1, used, n_student);

  int count = 0;

  for (int i = 0; i < N; ++i) {
    if (i == curr_student) continue;
    if (is_friend[i][curr_student] && !used[i]) {
      used[i] = true;
      used[curr_student] = true;

      count += helper(curr_student + 1, used, n_student + 2);

      used[i] = false;
      used[curr_student] = false;
    }
  }

  return count;
}

int solve() {
  vector<bool> used(N, false);
  return helper(0, used, 0);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int C;
  cin >> C;
  while (C-- > 0) {
    cin >> N >> M;
    is_friend = vector<vector<bool>>(N, vector<bool>(N, false));

    while (M-- > 0) {
      int a, b;
      cin >> a >> b;
      is_friend[a][b] = true;
      is_friend[b][a] = true;
    }

    cout << solve() << endl;
  }
  return 0;
}
