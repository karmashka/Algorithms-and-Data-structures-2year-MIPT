//Вам задан массив префикс-функции некоторой строки. Ваша задача - найти лексикографически минимальную строку, массив префикс-функции которой совпадет с данным. Алфавит для построения ответа: a-z.
//
//Input format
//На входе в первой строке дано число N - размер массива префикс-функции (0 ≤ N ≤ 10^6). На второй строке через пробел идут сами элементы. Гарантируется, что исходный массив является корректным массивом префикс-функции.
//
//Output format
//Выведите искомую строку.

#include <vector>
#include <string>
#include <iostream>

using namespace std;

void build_str(vector<int> & pi, string& result) {
  if (pi.size() == 0) {
    return;
  }

  result = "a";

  for (size_t i = 1; i < pi.size(); i++) {
    if (pi[i] != 0) { //дописываем символ, который стоит на нужном месте в префиксе строки.
      result += result[pi[i] - 1];
    } else {
      vector<bool> used(26, false);
      size_t k = pi[i - 1];  // запоминаем символы, которые нам встретились.
      while (k > 0) {
        used[result[k] - 'a'] = true;
        k = pi[k - 1];
      }

      char c = 'b';
      while (used[c - 'a']) { // Ищем первый символ, который не был встречен
        c++;
      };
      result += c;
    }
  }
}

int main() {
  int n;
  cin >> n;
  vector<int> pi (n, 0);

  for (int i = 0; i < n; ++i) {
    cin >> pi[i];
  }

  string res;
  build_str(pi, res);
  cout << res;

  return 0;
}
