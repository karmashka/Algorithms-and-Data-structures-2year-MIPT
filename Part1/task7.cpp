//Вам дан неориентированный граф. Найдите кратчайший путь от вершины a до вершины b.
//
//Input format
//В первой строке входного файла идут целые числа n и m (1 ≤ n ≤ 50000, 1 ≤ m ≤ 100000) количества вершин и рёбер соответственно. Во второй строке идут целые числа a и b - стартовая и конечная вершины соответственно. Далее идут m строк, описывающих рёбра.
//
//Output format
//Если пути между a и b нет, выведите единственное число -1. Иначе выведите в первой строке число l - длину кратчайшего пути между этими двумя вершинами в рёбрах, а во второй строке выведите l + 1 число - вершины этого пути.
#include <iostream>
#include <vector>
#include <queue>
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
  int m_depth;
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

  void set_depth(int depth) {
    m_depth = depth;
  }

  int get_depth() const {
    return m_depth;
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

void BFS(Graph& graph, int start) {
  queue<int> q;
  for (Vertex& cur_vert : graph.get_graph()) {
    cur_vert.set_colour(white);
    cur_vert.add_parent(-1);
    cur_vert.set_depth(-1);
  }
  graph.get_vert(start).set_depth(0);
  graph.get_vert(start).add_parent(-1);
  graph.get_vert(start).set_colour(gray);
  q.push(start);

  while(!q.empty()) {
    int v = q.front();
    q.pop();
    for (int neighbor:graph.get_vert(v).get_related()) {
      Vertex& u = graph.get_vert(neighbor);
      if (u.get_colour() == white) {
        u.set_colour(gray);
        u.set_depth(graph.get_vert(v).get_depth() + 1);
        u.add_parent(v);
        q.push(neighbor);
      }
    }
    graph.get_vert(v).set_colour(black);
  }
}

void get_path(Graph& graph, int finish) {
  vector<int> path;
  if (graph.get_vert(finish).get_parent() == -1) {
    cout << -1;
    return;
  }

  for (int v = finish; v != -1; v = graph.get_vert(v).get_parent()) {
    path.push_back(v);
  }
  reverse(path.begin(), path.end());

  cout << graph.get_vert(finish).get_depth() << '\n';

  for (auto it = path.begin(); it != path.end(); ++it) {
    cout << *it << ' ';
  }
}

int main() {
  int M, N;
  cin >> M >> N;

  int from, to;
  cin >> from >> to;

  Graph graph(M);
  graph.read(N);

  if (from == to) {
    cout << 0 << '\n';
    cout << from;
    return 0;
  }

  BFS(graph, from);

  get_path(graph, to);

  return 0;
}