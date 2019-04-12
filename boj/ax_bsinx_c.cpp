#include <bits/stdc++.h>
using namespace std;

double relative_error(double a, double b) {
  return abs(a - b) * 1.0 / max(abs(a), abs(b));
}

/*
 * y(x) = Ax + Bsin(x) - c
 * y'(x) = A + Bcos(x)
 */
double solve(double A, double B, double C) {
  double x = 1.0;
  double new_x = 987654321.0;

  for(int i = 0; i < 987654321; ++i) {
    new_x = x - (A * x + B * sin(x) - C) / (A + B * cos(x));
    if (relative_error(new_x, x) < 1e-7) break;
    x = new_x;
  }

  return x;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int A, B, C;
  cin >> A >> B >> C;

  cout << fixed << setprecision(6) << solve(A, B, C) << endl;

  return 0;
}
