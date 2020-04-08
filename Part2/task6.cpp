//  Реализуйте структуру данных для хранения элементов и увеличения нескольких подряд идущих элементов на одно и то же число.
//
//Input format
//В первой строке вводится одно натуральное число N(1 ≤ N ≤ 105) - количество чисел в массиве.
//
//Во второй строке вводятся N чисел от 1 до 100000 - элементы массива.
//
//В третьей строке вводится одно натуральное число M(1 ≤ M ≤ 500000) - количество запросов.
//
//Каждая из следующих M строк представляет собой описание запроса. Сначала вводится одна буква, кодирующая вид запроса (g - получить текущее значение элемента по номеру, a - увеличить все элементы на отрезке). Следом за g вводится одно число - номер элемента. Следом за a вводится три числа - левый и правый концы отрезка и число add, на которое нужно увеличить все элементы данного отрезка массва(1 ≤ add ≤ 100000).
//
//Output format
//Выведите ответы на запросы вида g, разделяя их переводами строк.
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Tree {
  int size;
  vector<size_t > arr;
  vector<size_t> tree;
  Tree(int n): size ((1 << (int)(log2(n) + 1))), arr(size + 1, 0), tree(2 * size, 0) {}

  void build_tree(int v, int from, int to) {
    if (from == to) {
      tree[v] = arr[from];
      tree[v] = arr[from];
    } else {
      int med = (from + to) / 2;
      build_tree(v * 2, from, med);
      build_tree(v * 2 + 1, med + 1, to);
    }
  }

  void update (int v, int tree_l, int tree_r, int curr_l, int curr_r, size_t add) {
    if (tree_l > tree_r || tree_l > curr_r || tree_r < curr_l) {
      return;
    }
    if (tree_l >= curr_l && tree_r <= curr_r) {
      tree[v] += add;
    } else {
      int med = (tree_l + tree_r) / 2;
      update (v * 2, tree_l, med,  curr_l, curr_r, add);
      update (v * 2 + 1, med + 1, tree_r, curr_l, curr_r, add);
    }
  }

  size_t get_elem (int v, int left, int right, int pos) {
    if (left == right) {
      return tree[v];
    }
    int med = (left + right) / 2;
    if (pos <= med) {
      return tree[v] + get_elem(v * 2, left, med, pos);
    } else {
      return tree[v] + get_elem(v * 2 + 1, med + 1, right, pos);
    }
  }

};

int main() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  Tree t(n);

  for(int i = 1; i <= n; ++i) {
    size_t num;
    cin >> num;
    t.arr[i] = num;
  }

  t.build_tree(1, 1, t.size);
  int query_num;
  cin >> query_num;
  char command;
  for (int i = 1; i <= query_num; ++i) {
    cin >> command;
    if (command == 'a') {
      int from, to;
      size_t add;
      cin >> from >> to >> add;
      t.update(1, 1, t.size, from, to, add);
    } else if (command == 'g') {
      int i;
      cin >> i;
      cout << t.get_elem(1, 1, t.size, i) << '\n';
    }

  }
}
