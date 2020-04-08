//Найти все вхождения строки T в строку S.
//
//Input format
//Первые две строки входных данных содержат строки S и T, соответственно. Длины строк больше 0 и меньше 50000, строки содержат только латинские буквы.
//
//Output format
//Выведите номера символов, начиная с которых строка T входит в строку S, в порядке возрастания.
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void prefix_function(int N, vectsor<int>& pi, string& s) {
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
  string s, str_to_find;
  cin >> s;
  int s_size = s.size();
  cin >> str_to_find;
  int str_to_find_size = str_to_find.size();

  str_to_find += "#";
  str_to_find += s;

  int N = str_to_find.size();
  vector<int> pi(N, 0);
  prefix_function(N, pi, str_to_find);

  for (int i = str_to_find_size; i < N; ++i) {
    if (pi[i] == str_to_find_size) {
      cout << i - 2 * str_to_find_size << '\n';
    }
  }

  return 0;
}
