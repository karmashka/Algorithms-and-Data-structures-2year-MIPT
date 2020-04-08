//Дан массив из n чисел. Требуется написать программу, которая будет отвечать на запросы следующего вида: найти минимум на отрезке между u и v включительно.

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct STable{
  vector<vector<long long>> table;
  int size;

  STable(int n): size(n) {
    for (int i = 0; i <= log2(n); ++i) {
      table.emplace_back(vector<long long>(n + 1, 0));
    }
  }

  void create_table(long long num) {
    table[0][1] = num;
    for (int i = 2; i <= size; ++i)  {
      table[0][i] = ((23 * table[0][i - 1] + 21563) % 16714589);
    }

    for (int k = 1; k <= log2(size); ++k) {
      for (int i = 1; i <= size; ++i) {
        table[k][i] = min(table[k - 1][i], table[k - 1][i + (1ull << (k - 1))]);
      }
    }
  }

  long long get_min (int from, int to) {
    if (from > to) swap(from, to);
    int k = log2(to - from + 1);
    return min (table[k][from], table[k][to - (1ull << k) + 1]);
  }

};

int main() {
  int n, m, a1;
  cin >> n >> m >> a1;
  STable table(n);
  table.create_table(a1);

  size_t u, v;
  size_t u_old, v_old;
  cin >> u >> v;
  long long ans;
  for (size_t i = 1; i <= m; ++i) {
    ans = table.get_min(u, v);
    if (i == m) {
      u_old = u;
      v_old = v;
    }
    u = (17 * u + 751 + ans + 2 * (i)) % n + 1;
    v = (13 * v + 593 + ans + 5 * (i)) % n + 1;


  }
  cout << u_old << ' ' << v_old << ' ' << ans;


  return 0;
}
