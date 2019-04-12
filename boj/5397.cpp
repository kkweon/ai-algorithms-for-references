#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;
  while (T-- > 0) {
    string line;
    cin >> line;
    stack<char> front;
    stack<char> back;
    for (auto& c : line) {
      if (c == '<') {
        if (front.size()) {
          back.push(front.top());
          front.pop();
        }
      } else if (c == '>') {
        if (back.size()) {
          front.push(back.top());
          back.pop();
        }
      } else if (c == '-') {
        if (front.size()) front.pop();
      } else {
        front.push(c);
      }
    }

    while (back.size()) {
      front.push(back.top());
      back.pop();
    }

    string ret;
    while (front.size()) {
      ret.push_back(front.top());
      front.pop();
    }
    reverse(ret.begin(), ret.end());
    cout << ret << endl;
  }

  return 0;
}
