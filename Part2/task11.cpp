//Реализуйте структуру данных для эффективного вычисления значения максимального из нескольких подряд идущих элементов массива, а также количества элементов, равных максимальному на данном отрезке.
//
//Input format
//В первой строке вводится одно натуральное число N(1 ≤ N ≤ 105) - количество чисел в массиве.
//
//Во второй строке вводятся N чисел от 1 до 100000 - элементы массива.
//
//В третьей строке вводится одно натуральное число K(1 ≤ K ≤ 30000) — количество запросов на вычисление максимума.
//
//В следующих K строках вводится по два числа - номера левого и правого элементов отрезка массива (считается, что элементы массива нумеруются с единицы).
//
//Output format
//Для каждого запроса выведите в отдельной строке через пробел значение максимального элемента на указанном отрезке массива и количество максимальных элементов на этом отрезке.
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Tree {
  int size;
  vector<int> arr;
  vector<pair<int, int>> tree;
  Tree(int n): size ((1 << (int)(log2(n) + 1))), arr(size + 1, 0), tree(2 * size, make_pair(0, 0)) {}

  void build_tree(int v, int from, int to) {
    if (from == to) {
      tree[v] = make_pair(arr[from], 1);
    } else {
      int med = (from + to) / 2;
      build_tree(v * 2, from, med);
      build_tree(v * 2 + 1, med + 1, to);
      if (tree[v * 2].first == tree[v * 2 + 1].first) {
        tree[v] = make_pair(tree[v * 2].first, tree[v * 2].second + tree[v * 2 + 1].second);
      } else {
        if (tree[v * 2].first > tree[v * 2 + 1].first) {
          tree[v] = make_pair(tree[v * 2].first, tree[v * 2].second);
        } else {
          tree[v] = make_pair(tree[v * 2 + 1].first, tree[v * 2 + 1].second);
        }
      }

    }
  }

  pair<int, int> get_max(int l, int r, int v, int left, int right) {
    if (right < l || r < left || left > right) {
      return make_pair(0, 0);
    }
    if (l <= left && right <= r) {
      return tree[v];
    }


    int med = (left + right) / 2;
    pair<int, int> r_max = get_max(l, r, v * 2, left, med);
    pair<int, int> l_max =  get_max(l, r, v * 2 + 1, med + 1, right);
    if (r_max.first == l_max.first) {
      return make_pair(r_max.first, r_max.second + l_max.second);
    } else {
      return max(r_max, l_max);
    }
  }

};

int main() {
  int n;
  cin >> n;
  Tree t(n);

  for(int i = 1; i <= n; ++i) {
    int num;
    cin >> num;
    t.arr[i] = num;
  }

  t.build_tree(1, 1, t.size);
  int query_num;
  cin >> query_num;
  for (int i = 0; i < query_num; ++i) {
    int from;
    int to;
    cin >> from >> to;
    pair<int, int> ans =  t.get_max(from, to, 1, 1, t.size);
    cout << ans.first << ' ' << ans.second <<  '\n';
  }

}
