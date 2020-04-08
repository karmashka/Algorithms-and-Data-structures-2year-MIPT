//Требуется найти в связном графе остовное дерево минимального веса.
//
//Input format
//Первая строка входного файла содержит два натуральных числа n и m — количество вершин и ребер графа соответственно (1 ≤ n ≤ 20000, 0 ≤ m ≤ 100000). Следующие m строк содержат описание ребер по одному на строке. Ребро номер i описывается тремя натуральными числами b_i, e_i и w_i — номера концов ребра и его вес соответственно (1 ≤ b_i,e_i ≤ n, 0 ≤ w_i ≤ 100000).
//
//Граф является связным.


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Set{
private:
  vector<int> m_set;
  vector<int> m_size;
  int m_current_number_of_sets;
public:
  Set(int n):m_current_number_of_sets(n) {
    for (int i = 0; i <= n; ++i) {
      m_set.emplace_back(i);
      m_size.emplace_back(1);
    }
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

class Edge {
private:
  int m_from;
  int m_to;
  int m_weight;

public:
  Edge() = default;
  Edge(int from, int to, int weight): m_from(from), m_to(to), m_weight(weight){}

  int get_weight() {
    return m_weight;
  }
  int get_from() {
    return m_from;
  }

  int get_to() {
    return m_to;
  }

  bool operator < (const Edge& second) const {
    return m_weight < second.m_weight;
  }

  bool operator == (const Edge& second) const {
    return m_weight == second.m_weight && m_from == second.m_from && m_to == second.m_to;
  }
};

class Graph {
private:
  vector<Edge> edges;
  Set s;
public:
  Graph(int n): s(n){};
  void read(int size) {
    int from, to, weight;
    for (int i = 1; i <= size; ++i) {
      cin >> from >> to >> weight;
      edges.emplace_back(from, to, weight);
    }
  }
  friend int Kruskal(Graph& graph);
};

int Kruskal(Graph& graph) {
  int weight = 0;
  sort(graph.edges.begin(), graph.edges.end());
  Edge current = graph.edges[0];
  int i = 0;
  while (graph.s.current_number_of_sets() != 1) {
    current = graph.edges[i];
    if (graph.s.find_set(current.get_from()) != graph.s.find_set(current.get_to())) {
      graph.s.union_set(current.get_from(), current.get_to());
      weight += current.get_weight();
    } else {
      i++;
      continue;
    }
  }

  return weight;
}

int main() {
  int M, N;
  cin >> M >> N;
  Graph g(M);
  g.read(N);
  cout << Kruskal(g);

  return 0;
}