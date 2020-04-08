//
//  Вам задан ориентированный граф с N вершинами и M ребрами (1 ≤ N ≤ 20000, 1 ≤ M ≤ 200000). Найдите компоненты сильной связности заданного графа и топологически отсортируйте его конденсацию.
//
//Input format
//Граф задан во входном файле следующим образом: первая строка содержит числа N и M. Каждая из следующих M строк содержит описание ребра — два целых числа из диапазона от 1 до N — номера начала и конца ребра.
//
//Output format
//На первой строке выведите число K — количество компонент сильной связности в заданном графе. На следующей строке выведите N чисел — для каждой вершины выведите номер компоненты сильной связности, которой принадлежит эта вершина. Компоненты сильной связности должны быть занумерованы таким образом, чтобы для любого ребра номер компоненты сильной связности его начала не превышал номера компоненты сильной связности его конца.
#include <iostream>
#include <vector>
#include <list>
#include <map>
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

struct great {
  bool operator()(const Vertex& a, const Vertex& b) const { return a.get_number() > b.get_number(); }
};

void DFS_visit(Graph& gr, Vertex& v, vector<int>& sorted_list) {
  v.set_colour(gray);
  gr.time_update();
  v.set_discovered_time(gr.get_time());

  for (int elem : v.get_related()) {
    Vertex& next_vertex = gr.get_vert(elem);
    if (next_vertex.get_colour() == white) {
      next_vertex.add_parent(v.get_number());
      DFS_visit(gr, next_vertex, sorted_list);

    }
  }

  gr.time_update();
  v.set_closed_time(gr.get_time());
  v.set_colour(black);
  sorted_list.push_back(v.get_number());
}

void DFS_visit(Graph& gr, Vertex& v, vector<vector<int>>& comps) {
  v.set_colour(gray);
  gr.time_update();
  v.set_discovered_time(gr.get_time());
  for (int elem : v.get_related()) {
    Vertex& vert = gr.get_vert(elem);
    if (vert.get_colour() == white) {
      DFS_visit(gr, vert, comps);
      comps.back().push_back(vert.get_number());
    }
  }

  gr.time_update();
  v.set_closed_time(gr.get_time());
  v.set_colour(black);
}

void transponation(Graph& gr, Graph& gr1) {
  for (auto i : gr.get_graph()) {
    for (auto j : i.get_related()) {
      gr1.add_vertex(j, i.get_number());
      gr1.get_vert(j).set_closed_time(gr.get_vert(j).get_closed_time());
      gr1.get_vert(j).set_discovered_time(gr.get_vert(j).get_discovered_time());
    }
  }
}

void DFS (Graph& gr, vector<vector<int>>& comps, vector<int>& sorted_list) {
  for (Vertex& cur_vert : gr.get_graph()) {
    cur_vert.set_colour(white);
  }

  gr.set_time(0);

  for (int elem:sorted_list) {
    Vertex& cur_vert = gr.get_vert(elem);
    if (cur_vert.get_colour() == white) {
      comps.push_back(vector<int>());
      comps.back().push_back(cur_vert.get_number());
      DFS_visit(gr, cur_vert, comps);
    }
  }
}

void DFS (Graph& gr, vector<int>& sorted_list) {
  for (Vertex& cur_vert : gr.get_graph()) {
    cur_vert.set_colour(white);
  }

  gr.set_time(0);

  for (int i = 1; i <= gr.get_size(); ++i) {
    Vertex& cur_vert = gr.get_vert(i);
    if (cur_vert.get_colour() == white) {
      DFS_visit(gr, cur_vert, sorted_list);

    }
  }
}

int main() {
  int M;
  int N;
  cin >> M >> N;
  vector<vector<int>> comps;
  vector<int> sorted_list;
  Graph graph(M);
  Graph graph1(M);
  int p1, p2;
  for (int i = 0; i < N; ++i) {
    cin >> p1 >> p2;
    graph.add_vertex(p1, p2);
  }

  DFS(graph, sorted_list);
  reverse(sorted_list.begin(), sorted_list.end());
  transponation(graph, graph1);
  DFS(graph1, comps, sorted_list);

  cout << comps.size() << endl;
  for (int i = 1; i <= M; ++i) {
    for (int j = 0; j < comps.size(); ++j) {
      if (find(comps[j].begin(), comps[j].end(), i) != comps[j].end()) {
        cout << j + 1 << ' ';
      }
    }
  }

  return 0;
}