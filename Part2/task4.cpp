//Реализуйте структуру данных для эффективного вычисления НОД нескольких подряд идущих элементов массива.
//
//Input format
//В первой строке вводится одно натуральное число N(1 ≤ N ≤ 105) - количество чисел в массиве.
//
//Во второй строке вводятся N чисел от 1 до 100000 - элементы массива.
//
//В третьей строке вводится одно натуральное число K(1 ≤ K ≤ 30000) - количество запросов на вычисление НОД.
//
//В следующих K строках вводится по два числа - номера левого и правого элементов отрезка массива (считается, что элементы массива нумеруются с единицы).
//
//Output format
//Для каждого запроса выведите НОД всех чисел соответствующего участка массива. Разделяйте числа переводами строк.

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int gcd (int a, int b) {
  while (b) {
    a %= b;
    swap (a, b);
  }
  return a;
}

struct Tree {
  int size;
  vector<int> arr;
  vector<int> tree;
  Tree(int n): size ((1 << (int)(log2(n) + 1))), arr(size + 1, 0), tree(2 * size,0) {}

  void build_tree(int v, int from, int to) {
    if (from == to) {
      tree[v] = arr[from];
    } else {
      int med = (from + to) / 2;
      build_tree(v * 2, from, med);
      build_tree(v * 2 + 1, med + 1, to);
      if (tree[v * 2] == tree[v * 2 + 1]) {
        tree[v] = tree[v * 2];
      } else {
        tree[v] = gcd(tree[v * 2], tree[v * 2 + 1]);
      }
    }
  }

  size_t get_gcd(int l, int r, int v, int left, int right) {
    if (right < l || r < left || left > right) {
      return 0;
    }
    if (l <= left && right <= r) {
      return tree[v];
    }


    int med = (left + right) / 2;
    size_t r_gcd = get_gcd(l, r, v * 2, left, med);
    size_t l_gcd = get_gcd(l, r, v * 2 + 1, med + 1, right);
    if (r_gcd == l_gcd) {
      return r_gcd;
    } else {
      return gcd(r_gcd, l_gcd);
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
    size_t  ans =  t.get_gcd(from, to, 1, 1, t.size);
    cout << ans <<  '\n';
  }

}
