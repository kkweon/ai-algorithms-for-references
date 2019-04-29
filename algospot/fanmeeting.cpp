#include <bits/stdc++.h>
using namespace std;

string idols;
string fans;

vector<int> karatsuba(vector<int>& xs, vector<int>& ys) {
  if (xs.size() < ys.size()) swap(xs, ys);
  if (xs.empty() || ys.empty()) return { };

  int half = xs.size() / 2;

  vector<int> x0 { xs.begin(), xs.begin() + half };
  vector<int> x1 { xs.begin() + half, xs.end() };
  vector<int> y0 { ys.begin(), ys.begin() + min<int>(ys.size(), half) };
  vector<int> y1 { ys.begin() + min<int>(ys.size(), half), ys.end() };

  vector<int> z2 = karatsuba(x1, b1);
  vector<int> z0 = karatsuba(x0, b0);
}

int get_hugs() {
  vector<int> xs(idols.size(), 0);
  transform(idols.begin(), idols.end(), xs.begin(), [](char c) { return c == 'M'; });
  vector<int> ys(fans.size(), 0);
  transform(fans.rbegin(), fans.rend(), ys.begin(), [](char c) { return c == 'M'; });

  vector<int> ret = karatsuba(xs, ys);
  return count_if(ret.begin() + (xs.size() - 1), ret.end() - (xs.size() - 1), [](int x) { return x == 0; });
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int C;
  cin >> C;
  while (C -- > 0) {
    cin >> idols;
    cin >> fans;

    cout << get_hugs() << endl;
  }
  return 0;
}
