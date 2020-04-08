//Вам задан массив Z-функции некоторой строки. Ваша задача - найти лексикографически минимальную строку, массив Z-функции которой совпадет с данным. Алфавит для построения ответа: a-z.
//
//Input format
//На входе в первой строке дано число N - размер массива префикс-функции (0 ≤ N ≤ 10^6). На второй строке через пробел идут сами элементы. Гарантируется, что исходный массив является корректным массивом Z-функции.

#include <iostream>
#include <vector>

using namespace std;

void str_by_z(vector<int> & z, string& answer) {
  if (z.size() == 0) {
    return;
  }
  answer = "a";
  vector<size_t> used_indices;

  bool append_after_block = true;

  size_t str_index = 1;
  while (str_index < z.size()) {
    if (z[str_index] != 0) {
      used_indices.clear();
      size_t prefix_index = 0;
      size_t curr_len_to_blck_end = z[str_index];

      while (curr_len_to_blck_end > 0) {

        if (z[str_index] > curr_len_to_blck_end) {
          curr_len_to_blck_end = z[str_index];
          used_indices.push_back(z[str_index]);
          prefix_index = 0;
        }

        if (z[str_index] == curr_len_to_blck_end) {
          used_indices.push_back(z[str_index]);
        }

        answer += answer[prefix_index];

        prefix_index++;
        str_index++;
        curr_len_to_blck_end--;
      }
      append_after_block = true;
    } else {
      if (append_after_block) {
        vector<bool> used_chars(26, false);
        for (size_t n : used_indices) {
          used_chars[answer[n] - 'a'] = true;
        }

        char c = 'b';
        while (used_chars[c - 'a']) {
          c++;
        }
        answer += c;
        append_after_block = false;
      } else {
        answer += "b";
      }
      str_index++;
    }
  }
}

int main() {
  int n;
  cin >> n;
  string res(n, 0);
  vector<int> z(n, 0);
  for (int i = 0; i < n; ++i) {
    cin >> z[i];
  }

  str_by_z(z, res);
  cout << res;
  return 0;
}
