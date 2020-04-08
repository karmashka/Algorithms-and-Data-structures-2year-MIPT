//У Сережи есть скобочная последовательность s1, s2, ..., sn, или, другими словами, строка s длины n, состоящая из символов ( и ).
//
//Сереже нужно ответить на m запросов, каждый из которых характеризуется двумя целыми числами li, ri (1 ≤ li ≤ ri ≤ n). Ответом на i-ый запрос является длина наибольшей правильной скобочной подпоследовательности последовательности sli, sli + 1, ..., sri. Помогите Сереже ответить на все запросы.
//
//Input format
//Первая строка содержит последовательность символов без пробелов s1, s2, ..., sn (1 ≤ n ≤ 106). Каждый символ это либо (, либо ). Вторая строка содержит целое число m (1 ≤ m ≤ 105) количество запросов. Каждая из следующих m строк содержит пару целых чисел. В i-ой строке записаны числа li, ri (1 ≤ li ≤ ri ≤ n) - описание i-го запроса.
//
//Output format
//Выведите ответ на каждый запрос в отдельной строке. Ответы выводите в порядке следования запросов во входных данных.
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

struct vert{
  int pairs;
  int open;
  int close;
  vert(int p, int o, int c):pairs(p), open(o), close(c) {}
};
struct Tree {
  int size;
  vector<int> arr;
  vector<vert> tree;
  Tree(int n): size ((1 << (int)(log2(n) + 1))), arr(size + 1, 0), tree(2 * size + 1, vert(0, 0, 0)) {}

  static int left(int i) {
    return i * 2;
  }

  static int right(int i) {
    return i * 2 + 1;
  }

  void build_tree(int v, int from, int to) {
    if (from == to) {
      if (arr[from] == 1) {
        tree[v] = vert(0, 1, 0);
      } else if (arr[from] == -1) {
        tree[v]= vert(0, 0, 1);
      }
    } else {
      int med = (from + to) / 2;
      build_tree(left(v), from, med);
      build_tree(right(v), med + 1, to);

      tree[v].pairs += tree[left(v)].pairs + tree[right(v)].pairs;
      if ((tree[left(v)].open > 0 && tree[right(v)].close > 0)) {
        if (tree[left(v)].open > tree[right(v)].close) {
          tree[v].pairs += tree[right(v)].close;
          tree[v].open += tree[left(v)].open - tree[right(v)].close;
          tree[v].open += tree[right(v)].open;
          tree[v].close += tree[left(v)].close;
        } else if (tree[left(v)].open < tree[right(v)].close) {
          tree[v].pairs += tree[left(v)].open;
          tree[v].close += tree[right(v)].close - tree[left(v)].open;
          tree[v].close += tree[left(v)].close;
          tree[v].open += tree[right(v)].open;
        } else {
          tree[v].pairs += tree[left(v)].open;
          tree[v].open += tree[right(v)].open;
          tree[v].close += tree[left(v)].close;
        }
      } else {
        tree[v].open += tree[left(v)].open;
        tree[v].open += tree[right(v)].open;
        tree[v].close += tree[left(v)].close;
        tree[v].close += tree[right(v)].close;
      }
    }
  }

  vert get_pair_count(int l, int r, int v, int left_curr, int right_curr) {
    if (right_curr < l || r < left_curr || left_curr > right_curr) {
      return vert(0, 0, 0);
    }
    if (l <= left_curr && right_curr <= r) {
      return tree[v];
    }


    int med = (left_curr + right_curr) / 2;
    vert l_max = get_pair_count(l, r, left(v), left_curr, med);
    vert r_max =  get_pair_count(l, r, right(v), med + 1, right_curr);
    vert ans(r_max.pairs + l_max.pairs, 0, 0);
    if (l_max.open > 0 && r_max.close > 0) {
      if (l_max.open > r_max.close) {
        ans.pairs += r_max.close;
        ans.open += l_max.open - r_max.close;
        ans.open += r_max.open;
        ans.close += l_max.close;
      } else if (l_max.open < r_max.close) {
        ans.pairs += l_max.open;
        ans.close += r_max.close - l_max.open;
        ans.close += l_max.close;
        ans.open += r_max.open;
      } else {
        ans.pairs += l_max.open;
        ans.open += r_max.open;
        ans.close += l_max.close;
      }
    } else {
      ans.open += l_max.open;
      ans.open += r_max.open;
      ans.close += l_max.close;
      ans.close += r_max.close;
    }
    return ans;
  }


};

int main() {
  string s;
  cin >> s;
  int n = s.length();
  Tree t(n);
  for (int i = 0; i < n; ++i) {
    if (s[i] == ')') {
      t.arr[i + 1] = -1;
    } else if (s[i] == '(') {
      t.arr[i + 1] = 1;
    }
  }

  t.build_tree(1, 1, t.size);
  int query_num;
  cin >> query_num;
  for (int i = 0; i < query_num; ++i) {
    int from;
    int to;
    cin >> from >> to;
    cout << t.get_pair_count(from, to, 1, 1, t.size).pairs * 2 << '\n';
  }

}
