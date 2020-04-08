//Одно разбросанное на островах Океании государство решило создать сеть автомобильных дорог (вернее, мостов). По каждому мосту можно перемещаться в обе стороны. Был разработан план очередности строительства мостов и известно, что после постройки всех мостов можно будет проехать по ним с каждого острова на каждый (возможно, через некоторые промежуточные острова).
//
//Однако, этот момент может наступить до того, как будут построены все мосты. Ваша задача состоит такое минимальное количество мостов, после постройки которых (в порядке строительства по плану) можно будет попасть с любого острова на любой другой.
//
//Input format
//Первая строка содержит два числа: N — число островов (1 ≤ N ≤ 100000) и M — количество мостов в плане (1 ≤ M ≤ 200000). В каждой следующей строке содержится описание моста – два числа x и y (0 ≤ x, y ≤ N-1) – номера соединяемых островов.
//
//Output format
//Выведите в выходной файл одно число – минимальное количество построенных мостов, по которым можно попасть с любого острова на любой.


#include <iostream>
#include <vector>
using namespace std;
class Set{
private:
  vector<int> m_set;
  vector<int> m_size;
  int m_current_number_of_sets;
public:
  Set(int n):m_current_number_of_sets(0) {
    for (int i = 0; i < n; ++i) {
      m_set.emplace_back(i);
      m_size.emplace_back(0);
    }

  }

  void make_set(int x) {
    m_size[x] = 1;
    m_set[x] = x;
    m_current_number_of_sets++;
  }

  int current_number_of_sets() {
    return m_current_number_of_sets;
  }

  int find_set(int x) {
    if (x == m_set[x]) {
      return x;
    }
    return m_set[x] = find_set(m_set[x]);
  }

  void union_set(int x, int y) {
    if (x != y) {
      if(m_size[x] > m_size[y]) {
        swap(x, y);
      }
    }
    x = find_set(x);
    y = find_set(y);
    if (x != y) {
      m_set[y] = x;
      m_size[x] += m_size[y];
      m_current_number_of_sets--;
    }
  }
};

int main() {
  int number_of_islands;
  int number_of_ways;
  int min_number_of_bridges = 0;
  cin >> number_of_islands >> number_of_ways;
  Set s(number_of_islands);
  for (int i = 1; i <= number_of_islands; ++i) {
    s.make_set(i);
  }

  for (int i = 0; i < number_of_ways; ++i) {
    int from, to;
    cin >> from >> to;
    if (s.current_number_of_sets() == 1) {
      continue;
    } else {
      s.union_set(from, to);
      min_number_of_bridges++;
    }
  }

  cout << min_number_of_bridges;
  return 0;
}

