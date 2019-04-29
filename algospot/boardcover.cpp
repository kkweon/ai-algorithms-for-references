#include <bits/stdc++.h>
using namespace std;

int H, W;
char board[20][20];

/*
   x    xx
   xx   x

   xx    x
    x   xx

 */
int cover_type[4][3][2] = {
  {{0, 0}, { 1, 0 }, {1, 1}},
  {{0, 0}, {1, 0}, {0, 1}},
  {{0, 0}, {0, 1}, {1, 1}},
  {{0, 0}, {1, 0}, {1, -1}}
};

bool check(int r, int c, int type) {
  for (int i = 0; i < 3; ++i) {
    int nr = r + cover_type[type][i][0];
    int nc = c + cover_type[type][i][1];
    if (nr < 0 || nc < 0 || H <= nr || W <= nc || board[nr][nc] != '.') return false;
  }
  return true;
}

void set_board(int r, int c, int type, char val) {
  for (int i = 0; i < 3; ++i) {
    int nr = r + cover_type[type][i][0];
    int nc = c + cover_type[type][i][1];
    assert(0 <= nr && nr < H && 0 <= nc && nc < W && board[nr][nc] != val);
    board[nr][nc] = val;
  }
}



int solve(int r, int c) {
  if (H <= r) {
    bool ok = true;
    for (int i = 0; i < H; ++i) {
      for (int j = 0; j < W; ++j) {
        if (board[i][j] == '.') {
          ok = false;
          break;
        }
      }
    }
    return ok;
  }

  if (W <= c) return solve(r + 1, 0);
  if (board[r][c] == '#') return solve(r, c + 1);

  int count = 0;
  for (int i = 0; i < 4; ++i) {
    if (check(r, c, i)) {
      set_board(r, c, i, '#');
      count += solve(r, c + 1);
      set_board(r, c, i, '.');
    }
  }
  return count;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T;
  cin >> T;
  while(T-->0) {
    cin >> H >> W;
    for (int i = 0; i < H; ++i) {
      for (int j = 0; j < W; ++j) {
        cin >> board[i][j];
      }
    }

    cout << solve(0, 0) << endl;
  }
  return 0;
}
