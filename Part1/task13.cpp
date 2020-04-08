//Дан ориентированный невзвешенный граф. Необходимо его топологически отсортировать.
//
//Input format
//В первой строке входного файла даны два целых числа N и M (1 ≤ N ≤ 100000, 0 ≤ M ≤ 100000) - количества вершин и рёбер в графе соответственно. Далее в M строках перечислены рёбра графа. Каждое ребро задаётся парой чисел - номерами начальной и конечной вершин соответственно.
//
//Output format
//Вывести любую топологическую сортировку графа в виде последовательности номеров вершин. Если граф невозможно топологически отсортировать, вывести -1.
#include <iostream>
#include <vector>
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

  void add_parent(const int parent) {
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

bool DFS_visit(Graph& gr, Vertex& v, vector<int>& sorted_list) {
  v.set_colour(gray);
  gr.time_update();
  v.set_discovered_time(gr.get_time());

  for (int elem : v.get_related()) {
    Vertex& next_vertex = gr.get_vert(elem);
    if (next_vertex.get_colour() == gray) {
      return false;
    }
    if (next_vertex.get_colour() == white) {
      next_vertex.add_parent(v.get_number());
      bool result = DFS_visit(gr, next_vertex, sorted_list);
      if (!result)  {
        return false;
      }

    }
  }

  gr.time_update();
  v.set_closed_time(gr.get_time());
  v.set_colour(black);
  sorted_list.push_back(v.get_number());
  return true;
}

bool DFS (Graph& gr, vector<int>& sorted_list) {
  for (Vertex& cur_vert : gr.get_graph()) {
    cur_vert.set_colour(white);
  }

  gr.set_time(0);

  for (int i = 1; i <= gr.get_size(); ++i) {
    Vertex& cur_vert = gr.get_vert(i);
    if (cur_vert.get_colour() == white) {
      bool result = DFS_visit(gr, cur_vert, sorted_list);
      if (!result) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int n, m;
  cin >> n >> m;
  Graph graph(n);
  vector<int> sorted_list;

  graph.read(m);

  bool is_cycled = DFS(graph,sorted_list);
  if (is_cycled) {
    for (auto it = sorted_list.rbegin(); it != sorted_list.rend(); ++it) {
      cout << *it << ' ';
    }
  } else {
    cout << -1;
  }

  return 0;
}
