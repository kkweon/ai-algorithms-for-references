#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string username;
  cin >> username;

  unordered_set<char> s{ username.begin(), username.end() };
  if (s.size() & 1) cout << "IGNORE HIM!" << '\n';
  else cout << "CHAT WITH HER!" << '\n';
  return 0;
}
