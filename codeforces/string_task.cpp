#include <bits/stdc++.h>
using namespace std;

unordered_set<char> vowels = {'A', 'O', 'Y', 'E', 'U', 'I'};

string solve(const string& s) {
  string ret = "";
  for (auto& c : s) {
    if (vowels.find(toupper(c)) != vowels.end()) {
      continue;
    }
    ret.push_back('.');
    ret.push_back(tolower(c));
  }
  return ret;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string in;
  cin >> in;
  cout << solve(in) << endl;
  return 0;
}
