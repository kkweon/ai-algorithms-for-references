#include <bits/stdc++.h>
using namespace std;
int N, P, L;
constexpr int MAX = 1000000000 + 1;
int length[51];

void precalc() {
  length[0] = 1;
  for (int i = 1; i <= 50; ++i)
    length[i] = min(MAX, length[i - 1] * 2 + 2);
}

const string DRAGON_CURVE = "FX";
const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";

char expand(const string& dragon_curve, int gen, int skip) {
  if (gen == 0) {
    assert(skip < dragon_curve.size());
    return dragon_curve[skip];
  }
  for (auto& c : dragon_curve) {
    if (c == 'X' || c == 'Y') {

      if (length[gen] <= skip) skip -= length[gen];
      else if (c == 'X') return expand(EXPAND_X, gen - 1, skip);
      else return expand(EXPAND_Y, gen - 1, skip);

    } else if (0 < skip) skip--;
    else return c;
  }

  return '#';
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int C;
  cin >> C;

  precalc();

  while(C -- > 0) {
    cin >> N >> P >> L;
    for (int i = P; i < P + L; ++i) {
      cout << expand(DRAGON_CURVE, N, i - 1);
    }
    cout << '\n';
  }

  return 0;
}
