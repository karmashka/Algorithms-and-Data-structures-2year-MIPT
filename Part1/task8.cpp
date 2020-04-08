//Дан ориентированный граф, в котором могут быть кратные ребра и петли. Каждое ребро имеет вес, выражающийся целым числом (возможно, отрицательным). Гарантируется, что циклы отрицательного веса отсутствуют.
//
//Требуется посчитать длины кратчайших путей от вершины номер 1 до всех остальных вершин.
//
//Input format
//Программа получает сначала число N (1 ≤ N ≤ 100) – количество вершин графа и число M (0 ≤ M ≤ 10000) – количество ребер. В следующих строках идет M троек чисел, описывающих ребра: начало ребра, конец ребра и вес (вес – целое число от -100 до 100).
//
//Output format
//Программа должна вывести N чисел – расстояния от вершины номер 1 до всех вершин графа. Если пути до соответствующей вершины не существует, вместо длины пути выведите число 30000.
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
    int from, to, weight;
    for (int i = 1; i <= size; ++i) {
      cin >> from >> to >> weight;
      add_vertex(from, to);
      edges.emplace_back(from, to, weight);
    }
  }

  friend void FordBellman(Graph& graph);
};

void FordBellman(Graph& graph) {
  int infinity = 30000;
  int size = graph.get_size();
  int matrix[size + 1][size + 1];
  for (int i = 0; i <= size; ++i) {
    for (int j = 0; j <= size; ++j) {
      matrix[i][j] = infinity;
    }
  }
  matrix[1][0] = 0;
  for (int i = 1; i <= size; ++i) {
    for (Edge elem: graph.edges) {
      if (matrix[elem.get_from()][i - 1] != infinity && matrix[elem.get_to()][i] > matrix[elem.get_from()][i - 1] + elem.get_weight()) {
        matrix[elem.get_to()][i] = matrix[elem.get_from()][i - 1] + elem.get_weight();
      }
    }
  }

  for (int i = 1; i <= size; ++i) {
    int min = matrix[i][0];
    for (int j = 1; j <= size; ++j) {
      if (min > matrix[i][j]) {
        min = matrix[i][j];
      }
    }
    cout << min << ' ';
  }
  cout << '\n';
}

int main() {
  int M, N;
  cin >> M >> N;
  Graph g(M);
  g.read(N);
  FordBellman(g);

  return 0;
}