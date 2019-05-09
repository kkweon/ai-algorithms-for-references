#include <bits/stdc++.h>
using namespace std;

int k;
string words[15];

string merge(const string& s1, const string& s2) {
  int i = s1.size() - 1;
  int j = 0;

  while (0 <= i && j < s2.size() && s1[i] == s2[j]) {
    --i;
    ++j;
  }

  return s1 + s2.substr(j);
}

string find() {
  string temp = words[0];
  for (int i = 1; i < k; ++i) {
    temp = merge(temp, words[i]);
  }
  return temp;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int C;
  cin >> C;
  while(C--) {
    cin >> k;
    for (int i = 0; i < k; ++i) cin >> words[i];
    cout << find() << '\n';
  }
  return 0;
}
