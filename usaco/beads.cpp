/*
ID: kkweon1
TASK: beads
LANG: C++
*/
#include <bits/stdc++.h>
using namespace std;

int solve(string& beads) {
  int n = beads.size();
  beads += beads;

  int max_len = 0;

  int n_color = 0;

  for (int i = 0; i < n; ++i) {
    char c = beads[i];

    if (c == 'w') {
      n_color = 0;
    } else {
      n_color = 1;
    }

    int j = i;

    while (n_color <= 2) {
      while (j < i + n && (beads[j] == c || beads[j] == 'w')) {
        j++;
      }
      n_color++;
      c = beads[j];
    }

    max_len = max(max_len, j - i);
  }
  return max_len;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ifstream fin("beads.in");
  ofstream fout("beads.out");

  int n;
  fin >> n;

  string beads;
  fin >> beads;

  fout << solve(beads) << endl;

  return 0;
}
