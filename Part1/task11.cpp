//Дан неориентированный граф. Требуется найти все точки сочленения в нём.
//
//Input format
//Первая строка входного файла содержит два натуральных числа n и m — количества вершин и рёбер графа соответственно (1 ≤ n ≤ 20000, 1 ≤ m ≤ 200000).
//
//Ребро номер i описывается двумя натуральными числами b_i, e_i — номерами концов ребра (1 ≤ b_i,e_i ≤ n).
//
//Output format
//Первая строка выходного файла должна содержать одно натуральное число b — количество точек сочленения в заданном графе. На следующих b строках выведите b целых чисел — номера вершин, которые являются точками сочленения, в возрастающем порядке.
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

enum e_color {
  white,
  gray,
  black
};

class Vertex {
private:
  e_color m_colour;
  int m_number;
  int m_discovered_time;
  int m_up;
  int m_closed_time;
  int m_parent;
  vector <int> m_related;

public:
  Vertex () = default;
  Vertex(const Vertex& second) = default;

  explicit Vertex (int num, e_color new_colour = white): m_colour(new_colour), m_number(num), m_parent(-1) {}

  ~Vertex() = default;

  void set_colour (e_color new_colour) {
    m_colour = new_colour;
  }

  e_color get_colour() const {
    return m_colour;
  }

  void set_number(int num) {
    m_number = num;
  }

  int get_number() const {
    return m_number;
  }

  void set_up(int n) {
    m_up = n;
  }

  int get_up() const {
    return m_up;
  }

  void set_closed_time(int time) {
    m_closed_time = time;
  }

  int get_closed_time() const {
    return m_closed_time;
  }

  int get_discovered_time() const {
    return m_discovered_time;
  }

  void set_discovered_time(int time) {
    m_discovered_time = time;
  }

  void add_related(const int v) {
    m_related.push_back(v);
  }

  void set_parent(const int parent) {
    m_parent = parent;
  }

  const vector <int>& get_related() const  {
    return m_related;
  }

  vector <int>& get_related()  {
    return m_related;
  }

  int get_parent() const {
    return m_parent;
  }

  bool operator== (const Vertex& v) const {
    return m_number == v.m_number;
  }

  bool operator!= (const Vertex& v) const {
    return !(*this == v);
  }

  Vertex& operator = (const Vertex& v) {
    m_number = v.m_number;
    m_colour = v.m_colour;
    m_related = v.m_related;
    m_discovered_time = v.m_discovered_time;
    m_closed_time = v.m_closed_time;
    m_parent = v.m_parent;
    return *this;
  }

};

class Graph {
private:
  int m_time = 0;
  vector<Vertex> graph;
public:
  Graph() = default;
  explicit Graph(int number) {
    for (int i = 0; i <= number; ++i) {
      graph.emplace_back(i);
    }
  }

  int get_size() const {
    return graph.size() - 1;
  }

  void add_vertex(int from, int to) {
    graph[from].add_related(to);
    graph[to].add_related(from);
  }

  Vertex& get_vert(int i) {
    return graph[i];
  }

  vector <Vertex>& get_graph() {
    return graph;
  }

  void set_time(int time) {
    m_time = time;
  }

  int get_time() const {
    return m_time;
  }

  void time_update() {
    m_time++;
  }

  void read(int size) {
    int from, to;
    for (int i = 1; i <= size; ++i) {
      cin >> from >> to;
      add_vertex(from, to);
    }
  }
};

void DFS_visit(Graph& gr, Vertex& v, set<int>& cut_points) {
  v.set_colour(gray);
  gr.time_update();
  v.set_up(gr.get_time());
  v.set_discovered_time(gr.get_time());
  int children = 0;

  for (int elem : v.get_related()) {
    Vertex& next_vertex = gr.get_vert(elem);
    if (elem == v.get_number()  || elem == v.get_parent() ) {
      continue;
    }
    if (next_vertex.get_colour() == gray) {
      v.set_up(min(v.get_up(), next_vertex.get_discovered_time()));
    }
    if (next_vertex.get_colour() == white) {
      children++;
      next_vertex.set_parent(v.get_number());
      DFS_visit(gr, next_vertex, cut_points);
      v.set_up(min(v.get_up(), next_vertex.get_up()));
      if (next_vertex.get_up() >= v.get_discovered_time() && v.get_parent() != -1) {
        cut_points.insert(v.get_number());
      }
    }
  }

  if (v.get_parent() == -1 && children > 1) {
    cut_points.insert(v.get_number());
  }

  gr.time_update();
  v.set_closed_time(gr.get_time());
  v.set_colour(black);
}


void DFS (Graph& gr,  set<int>& cut_points) {
  for (Vertex& cur_vert : gr.get_graph()) {
    cur_vert.set_colour(white);
  }

  gr.set_time(0);

  for (int i = 1; i <= gr.get_size(); ++i) {
    Vertex& cur_vert = gr.get_vert(i);

    if (cur_vert.get_colour() == white) {
      cur_vert.set_parent(-1);
      DFS_visit(gr, cur_vert, cut_points);
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;

  Graph g(n);
  set<int> cut_points;
  g.read(m);

  DFS(g, cut_points);

  cout << cut_points.size() << '\n';

  for (int cut_point : cut_points) {
    cout << cut_point << '\n';
  }

}