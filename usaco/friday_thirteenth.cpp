/*
ID: kkweon1
TASK: friday
LANG: C++
*/
#include <bits/stdc++.h>
using namespace std;

// feb 28 or 29 if is _leap
bool is_leap(int year) {
  return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

unordered_set<int> thirties = {9, 4, 6, 11};

enum Day { Mon, Tue, Wed, Thu, Fri, Sat, Sun };

Day get_day(int year) {
  assert(1900 <= year);

  int start = 0;

  for (int i = 1901; i <= year; ++i) {
    if (is_leap(i - 1)) {
      start += (366 % 7);
    } else {
      start += (365 % 7);
    }
    start %= 7;
  }
  return (Day)start;
}

Day get_day(int year, int month) {
  int d = get_day(year);
  for (int m = 1; m < month; ++m) {
    if (thirties.find(m) != thirties.end()) {
      d += (30 % 7);
    } else if (m == 2) {
      if (is_leap(year)) {
        d += (29 % 7);
      } else {
        d += (28 % 7);
      }
    } else {
      d += (31 % 7);
    }
    d %= 7;
  }
  return (Day)d;
}

Day get_day(int year, int month, int day) {
  int d = get_day(year, month);
  return (Day)((d + ((day - 1) % 7)) % 7);
}

vector<int> solve(int n) {
  int end_year = 1900 + n - 1;
  int end_month = 12;

  vector<int> sat_to_fri(7, 0);

  for (int year = 1900; year <= end_year; ++year) {
    for (int month = 1; month <= end_month; ++month) {
      int d = get_day(year, month, 13);
      // mon 0 - 2
      // tue 1 - 3
      // sat 5 - 0
      // sun 6 - 1
      //
      int idx = (d + 2) % 7;
      sat_to_fri[idx]++;
    }
  }

  return sat_to_fri;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ifstream in("friday.in");
  ofstream out("friday.out");

  int N;
  in >> N;

  vector<int> result = solve(N);
  for (int i = 0; i < static_cast<int>(result.size()); ++i) {
    out << result[i] << (i < static_cast<int>(result.size()) - 1 ? ' ' : '\n');
  }
  return 0;
}
