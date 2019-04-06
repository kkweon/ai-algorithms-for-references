#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int M, N;
  cin >> M >> N;

/*
  2 x 4 = 8 / 2 = 4

  o o o o
  o o o o  2x1 square


  3 x 3 = 9 / 2 = 4

  o o o
  o o o
  o o o

  4 x 3 = 12 / 2 = 6
  x x x x
  x x x x
  x x x x
*/
  cout << (M * N) / 2 << '\n';
  return 0;
}
