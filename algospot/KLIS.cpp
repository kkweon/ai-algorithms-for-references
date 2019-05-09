#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 500;
constexpr int MAX = 2000000000 + 1;
int N, K;
int A[MAXN];

int best = 0;
int skip = 0;

int memo_len[MAXN + 1];
int memo_cnt[MAXN + 1];

int find_lis(int idx) {
  auto& ret = memo_len[idx + 1];
  if (ret != -1) return ret;
  ret = 1;
  for (int i = idx + 1; i < N; ++i) {
    if (idx == -1 || A[idx] < A[i])
      ret = max(ret, 1 + find_lis(i));
  }
  return ret;
}

int count(int idx) {
  if (find_lis(idx) == 1) return 1;
  auto& ret = memo_cnt[idx + 1];
  if (ret != -1) return ret;
  ret = 0;
  for (int next = idx + 1; next < N; ++next) {
    if (idx == -1 || (A[idx] < A[next] && find_lis(idx) == find_lis(next) + 1)) {
      ret = min<long long>(MAX, static_cast<long long>(ret) + count(next));
    }
  }
  return ret;
}

void reconstruct(int start, int skip, vector<int>& lis) {
  if (start != -1) lis.push_back(A[start]);
  vector<pair<int, int>> followers;
  for (int next = start + 1; next < N; ++ next) {
    if ((start == -1 || A[start] < A[next]) && find_lis(start) == find_lis(next) + 1)
      followers.push_back(make_pair(A[next], next));
  }
  sort(followers.begin(), followers.end());
  for (int i = 0; i < followers.size(); ++i) {
    int idx = followers[i].second;
    int cnt = count(idx);
    if (cnt <= skip) {
      skip -= cnt;
    } else {
      reconstruct(idx, skip, lis);
      break;
    }
  }
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int C;
  cin >> C;
  while (C-- > 0) {
    cin >> N >> K;
    memset(memo_len, -1, sizeof(memo_len));
    memset(memo_cnt, -1, sizeof(memo_cnt));
    // for (int i = 0; i <= N; ++i) memo_len[i] = -1;
    for (int i = 0; i < N; ++i) cin >> A[i];
    best = find_lis(-1) - 1;
    cout << best << '\n';

    vector<int> ret;
    reconstruct(-1, K - 1, ret);
    for (auto& r : ret) cout << r << ' ';
    cout << '\n';
  }
  return 0;
}
