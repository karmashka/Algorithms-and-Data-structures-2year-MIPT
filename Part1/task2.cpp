//Во время контрольной работы профессор Флойд заметил, что некоторые студенты обмениваются записками. Сначала он хотел поставить им всем двойки, но в тот день профессор был добрым, а потому решил разделить студентов на две группы: списывающих и дающих списывать, и поставить двойки только первым.
//
//У профессора записаны все пары студентов, обменявшихся записками. Требуется определить, сможет ли он разделить студентов на две группы так, чтобы любой обмен записками осуществлялся от студента одной группы студенту другой группы.
//
//Input format
//В первой строке находятся два числа N и M — количество студентов и количество пар студентов, обменивающихся записками (1 ≤ N ≤ 100, 0 ≤ M ≤ N*(N−1)/2). Далее в M строках расположены описания пар студентов: два числа, соответствующие номерам студентов, обменивающихся записками (нумерация студентов идёт с 1). Каждая пара студентов перечислена не более одного раза.
//
//Output format
//Необходимо вывести ответ на задачу профессора Флойда. Если возможно разделить студентов на две группы — выведите «YES»; иначе выведите «NO».
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

enum e_color {
  white,
  gray,
  black,
  red,
  blue
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

  void add_edge(int from, int to) {
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
      add_edge(from, to);
    }
  }
};

bool DFS_visit(Graph& gr, Vertex& v) {

  gr.time_update();
  v.set_discovered_time(gr.get_time());
  if (v.get_parent() == white) {
    if (gr.get_vert(v.get_parent()).get_colour() == red) {
      v.set_colour(blue);
    } else {
      v.set_colour(red);
    }
  }
  for (int elem : v.get_related()) {
    Vertex& next_vertex = gr.get_vert(elem);
    if (next_vertex.get_colour() == v.get_colour()) {
      return false;
    }
    if (next_vertex.get_colour() == white) {
      next_vertex.add_parent(v.get_number());
      if (v.get_colour() == blue) {
        next_vertex.set_colour(red);
      } else {
        next_vertex.set_colour(blue);
      }
      if (!DFS_visit(gr, next_vertex)) {
        return false;
      }
    }
  }

  gr.time_update();
  v.set_closed_time(gr.get_time());
  return true;
}

bool DFS (Graph& gr) {
  for (Vertex& cur_vert : gr.get_graph()) {
    cur_vert.set_colour(white);
  }

  gr.set_time(0);
  gr.get_vert(0).set_colour(blue);
  for (int i = 1; i <= gr.get_size(); ++i) {
    Vertex& cur_vert = gr.get_vert(i);
    if (cur_vert.get_colour() == white) {
      cur_vert.set_colour(red);
      if (!DFS_visit(gr, cur_vert)) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int n, m;
  cin >> n >> m;

  Graph g(n);

  g.read(m);

  bool is_divided = DFS(g);

  if (is_divided) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }

  return 0;
}