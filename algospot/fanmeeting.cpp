#include <bits/stdc++.h>
using namespace std;

string idols;
string fans;

void add(vector<int>& xs, vector<int>& ys, int k) {
  int s = max(xs.size(), ys.size() + k);
  xs.resize(s, 0);
  ys.resize(s, 0);

  for (int i = 0; i < s - k; ++i) {
    xs[i + k] += ys[i];
  }
}

void sub(vector<int>& xs, vector<int>& ys) {
  int s = max(xs.size(), ys.size());
  xs.resize(s, 0);
  ys.resize(s, 0);
  for (int i = 0; i < s; ++i) xs[i] -= ys[i];
}

vector<int> multi(vector<int>& xs, vector<int>& ys) {
  int s1 = xs.size();
  int s2 = ys.size();
  vector<int> res(s1 + s2 - 1, 0);

  for (int i = 0; i < s1; ++i) {
    for (int j = 0; j < s2; ++j) {
      res[i + j] += xs[i] * ys[j];
    }
  }

  return res;
}

vector<int> karatsuba(vector<int>& xs, vector<int>& ys) {
  if (xs.empty() || ys.empty()) return {};
  if (xs.size() < ys.size()) karatsuba(ys, xs);
  if (xs.size() < 50) return multi(xs, ys);

  int half = xs.size() / 2;

  vector<int> x0{xs.begin(), xs.begin() + half};
  vector<int> x1{xs.begin() + half, xs.end()};
  vector<int> y0{ys.begin(), ys.begin() + min<int>(ys.size(), half)};
  vector<int> y1{ys.begin() + min<int>(ys.size(), half), ys.end()};

  vector<int> z2 = karatsuba(x1, y1);
  vector<int> z0 = karatsuba(x0, y0);

  add(x0, x1, 0);
  add(y0, y1, 0);

  auto z1 = karatsuba(x0, y0);
  sub(z1, z2);
  sub(z1, z0);

  vector<int> res;
  add(res, z2, 0);
  add(res, z1, half);
  add(res, z0, half + half);
  return res;
}

int get_hugs() {
  vector<int> xs(idols.size(), 0);
  transform(idols.begin(), idols.end(), xs.begin(),
            [](char c) { return c == 'M'; });

  vector<int> ys(fans.size(), 0);
  transform(fans.rbegin(), fans.rend(), ys.begin(),
            [](char c) { return c == 'M'; });

  vector<int> ret = karatsuba(ys, xs);
  return count_if(ret.begin() + (xs.size() - 1), ret.begin() + ys.size(),
                  [](int x) { return x == 0; });
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int C;
  cin >> C;
  while (C-- > 0) {
    cin >> idols;
    cin >> fans;

    cout << get_hugs() << endl;
  }
  return 0;
}
