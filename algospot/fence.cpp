#include <bits/stdc++.h>
using namespace std;

int fences[20000];
int n_fence;

int get_area() {
  stack<int> st;

  int max_area = 0;

  for (int i = 0; i < n_fence; ++i) {
    while (st.size() && fences[st.top()] > fences[i]) {
      int idx = st.top(); st.pop();
      int height = fences[idx];
      int width = st.empty() ? 0 : st.top() + 1;
      width = i - width;

      max_area = max(max_area, height * width);
    }

    st.push(i);
  }

  while (st.size()) {
    int idx = st.top(); st.pop();
    int height = fences[idx];
    int width = st.empty() ? 0 : st.top() + 1;
    width = n_fence - width;

    max_area = max(max_area, height * width);
  }

  return max_area;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int C;
  cin >> C;
  while (C -- > 0) {
    cin >> n_fence;

    for (int i = 0; i < n_fence; ++i) {
      cin >> fences[i];
    }

    cout << get_area() << endl;
  }

  return 0;
}
