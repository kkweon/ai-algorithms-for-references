#include <bits/stdc++.h>
using namespace std;

// n_word, n_query
int m, q;
string words[500];
unordered_map<string, int> w2i;

double B[500];
double T[500][500];
double M[500][500];

int n;
int Q[100];

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> m >> q;
  for (int i = 0; i < m; ++i) {
    cin >> words[i];
    w2i[words[i]] = i;
  }

  for (int i = 0; i < m; ++i) cin >> B[i];
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < m; ++j)
      cin >> T[i][j];
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < m; ++j)
      cin >> M[i][j];

  for (int i = 0; i < q; ++i) {
    cin >> n;
    for (int j = 0; j < n; ++j) {
      string word;
      cin >> word;
      Q[j] = w2i[word];
    }
  }

  return 0;
}
