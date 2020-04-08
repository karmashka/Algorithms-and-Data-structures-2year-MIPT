//префикс-функция

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void prefix_function(int N, vector<int>& pi, string& s) {
  for (int i = 1; i < N; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) {
      j = pi[j - 1];
    }
    if (s[i] == s[j]) {
      j++;
    }
    pi[i] = j;
  }
}

int main() {
  string s;
  cin >> s;
  int N = s.size();
  vector<int> pi(N, 0);
  prefix_function(N, pi, s);

  for (auto elem: pi) {
    cout << elem << ' ';
  }
  return 0;
}