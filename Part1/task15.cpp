//Дан ориентированный граф. Определить, есть ли в нем цикл отрицательного веса, и если да, то вывести его.
//
//Input format
//В первой строке содержится число N (1 ≤ N ≤ 100) – количество вершин графа. В следующих N строках находится по N чисел – матрица смежности графа. Веса ребер по модулю меньше 100000. Если ребра нет, соответствующее значение равно 100000.
//
//Output format
//В первой строке выведите "YES", если цикл существует, или "NO", в противном случае. При наличии цикла выведите во второй строке количество вершин в нем (считая одинаковые – первую и последнюю), а в третьей строке – вершины, входящие в этот цикл, в порядке обхода. Если циклов несколько, то выведите любой из них.
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
  int distance;
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

  int get_distance() const {
    return distance;
  }

  void set_distance(int dist) {
    distance = dist;
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
    distance = v.distance;
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
    return graph.size();
  }

  void add_edge(int from, int to, int weight) {
    graph[from].add_related(to);
    edges.emplace_back(Edge(from, to, weight));
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

  friend int FordBellman(Graph& graph);
};

int FordBellman(Graph& graph) {
  int infinity = 100000;
  int is_dist_change = 0;
  int size = graph.get_size();
  for (auto vert: graph.get_graph()) {
    vert.set_distance(infinity);
  }
  graph.get_graph()[0].set_distance(0);
  for (int i = 1; i < graph.get_size(); ++i) {
    for (auto edge: graph.edges) {
      int from = edge.get_from();
      int to = edge.get_to();
      if (graph.graph[to].get_distance() > graph.graph[from].get_distance() + edge.get_weight()) {
        graph.graph[to].set_distance(graph.graph[from].get_distance() + edge.get_weight());
        graph.get_vert(to).add_parent(from);
      }
    }
  }

  for (auto edge: graph.edges) {
    int from = edge.get_from();
    int to = edge.get_to();
    if (graph.graph[to].get_distance() > graph.graph[from].get_distance() + edge.get_weight()) {
      graph.graph[to].set_distance(graph.graph[from].get_distance() + edge.get_weight());
      graph.get_vert(to).add_parent(from);
      is_dist_change = to;
    }
  }

  return is_dist_change;
}

void find_negative_cycle(Graph& graph) {
  int cycle_begin = FordBellman(graph);
  if (!cycle_begin) {
    cout << "NO";
  } else {
    cout << "YES" << '\n';
    vector<int> parents;
    vector<int> cycle;
    int previous =  graph.get_vert(cycle_begin).get_parent();
    bool get_cycle = false;
    while(!get_cycle) {
      if (find(parents.begin(), parents.end(), previous) != parents.end()) {
        get_cycle = true;
        cycle_begin = previous;
        break;
      }
      parents.push_back(previous);
      previous = graph.get_vert(previous).get_parent();
    }
    cycle_begin = graph.get_vert(cycle_begin).get_parent();
    cycle.emplace_back(cycle_begin);
    int parent = graph.get_vert(cycle_begin).get_parent();
    while(parent != cycle_begin) {
      cycle.push_back(parent);
      int next_vert = parent;
      parent = graph.get_vert(next_vert).get_parent();
    }
    cycle.emplace_back(cycle_begin);
    cout << cycle.size() << '\n';
    for (auto it = cycle.rbegin(); it != cycle.rend(); ++it) {
      cout << *it << ' ';
    }
  }
}

int main() {
  int M;
  cin >> M;
  Graph g(M);
  for (int i = 1; i <= M; ++i) {
    for (int j = 1; j <= M; ++j) {
      int elem;
      cin >> elem;
      if (elem == 100000 || (i == j && elem >= 0)){
        continue;
      } else {
        g.add_edge(i, j, elem);
      }
    }
  }

  for (int i = 1; i <= M; ++i) {
    g.add_edge(0, i, 0);
  }

  find_negative_cycle(g);
  return 0;
}
