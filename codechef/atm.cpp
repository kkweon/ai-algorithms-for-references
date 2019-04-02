#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int withdraw;
  double balance;

  cin >> withdraw >> balance;

  if (double(withdraw) + 0.5 <= balance && withdraw % 5 == 0) {
    cout << balance - (double)withdraw - 0.5 << endl;
  } else {
    cout << fixed << setprecision(2) << balance << endl;
  }

  return 0;
}
